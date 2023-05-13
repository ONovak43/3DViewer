#pragma once
#include "Event/Events.hpp"
#include "Memory/StackAllocator.hpp"
#include "Renderer/Renderer.hpp"

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
		virtual void setRenderer(Renderer* renderer) = 0;

		// Events
		virtual void onKeyPressedEvent(const std::shared_ptr<KeyPressEvent>& e) = 0;
		virtual void onKeyReleasedEvent(const std::shared_ptr<KeyReleaseEvent>& e) = 0;
		virtual void onMouseMovedEvent(const std::shared_ptr<MouseMoveEvent>& e) = 0;
		virtual void onMouseButtonPressedEvent(const std::shared_ptr<MouseButtonPressEvent>& e) = 0;
		virtual void onMouseButtonReleasedEvent(const std::shared_ptr<MouseButtonReleaseEvent>& e) = 0;
	};
}