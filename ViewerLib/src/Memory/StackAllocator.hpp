#pragma once
#include "Core/Base.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>

namespace VL
{
	// Dyamic memory allocation stack allocator (LIFO)
	template <std::size_t S>
	class StackAllocator
	{
	using Marker = std::size_t;
	public:
		StackAllocator();
		~StackAllocator();
		StackAllocator(const StackAllocator&) = delete;
		StackAllocator& operator=(const StackAllocator&) = delete;
		StackAllocator(StackAllocator&&) = delete;
		StackAllocator& operator=(StackAllocator&&) = delete;
		void* allocate(std::size_t size);
		void clear();
		Marker getMarker();
		void freeToMarker(Marker marker);
		std::size_t getUsedMemory() const;
		std::size_t getFreeMemory() const;
	private:
		char* m_buffer; // buffer pro pamÏù alokovanou na heapu
		Marker m_marker; // index vrcholu z·sobnÌku
	};
}

#include "StackAllocator.inl"