#include "pch.hpp"

namespace MemoryTests
{
    namespace StackAllocatorTest
    {
        TEST(StackAllocatorTest, TestAllocation)
        {
            // Given
            VL::StackAllocator<256> allocator;
            std::size_t size = 16;

            // When
            auto ptr1 = static_cast<float*>(allocator.allocate(size));
            auto marker = allocator.getMarker();
            auto ptr2 = static_cast<int*>(allocator.allocate(size));

            // Then
            EXPECT_NE(ptr1, nullptr);
            EXPECT_NE(ptr2, nullptr);
            EXPECT_EQ(allocator.getUsedMemory(), 2 * size);
            EXPECT_EQ(allocator.getFreeMemory(), 256 - 2 * size);

            // When
            allocator.freeToMarker(marker);
            auto ptr3 = static_cast<int*>(allocator.allocate(size));

            // Then
           // EXPECT_EQ(ptr3, ptr2);
            EXPECT_EQ(allocator.getUsedMemory(), 2 * size);
            EXPECT_EQ(allocator.getFreeMemory(), 256 - 2 * size);
        }

        TEST(StackAllocatorTest, TestOverflow)
        {
            // Given
            VL::StackAllocator<16> allocator;
            std::size_t size = 16;

            // When/Then
            auto ptr1 = static_cast<int*>(allocator.allocate(size));
            auto ptr2 = static_cast<float*>(allocator.allocate(size));
            EXPECT_NE(ptr1, nullptr);
            EXPECT_EQ(ptr2, nullptr);
            EXPECT_EQ(allocator.getUsedMemory(), size);
            EXPECT_EQ(allocator.getFreeMemory(), 0);
        }

        TEST(StackAllocatorTest, TestClear)
        {
            // Given
            VL::StackAllocator<256> allocator;
            std::size_t size = 16;

            // When
            auto ptr1 = static_cast<int*>(allocator.allocate(size));
            auto marker = allocator.getMarker();
            auto ptr2 = static_cast<float*>(allocator.allocate(size));

            // Then
            EXPECT_NE(ptr1, nullptr);
            EXPECT_NE(ptr2, nullptr);
            EXPECT_EQ(allocator.getUsedMemory(), 2 * size);
            EXPECT_EQ(allocator.getFreeMemory(), 256 - 2 * size);

            // When
            allocator.clear();

            // Then
            EXPECT_EQ(allocator.getUsedMemory(), 0);
            EXPECT_EQ(allocator.getFreeMemory(), 256);
        }
    }
} 