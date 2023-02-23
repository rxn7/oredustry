#pragma once

#include "core/Libs.h"
#include "core/Color.h"
#include <unordered_map>

namespace od {
	class Shader {
	public:
		Shader(const std::string_view &vertexSrc, const std::string_view &fragmentSrc);
		~Shader();

		void SetUniformMat4(const std::string &name, const glm::f32mat4 &value);
		void SetUniformVec2(const std::string &name, const glm::f32vec2 &value);
		void SetUniformColor(const std::string &name, const od::Color &color);
		void SetUniformFloat(const std::string &name, float value);
		void SetUniformInt(const std::string &name, int value);
		void Bind() const;
		void Unbind() const;
		inline uint32_t GetID() const { return m_ID; }

	private:
		uint32_t GetLocation(const std::string &name);
		void CheckProgramError(GLenum type) const;
	
	private:
		std::unordered_map<std::string, uint32_t> m_Locations;
		uint32_t m_ID;
	};
}
