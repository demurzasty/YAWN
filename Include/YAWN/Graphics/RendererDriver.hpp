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

        static constexpr int MaxMaterialCount = 0x400;

        static constexpr int MaxMeshCount = 0x1000;

        static constexpr int MaxVertexCount = 0x1000000;

        static constexpr int MaxIndexCount = 0x1000000;

        static constexpr int MaxCanvasVertexCount = 0x100000;

        static constexpr int MaxCanvasIndexCount = 0x100000;

    public:
        virtual ~RendererDriver() = default;

        virtual void SetFramebufferSize(const Vector2& size) = 0;

        virtual void SetClearColor(const Color& color);

        ///////////////////////////
        ////////// Camera /////////
        ///////////////////////////

        virtual void SetCameraProjection(const Matrix4& projection) = 0;

        virtual void SetCameraTransform(const Matrix4& transform) = 0;

        ///////////////////////////
        ///////// Viewport ////////
        ///////////////////////////

        virtual OID CreateViewport(int width, int height, bool directToScreen);

        virtual void DestroyViewport(OID id);

        virtual bool IsViewportValid(OID id);

        virtual void SetViewportSize(OID id, int width, int height) = 0;

        virtual OID GetViewportColorTexture(OID id) const = 0;

        ///////////////////////////
        ///////// Texture /////////
        ///////////////////////////

        virtual OID CreateTexture(int width, int height, TextureFormat format, TextureFilter filter, TextureWrapping wrapping, int mipmapCount);

        virtual void DestroyTexture(OID id);

        virtual bool IsTextureValid(OID id);

        virtual void SetTextureData(OID id, int mipmap, const void* data) = 0;

        virtual Vector2 GetTextureSize(OID id) const = 0;

        virtual OID GetWhiteTexture() = 0;

        ///////////////////////////
        ///////// Material ////////
        ///////////////////////////

        virtual OID CreateMaterial();

        virtual void DestroyMaterial(OID id);

        virtual bool IsMaterialValid(OID id);

        virtual void SetMaterialBaseColor(OID id, const Color4& color) = 0;

        virtual void SetMaterialRoughness(OID id, float roughness) = 0;

        virtual void SetMaterialMetallic(OID id, float metallic) = 0;

        virtual void SetMaterialOcclusionStrength(OID id, float strength) = 0;

        virtual void SetMaterialAlbedoTexture(OID id, OID textureId) = 0;

        virtual void SetMaterialNormalTexture(OID id, OID textureId) = 0;

        virtual void SetMaterialMetallicRoughnessTexture(OID id, OID textureId) = 0;

        virtual void SetMaterialEmissiveTexture(OID id, OID textureId) = 0;

        virtual void SetMaterialOcclusionTexture(OID id, OID textureId) = 0;

        ///////////////////////////
        ////////// Mesh ///////////
        ///////////////////////////

        virtual OID CreateMesh(int vertexCount, int indexCount);

        virtual void DestroyMesh(OID id);

        virtual bool IsMeshValid(OID id);

        virtual void SetMeshData(OID id, const ArrayView<const Vertex3D>& vertices, const ArrayView<const int>& indices) = 0;

        ///////////////////////////
        ///////// Instance ////////
        ///////////////////////////

        virtual OID CreateInstance();

        virtual void DestroyInstance(OID id);

        virtual bool IsInstanceValid(OID id);

        virtual void SetInstanceTransform(OID id, const Matrix4& transform) = 0;

        virtual void SetInstanceMaterial(OID id, OID materialId) = 0;

        virtual void SetInstanceMesh(OID id, OID meshId) = 0;

        virtual void SetInstanceViewport(OID id, OID viewportId) = 0;

        ///////////////////////////
        /// Canvas (deprecated) ///
        ///////////////////////////

        virtual OID CreateCanvasItem();

        virtual void DestroyCanvasItem(OID id);

        virtual bool IsCanvasItemValid(OID id);

        virtual void SetCanvasItemData(OID id, const ArrayView<const Vertex2D>& vertices, const ArrayView<const int>& indices) = 0;

        virtual void SetCanvasItemTexture(OID id, OID textureId) = 0;

        virtual void DrawCanvasItem(OID id, int vertexOffset, int indexOffset, int indexCount) = 0;

        virtual void Render() = 0;

    public:
        virtual void LLSetVertexBufferData2D(const ArrayView<const Vertex2D>& vertices) = 0;

        virtual void LLSetIndexBufferData2D(const ArrayView<const unsigned short>& indices) = 0;

        virtual void LLSetTexture2D(OID textureId) = 0;

        virtual void LLSetClipRect(const Rectangle& clipRect) = 0;

        virtual void LLPushClipRect(const Rectangle& clipRect);

        virtual void LLPopClipRect();

        virtual void LLDraw2D(Topology topology, int vertexOffset, int indexOffset, int indexCount) = 0;

    protected:
        struct GPUTextureData {
            OID SamplerId = Pool::None;
        };

        struct GPUEnvironmentData {
            OID RadianceSamplerId = Pool::None;
            OID IrradianceSamplerId = Pool::None;
            OID PrefilterSamplerId = Pool::None;
        };

        struct GPUGlobalData {
            Matrix4 Projection = Matrix4::Identity;
            Matrix4 View = Matrix4::Identity;
            Matrix4 ProjectionView = Matrix4::Identity;
            Matrix4 InvertedProjectionView = Matrix4::Identity;
            Vector4 CameraPosition = Vector4::Zero;
            Vector4 CameraFrustum = Vector4::Zero;
            Vector2 FramebufferSize = Vector2::Zero;
            OID CameraEnvironmentId = Pool::None;
            int InstanceCount = 0;
            int LightCount = 0;
            OID TextureId = Pool::None;
            OID CurrentViewportId = Pool::None;
            float Time = 0.0f;
        };

        struct GPUMeshData {
            // Vector4 BoundingSphere = Vector4::Zero;
            int VertexOffset = 0;
            int VertexCount = 0;
            int IndexOffset = 0;
            int IndexCount = 0;
        };

        struct GPUMaterialData {
            Color BaseColor = Color::White;

            float Roughness = 0.8f;
            float Metallic = 0.0f;
            float OcclusionStrength = 1.0f;
            OID AlbedoTextureId = Pool::None;

            OID NormalTextureId = Pool::None;
            OID MetallicRoughnessTextureId = Pool::None;
            OID EmissiveTextureId = Pool::None;
            OID OcclusionTextureId = Pool::None;
        };

        struct GPULightData {
            Vector4 PositionOrDirectionAndType; // .W < 0.5 ? PointLight : DirectionalLight
            Vector4 ColorAndRadius; // .W = Radius
        };

        struct GPUInstanceData {
            Matrix4 Transform = Matrix4::Identity;
            int Visible = 1;
            OID MeshId = Pool::None;
            OID MaterialId = Pool::None;
            OID ViewportId = Pool::None;
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

        Pool mViewportPool;
        Pool mInstancePool;
        Pool mMeshPool;
        Pool mTexturePool;
        Pool mMaterialPool;
        Pool mCanvasItemPool;

        Array<Rectangle> mClipRects;
    };
}
