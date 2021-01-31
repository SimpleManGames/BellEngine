// Event Definition
// ----------------

#ifndef _EVENT_H
#define _EVENT_H

#include "bpch.h"
#include "Bell/Base/Core.h"
#include "Bell/Common/bitmaskenums.h"

namespace Bell
{

    /**
     * @brief Describes the Type of which an Event may be
     * 
     */
    enum class EventType
    {
        None = 0,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        AppTick,
        AppUpdate,
        AppRender,
        KeyPressed,
        KeyReleased,
        KeyTyped,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    /**
     * @brief Describes the Categories of which an Event may be
     * 
     */
    enum class EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };
    ENABLE_BITMASK_OPERATORS(EventCategory);

    /// Function define for inherited Event classes
#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType GetStaticType() { return EventType::type; }                \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char *GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual EventCategory GetCategoryFlags() const override { return category; }

    /**
     * @brief Abstracted Event Class
     * Inherit from this and use both, EVENT_CLASS_TYPE and EVENT_CLASS CATEGORY, defines
     * in order for your event to be seen by the Event Dispatche
     * 
     */
    class Event
    {
    public:
        virtual ~Event() = default;

        /**
         * @brief If this event has been handled and no longer should be used in other event
         * 
         */
        bool Handled = false;

        /**
         * @brief Returns the event type set in the inherited class from EVENT_CLASS_TYPE define
         * 
         * @return EventType of this Event
         */
        virtual EventType GetEventType() const = 0;
        /**
         * @brief Returns the name from the EVENT_CLASS_TYPE define
         * 
         * @return const char* Name of the Event
         */
        virtual const char *GetName() const = 0;
        /**
         * @brief Returns the Event Category from the EVENT_CLASS_TYPE define
         * 
         * @return EventCategory of this Event
         */
        virtual EventCategory GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        /**
         * @brief Compares this Event to an Event Category
         * 
         * @param category Category to compare to
         * @return true If this Event is in the category
         * @return false If this Event is not in the category
         */
        inline bool IsInCategory(Bell::EventCategory category) { return (bool)(GetCategoryFlags() & category); }
    };

    /**
     * @brief Event Dispatcher Class
     * Used to send out when a Event happens
     * 
     */
    class EventDispatcher
    {
    public:
        EventDispatcher(Event &e)
            : m_Event(e) {}

        // F 
        /**
         * @brief Dispatch an Event with a function pointer
         * 
         * @tparam T Event that we are trying to dispatch
         * @tparam F is deduced by the complier
         * @param func Function Pointer that for this dispatch
         * @return true If the function was successfully sent
         * @return false If the function wasn't sent
         */
        template <typename T, typename F>
        bool Dispatch(const F &func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled = func(static_cast<T &>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event &m_Event;
    };

    /**
     * @brief Operator interacting with the logging library
     * 
     */
    inline std::ostream &operator<<(std::ostream &os, const Event &e)
    {
        return os << e.ToString();
    }
} // namespace Bell

#endif // !_EVENT_H