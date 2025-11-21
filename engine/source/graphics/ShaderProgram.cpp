#include "ShaderProgram.h"


namespace eng
{
	ShaderProgram::ShaderProgram(GLuint shaderProgram):m_ShaderProgramID(shaderProgram)
	{

	}
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ShaderProgramID);
	}
	void ShaderProgram::Bind()
	{
		glUseProgram(m_ShaderProgramID);
	}

	GLint eng::ShaderProgram::GetUniformLocation(const std::string& name)
	{
		auto it = m_uniformLocationCache.find(name);
		if (it != m_uniformLocationCache.end())return it->second;

		GLint loc = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		m_uniformLocationCache[name] = loc;
		return loc;
	}

	void eng::ShaderProgram::SetUniform(const std::string name, float value)
	{
		auto loc = GetUniformLocation(name);
		glUniform1f(loc, value);
	}
}