#pragma once
#include "Renderer/IShader.hpp"
namespace VL
{
	namespace OpenGL
	{
		class OpenGLShader
			: public VL::IShader
		{
		public:
			explicit OpenGLShader(const std::string& name);
			OpenGLShader(std::shared_ptr<std::string> source, uint32_t type);
			~OpenGLShader();

			[[nodiscard]] uint32_t getId() const override { return m_id; }

		private:
			uint32_t m_id;
		};
	}
}

