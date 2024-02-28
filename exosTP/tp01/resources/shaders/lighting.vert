#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vColor;
out vec2 TexCoord;
out vec3 Normal;


 
void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vColor = vec4(clamp(aPos, 0.0, 1.0), 1.0);

    TexCoord = tex;
    Normal = mat3(transpose(inverse(model))) * norm;
}
