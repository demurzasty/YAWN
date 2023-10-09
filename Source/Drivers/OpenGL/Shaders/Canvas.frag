#version 460 core
#extension GL_ARB_bindless_texture : enable

layout (location = 0) in vec2 vUV;
layout (location = 1) in vec4 vColor;

layout (location = 0) out vec4 oColor;

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

layout (std140, binding = 0) uniform GlobalUniform {
    GlobalData Data;
} uGlobal;

layout (std430, binding = 3) buffer uSampler {
    sampler2D uSamplers[];
};

uniform int uSamplerId;

void main() {
    oColor = vColor * texture(uSamplers[uGlobal.Data.TextureId & 0xFFFFF], vUV);
}
