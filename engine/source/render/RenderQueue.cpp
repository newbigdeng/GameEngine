#include "RenderQueue.h"
#include "Mesh.h"
#include "Material.h"
#include "graphics\GraphicsAPI.h"
#include "graphics\ShaderProgram.h"

namespace eng
{
	void RenderQueue::Submit(const RenderCommand& command)
	{
		m_commands.push_back(command);
	}
	void RenderQueue::Draw(GraphicsAPI& graphicsAPI, const CameraData& cameradata)
	{
		for (auto& command : m_commands)
		{
			graphicsAPI.BindMaterial(command.material);
			auto shaderProgram = command.material->GetShaderProgram();
			shaderProgram->SetUniform("uModel", command.modelMatrix);
			shaderProgram->SetUniform("uView", cameradata.viewMatrix);
			shaderProgram->SetUniform("uProjection", cameradata.projectionMatrix);
			graphicsAPI.BindMesh(command.mesh);
			graphicsAPI.DrawMesh(command.mesh);
		}

		m_commands.clear();
	}
}