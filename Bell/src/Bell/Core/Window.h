// Window Abstraction
// Each OS will have their own window using this class
// ---------------------------------------------------

#ifndef _WINDOW_H
#define _WINDOW_H

#include "bpch.h"

#include "Bell/Core/Core.h"
#include "Bell/Core/Events/Event.h"

namespace Bell
{
    // Window Properties
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "Bell Engine",
            unsigned int width = 1280,
            unsigned int height = 720)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    // Window Interface
    // Virtual class to be used for each OS type window
    class BELL_API Window
    {
    public:
        using EventCallBackFn = std::function<void(Event&)>;

        virtual ~Window() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallBackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void CenterWindow() = 0;
        virtual void* GetBestMonitor() = 0;

        virtual void* GetNativeWindow() const = 0;

        static Ref<Window> Create(const WindowProps& props = WindowProps());
    };
}

#endif // !_WINDOW_H