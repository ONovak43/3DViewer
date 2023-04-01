namespace VL
{
	using Marker = std::size_t;

	template<std::size_t S>
	inline StackAllocator<S>::StackAllocator()
		: m_buffer(nullptr), m_marker(0)
	{
		m_buffer = static_cast<char*>(std::malloc(S));
	}

	template<std::size_t S>
	inline StackAllocator<S>::~StackAllocator()
	{
		std::free(m_buffer);
	}

	template<std::size_t S>
	inline void* VL::StackAllocator<S>::allocate(std::size_t size)
	{
		if (m_marker + size > S)
		{
			return nullptr;
		}
		
		void* ptr = m_buffer + m_marker;
		m_marker += size;
		return ptr;	
	}

	template<std::size_t S>
	inline void StackAllocator<S>::clear()
	{
		m_marker = 0;
	}

	template<std::size_t S>
	inline Marker StackAllocator<S>::getMarker()
	{
		return m_marker;
	}

	template<std::size_t S>
	inline void StackAllocator<S>::freeToMarker(Marker marker)
	{
		ASSERT(m_marker > marker, "Marker is out of range");

		m_marker = marker;
	}

	template<std::size_t S>
	inline std::size_t StackAllocator<S>::getUsedMemory() const
	{
		return m_marker * sizeof(char);
	}

	template<std::size_t S>
	inline std::size_t StackAllocator<S>::getFreeMemory() const
	{
		return S * sizeof(char) - m_marker;
	}
}