#include "pch.hpp"
#include "OpenGLShaderProgram.hpp"
#include "Assets/AssetManager.hpp"

namespace VL
{
	namespace OpenGL
	{
		OpenGLShaderProgram::OpenGLShaderProgram(const std::string& name)
			: OpenGLShaderProgram(
				AssetManager::getInstance().getShader(name + ".glvert"), 
				AssetManager::getInstance().getShader(name + ".glfrag")
			)
		{
		}

		OpenGLShaderProgram::OpenGLShaderProgram(const std::shared_ptr<OpenGLShader> vertexShader, const std::shared_ptr<OpenGLShader> fragmentShader)
		{
			auto vertexId = vertexShader->getId();
			auto fragId = fragmentShader->getId();

			ASSERT(vertexId != 0, "Invalid vertex shader.");
			ASSERT(fragId != 0, "Invalid fragment shader.");

			m_id = glCreateProgram();
			glAttachShader(m_id, vertexId);
			glAttachShader(m_id, fragId);
			glLinkProgram(m_id);
			glValidateProgram(m_id);

			GLint success{};
			glGetProgramiv(m_id, GL_LINK_STATUS, &success);

			if (!success)
			{
				GLchar infoLog[512];
				glGetProgramInfoLog(m_id, sizeof(infoLog) / sizeof(infoLog[0]), nullptr, infoLog);
				std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";

				glDeleteProgram(m_id);
				m_id = 0;
			}
		}

		OpenGLShaderProgram::~OpenGLShaderProgram()
		{
			if (getId() != 0)
			{
				glDeleteProgram(m_id);
			}
		}

		void OpenGLShaderProgram::bind() const
		{
			ASSERT(m_id != 0, "Invalid shader program.");
			glUseProgram(m_id);
		}

		void OpenGLShaderProgram::unbind() const
		{
			glUseProgram(0);
		}

		void OpenGLShaderProgram::setInt(const std::string& name, int32_t value)
		{
			glProgramUniform1i(m_id, getUniformLocation(name), static_cast<GLint>(value));
		}

		void OpenGLShaderProgram::setUInt(const std::string& name, uint32_t value)
		{
			glProgramUniform1ui(m_id, getUniformLocation(name), static_cast<GLuint>(value));
		}

		void OpenGLShaderProgram::setFloat(const std::string& name, float value)
		{
			glProgramUniform1f(m_id, getUniformLocation(name), static_cast<GLfloat>(value));
		}

		void OpenGLShaderProgram::setVec2(const std::string& name, vec2 value)
		{
			setVec(name, value);
		}

		void OpenGLShaderProgram::setVec3(const std::string& name, vec3 value)
		{
			setVec(name, value);
		}

		void OpenGLShaderProgram::setVec4(const std::string& name, vec4 value)
		{
			setVec(name, value);
		}

		void OpenGLShaderProgram::setMat3(const std::string& name, mat3 value, bool transpose)
		{
			setMat(name, value, transpose);
		}

		void OpenGLShaderProgram::setMat4(const std::string& name, mat4 value, bool transpose)
		{
			setMat(name, value, transpose);
		}
	}
}
