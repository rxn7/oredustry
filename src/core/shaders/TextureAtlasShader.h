#pragma once

#include <string>

namespace od::Shaders::TextureAtlasShader {
	const std::string VertexSrc = R"(
	#version 330 core
	layout(location = 0) in vec2 a_Position;
	layout(location = 1) in vec2 a_TexCoord;
	layout(location = 2) in vec4 a_Color;

	uniform mat4 u_Projection;
	uniform mat4 u_Model;
	uniform int u_Frame;
	uniform float u_FrameSize;

	out vec2 v_TexCoord;
	out vec4 v_Color;

	void main() {
		gl_Position = u_Projection * u_Model * vec4(a_Position, 0.0, 1.0);
		v_TexCoord.x = u_Frame * u_FrameSize - a_TexCoord.x * u_FrameSize;
		v_TexCoord.y = a_TexCoord.y;
		v_Color = a_Color;
	}
	)";

	const std::string FragmentSrc = R"(
	#version 330 core

	in vec2 v_TexCoord;
	in vec4 v_Color;

	out vec4 f_Color;

	uniform sampler2D u_Texture;
	uniform vec4 u_Color;

	void main() {
		f_Color = texture(u_Texture, v_TexCoord) * v_Color * u_Color;
	}
	)";
}
