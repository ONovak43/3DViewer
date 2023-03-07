#pragma once
#include "IEventManager.hpp"
#include "IEvent.hpp"
#include <functional>
#include <map>

namespace VL 
{
	class EventManager : public IEventManager
	{
	public:
		using eventCallbackFn = std::function<void(std::shared_ptr<IEvent>)>;
		EventManager() = default;
		virtual ~EventManager() = default;
		virtual void subscribe(IEventManager::EVENT_TYPE eventType, eventCallbackFn callback) override;
		virtual void unsubscribe(EVENT_TYPE eventType, eventCallbackFn callback) override;
		virtual void notify(EVENT_TYPE eventType, std::shared_ptr<IEvent>) override;

	private:	
		using eventCallbacks = std::vector<eventCallbackFn>;
		using events = std::map<EVENT_TYPE, eventCallbacks>;
		events callbacks;
	};
}