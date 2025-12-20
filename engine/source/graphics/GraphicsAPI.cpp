#include "GraphicsAPI.h"
#include "GraphicsAPI.h"

#include "GraphicsAPI.h"
#include "ShaderProgram.h"
#include "render\Material.h"
#include <iostream>
#include "render\Mesh.h"
//#include "glad\glad.h"

namespace eng
{
	bool GraphicsAPI::Init()
	{
		glEnable(GL_DEPTH_TEST);//深度测试
		return true;
	}

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

	const std::shared_ptr<ShaderProgram>& GraphicsAPI::GetDefaultShaderProgram()
	{
		if (!m_defaultShaderProgram)
		{
			std::string vertexShaderSource = R"(
				#version 330 core
				layout(location = 0)in vec3 position;
				layout(location = 1)in vec3 color;
				layout(location = 2)in vec2 uv;
				layout(location = 3)in vec3 normal;

				uniform mat4 uModel;
				uniform mat4 uView;
				uniform mat4 uProjection;

				//out vec3 vColor;
				out vec2 vUV;
				out vec3 vNormal;
				out vec3 vFragPos;
				void main()
				{
					//vColor = color;
					vUV = uv;

					vFragPos = vec3(uModel * vec4(position, 1.0));
					vNormal = mat3(transpose(inverse(uModel))) * normal;

					gl_Position = uProjection * uView * uModel * vec4(position, 1.0);
				}
			)";
			std::string fragmentShaderSource = R"(
				#version 330 core
				//in vec3 vColor;
				in vec2 vUV;
				in vec3 vNormal;
				in vec3 vFragPos;
				out vec4 FragColor;

				struct Light
				{
					vec3 color;
					vec3 position;
				};
				uniform Light uLight;
				uniform vec3 uCameraPos;

				uniform sampler2D brick;
				uniform sampler2D baseColor;
				uniform vec4 uColor;

				void main()
				{
					vec3 norm = normalize(vNormal);
					vec3 lightDir = normalize(uLight.position - vFragPos);

					//diffuse
					float diff = max(dot(norm, lightDir),0.0f);
					vec3 diffuse = diff * uLight.color;

					//specular
					vec3 viewDir = normalize(uCameraPos - vFragPos);
					vec3 reflectDir = reflect(-lightDir,norm);
					float spec = pow(max(dot(viewDir,reflectDir),0.0),32.0);
					float specularStrength = 0.5;
					vec3 specular = spec * specularStrength * uLight.color;
					
					vec3 result = diffuse + specular;

					vec4 texColor = texture(baseColor, vUV);
					//FragColor = texColor * vec4(vColor, 1.0f);
					FragColor = texColor * vec4(result,1.0f);
				}
			)";
			//默认着色器
			m_defaultShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
		}

		return m_defaultShaderProgram;
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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