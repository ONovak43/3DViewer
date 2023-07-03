#pragma once
#include "Asset.hpp"
#include "Renderer/OpenGL/OpenGLTexture.hpp"

namespace VL
{
	class GLCubeMapTextureAsset :
		public Asset<OpenGL::OpenGLTexture>
	{
	protected:
		std::shared_ptr<OpenGL::OpenGLTexture> loadAsset(const std::string& name) override
		{
			return std::make_shared<OpenGL::OpenGLTexture>(name, TEXTURE_TYPE::TEXTURE_CUBE_MAP);
		}
	};
}
