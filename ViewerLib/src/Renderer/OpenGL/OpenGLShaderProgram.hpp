#pragma once
#include "glad/glad.h"
#include "OpenGLShader.hpp"
#include "Renderer/IShaderProgram.hpp"

namespace VL
{ 
	namespace OpenGL
	{
		class OpenGLShaderProgram 
			: public VL::IShaderProgram
		{
		public:
			explicit OpenGLShaderProgram(const std::string& filePath);
			OpenGLShaderProgram(const std::shared_ptr<OpenGLShader> vertexShader, const std::shared_ptr<OpenGLShader> fragmentShader);
			~OpenGLShaderProgram();

			inline uint32_t getId() const { return m_id; }
			void bind() const;
			void unbind() const;

			// Uniforms
			void setInt(const std::string& name, int32_t value) override;
			void setUInt(const std::string& name, uint32_t value) override;
			void setFloat(const std::string& name, float value) override;

			void setVec2(const std::string& name, vec2 value);
			void setVec3(const std::string& name, vec3 value);
			void setVec4(const std::string& name, vec4 value);

			virtual void setMat3(const std::string& name, mat3 value, bool transpose);
			virtual void setMat4(const std::string& name, mat4 value, bool transpose) override;

		private:
			uint32_t m_id;
			inline uint32_t getUniformLocation(const std::string& location) const
			{
				return glGetUniformLocation(m_id, location.c_str());;
			}

			// Uniforms
			template<typename T>
			void setVec(const std::string& name, T value);
			template<typename T>
			void setMat(const std::string& name, T value, bool transpose = GL_FALSE);
		};

		// Explicit templates
		template void OpenGLShaderProgram::setVec<vec2>(const std::string& name, vec2 value);
		template void OpenGLShaderProgram::setVec<vec3>(const std::string& name, vec3 value);
		template void OpenGLShaderProgram::setVec<vec4>(const std::string& name, vec4 value);

		template void OpenGLShaderProgram::setMat<mat3>(const std::string& name, mat3 value, bool transpose);
		template void OpenGLShaderProgram::setMat<mat4>(const std::string& name, mat4 value, bool transpose);
	}
}

#include "OpenGLShaderProgram.inl"
