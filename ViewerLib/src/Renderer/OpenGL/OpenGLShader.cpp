#include "pch.hpp"
#include "OpenGLShader.hpp"
#include "Assets/AssetManager.hpp"

namespace VL
{
	namespace OpenGL
	{
		OpenGLShader::OpenGLShader(const std::string& name)
			: OpenGLShader(AssetManager::getInstance().getTextAsset(name),
				name.ends_with(".glvert") ? GL_VERTEX_SHADER : name.ends_with(".glfrag") ? GL_FRAGMENT_SHADER : GL_GEOMETRY_SHADER)
		{
		}

		OpenGLShader::OpenGLShader(std::shared_ptr<std::string> source, uint32_t type)
			: m_id(0)
		{
			m_id = glCreateShader(type);
			const char* src = source->c_str();
			glShaderSource(m_id, 1, &src, nullptr);
			glCompileShader(m_id);

			GLint success{};
			glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				char infoLog[512];
				glGetShaderInfoLog(m_id, sizeof(infoLog) / sizeof(infoLog[0]), nullptr, infoLog);
				std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << "\n";
				m_id = 0;
			}
		}

		OpenGLShader::~OpenGLShader()
		{
			if (m_id != 0)
			{
				glDeleteShader(m_id);
			}
		}
	}
}
