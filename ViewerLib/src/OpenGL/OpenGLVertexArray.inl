namespace VL
{
	namespace OpenGL
	{
		constexpr GLenum convertVertexType(VertexAttribute::Type type)
		{
			using Type = VertexAttribute::Type;
			switch (type)
			{
			case Type::BYTE:
				return GL_BYTE;
			case Type::USHORT:
				return GL_UNSIGNED_SHORT;
			case Type::INT:
			case Type::VEC2I:
			case Type::VEC3I:
			case Type::VEC4I:
				return GL_INT;
			case Type::UINT:
				return GL_UNSIGNED_INT;
			case Type::FLOAT:
			case Type::VEC2F:
			case Type::VEC3F:
			case Type::VEC4F:
			case Type::MAT3:
			case Type::MAT4:
				return GL_FLOAT;
			}
			return 0;
		}
	}
}