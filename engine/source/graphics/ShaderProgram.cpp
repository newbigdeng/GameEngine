#include "ShaderProgram.h"
#include "Texture.h"
#include <glm\gtc\type_ptr.hpp>

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
		m_currentTextureUnit = 0;
	}

	GLint eng::ShaderProgram::GetUniformLocation(const std::string& name)
	{
		auto it = m_uniformLocationCache.find(name);
		if (it != m_uniformLocationCache.end())return it->second;

		GLint loc = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		m_uniformLocationCache[name] = loc;
		return loc;
	}

	void eng::ShaderProgram::SetUniform(const std::string& name, float value)
	{
		auto loc = GetUniformLocation(name);
		glUniform1f(loc, value);
	}
	void ShaderProgram::SetUniform(const std::string& name, float v0, float v1)
	{
		auto loc = GetUniformLocation(name);
		glUniform2f(loc, v0, v1);
	}
	void ShaderProgram::SetUniform(const std::string& name, const glm::mat4& mat)
	{
		auto loc = GetUniformLocation(name);
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void ShaderProgram::SetTexture(const std::string& name, Texture* texture)
	{
		auto loc = GetUniformLocation(name);
		
		glActiveTexture(GL_TEXTURE0 + m_currentTextureUnit);
		glBindTexture(GL_TEXTURE_2D, texture->GetID());
		glUniform1i(loc, m_currentTextureUnit);
		++m_currentTextureUnit;
	}
}