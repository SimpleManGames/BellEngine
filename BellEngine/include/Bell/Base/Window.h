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

    // Window Interface
    // Virtual class to be used for each OS type window
    class Window
    {
    public:
        using EventCallBackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallBackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void CenterWindow() = 0;
        virtual void* GetBestMonitor() = 0;

        virtual void* GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowProps& props = WindowProps());
    };
}

#endif // !_WINDOW_H