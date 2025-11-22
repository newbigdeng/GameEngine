
#include "Mesh.h"
#include "graphics\GraphicsAPI.h"
#include "Engine.h"

namespace eng
{
	Mesh::Mesh(const VertexLayout& layout, const std::vector<float>& vertics, const std::vector<uint32_t> indices)
	{
		m_vertexLayout = layout;

		auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();
		m_VBO = graphicsAPI.CreateVertexBuffer(vertics);
		m_EBO = graphicsAPI.CreateIndexBuffer(indices);

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		for (const auto& element : m_vertexLayout.elements)
		{
			glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE, 
				m_vertexLayout.stride, (void*)element.offset);
			glEnableVertexAttribArray(element.index);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

		glBindVertexArray(0);//ох╫Б╟С
		glBindBuffer(GL_VERTEX_ARRAY, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_vertexCount = (vertics.size() * sizeof(float)) / m_vertexLayout.stride;
		m_indexCount = indices.size();
	}
	Mesh::Mesh(const VertexLayout& layout, const std::vector<float>& vertics)
	{
		m_vertexLayout = layout;

		auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();
		m_VBO = graphicsAPI.CreateVertexBuffer(vertics);

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		for (const auto& element : m_vertexLayout.elements)
		{
			glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE,
				m_vertexLayout.stride, (void*)element.offset);
			glEnableVertexAttribArray(element.index);
		}


		glBindVertexArray(0);
		glBindBuffer(GL_VERTEX_ARRAY, 0);

		m_vertexCount = (vertics.size() * sizeof(float)) / m_vertexLayout.stride;
	}

	void Mesh::Bind()
	{
		glBindVertexArray(m_VAO);

	}

	void Mesh::Draw()
	{
		if (m_indexCount > 0)
		{
			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
		}
	}
}