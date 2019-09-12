// Application Events Definitions
// ------------------------------

#ifndef APPLICATION_EVENT_H
#define APPLICATION_EVENT_H

#include "Event.h"

namespace Bell
{
    // Window Resize Event
    // Used to process and telegraph when a Window Resizing takes place
    class BELL_API WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {}

        // Returns the Width of the Window
        inline unsigned int GetWidth() const { return m_Width; }
        // Returns the Height of the Window
        inline unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)

    protected:
        unsigned int m_Width, m_Height;
    };

    // Window Close Event
    // Used to process and telegraph when a Window Close takes place
    class BELL_API WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    // Application Tick Event
    // Used to process and telegraph when a Application Tick takes place
    class BELL_API AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    // Application Update Event
    // Used to process and telegraph when a Application Update takes place
    class BELL_API AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    // Application Render Event
    // Used to process and telegraph when a Application Render takes place
    class BELL_API AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
            EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}

// Header Guard
#endif