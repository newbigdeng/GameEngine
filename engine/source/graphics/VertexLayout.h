#pragma once
#include <glad/glad.h>
#include <vector>
#include <stdint.h>

namespace eng
{
	struct VertexElement
	{
		GLuint index;//Layout的数
		GLuint size;//数量，比如位置需要x,y,z三个数量
		GLuint type;//类型，比如GL_FLOAT
		uint32_t offset;//从开始位置的偏移

		static constexpr int PositionIndex = 0;
		static constexpr int ColorIndex = 1;
		static constexpr int UVIndex = 2;
		static constexpr int NormalIndex = 3;
	};
	struct VertexLayout
	{
		std::vector<VertexElement> elements;
		uint32_t stride = 0;//单个顶点的总大小
	};
}