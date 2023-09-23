#version 460 core

layout (location = 0) in vec2 iPosition;
layout (location = 1) in vec2 iUV;
layout (location = 2) in vec4 iColor;

layout (location = 0) out vec2 vUV;
layout (location = 1) out vec4 vColor;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    vUV = iUV;
    vColor = iColor;
    gl_Position = vec4(((iPosition / vec2(1280.0, 720.0)) * 2.0 - 1.0) * vec2(1.0, -1.0), 0.0, 1.0);
}
