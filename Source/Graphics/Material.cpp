#include <YAWN/Graphics/Material.hpp>
#include <YAWN/Graphics/Renderer.hpp>

using namespace YAWN;

void Material::Register(Meta<Material>& meta) {
    meta.SetConstructable();
    meta.AddField<&Material::SetBaseColor, &Material::GetBaseColor>(L"BaseColor");
    meta.AddField<&Material::SetRoughness, &Material::GetRoughness>(L"Roughness");
    meta.AddField<&Material::SetMetallic, &Material::GetMetallic>(L"Metallic");
    meta.AddField<&Material::SetOcclusionStrength, &Material::GetOcclusionStrength>(L"OcclusionStrength");
    meta.AddField<&Material::SetAlbedoTexture, &Material::GetAlbedoTexture>(L"AlbedoTexture");
    meta.AddField<&Material::SetNormalTexture, &Material::GetNormalTexture>(L"NormalTexture");
    meta.AddField<&Material::SetMetallicRoughnessTexture, &Material::GetMetallicRoughnessTexture>(L"MetallicRoughnessTexture");
    meta.AddField<&Material::SetEmissiveTexture, &Material::GetEmissiveTexture>(L"EmissiveTexture");
    meta.AddField<&Material::SetOcclusionTexture, &Material::GetOcclusionTexture>(L"OcclusionTexture");
}

Material::Material()
    : mId(Renderer::CreateMaterial()) {
}

Material::~Material() {
    Renderer::DestroyMaterial(mId);
}

void Material::SetBaseColor(const Color4& baseColor) {
    mBaseColor = baseColor;

    Renderer::SetMaterialBaseColor(mId, baseColor);
}

const Color4& Material::GetBaseColor() const {
    return mBaseColor;
}

void Material::SetRoughness(float roughness) {
    mRoughness = roughness;

    Renderer::SetMaterialRoughness(mId, roughness);
}

float Material::GetRoughness() const {
    return mRoughness;
}

void Material::SetMetallic(float metallic) {
    mMetallic = metallic;

    Renderer::SetMaterialMetallic(mId, metallic);
}

float Material::GetMetallic() const {
    return mMetallic;
}

void Material::SetOcclusionStrength(float strength) {
    mOcclusionStrength = strength;

    Renderer::SetMaterialOcclusionStrength(mId, strength);
}

float Material::GetOcclusionStrength() const {
    return mOcclusionStrength;
}

void Material::SetAlbedoTexture(Ref<Texture> texture) {
    mAlbedoTexture = texture;

    Renderer::SetMaterialAlbedoTexture(mId, texture ? texture->GetId() : Pool::None);
}

const Ref<Texture>& Material::GetAlbedoTexture() const {
    return mAlbedoTexture;
}

void Material::SetNormalTexture(Ref<Texture> texture) {
    mNormalTexture = texture;

    Renderer::SetMaterialNormalTexture(mId, texture ? texture->GetId() : Pool::None);
}

const Ref<Texture>& Material::GetNormalTexture() const {
    return mNormalTexture;
}

void Material::SetMetallicRoughnessTexture(Ref<Texture> texture) {
    mMetallicRoughnessTexture = texture;

    Renderer::SetMaterialMetallicRoughnessTexture(mId, texture ? texture->GetId() : Pool::None);
}

const Ref<Texture>& Material::GetMetallicRoughnessTexture() const {
    return mMetallicRoughnessTexture;
}

void Material::SetEmissiveTexture(Ref<Texture> texture) {
    mEmissiveTexture = texture;

    Renderer::SetMaterialEmissiveTexture(mId, texture ? texture->GetId() : Pool::None);
}

const Ref<Texture>& Material::GetEmissiveTexture() const {
    return mEmissiveTexture;
}

void Material::SetOcclusionTexture(Ref<Texture> texture) {
    mOcclusionTexture = texture;

    Renderer::SetMaterialOcclusionTexture(mId, texture ? texture->GetId() : Pool::None);
}

const Ref<Texture>& Material::GetOcclusionTexture() const {
    return mOcclusionTexture;
}

int Material::GetId() const {
    return mId;
}
