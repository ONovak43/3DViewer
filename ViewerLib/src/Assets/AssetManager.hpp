#pragma once
#include "GLShaderAsset.hpp"
#include "TextAsset.hpp"
#include "GLShaderProgramAsset.hpp"

#include "OpenGL/OpenGLShader.hpp"
#include "OpenGL/OpenGLShaderProgram.hpp"


namespace VL
{
	class AssetManager
	{
	public:
		static AssetManager& getInstance() {
			static AssetManager instance;
			return instance;
		}

		AssetManager(const AssetManager&) = delete;
		AssetManager(AssetManager&) = delete;
		AssetManager(AssetManager&&) noexcept = delete;
		AssetManager& operator=(const AssetManager&) = delete;
		AssetManager& operator=(AssetManager&&) noexcept = delete;

		inline std::shared_ptr<VL::OpenGL::OpenGLShader> getShader(const std::string& name)
		{
			return m_shaderAssets.getAsset(name);
		}

		inline std::shared_ptr<VL::OpenGL::OpenGLShaderProgram> getShaderProgram(const std::string& name)
		{
			return m_shaderProgramAssets.getAsset(name);
		}

		inline std::shared_ptr<std::string> getTextAsset(const std::string& name)
		{
			return m_textAssets.getAsset(name);
		}
	private:
		AssetManager();
		~AssetManager();
		GLShaderAsset m_shaderAssets;
		GLShaderProgramAsset m_shaderProgramAssets;
		TextAsset m_textAssets;
	};
}