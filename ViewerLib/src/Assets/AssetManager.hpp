#pragma once
#include "TextAsset.hpp"
#include "ImageAsset.hpp"
#include "GLShaderAsset.hpp"
#include "GLShaderProgramAsset.hpp"
#include "GL2DTextureAsset.hpp"
#include "GLCubeMapTextureAsset.hpp"

#include "Renderer/OpenGL/OpenGLShader.hpp"
#include "Renderer/OpenGL/OpenGLShaderProgram.hpp"


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

		inline std::shared_ptr<std::string> getTextAsset(const std::string& name, bool cache = true)
		{
			return m_textAssets.getAsset(name, cache);
		}

		inline std::shared_ptr<VL::Utils::Image> getImageAsset(const std::string& name, bool cache = true)
		{
			return m_imageAssets.getAsset(name, cache);
		}

		inline std::shared_ptr<VL::OpenGL::OpenGLShader> getShader(const std::string& name, bool cache = true)
		{
			return m_shaderAssets.getAsset(name, cache);
		}

		inline std::shared_ptr<VL::OpenGL::OpenGLShaderProgram> getShaderProgram(const std::string& name, bool cache = true)
		{
			return m_shaderProgramAssets.getAsset(name, cache);
		}

		inline std::shared_ptr<VL::OpenGL::OpenGLTexture> get2DTexture(const std::string& name, bool cache = true)
		{
			return m_gl2DTextureAssets.getAsset(name, cache);
		}

		inline std::shared_ptr<VL::OpenGL::OpenGLTexture> getCubeMapTexture(const std::string& name, bool cache = true)
		{
			return m_glCubeMapTextureAssets.getAsset(name, cache);
		}

	private:
		AssetManager();
		~AssetManager();
		TextAsset m_textAssets;
		ImageAsset m_imageAssets;
		GLShaderAsset m_shaderAssets;
		GLShaderProgramAsset m_shaderProgramAssets;
		GL2DTextureAsset m_gl2DTextureAssets;
		GLCubeMapTextureAsset m_glCubeMapTextureAssets;
	};
}