#include "TextShader.h"

const std::string od::Shaders::TextShader::VertexSrc = R"(
#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_Projection;

out vec2 v_TexCoord;

void main() {
	gl_Position = u_Projection * vec4(a_Position, 0.0, 1.0);
	v_TexCoord = a_TexCoord;
}
)";

const std::string od::Shaders::TextShader::FragmentSrc = R"(
#version 330 core

in vec2 v_TexCoord;

out vec4 f_Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() {
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_Texture, v_TexCoord).r);
	f_Color = vec4(u_Color) * sampled;
}
)";
