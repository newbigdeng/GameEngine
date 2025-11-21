#pragma once
#include <memory>
#include <string>
#include <glad\glad.h>

namespace eng
{
	class ShaderProgram;
	class GraphicsAPI
	{
	public:
		std::shared_ptr<ShaderProgram> CreateShaderProgram(const std::string vertexSource, const std::string fragSource);
		void BindShaderProgram(ShaderProgram* shaderProgram);
	private:

	};
}