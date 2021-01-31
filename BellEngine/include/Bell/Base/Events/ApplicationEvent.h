// Application Events Definitions
// ------------------------------

#ifndef _APPLICATION_EVENT_H
#define _APPLICATION_EVENT_H

#include "Event.h"

namespace Bell
{
    /**
     * @brief Window Resize Event
     * Used to process and telegraph when a Window Resizing takes place
     * 
     */
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {}

        /**
         * @brief Returns the Width of the Window
         * 
         * @return unsigned int Width
         */
        inline unsigned int GetWidth() const { return m_Width; }
        /**
         * @brief Returns the Height of the Window
         * 
         * @return unsigned int Height
         */
        inline unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)

    protected:
        unsigned int m_Width, m_Height;
    };

    /**
     * @brief Window Close Event
     * Used to process and telegraph when a Window Close takes place
     * 
     */
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };

    /**
     * @brief Application Tick Event
     * Used to process and telegraph when a Application Tick takes place
     * 
     */
    class AppTickEvent : public Event
    {
    public:
        AppTickEvent() = default;

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };

    /**
     * @brief Application Update Event
     * Used to process and telegraph when a Application Update takes place
     * 
     */
    class AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() = default;

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };

    /**
     * @brief Application Render Event
     * Used to process and telegraph when a Application Render takes place
     * 
     */
    class AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() = default;

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
    };
} // namespace Bell

#endif // !_APPLICATION_EVENT_H