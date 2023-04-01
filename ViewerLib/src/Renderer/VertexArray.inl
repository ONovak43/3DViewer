namespace VL
{
    constexpr std::size_t vertexTypeSize(VertexAttribute::Type type)
    {
        using Type = VertexAttribute::Type;
        switch (type) {
        case Type::BYTE:
            return sizeof(int8_t);
        case Type::USHORT:
            return sizeof(uint16_t);
        case Type::INT:
            return sizeof(int32_t);
        case Type::VEC2I:
            return sizeof(int32_t) * 2;
        case Type::VEC3I:
            return sizeof(int32_t) * 3;
        case Type::VEC4I:
            return sizeof(int32_t) * 4;
        case Type::UINT:
            return sizeof(uint32_t);
        case Type::FLOAT:
            return sizeof(float);
        case Type::VEC2F:
            return sizeof(float) * 2;
        case Type::VEC3F:
            return sizeof(float) * 3;
        case Type::VEC4F:
            return sizeof(float) * 4;
        case Type::MAT3:
            return sizeof(float) * 3 * 3;
        case Type::MAT4:
            return sizeof(float) * 4 * 4;
        }
        return 0;
    }
}