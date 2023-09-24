#version 460 core

layout (location = 0) in vec2 iPosition;
layout (location = 1) in vec2 iUV;
layout (location = 2) in vec4 iColor;

layout (location = 0) out vec2 vUV;
layout (location = 1) out vec4 vColor;

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
    float Time;
};

layout (std140, binding = 0) uniform GlobalUniform {
    GlobalData Data;
} uGlobal;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    vUV = iUV;
    vColor = iColor;
    gl_Position = vec4(((iPosition / uGlobal.Data.FramebufferSize) * 2.0 - 1.0) * vec2(1.0, -1.0), 0.0, 1.0);
}
