// Window Abstraction
// Each OS will have their own window using this class
// ---------------------------------------------------

#ifndef _WINDOW_H
#define _WINDOW_H

#include "bpch.h"

#include "Bell/Base/Core.h"
#include "Bell/Base/Events/Event.h"

namespace Bell
{
    // Window Properties
    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string& title = "Bell Engine",
            uint32_t width = 1280,
            uint32_t height = 720)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    // 
    /**
     * @brief Abstract Window Declaration- 
     * Virtual class to be used for each OS type window
     * 
     */
    class Window
    {
    public:
        using EventCallBackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        /**
         * @brief Abstract Declaration for OnUpdate.
         * Each OS will have their own implemention for updating their window
         * 
         */
        virtual void OnUpdate() = 0;

        /**
         * @brief Abstract Declaration for obtaining the Window's Width
         * 
         * @return uint32_t Width
         */
        virtual uint32_t GetWidth() const = 0;
        /**
         * @brief Abstract Declaration for obtaining the Window's Height
         * 
         * @return uint32_t Height
         */
        virtual uint32_t GetHeight() const = 0;
        
        virtual void SetEventCallback(const EventCallBackFn& callback) = 0;
        /**
         * @brief Abstract Declaration for setting VSync on this window
         * 
         * @param enabled New value
         */
        virtual void SetVSync(bool enabled) = 0;
        /**
         * @brief Abstract Declaration for checking if VSync is on
         * 
         * @return true If VSync is On.
         * @return false If VSync is Off.
         */
        virtual bool IsVSync() const = 0;

        /**
         * @brief Abstract Declaration for setting the window to the center of the screen
         * 
         */
        virtual void CenterWindow() = 0;
        /**
         * @brief Abstract Declaration for finding which monitor this window is most on
         * 
         * @return void* Pointer to the specific OS window
         */
        virtual void* GetBestMonitor() = 0;

        /**
         * @brief Abstract Declaration for retrieving OS specific window 
         * 
         * @return void* OS Specific Window
         */
        virtual void* GetNativeWindow() const = 0;

        /**
         * @brief Static creation function that creates the window based on your OS
         * 
         * @param props Window Properties to initialize the window with
         * @return Scope<Window> Newly created Window
         */
        static Scope<Window> Create(const WindowProps& props = WindowProps());
    };
}

#endif // !_WINDOW_H