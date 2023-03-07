#include "pch.hpp"
#include "EventManager.hpp"
namespace VL
{
	/*
	EventManager::Impl::Impl()
	{
		callback.emplace(EVENT_TYPE::APP_RENDER);
		callback.emplace(EVENT_TYPE::APP_TICK);
		callback.emplace(EVENT_TYPE::APP_UPDATE);
		callback.emplace(EVENT_TYPE::KEY_PRESSED);
		callback.emplace(EVENT_TYPE::KEY_RELEADED);
		callback.emplace(EVENT_TYPE::KEY_TYPED);
		callback.emplace(EVENT_TYPE::MOUSE_BUTTON_PRESSED);
		callback.emplace(EVENT_TYPE::MOUSE_BUTTON_RELEASED);
		callback.emplace(EVENT_TYPE::MOUSE_MOVED);
		callback.emplace(EVENT_TYPE::MOUSE_SCROLLED);
		callback.emplace(EVENT_TYPE::WINDOW_CLOSE);
		callback.emplace(EVENT_TYPE::WINDOW_RESIZE);
		callback.emplace(EVENT_TYPE::WINDOW_MOVE);
		callback.emplace(EVENT_TYPE::WINDOW_FOCUS);
		callback.emplace(EVENT_TYPE::WINDOW_LOST_FOCUS);
		callback.emplace(EVENT_TYPE::WINDOW_ICONIFY);
		callback.emplace(EVENT_TYPE::WINDOW_RESTORE);
	}
	*/

	//EventManager::EventManager()
	//	: _impl(std::make_unique<Impl>())
	//{
	//}

	void EventManager::subscribe(IEventManager::EVENT_TYPE eventType, eventCallbackFn callback)
	{
		auto& cb = callbacks[eventType];
		cb.push_back(callback); // not checking if callback already exists
	}

	void EventManager::unsubscribe(EVENT_TYPE eventType, eventCallbackFn callback)
	{
		auto& cb = callbacks[eventType];
		std::erase_if(cb, [&](const auto& cb) {
			return cb.target_type() == callback.target_type(); 
		});
	}

	void EventManager::notify(EVENT_TYPE eventType, std::shared_ptr<IEvent> e)
	{
		for (auto& cb : callbacks[eventType]) {
			cb(e);
		}
	}
}