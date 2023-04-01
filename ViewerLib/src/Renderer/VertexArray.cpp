#include "pch.hpp"
#include "VertexArray.hpp"

namespace VL
{
    VertexAttribute::VertexAttribute(uint32_t count, Type type, uint32_t offset, uint32_t size)
        : m_normalized(false), m_count(count), m_offset(offset), m_type(type), m_size(size)
    {

    }
}