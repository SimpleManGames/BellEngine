#include "bpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"
#include "Bell/Application.h"
#include "Bell/Events/MouseEvent.h"

// TEMP
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Bell
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGui Layer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // Temp will use our own keycodes
        io.KeyMap[ImGuiKey_Tab] = B_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = B_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = B_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = B_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = B_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = B_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = B_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = B_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = B_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = B_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = B_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = B_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = B_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = B_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = B_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = B_KEY_A;
        io.KeyMap[ImGuiKey_C] = B_KEY_C;
        io.KeyMap[ImGuiKey_V] = B_KEY_V;
        io.KeyMap[ImGuiKey_X] = B_KEY_X;
        io.KeyMap[ImGuiKey_Y] = B_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = B_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event & event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(B_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(B_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(B_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(B_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(B_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(B_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(B_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(B_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;

        return false;
    }
    
    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());

        return false;
    }
    
    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheel += e.GetYOffset();
        io.MouseWheelH += e.GetXOffset();

        return false;
    }
    
    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[B_KEY_LEFT_CONTROL] | io.KeysDown[B_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[B_KEY_LEFT_SHIFT] | io.KeysDown[B_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[B_KEY_LEFT_ALT] | io.KeysDown[B_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[B_KEY_LEFT_SUPER] | io.KeysDown[B_KEY_RIGHT_SUPER];

        return false;
    }
    
    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.GetKeyCode();

        if (keycode > 0 && keycode < 0x100000)
            io.AddInputCharacter((unsigned short)keycode);

        return false;
    }
    
    bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent & e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());

        return false;
    }
}