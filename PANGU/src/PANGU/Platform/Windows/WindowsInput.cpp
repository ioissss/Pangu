#include "pgpch.h"
#include "WindowsInput.h"
#include<GLFW/glfw3.h>

namespace PANGU {
    Input* Input::instance = new WindowsInput();

    bool PANGU::WindowsInput::IsKeyPressedImpl(int keycode)
    {   
        auto window = Application::Get().GetWindow().GetNativeWindow();
        auto state = glfwGetKey(static_cast<GLFWwindow*>(window), keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool PANGU::WindowsInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = Application::Get().GetWindow().GetNativeWindow();
        auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(window), button);
        return state == GLFW_PRESS;
    }

    float PANGU::WindowsInput::GetMouseXImpl()
    {
        auto window = Application::Get().GetWindow().GetNativeWindow();
        double xPos, yPos;
        glfwGetCursorPos(static_cast<GLFWwindow*>(window), &xPos, &yPos);
        return (float)xPos;
    }

    float PANGU::WindowsInput::GetMouseYImpl()
    {
        auto window = Application::Get().GetWindow().GetNativeWindow();
        double xPos, yPos;
        glfwGetCursorPos(static_cast<GLFWwindow*>(window), &xPos, &yPos);
        return (float)yPos;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl()
    {
        auto window = Application::Get().GetWindow().GetNativeWindow();
        double xPos, yPos;
        glfwGetCursorPos(static_cast<GLFWwindow*>(window), &xPos, &yPos);
        return { xPos,yPos };
    }

    
}
