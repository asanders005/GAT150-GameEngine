#include "EventManager.h"

void EventManager::AddObserver(const id_t& id, Observer* observer, EventHandler eventHandler)
{
	Dispatcher dispatcher;
	dispatcher.observer = observer;
	dispatcher.eventHandler = eventHandler;

	m_dispatchers[id].push_back(dispatcher);
}

void EventManager::Notify(const Event& event)
{
	auto iter = m_dispatchers.find(event.id);
	if (iter != m_dispatchers.end())
	{
		// get list of dispatchers
		auto dispatchers = iter->second;
		// for each dispatcher, call event handler
		for (auto& dispatcher : dispatchers)
		{
			dispatcher.eventHandler(event);
		}
	}
}
