#ifndef _MOUSE_EVENT_H
#define _MOUSE_EVENT_H

#include "Event.h"

namespace Bell
{
    /**
     * @brief Event for describing the mouse moving
     * 
     */
    class MouseMovedEvent : public Event
    {
    public:
        /**
         * @brief Construct a Mouse Moved Event
         * 
         * @param x Screen Space X Coord
         * @param y Screen Space Y Coord
         */
        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {}

        /**
         * @brief Gets the X value of the mouse in screen space
         * 
         * @return float Screen Space X value 
         */
        inline float GetX() const { return m_MouseX; }
        /**
         * @brief Gets the Y value of the mouse in screen space
         * 
         * @return float Screen Space Y value 
         */
        inline float GetY() const { return m_MouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

    private:
        float m_MouseX, m_MouseY;
    };

    /**
     * @brief Event for describing mouse wheel events
     * 
     */
    class MouseScrolledEvent : public Event
    {
    public:
        /**
         * @brief Construct a Mouse Scrolled Event
         * 
         * @param xOffset Delta X
         * @param yOffset Delta Y
         */
        MouseScrolledEvent(float xOffset, float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

        /**
         * @brief Gets the X value of the scroll event as a Delta
         * 
         * @return float Delta X
         */
        inline float GetXOffset() const { return m_XOffset; }
        /**
         * @brief Gets the Y value of the scroll event as a Delta
         * 
         * @return float Delta Y
         */
        inline float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)

    private:
        float m_XOffset, m_YOffset;
    };

    /**
     * @brief Base Event for describing a mouse button event
     * 
     */
    class MouseButtonEvent : public Event
    {
    public:
        /**
         * @brief Gets the button code that was pressed on the mouse
         * 
         * @return int 
         */
        inline int GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput)
    protected:
        /**
         * @brief Construct a Mouse Button Event
         * 
         * @param button Button code that was pressed
         */
        MouseButtonEvent(int button)
            : m_Button(button) {}

        int m_Button;
    };

    /**
     * @brief Event to describe when a mouse button was pressed
     * 
     */
    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        /**
         * @brief Construct a Mouse Button Pressed Event
         * 
         * @param button Mouse Code of the button that was pressed
         */
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    /**
     * @brief Event to describe when a mouse button was released
     * 
     */
    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        /**
         * @brief Construct a Mouse Button Released Event
         * 
         * @param button Mouse Code of the button that was released
         */
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
} // namespace Bell

#endif // !_MOUSE_EVENT_H