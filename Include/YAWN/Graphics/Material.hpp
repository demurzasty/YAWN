#pragma once 

#include "../Runtime/Resource.hpp"
#include "Texture.hpp"
#include "Color.hpp"

namespace YAWN {
    class Material : public Resource {
        YAWN_OBJECT(Material, Resource);

    public:
        static void Register(Meta<Material>& meta);

        Material();

        virtual ~Material();

        void SetBaseColor(const Color4& baseColor);

        const Color4& GetBaseColor() const;

        void SetRoughness(float roughness);

        float GetRoughness() const;

        void SetMetallic(float metallic);

        float GetMetallic() const;

        void SetOcclusionStrength(float strength);

        float GetOcclusionStrength() const;

        void SetAlbedoTexture(Ref<Texture> texture);

        const Ref<Texture>& GetAlbedoTexture() const;

        void SetNormalTexture(Ref<Texture> texture);

        const Ref<Texture>& GetNormalTexture() const;

        void SetMetallicRoughnessTexture(Ref<Texture> texture);

        const Ref<Texture>& GetMetallicRoughnessTexture() const;

        void SetEmissiveTexture(Ref<Texture> texture);

        const Ref<Texture>& GetEmissiveTexture() const;

        void SetOcclusionTexture(Ref<Texture> texture);

        const Ref<Texture>& GetOcclusionTexture() const;

        OID GetId() const;

    private:
        const OID mId;
        Color4 mBaseColor = Color::White;
        float mRoughness = 0.8f;
        float mMetallic = 0.0f;
        float mOcclusionStrength = 1.0f;
        Ref<Texture> mAlbedoTexture;
        Ref<Texture> mNormalTexture;
        Ref<Texture> mMetallicRoughnessTexture;
        Ref<Texture> mEmissiveTexture;
        Ref<Texture> mOcclusionTexture;
    };
}