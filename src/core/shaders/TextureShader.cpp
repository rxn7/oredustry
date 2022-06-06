#include "TextureShader.h"

const std::string od::Shaders::TextureShader::VertexSrc = R"(
#version 330 core
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;
uniform mat4 u_Projection;
uniform mat4 u_Model;
out vec2 v_TexCoord;
void main() {
	gl_Position = u_Projection * u_Model * vec4(a_Position, 0.0, 1.0);
	v_TexCoord = a_TexCoord;
}
)";

const std::string od::Shaders::TextureShader::FragmentSrc = R"(
#version 330 core
in vec2 v_TexCoord;
out vec4 f_Color;
uniform sampler2D u_Texture;
uniform vec4 u_Color;
void main() {
	f_Color = texture(u_Texture, v_TexCoord) * u_Color;
}
)";
