#include "GraphicsAPI.h"
#include "GraphicsAPI.h"

#include "GraphicsAPI.h"
#include "ShaderProgram.h"
#include "render\Material.h"
#include <iostream>
#include "render\Mesh.h"

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

	GLuint GraphicsAPI::CreateVertexBuffer(const std::vector<float> vertices)
	{
		GLuint vbo = 0;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return vbo;
	}

	GLuint GraphicsAPI::CreateIndexBuffer(const std::vector<uint32_t> indices)
	{
		GLuint ebo;
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		return ebo;
	}

	void GraphicsAPI::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void GraphicsAPI::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}


	void GraphicsAPI::BindShaderProgram(ShaderProgram* shaderProgram)
	{
		if (shaderProgram)
		{
			shaderProgram->Bind();
		}
	}

	void GraphicsAPI::BindMaterial(Material* material)
	{
		if (material)
		{
			material->Bind();
		}
	}

	void GraphicsAPI::BindMesh(Mesh* mesh)
	{
		if (mesh)
		{
			mesh->Bind();
		}
	}

	void GraphicsAPI::DrawMesh(Mesh* mesh)
	{
		if (mesh)
		{
			mesh->Draw();
		}
	}
}