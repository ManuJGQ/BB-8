#version 400

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;

uniform mat4 mvpMatrix;
uniform float pointSize;

out vec4 destinationColor;

void main() {
    gl_PointSize = pointSize;
    destinationColor = vec4(vColor, 1.0);
    gl_Position = mvpMatrix * vec4(vPosition, 1.0);
}

