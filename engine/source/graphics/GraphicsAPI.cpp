
#include "GraphicsAPI.h"
#include "ShaderProgram.h"
#include <iostream>

namespace eng
{
	std::shared_ptr<ShaderProgram> GraphicsAPI::CreateShaderProgram(const std::string vertexSource, const std::string fragSource)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexShaderCStr = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
		glCompileShader(vertexShader);
		GLint success;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
			std::cerr << "ERROR:VERTEX_SHADER_COMPILE_FALIED: " << infoLog << std::endl;
			return nullptr;
		}

		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentShaderCStr = fragSource.c_str();
		glShaderSource(fragShader, 1, &fragmentShaderCStr, nullptr);
		glCompileShader(fragShader);
		//GLint success;
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
			std::cerr << "ERROR:FRAGMENT_SHADER_COMPILE_FAILED: " << infoLog << std::endl;
			return nullptr;
		}

		GLuint ShaderProgramID = glCreateProgram();
		glAttachShader(ShaderProgramID, vertexShader);
		glAttachShader(ShaderProgramID, fragShader);
		glLinkProgram(ShaderProgramID);

		glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(fragShader, 512, nullptr, infoLog);
			std::cerr << "ERROR:SHADER_PROGRAM_LINKING_FALIED: " << infoLog << std::endl;
			return nullptr;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragShader);

		return std::make_shared<ShaderProgram>(ShaderProgramID);
	}
	void GraphicsAPI::BindShaderProgram(ShaderProgram* shaderProgram)
	{
		shaderProgram->Bind();
	}
}