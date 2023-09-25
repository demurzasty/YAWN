#pragma once 

#include "../Runtime/Reference.hpp"
#include "../Math/Matrix4.hpp"
#include "../Math/Rectangle.hpp"
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

        virtual void SetFramebufferSize(const Vector2& size) = 0;

        virtual void SetClearColor(const Color& color);

        virtual void SetCameraProjection(const Matrix4& projection) = 0;

        virtual void SetCameraTransform(const Matrix4& transform) = 0;

        virtual int CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount);

        virtual void DestroyTexture(int id);

        virtual bool IsTextureValid(int id);

        virtual void SetTextureData(int id, int mipmap, const void* data) = 0;

        virtual Vector2 GetTextureSize(int id) const = 0;

        virtual int GetWhiteTexture() = 0;

        virtual int CreateMesh(int vertexCount, int indexCount);

        virtual void DestroyMesh(int id);

        virtual bool IsMeshValid(int id);

        virtual void SetMeshData(int id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices);

        virtual int CreateInstance();

        virtual void DestroyInstance(int id);

        virtual bool IsInstanceValid(int id);

        virtual void SetInstanceTransform(int id, const Matrix4& transform) = 0;

        virtual int CreateCanvasItem();

        virtual void DestroyCanvasItem(int id);

        virtual bool IsCanvasItemValid(int id);

        virtual void SetCanvasItemData(int id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices) = 0;

        virtual void SetCanvasItemTexture(int id, int textureId) = 0;

        virtual void DrawCanvasItem(int id, int vertexOffset, int indexOffset, int indexCount) = 0;

        virtual void Render() = 0;

    public:
        virtual void LLSetVertexBufferData2D(const ArrayView<const Vertex2D>& vertices) = 0;

        virtual void LLSetIndexBufferData2D(const ArrayView<const unsigned short>& indices) = 0;

        virtual void LLSetTexture2D(int textureId) = 0;

        virtual void LLSetClipRect(const Rectangle& clipRect) = 0;

        virtual void LLDraw2D(int vertexOffset, int indexOffset, int indexCount) = 0;

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
            Vector2 FramebufferSize = Vector2::Zero;
            int CameraEnvironmentId = Pool::None;
            int InstanceCount = 0;
            int LightCount = 0;
            int TextureId = 0;
            float Time = 0.0f;
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

        struct GPUCanvasItemData {
            int VertexOffset = 0;
            int VertexCount = 0;
            int VertexCapacity = 0;
            int IndexOffset = 0;
            int IndexCount = 0;
            int IndexCapacity = 0;
        };

    protected:
        Color mClearColor = Color::CornflowerBlue;

        Pool mInstancePool;
        Pool mMeshPool;
        Pool mTexturePool;
        Pool mMaterialPool;
        Pool mCanvasItemPool;
    };
}
