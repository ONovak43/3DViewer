namespace VL
{
	namespace OpenGL
	{
		template<typename T>
		inline void VL::OpenGL::OpenGLShaderProgram::setVec(const std::string& name, T value)
		{
			if constexpr (std::is_same_v<T, vec2>)
			{
				glProgramUniform2f(m_id, getUniformLocation(name), value[0], value[1]);
			}
			else if constexpr (std::is_same_v<T, vec3>)
			{
				glProgramUniform3f(m_id, getUniformLocation(name), value[0], value[1], value[2]);
			}
			else if constexpr (std::is_same_v<T, vec4>)
			{
				glProgramUniform4f(m_id, getUniformLocation(name), value[0], value[1], value[3], value[4]);
			}
		}

		template<typename T>
		inline void OpenGLShaderProgram::setMat(const std::string& name, T value, bool transpose)
		{
			if constexpr (std::is_same_v<T, mat3>)
			{
				glProgramUniformMatrix3fv(m_id, getUniformLocation(name), 1, transpose, static_cast<mat3>(value).data());
			}
			else if constexpr (std::is_same_v<T, mat4>)
			{
				glProgramUniformMatrix4fv(m_id, getUniformLocation(name), 1, transpose, static_cast<mat4>(value).data());
			}
		}
	}
}