#pragma once
#include "Event/Events.hpp"
#include "Memory/StackAllocator.hpp"
#include <memory>

namespace VL
{
	class Client
	{
	public:
		Client(const Client&) = delete;
		Client(Client&) = delete;
		Client(Client&&) noexcept = delete;
		Client& operator=(const Client&) = delete;
		Client& operator=(Client&) noexcept = delete;
		Client() = default;
		virtual ~Client() = default;
		virtual void start() = 0;
		virtual void update(StackAllocator<STACK_ALLOCATOR_SIZE>& stackAllocator, float deltaTime) = 0;
		virtual void renderGUI() = 0;
		virtual void stop() = 0;
		virtual void onKeyEvent(std::shared_ptr<KeyPressEvent>& e) = 0;
	};
}