#pragma once
#include "Asset.hpp"
#include "OpenGL/OpenGLShader.hpp"

namespace VL
{
	class GLShaderAsset :
		public Asset<VL::OpenGL::OpenGLShader>
	{
	protected:
		std::shared_ptr<VL::OpenGL::OpenGLShader> loadAsset(const std::string& name) override
		{
			return std::make_shared<OpenGL::OpenGLShader>(name);
		}
	};
}