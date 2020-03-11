#pragma once
#include <list>

template <class EventType>
class Listener
{
public:
	virtual bool handleEvent(EventType const & e) = 0;
};

template <class EventType>
class Emitter
{
public:
	inline void registerListener(Listener<EventType>* lis) {
		listeners_.push_back(lis);
	}

	//simply emit to all listeners until one handles (return if handled)
	bool Emit(EventType const & e) const {
		for (auto l : listeners_) {
			if (l->handleEvent(e)) return true;
		}
		return false;
	};

protected:
	std::list<Listener<EventType>*> listeners_;
};
