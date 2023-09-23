#pragma once 

#include "../Runtime/Reference.hpp"
#include "../Math/Matrix4.hpp"
#include "../Runtime/Arena.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"
#include "Color.hpp"
#include "Topology.hpp"

namespace YAWN {
    class RendererDriver : public Reference {
        YAWN_OBJECT(RendererDriver, Reference);

        static constexpr int MaxTextureCount = 0x1000;

        static constexpr int MaxInstanceCount = 0x10000;

        static constexpr int MaxMeshCount = 0x1000;

        static constexpr int MaxVertexCount = 0x1000000;

        static constexpr int MaxIndexCount = 0x1000000;

        static constexpr int MaxCanvasVertexCount = 0x100000;

        static constexpr int MaxCanvasIndexCount = 0x100000;

    public:
        virtual ~RendererDriver() = default;

        virtual void SetClearColor(const Color& color);

        virtual void SetCameraProjection(const Matrix4& projection) = 0;

        virtual void SetCameraTransform(const Matrix4& transform) = 0;

        virtual int CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount);

        virtual void DestroyTexture(int id);

        virtual bool IsTextureValid(int id);

        virtual int CreateMesh(int vertexCount, int indexCount);

        virtual void DestroyMesh(int id);

        virtual bool IsMeshValid(int id);

        virtual void SetMeshData(int id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices);

        virtual int CreateInstance();

        virtual void DestroyInstance(int id);

        virtual bool IsInstanceValid(int id);

        virtual void SetInstanceTransform(int id, const Matrix4& transform) = 0;

        virtual void Draw2D(Topology topology, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices) = 0;

        virtual void Present() = 0;

    protected:
        struct GPUTextureData {
            int SamplerId = Pool::None;
        };

        struct GPUEnvironmentData {
            int RadianceSamplerId = Pool::None;
            int IrradianceSamplerId = Pool::None;
            int PrefilterSamplerId = Pool::None;
        };

        struct GPUGlobalData {
            Matrix4 Projection = Matrix4::Identity;
            Matrix4 View = Matrix4::Identity;
            Matrix4 ProjectionView = Matrix4::Identity;
            Matrix4 InvertedProjectionView = Matrix4::Identity;
            Vector4 CameraPosition = Vector4::Zero;
            Vector4 CameraFrustum = Vector4::Zero;
            int CameraEnvironmentId = Pool::None;
            int InstanceCount = 0;
            int LightCount = 0;
        };

        struct GPUMeshData {
            Vector4 BoundingSphere = Vector4::Zero;
            int VertexOffset = 0;
            int IndexOffset = 0;
            int IndexCount = 0;
        };

        struct GPUMaterialData {
            Vector4 BaseColor = Vector4::One;
            float Roughness = 0.8f;
            float Metallic = 0.0f;
            float OcclusionStrength = 1.0f;
            int AlbedoTextureId = Pool::None;
            int NormalTextureId = Pool::None;
            int RoughnessTextureId = Pool::None;
            int MetallicTextureId = Pool::None;
            int EmissiveTextureId = Pool::None;
            int OcclusionTextureId = Pool::None;
        };

        struct GPULightData {
            Vector4 PositionOrDirectionAndType; // .W < 0.5 ? PointLight : DirectionalLight
            Vector4 ColorAndRadius; // .W = Radius
        };

        struct GPUInstanceData {
            Matrix4 Transform = Matrix4::Identity;
            int Visible = 0;
            int MeshId = Pool::None;
            int MaterialId = Pool::None;
        };

    protected:
        Color mClearColor = Color::CornflowerBlue;

        Pool mInstancePool;
        Pool mMeshPool;
        Pool mTexturePool;
        Pool mMaterialPool;
    };
}
