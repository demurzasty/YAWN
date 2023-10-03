#version 460 core
#extension GL_ARB_bindless_texture : enable

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vUV;
layout (location = 2) in vec3 vNormal;
layout (location = 3) flat in int vInstanceId;

struct GlobalData {
    mat4 Projection;
    mat4 View;
    mat4 ProjectionView;
    mat4 InvertedProjectionView;
    vec4 CameraPosition;
    vec4 CameraFrustum;
    vec2 FramebufferSize;
    int CameraEnvironmentId;
    int InstanceCount;
    int LightCount;
    int TextureId;
    int CurrentViewportId;
    float Time;
};

struct InstanceData {
    mat4 Transform;
    int Visible;
    int MeshId;
    int MaterialId;
    int ViewportId;
};

struct MaterialData {
    vec4 BaseColor;

    float Roughness;
    float Metallic;
    float OcclusionStrength;
    int AlbedoTextureId;

    int NormalTextureId;
    int MetallicRoughnessTextureId;
    int EmissiveTextureId;
    int OcclusionTextureId;
};

layout (std140, binding = 0) uniform GlobalUniform {
    GlobalData Data;
} uGlobal;

layout (std430, binding = 1) readonly buffer InstanceBuffer {
    InstanceData Data[];
} uInstances;

layout (std430, binding = 3) buffer uSampler {
    sampler2D uSamplers[];
};

layout (std430, binding = 5) readonly buffer MaterialBuffer {
    MaterialData Data[];
} uMaterials;

layout (location = 0) out vec4 oColor;

void main() {
    oColor = vec4(1.0, 1.0, 1.0, 1.0);

    if (uInstances.Data[vInstanceId].MaterialId > -1) {
        int textureId = uMaterials.Data[uInstances.Data[vInstanceId].MaterialId].AlbedoTextureId;

        if (textureId > -1) {
            oColor.rgb = texture(uSamplers[textureId], vUV).rgb;
        }
    }
}
