#pragma once
#include "Event.hpp"
#include <functional>
#include <map>

namespace VL
{
	class IEventManager
	{
	public:
		enum class EVENT_TYPE
		{
			APP_TICK, APP_UPDATE, APP_RENDER,
			KEY_PRESSED, KEY_RELEASED,
			MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED,
			WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_MOVE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_ICONIFY, WINDOW_RESTORE,

		};
	public:
		using eventCallbackFn = std::function<void(std::shared_ptr<Event>)>;
		IEventManager() = default;
		virtual ~IEventManager() = default;
		virtual void subscribe(IEventManager::EVENT_TYPE eventType, eventCallbackFn callback) = 0;
		virtual void unsubscribe(EVENT_TYPE eventType, eventCallbackFn callback) = 0;
		virtual void notify(EVENT_TYPE eventType, std::shared_ptr<Event> e) = 0;
	};
}