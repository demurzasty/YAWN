#include <YAWN/Editor/Importers/ModelImporter.hpp>
#include <YAWN/Runtime/JSON.hpp>
#include <YAWN/Runtime/Console.hpp>
#include <YAWN/IO/File.hpp>
#include <YAWN/Math/Matrix4.hpp>
#include <YAWN/Graphics/Image.hpp>
#include <YAWN/Runtime/YTXT.hpp>

#include <Windows.h>
#include <stdio.h>

#include <cgltf.h>

using namespace YAWN;

static thread_local Map<int, Guid> sMeshes;
static thread_local Map<int, Guid> sTextures;
static thread_local Map<int, Guid> sMaterials;

static void WriteMesh(const Path& outputPath, const Array<Vertex3D>& vertices, const Array<unsigned int>& indices) {
    File file;
    file.Open(outputPath, FileModeFlags::Write);
    YAWN_ASSERT(file.IsOpen());

    file.Write32(vertices.GetSize());
    file.Write32(indices.GetSize());

    file.Write(vertices.GetData(), vertices.GetSizeInBytes());
    file.Write(indices.GetData(), indices.GetSizeInBytes());
}

static void WriteTexture(const Path& outputPath, const Ref<Image>& image) {
    YAWN_ASSERT(image);

    File file;
    file.Open(outputPath, FileModeFlags::Write);
    YAWN_ASSERT(file.IsOpen());

    file.Write32(image->GetInfo().GetWidth());
    file.Write32(image->GetInfo().GetHeight());
    file.Write32(image->GetInfo().GetChannels());
    file.Write(image->GetData().GetData(), image->GetData().GetSizeInBytes());
}

static Guid GetTextureGuid(const Path& texturePath) {
    Path metaPath = texturePath.ToString() + L".meta";

    if (File::Exists(metaPath)) {
        Map<String, Variant> meta = YTXT::Parse(File::ReadAllText(metaPath));

        Variant guid;
        if (meta.TryGet(L"Guid", guid) && guid.GetType() == VariantType::String) {
            return Guid(guid.AsString());
        }
    }

    return Guid();
}

void ModelImporter::Register(Meta<ModelImporter>& meta) {
    meta.SetBase<Importer>();
    meta.SetName(L"ModelImporter");
    meta.SetConstructable();
}

void ModelImporter::Import(const Path& inputPath, const Path& outputPath, const Map<String, Variant>& metadata) {
    cgltf_options options = { cgltf_file_type_invalid };
    cgltf_data* data = nullptr;

    Array<char> filename(inputPath.ToString().ToUTF8());

    if (cgltf_parse_file(&options, filename.GetData(), &data) == cgltf_result_success) {
        cgltf_load_buffers(&options, data, filename.GetData());

        Console::WriteLine(L"Base: %s", (inputPath / L"..").ToString().GetData());

        //
        // 1. Import meshes
        //

        sMeshes.Clear();
        for (int i = 0; i < data->meshes_count; ++i) {
            for (int j = 0; j < data->meshes[i].primitives_count; ++j) {
                cgltf_accessor* indexAccessor = data->meshes[i].primitives[j].indices;

                cgltf_size indexCount = indexAccessor->count;
                cgltf_size byteOffset = indexAccessor->offset;

                cgltf_buffer_view* indexBufferView = indexAccessor->buffer_view;

                cgltf_size indexBufferOffset = indexBufferView->offset;
                cgltf_buffer* indexBuffer = indexBufferView->buffer;

                cgltf_size indexStride = indexAccessor->component_type == cgltf_component_type_r_16u ? 2 : 4;

                Array<unsigned int> indices((int)indexCount);

                const unsigned char* indexData = (const unsigned char*)indexBuffer->data + (indexBufferOffset + byteOffset);
                for (int n = 0; n < indexCount; ++n) {
                    if (indexStride == 2) {
                        indices[n] = *(unsigned short*)(indexData + n * indexStride);
                    } else {
                        indices[n] = *(unsigned int*)(indexData + n * indexStride);
                    }
                }

                cgltf_size vertexCount = 0;
                for (int n = 0; n < data->meshes[i].primitives[j].attributes_count; ++n) {
                    cgltf_attribute* attribute = &data->meshes[i].primitives[j].attributes[n];
                    if (attribute->type != cgltf_attribute_type_position &&
                        attribute->type != cgltf_attribute_type_texcoord &&
                        attribute->type != cgltf_attribute_type_normal) {
                        continue;
                    }

                    cgltf_accessor* accessor = attribute->data;
                    if (accessor->count > vertexCount) {
                        vertexCount = accessor->count;
                    }
                }

                Array<Vertex3D> vertices((int)vertexCount);
                for (int n = 0; n < data->meshes[i].primitives[j].attributes_count; ++n) {
                    cgltf_attribute* attribute = &data->meshes[i].primitives[j].attributes[n];
                    if (attribute->type != cgltf_attribute_type_position &&
                        attribute->type != cgltf_attribute_type_texcoord &&
                        attribute->type != cgltf_attribute_type_normal) {
                        continue;
                    }

                    cgltf_accessor* accessor = attribute->data;
                    cgltf_size byteOffset = accessor->offset;
                    cgltf_buffer_view* bufferView = accessor->buffer_view;
                    cgltf_size bufferOffset = bufferView->offset;
                    cgltf_buffer* buffer = bufferView->buffer;

                    if (attribute->type == cgltf_attribute_type_position) {
                        cgltf_size bufferStride = bufferView->stride ? bufferView->stride : (sizeof(float) * 3);
                        unsigned char* vertexData = (unsigned char*)(buffer->data) + byteOffset + bufferOffset;
                        for (int m = 0; m < vertexCount; ++m) {
                            float* positionData = (float*)(vertexData + m * bufferStride);
                            vertices[m].Position = Vector3(positionData[0], positionData[1], positionData[2]);
                        }
                    } else if (attribute->type == cgltf_attribute_type_texcoord) {
                        cgltf_size bufferStride = bufferView->stride ? bufferView->stride : (sizeof(float) * 2);
                        unsigned char* vertexData = (unsigned char*)(buffer->data) + byteOffset + bufferOffset;
                        for (int m = 0; m < vertexCount; ++m) {
                            float* texcoordData = (float*)(vertexData + m * bufferStride);
                            vertices[m].UV = Vector2(texcoordData[0], texcoordData[1]);
                        }
                    } else if (attribute->type == cgltf_attribute_type_normal) {
                        cgltf_size bufferStride = bufferView->stride ? bufferView->stride : (sizeof(float) * 3);
                        unsigned char* vertexData = (unsigned char*)(buffer->data) + byteOffset + bufferOffset;
                        for (int m = 0; m < vertexCount; ++m) {
                            float* normalData = (float*)(vertexData + m * bufferStride);
                            vertices[m].Normal = Vector3(normalData[0], normalData[1], normalData[2]);
                        }
                    }

                }

                Guid guid = Guid::Generate();
                Path meshPath = outputPath / L".." / guid.ToString();
                WriteMesh(meshPath, vertices, indices);

                int uniqueId = (i & 0xFFFF) | ((j & 0xFFFF) << 16);
                sMeshes.Add(uniqueId, guid);
            }
        }

        ////
        //// 2. Import textures.
        ////
        //sTextures.Clear();
        //for (int i = 0; i < data->textures_count; ++i) {
        //    cgltf_texture* texture = &data->textures[i];

        //    Guid guid = Guid::Generate();
        //    Path materialPath = outputPath / L".." / guid.ToString();

        //    String uri = String::FromUTF8(texture->image->uri);

        //    Path imagePath = inputPath / L".." / uri;

        //    Ref<Image> image = Image::FromFile(imagePath, 4);

        //    WriteTexture(outputPath / L".." / guid.ToString(), image);

        //    sTextures.Add(i, guid);
        //}

        //
        // 3. Import materials.
        //
        sMaterials.Clear();
        for (int i = 0; i < data->materials_count; ++i) {
            cgltf_material* material = &data->materials[i];

            Guid guid = Guid::Generate();
            Path materialPath = outputPath / L".." / guid.ToString();
            
            File file;
            file.Open(materialPath, FileModeFlags::Write);
            YAWN_ASSERT(file.IsOpen());

            if (material->has_pbr_metallic_roughness) {
                Color4 baseColor = Color(material->pbr_metallic_roughness.base_color_factor);
                file.WriteColor4(baseColor);
                file.WriteFloat(material->pbr_metallic_roughness.roughness_factor);
                file.WriteFloat(material->pbr_metallic_roughness.metallic_factor);
                file.WriteFloat(1.0f);

                cgltf_texture* texture = material->pbr_metallic_roughness.base_color_texture.texture;
                if (texture && texture->image) {
                    Path texturePath = inputPath / L".." / String::FromUTF8(texture->image->uri);

                    file.WriteGuid(GetTextureGuid(texturePath));
                } else {
                    file.WriteGuid(Guid());
                }

                texture = material->pbr_metallic_roughness.metallic_roughness_texture.texture;
                if (texture && texture->image) {
                    Path texturePath = inputPath / L".." / String::FromUTF8(texture->image->uri);

                    file.WriteGuid(GetTextureGuid(texturePath));
                } else {
                    file.WriteGuid(Guid());
                }
            } else {
                file.WriteColor4(Color::White);
                file.WriteFloat(0.8f);
                file.WriteFloat(0.0f);
                file.WriteFloat(1.0f);
                file.WriteGuid(Guid());
                file.WriteGuid(Guid());
            }

            cgltf_texture* texture = material->normal_texture.texture;
            if (texture && texture->image) {
                Path texturePath = inputPath / L".." / String::FromUTF8(texture->image->uri);

                file.WriteGuid(GetTextureGuid(texturePath));
            } else {
                file.WriteGuid(Guid());
            }

            texture = material->emissive_texture.texture;
            if (texture && texture->image) {
                Path texturePath = inputPath / L".." / String::FromUTF8(texture->image->uri);

                file.WriteGuid(GetTextureGuid(texturePath));
            } else {
                file.WriteGuid(Guid());
            }

            texture = material->occlusion_texture.texture;
            if (texture && texture->image) {
                Path texturePath = inputPath / L".." / String::FromUTF8(texture->image->uri);

                file.WriteGuid(GetTextureGuid(texturePath));
            } else {
                file.WriteGuid(Guid());
            }

            sMaterials.Add(i, guid);
        }


        //
        // 3. Import nodes.
        //

        Map<String, Variant> prefab;
        prefab.Add(L"$Type", String(L"Node3D"));
        prefab.Add(L"Position", Vector3::Zero);
        prefab.Add(L"Rotation", Vector3::Zero);
        prefab.Add(L"Scale", Vector3::One);

        Array<Map<String, Variant>> children;
        for (int i = 0; i < data->scene->nodes_count; ++i) {
            Map<String, Variant> node;
            node.Add(L"$Type", L"Node3D");

            Import(node, inputPath, outputPath, data, data->scene->nodes[i]);

            children.Add(node);
        }
        prefab.Add(L"Children", children);

        File::WriteAllText(outputPath, JSON::Stringify(prefab));

        cgltf_free(data);
    }

    sMeshes.Clear();
    sTextures.Clear();
    sMaterials.Clear();
}

void ModelImporter::Import(Map<String, Variant>& prefab, const Path& basePath, const Path& outputPath, cgltf_data* data, cgltf_node* node) {
    if (node->has_matrix) {
        Matrix4 matrix;
        memcpy(matrix.Values, node->matrix, sizeof(float) * 16);
        // TODO:
    } else {
        float positionX = 0.0f;
        float positionY = 0.0f;
        float positionZ = 0.0f;

        float rotationX = 0.0f;
        float rotationY = 0.0f;
        float rotationZ = 0.0f;

        float scaleX = 1.0f;
        float scaleY = 1.0f;
        float scaleZ = 1.0f;

        if (node->has_rotation) {
            float* quat = node->rotation;

            float sinr_cosp = 2.0f * (quat[3] * quat[0] + quat[1] * quat[2]);
            float cosr_cosp = 1.0f - 2.0f * (quat[0] * quat[0] + quat[1] * quat[1]);
            rotationX = Math::Atan2(sinr_cosp, cosr_cosp);

            float sinp = 2.0f * (quat[3] * quat[1] - quat[2] * quat[0]);
            if (Math::Abs(sinp) >= 1.0f) {
                rotationY = Math::CopySign(Math::PI, sinp);
            } else {
                rotationY = Math::Asin(sinp);
            }

            float siny_cosp = 2.0f * (quat[3] * quat[2] + quat[0] * quat[1]);
            float cosy_cosp = 1.0f - 2.0f * (quat[1] * quat[1] + quat[2] * quat[2]);
            rotationZ = Math::Atan2(siny_cosp, cosy_cosp);
        }

        if (node->has_translation) {
            positionX = node->translation[0];
            positionY = node->translation[1];
            positionZ = node->translation[2];
        }

        if (node->has_scale) {
            scaleX = node->scale[0];
            scaleY = node->scale[1];
            scaleZ = node->scale[2];
        }

        prefab.Add(L"Position", Vector3(positionX, positionY, positionZ));
        prefab.Add(L"Rotation", Vector3(rotationX, rotationY, rotationZ));
        prefab.Add(L"Scale", Vector3(scaleX, scaleY, scaleZ));
    }

    Array<Map<String, Variant>> children;
    if (node->mesh) {
        for (int i = 0; i < data->meshes_count; ++i) {
            if (node->mesh == (data->meshes + i)) {
                for (int j = 0; j < node->mesh->primitives_count; ++j) {
                    Map<String, Variant> child;
                    child.Add(L"$Type", L"Geometry3D");
                    child.Add(L"Position", Vector3::Zero);
                    child.Add(L"Rotation", Vector3::Zero);
                    child.Add(L"Scale", Vector3::One);

                    int uniqueId = (i & 0xFFFF) | ((j & 0xFFFF) << 16);
                    Guid guid = sMeshes[uniqueId];

                    Map<String, Variant> mesh;
                    mesh.Add(L"$Type", L"ResourceLink");
                    mesh.Add(L"ResourceType", L"Mesh");
                    mesh.Add(L"Guid", guid.ToString());
                    child.Add(L"Mesh", mesh);

                    int materialIndex = (int)(node->mesh->primitives[j].material - data->materials);
                    guid = sMaterials[materialIndex];

                    Map<String, Variant> material;
                    material.Add(L"$Type", L"ResourceLink");
                    material.Add(L"ResourceType", L"Material");
                    material.Add(L"Guid", guid.ToString());
                    child.Add(L"Material", material);

                    children.Add(child);
                }

                break;
            }
        }
    }

    for (int i = 0; i < node->children_count; ++i) {
        Map<String, Variant> child;
        Import(child, basePath, outputPath, data, node->children[i]);
        children.Add(child);
    }

    prefab.Add(L"Children", children);
}

ArrayView<const String> ModelImporter::GetSupportedExtensions() const {
    static String extensions[] = {
        L".gltf",
    };

    return extensions;
}
