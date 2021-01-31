#ifndef _KEY_EVENT_H
#define _KEY_EVENT_H

#include "Event.h"

namespace Bell {

    /**
     * @brief Base Event for describing Key related events
     * 
     */
    class KeyEvent : public Event
    {
    public:
        /**
         * @brief Get the Key Code object
         * 
         * @return int Key Code
         */
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput)
    protected:
        /**
         * @brief Construct a Key Event 
         * 
         * @param keycode Key Code
         */
        KeyEvent(int keycode)
            : m_KeyCode(keycode) {}

        int m_KeyCode;
    };

    /**
     * @brief Event for describing a Key Pressed Event
     * 
     */
    class KeyPressedEvent : public KeyEvent
    {
    public:
        /**
         * @brief Construct a Key Pressed Event
         * 
         * @param keycode Key code that was pressed
         * @param repeatCount If the key is being held, this is the count of it
         */
        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        /**
         * @brief Get the Repeat Count 
         * If the key was being held, this is the amount of times it registered
         * 
         * @return int Repeated Count
         */
        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        int m_RepeatCount;
    };

    /**
     * @brief Event for describing a Key Released Event
     * 
     */
    class KeyReleasedEvent : public KeyEvent
    {
    public:
        /**
         * @brief Construct a Key Released Event
         * 
         * @param keycode Key Code of the released key
         */
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    private:
    };

    /**
     * @brief Event for describing if the Key Press should be considered typed
     * 
     */
    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}

#endif // !_KEY_EVENT_H