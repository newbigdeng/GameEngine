#include "Material.h"

#include "graphics\ShaderProgram.h"
#include "graphics\Texture.h"
#include "Engine.h"

#include <nlohmann\json.hpp>

namespace eng
{
	ShaderProgram* Material::GetShaderProgram()
	{
		return m_ShaderProgram.get();
	}
	void Material::SetShaderProgram(const std::shared_ptr<ShaderProgram> shaderProgram)
	{
		m_ShaderProgram = shaderProgram;
	}

	void eng::Material::SetParam(const std::string& name, float value)
	{
		m_floatParams[name] = value;
	}

	void Material::SetParam(const std::string& name, float v0, float v1)
	{
		m_float2Params[name] = std::make_pair(v0, v1);
	}

	void Material::SetParam(const std::string& name, std::shared_ptr<Texture>& texture)
	{
		m_textures[name] = texture;
	}

	void Material::Bind()
	{
		if (!m_ShaderProgram)
		{
			return;
		}
		m_ShaderProgram->Bind();

		for (const auto& param : m_floatParams)
		{
			m_ShaderProgram->SetUniform(param.first, param.second);
		}
		for (const auto& param : m_float2Params)
		{
			m_ShaderProgram->SetUniform(param.first, param.second.first,param.second.second);
		}
		for (const auto& param : m_textures)
		{
			m_ShaderProgram->SetTexture(param.first, param.second.get());
		}
	}

	std::shared_ptr<Material> Material::Load(const std::string& path)
	{
		auto contents = Engine::GetInstance().GetFileSystem().LoadAssetFileText(path);
		if(contents.empty())
			return nullptr;
		nlohmann::json json = nlohmann::json::parse(contents);
		std::shared_ptr<Material> result;

		if (json.contains("shader"))
		{
			auto shaderObj = json["shader"];
			std::string vertexPath = shaderObj.value("vertex", "");
			std::string fragmentPath = shaderObj.value("fragment", "");

			auto& fs = Engine::GetInstance().GetFileSystem();
			auto vertexSrc = fs.LoadAssetFileText(vertexPath);
			auto fragmentSrc = fs.LoadAssetFileText(fragmentPath);
			auto& graphicsAPI = Engine::GetInstance().GetGraphicsAPI();
			auto shaderProgram = graphicsAPI.CreateShaderProgram(vertexSrc, fragmentSrc);
			if(!shaderProgram)
					return nullptr;
			result = std::make_shared<Material>();
			result->SetShaderProgram(shaderProgram);
		}

		if (json.contains("params"))
		{
			auto paramsobj = json["params"];

			// Floats
			if (paramsobj.contains("float"))
			{
				for (auto& p : paramsobj["float"])
				{
					std::string name = p.value("name", "");
					float value = p.value("value", 0.0f);
					result->SetParam(name, value);
				}
			}

			// Float2
			if (paramsobj.contains("float2"))
			{
				for (auto& p : paramsobj["float2"])
				{
					std::string name = p.value("name", "");
					float v0 = p.value("value0", 0.0f);
					float v1 = p.value("value1", 0.0f);
					result->SetParam(name, v0, v1);
				}
			}

			//Textures
			if (paramsobj.contains("textures"))
			{
				for (auto& p : paramsobj["textures"])
				{
					std::string name = p.value("name", "");
					std::string texPath = p.value("path", "");

					auto texture = Texture::Load(texPath);
					result->SetParam(name, texture);
				}
			}
		}
		return result;
	}
}