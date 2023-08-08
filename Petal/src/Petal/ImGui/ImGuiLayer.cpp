#include "ptlpch.h"
#include "ImGuiLayer.h"

#include "Platform/OpenGL/imgui_impl_opengl3.h"

#include "Petal/Application.h"

#include <imgui.h>
#include <GLFW/glfw3.h>

namespace ptl
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGui")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::Init()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        Application& app = Application::Get();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void ImGuiLayer::ShutDown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnUpdate(Timestep timestep)
    {
    }

    void ImGuiLayer::OnEvent(Event& event)
    {
        PTL_CORE_TRACE(event);
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowResizeEvent>(PTL_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
        dispatcher.Dispatch<KeyPressEvent>(PTL_BIND_EVENT_FN(ImGuiLayer::OnKeyPressEvent));
        dispatcher.Dispatch<KeyReleaseEvent>(PTL_BIND_EVENT_FN(ImGuiLayer::OnKeyReleaseEvent));
        dispatcher.Dispatch<KeyTypeEvent>(PTL_BIND_EVENT_FN(ImGuiLayer::OnKeyTypeEvent));
        dispatcher.Dispatch<MouseButtonPressEvent>(PTL_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressEvent));
        dispatcher.Dispatch<MouseButtonReleaseEvent>(PTL_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleaseEvent));
        dispatcher.Dispatch<MouseMoveEvent>(PTL_BIND_EVENT_FN(ImGuiLayer::OnMouseMoveEvent));
        dispatcher.Dispatch<MouseScrollEvent>(PTL_BIND_EVENT_FN(ImGuiLayer::OnMouseScrollEvent));
    }

    void ImGuiLayer::OnImGuiRender()
    {
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
        return false;
    }

    bool ImGuiLayer::OnKeyPressEvent(KeyPressEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGuiKey key = PtlToImGuiKeyCode(event.GetKeyCode());

        // Activate modifier keys
        if (key == ImGuiKey_LeftAlt || key == ImGuiKey_RightAlt)
            io.AddKeyEvent(ImGuiMod_Alt, true);
        if (key == ImGuiKey_LeftCtrl || key == ImGuiKey_RightCtrl)
            io.AddKeyEvent(ImGuiMod_Ctrl, true);
        if (key == ImGuiKey_LeftShift || key == ImGuiKey_RightShift)
            io.AddKeyEvent(ImGuiMod_Shift, true);
        if (key == ImGuiKey_LeftSuper || key == ImGuiKey_RightSuper)
            io.AddKeyEvent(ImGuiMod_Super, true);

        io.AddKeyEvent(key, true);

        if (io.WantCaptureKeyboard)
            return true;
        return false;
    }

    bool ImGuiLayer::OnKeyReleaseEvent(KeyReleaseEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGuiKey key = PtlToImGuiKeyCode(event.GetKeyCode());

        // Deactivate modifier keys
        if (key == ImGuiKey_LeftAlt || key == ImGuiKey_RightAlt)
            io.AddKeyEvent(ImGuiMod_Alt, false);
        if (key == ImGuiKey_LeftCtrl || key == ImGuiKey_RightCtrl)
            io.AddKeyEvent(ImGuiMod_Ctrl, false);
        if (key == ImGuiKey_LeftShift || key == ImGuiKey_RightShift)
            io.AddKeyEvent(ImGuiMod_Shift, false);
        if (key == ImGuiKey_LeftSuper || key == ImGuiKey_RightSuper)
            io.AddKeyEvent(ImGuiMod_Super, false);

        io.AddKeyEvent(PtlToImGuiKeyCode(event.GetKeyCode()), false);

        if (io.WantCaptureKeyboard)
            return true;
        return false;
    }

    bool ImGuiLayer::OnKeyTypeEvent(KeyTypeEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        int16_t key = (int16_t)event.GetKeyCode();
        if (key > 0 && key < 0x1000)
            io.AddInputCharacter(key);

        if (io.WantTextInput)
            return true;
        return false;
    }

    bool ImGuiLayer::OnMouseButtonPressEvent(MouseButtonPressEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGuiMouseButton button = PtlToImGuiMouseButtonCode(event.GetMouseButton());

        if (button != -1)
            io.AddMouseButtonEvent(button, true);

        if (io.WantCaptureMouse)
            return true;
        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleaseEvent(MouseButtonReleaseEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGuiMouseButton button = PtlToImGuiMouseButtonCode(event.GetMouseButton());

        if (button != -1)
            io.AddMouseButtonEvent(button, false);

        if (io.WantCaptureMouse)
            return true;
        return false;
    }

    bool ImGuiLayer::OnMouseMoveEvent(MouseMoveEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMousePosEvent(event.GetXPos(), event.GetYPos());

        if (io.WantCaptureMouse)
            return true;
        return false;
    }

    bool ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseWheelEvent(event.GetXOffset(), event.GetYOffset());

        if (io.WantCaptureMouse)
            return true;
        return false;
    }

    ImGuiKey ImGuiLayer::PtlToImGuiKeyCode(KeyCode keyCode)
    {
        switch (keyCode)
        {
            case KeyCode::TAB: return ImGuiKey_Tab;
            case KeyCode::LEFT: return ImGuiKey_LeftArrow;
            case KeyCode::RIGHT: return ImGuiKey_RightArrow;
            case KeyCode::UP: return ImGuiKey_UpArrow;
            case KeyCode::DOWN: return ImGuiKey_DownArrow;
            case KeyCode::PAGE_UP: return ImGuiKey_PageUp;
            case KeyCode::PAGE_DOWN: return ImGuiKey_PageDown;
            case KeyCode::HOME: return ImGuiKey_Home;
            case KeyCode::END: return ImGuiKey_End;
            case KeyCode::INSERT: return ImGuiKey_Insert;
            case KeyCode::_DELETE: return ImGuiKey_Delete;
            case KeyCode::BACKSPACE: return ImGuiKey_Backspace;
            case KeyCode::SPACE: return ImGuiKey_Space;
            case KeyCode::ENTER: return ImGuiKey_Enter;
            case KeyCode::ESCAPE: return ImGuiKey_Escape;
            case KeyCode::APOSTROPHE: return ImGuiKey_Apostrophe;
            case KeyCode::COMMA: return ImGuiKey_Comma;
            case KeyCode::MINUS: return ImGuiKey_Minus;
            case KeyCode::PERIOD: return ImGuiKey_Period;
            case KeyCode::SLASH: return ImGuiKey_Slash;
            case KeyCode::SEMICOLON: return ImGuiKey_Semicolon;
            case KeyCode::EQUAL: return ImGuiKey_Equal;
            case KeyCode::LEFT_BRACKET: return ImGuiKey_LeftBracket;
            case KeyCode::BACKSLASH: return ImGuiKey_Backslash;
            case KeyCode::RIGHT_BRACKET: return ImGuiKey_RightBracket;
            case KeyCode::GRAVE_ACCENT: return ImGuiKey_GraveAccent;
            case KeyCode::CAPS_LOCK: return ImGuiKey_CapsLock;
            case KeyCode::SCROLL_LOCK: return ImGuiKey_ScrollLock;
            case KeyCode::NUM_LOCK: return ImGuiKey_NumLock;
            case KeyCode::PRINT_SCREEN: return ImGuiKey_PrintScreen;
            case KeyCode::PAUSE: return ImGuiKey_Pause;
            case KeyCode::KP_0: return ImGuiKey_Keypad0;
            case KeyCode::KP_1: return ImGuiKey_Keypad1;
            case KeyCode::KP_2: return ImGuiKey_Keypad2;
            case KeyCode::KP_3: return ImGuiKey_Keypad3;
            case KeyCode::KP_4: return ImGuiKey_Keypad4;
            case KeyCode::KP_5: return ImGuiKey_Keypad5;
            case KeyCode::KP_6: return ImGuiKey_Keypad6;
            case KeyCode::KP_7: return ImGuiKey_Keypad7;
            case KeyCode::KP_8: return ImGuiKey_Keypad8;
            case KeyCode::KP_9: return ImGuiKey_Keypad9;
            case KeyCode::KP_DECIMAL: return ImGuiKey_KeypadDecimal;
            case KeyCode::KP_DIVIDE: return ImGuiKey_KeypadDivide;
            case KeyCode::KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
            case KeyCode::KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
            case KeyCode::KP_ADD: return ImGuiKey_KeypadAdd;
            case KeyCode::KP_ENTER: return ImGuiKey_KeypadEnter;
            case KeyCode::KP_EQUAL: return ImGuiKey_KeypadEqual;
            case KeyCode::LEFT_SHIFT: return ImGuiKey_LeftShift;
            case KeyCode::LEFT_CONTROL: return ImGuiKey_LeftCtrl;
            case KeyCode::LEFT_ALT: return ImGuiKey_LeftAlt;
            case KeyCode::LEFT_SUPER: return ImGuiKey_LeftSuper;
            case KeyCode::RIGHT_SHIFT: return ImGuiKey_RightShift;
            case KeyCode::RIGHT_CONTROL: return ImGuiKey_RightCtrl;
            case KeyCode::RIGHT_ALT: return ImGuiKey_RightAlt;
            case KeyCode::RIGHT_SUPER: return ImGuiKey_RightSuper;
            case KeyCode::MENU: return ImGuiKey_Menu;
            case KeyCode::_0: return ImGuiKey_0;
            case KeyCode::_1: return ImGuiKey_1;
            case KeyCode::_2: return ImGuiKey_2;
            case KeyCode::_3: return ImGuiKey_3;
            case KeyCode::_4: return ImGuiKey_4;
            case KeyCode::_5: return ImGuiKey_5;
            case KeyCode::_6: return ImGuiKey_6;
            case KeyCode::_7: return ImGuiKey_7;
            case KeyCode::_8: return ImGuiKey_8;
            case KeyCode::_9: return ImGuiKey_9;
            case KeyCode::A: return ImGuiKey_A;
            case KeyCode::B: return ImGuiKey_B;
            case KeyCode::C: return ImGuiKey_C;
            case KeyCode::D: return ImGuiKey_D;
            case KeyCode::E: return ImGuiKey_E;
            case KeyCode::F: return ImGuiKey_F;
            case KeyCode::G: return ImGuiKey_G;
            case KeyCode::H: return ImGuiKey_H;
            case KeyCode::I: return ImGuiKey_I;
            case KeyCode::J: return ImGuiKey_J;
            case KeyCode::K: return ImGuiKey_K;
            case KeyCode::L: return ImGuiKey_L;
            case KeyCode::M: return ImGuiKey_M;
            case KeyCode::N: return ImGuiKey_N;
            case KeyCode::O: return ImGuiKey_O;
            case KeyCode::P: return ImGuiKey_P;
            case KeyCode::Q: return ImGuiKey_Q;
            case KeyCode::R: return ImGuiKey_R;
            case KeyCode::S: return ImGuiKey_S;
            case KeyCode::T: return ImGuiKey_T;
            case KeyCode::U: return ImGuiKey_U;
            case KeyCode::V: return ImGuiKey_V;
            case KeyCode::W: return ImGuiKey_W;
            case KeyCode::X: return ImGuiKey_X;
            case KeyCode::Y: return ImGuiKey_Y;
            case KeyCode::Z: return ImGuiKey_Z;
            case KeyCode::F1: return ImGuiKey_F1;
            case KeyCode::F2: return ImGuiKey_F2;
            case KeyCode::F3: return ImGuiKey_F3;
            case KeyCode::F4: return ImGuiKey_F4;
            case KeyCode::F5: return ImGuiKey_F5;
            case KeyCode::F6: return ImGuiKey_F6;
            case KeyCode::F7: return ImGuiKey_F7;
            case KeyCode::F8: return ImGuiKey_F8;
            case KeyCode::F9: return ImGuiKey_F9;
            case KeyCode::F10: return ImGuiKey_F10;
            case KeyCode::F11: return ImGuiKey_F11;
            case KeyCode::F12: return ImGuiKey_F12;
            default: return ImGuiKey_None;
        }
    }
    ImGuiMouseButton ImGuiLayer::PtlToImGuiMouseButtonCode(MouseButtonCode button)
    {
        switch (button)
        {
            case MouseButtonCode::_1: return ImGuiMouseButton_Left;
            case MouseButtonCode::_2: return ImGuiMouseButton_Right;
            case MouseButtonCode::_3: return ImGuiMouseButton_Middle;
            default: return -1;
        }
    }
}
