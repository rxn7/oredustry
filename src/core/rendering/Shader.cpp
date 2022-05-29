#include "Shader.h"
#include "core/Log.h"

static uint32_t s_CreateShader(const std::string_view &src, GLenum type);

od::Shader::Shader(const std::string_view &vertexSrc, const std::string_view &fragmentSrc) {
	m_ID = glCreateProgram();
	uint32_t fragmentShader = s_CreateShader(fragmentSrc, GL_FRAGMENT_SHADER);
	uint32_t vertexShader = s_CreateShader(vertexSrc, GL_VERTEX_SHADER);

	glAttachShader(m_ID, fragmentShader);
	glAttachShader(m_ID, vertexShader);

	glLinkProgram(m_ID);
	CheckProgramError(GL_LINK_STATUS);

	glValidateProgram(m_ID);
	CheckProgramError(GL_VALIDATE_STATUS);

	glDetachShader(m_ID, fragmentShader);
	glDetachShader(m_ID, vertexShader);
}

od::Shader::~Shader() {
	glDeleteProgram(m_ID);
	Unbind();
}

uint32_t od::Shader::GetLocation(const std::string &name) {
	std::unordered_map<std::string, uint32_t>::iterator it = m_Locations.find(name);

	if(it != m_Locations.end())
		return it->second;

	uint32_t location = glGetUniformLocation(m_ID, name.c_str());
	m_Locations.insert({name, location});

	return location;
}

void od::Shader::SetUniformMat4(const std::string &name, const glm::f32mat4 &value) {
	glUniformMatrix4fv(GetLocation(name), 1, false, &value[0][0]);
}

void od::Shader::SetUniformVec2(const std::string &name, const glm::f32vec2 &value) {
	glUniform2f(GetLocation(name), value.x, value.y);
}

void od::Shader::SetUniformColor(const std::string &name, const od::Color &color) {
	uint32_t location = glGetUniformLocation(m_ID, name.data());
	glUniform4f(location, color.x, color.y, color.z, color.w);
}

void od::Shader::Bind() const {
	glUseProgram(m_ID);
}

void od::Shader::Unbind() const {
	glUseProgram(0);
}

static uint32_t s_CreateShader(const std::string_view &src, GLenum type) {
	uint32_t id = glCreateShader(type);

	const char *cSrc = src.data();
	glShaderSource(id, 1, &cSrc, 0);
	glCompileShader(id);

	int32_t status = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if(!status) {
		int32_t logLen = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
		char log[logLen];
		glGetShaderInfoLog(id, logLen, &logLen, log);

		glDeleteShader(id);

		OD_LOG_ERROR("Error compiling " << (type == GL_FRAGMENT_SHADER ? "fragment" : "vertex") << " shader " << log);
	}

	return id;
}

void od::Shader::CheckProgramError(GLenum type) const {
	int32_t status = 0;
	glGetProgramiv(m_ID, type, &status);

	if(status) return;

	int32_t logLen = 0;
	glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &logLen);

	char log[logLen];
	glGetProgramInfoLog(m_ID, logLen, &logLen, log);

	OD_LOG_ERROR("Program error: " << log);
}
