// Event Definition
// ----------------

#ifndef EVENT_H
#define EVENT_H

#include "bpch.h"
#include "Bell/Core.h"

namespace Bell {

    // Describes the Type of which an Event may be
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    // Describes the Categories of which an Event may be
    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    // Function define for inherited Event classes
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                               virtual EventType GetEventType() const override { return GetStaticType(); }\
                               virtual const char* GetName() const override { return #type; }\

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    // Abstracted Event Class
    // Inherit from this and use both, EVENT_CLASS_TYPE and EVENT_CLASS CATEGORY, defines
    // in order for your event to be seen by the Event Dispatcher 
    class BELL_API Event {
    public:
        // If this event has been handled and no longer should be used in other event
        bool Handled = false;

        // Returns the event type set in the inherited class from EVENT_CLASS_TYPE define
        virtual EventType GetEventType() const = 0;
        // Returns the name from the EVENT_CLASS_TYPE define
        virtual const char* GetName() const = 0;
        // Returns the Event Category from the EVENT_CLASS_TYPE define
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        // Compares this Event to an Event Category and return true if it is
        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    };

    // Event Dispatcher Class
    // Used to send out when a Event happens
    class EventDispatcher
    {
    public:
        EventDispatcher(Event& e)
            : m_Event(e) {}

        // F is deduced by the complier
        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled = func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }
    private:
        Event& m_Event;
    };

    // For the logging lib
    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}

#endif // !EVENT_H