#include <YAWN/Runtime/Loaders/MaterialLoader.hpp>
#include <YAWN/Graphics/Material.hpp>
#include <YAWN/Graphics/Texture.hpp>
#include <YAWN/Runtime/ResourceManager.hpp>
#include <YAWN/IO/File.hpp>

using namespace YAWN;

void MaterialLoader::Register(Meta<MaterialLoader>& meta) {
    meta.SetBase<Loader>();
    meta.SetName(L"MaterialLoader");
    meta.SetConstructable();
}

Ref<Resource> MaterialLoader::Load(const Path& path) {
    File file;
    file.Open(path, FileModeFlags::Read);

    YAWN_ASSERT(file.IsOpen());

    Color4 baseColor;
    file.Read(&baseColor, sizeof(Color4));
    float roughness = file.ReadFloat();
    float metallic = file.ReadFloat();
    float occlusionStrength = file.ReadFloat();

    Guid albedoTexture, metallicRoughnessTexture, normalTexture, emissiveTexture, occlusionTexture;
    file.Read(&albedoTexture, sizeof(Guid));
    file.Read(&metallicRoughnessTexture, sizeof(Guid));
    file.Read(&normalTexture, sizeof(Guid));
    file.Read(&emissiveTexture, sizeof(Guid));
    file.Read(&occlusionTexture, sizeof(Guid));

    file.Close();

    Ref<Material> material = new Material();

    material->SetBaseColor(baseColor);
    material->SetRoughness(roughness);
    material->SetMetallic(metallic);
    material->SetOcclusionStrength(occlusionStrength);

    if (!albedoTexture.IsEmpty()) {
        material->SetAlbedoTexture(ResourceManager::Load<Texture>(albedoTexture));
    }

    if (!normalTexture.IsEmpty()) {
        material->SetNormalTexture(ResourceManager::Load<Texture>(normalTexture));
    }

    if (!metallicRoughnessTexture.IsEmpty()) {
        material->SetMetallicRoughnessTexture(ResourceManager::Load<Texture>(metallicRoughnessTexture));
    }

    if (!emissiveTexture.IsEmpty()) {
        material->SetEmissiveTexture(ResourceManager::Load<Texture>(emissiveTexture));
    }

    if (!occlusionTexture.IsEmpty()) {
        material->SetOcclusionTexture(ResourceManager::Load<Texture>(occlusionTexture));
    }

    return material;
}

TypeId MaterialLoader::GetSupportedResourceTypeId() const {
    return TypeId::From<Material>();
}
