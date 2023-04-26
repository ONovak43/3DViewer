#include "pch.hpp"
#include "EventManager.hpp"

namespace VL
{
	void EventManager::subscribe(IEventManager::EVENT_TYPE eventType, eventCallbackFn callback)
	{
		auto& cb = callbacks[eventType];
		cb.push_back(callback); // not checking if callback already exists
	}

	void EventManager::unsubscribe(EVENT_TYPE eventType, eventCallbackFn callback)
	{
		try {
			auto& cb = callbacks.at(eventType);
			std::erase_if(cb, [&](const auto& cb) {
				return cb.target_type() == callback.target_type();
			});
		}
		catch (std::out_of_range& e) {
			return;
		}
	}

	void EventManager::notify(EVENT_TYPE eventType, std::shared_ptr<Event> e)
	{
		for (auto& cb : callbacks[eventType]) {
			cb(e);
		}
	}
}