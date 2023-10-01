#version 460 core

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

layout (std140, binding = 0) uniform GlobalUniform {
    GlobalData Data;
} uGlobal;

layout (std430, binding = 1) readonly buffer InstanceBuffer {
    InstanceData Data[];
} uInstances;

layout (location = 0) out vec4 oColor;

void main() {
    oColor = vec4(1.0, 1.0, 1.0, 1.0);
}
