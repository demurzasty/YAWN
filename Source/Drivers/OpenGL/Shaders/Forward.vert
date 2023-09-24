#version 460 core

layout (location = 0) in vec3 iPosition;
layout (location = 1) in vec2 iUV;
layout (location = 2) in vec3 iNormal;

struct GlobalData {
    mat4 Projection;
    mat4 View;
    mat4 ProjectionView;
    mat4 LastProjectionView;
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

struct InstanceData {
    mat4 Transform;
    int MeshId;
    int MaterialId;
    int Visible;
};

layout (std140, binding = 0) uniform GlobalUniform {
    GlobalData Data;
} uGlobal;

layout (std430, binding = 1) readonly buffer InstanceBuffer {
    InstanceData Data[];
} uInstances;

layout (location = 0) out vec3 vPosition;
layout (location = 1) out vec2 vUV;
layout (location = 2) out vec3 vNormal;
layout (location = 3) flat out int vInstanceId;


out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    vInstanceId = gl_DrawID;
    vPosition = (uInstances.Data[vInstanceId].Transform * vec4(iPosition, 1.0)).xyz;
    vUV = iUV;
    vNormal = (uInstances.Data[vInstanceId].Transform * vec4(iNormal, 0.0)).xyz;
    gl_Position = uGlobal.Data.ProjectionView * uInstances.Data[vInstanceId].Transform * vec4(iPosition, 1.0);
}
