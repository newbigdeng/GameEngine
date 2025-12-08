#pragma once
#include <memory>
#include <string>
#include <glad\glad.h>
#include <vector>

namespace eng
{
	class ShaderProgram;
	class Material;
	class Mesh;

	class GraphicsAPI
	{
	public:
		bool Init();
		std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string vertexSource, const std::string fragSource);
		GLuint CreateVertexBuffer(const std::vector<float> vertices);
		GLuint CreateIndexBuffer(const std::vector<uint32_t> indices);
		
		void SetClearColor(float r, float g, float b, float a);
		void ClearBuffers();

		void BindShaderProgram(ShaderProgram* shaderProgram);
		void BindMaterial(Material* material);
		void BindMesh(Mesh* mesh);
		void DrawMesh(Mesh* mesh);

	private:

	};
}