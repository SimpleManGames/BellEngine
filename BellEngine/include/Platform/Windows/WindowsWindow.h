// Window OS specific definition for the window application 
// --------------------------------------------------------

#ifndef _WINDOWS_WINDOW_H
#define _WINDOWS_WINDOW_H

#include "Bell/Base/Window.h"
#include "Bell/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Bell
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& prop);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth()  const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        virtual void CenterWindow() override;
        virtual void* GetBestMonitor() override;

        inline void SetEventCallback(const EventCallBackFn& callback) override { m_Data.EventCallBack = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const { return m_Window; }
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;
        Scope<GraphicsContext> m_Context;

        struct WindowData
        {
            WindowData()
                : Title("Bell Engine"), Width(1280), Height(600), VSync(false)
            {

            }

            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallBackFn EventCallBack;
        };

        WindowData m_Data;
    };
}

#endif // !_WINDOWS_WINDOW_H