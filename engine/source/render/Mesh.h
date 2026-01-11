#pragma once
#include <glad/glad.h>
#include <glm\vec3.hpp>
#include "graphics\VertexLayout.h"
#include <memory>
#include <string>

namespace eng
{
	class Mesh
	{
	public:
		Mesh(const VertexLayout& layout, const std::vector<float>& vertics, const std::vector<uint32_t> indices);
		Mesh(const VertexLayout& layout, const std::vector<float>& vertics);
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		void Bind();
		void Draw();

		static std::shared_ptr<Mesh> CreateBox(const glm::vec3& extents = glm::vec3(1.0f));
		//static std::shared_ptr<Mesh> Load(const std::string& path);
	private:
		VertexLayout m_vertexLayout;//存储在GPU缓存里的几何体
		

		GLuint m_VBO = 0;
		GLuint m_EBO = 0;
		GLuint m_VAO = 0;

		size_t m_vertexCount = 0;
		size_t m_indexCount = 0;
	};
}