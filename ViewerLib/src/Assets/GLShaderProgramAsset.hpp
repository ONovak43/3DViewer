#pragma once
#include "Asset.hpp"
#include "Renderer/OpenGL/OpenGLShaderProgram.hpp"

namespace VL
{
	class GLShaderProgramAsset :
		public Asset<OpenGL::OpenGLShaderProgram>
	{
	protected:
		std::shared_ptr<OpenGL::OpenGLShaderProgram> loadAsset(const std::string& name) override
		{
			return std::make_shared<OpenGL::OpenGLShaderProgram>(name);
		}
	};
}
