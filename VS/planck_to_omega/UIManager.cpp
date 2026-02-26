#include "UIManager.h"
#include <imgui.h>
#include <GLFW/glfw3.h>

char fpsText[5 + sizeof(int) * 8] = "FPS: ";

void UIManager::Init(GLFWwindow* window, Camera* cam)
{
    m_Window = window;
    camera = cam;
    ToggleFullscreen();
}

void UIManager::ToggleFullscreen()
{
    if (isFullscreen)
    {
        GLFWmonitor* mon = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(mon);
        glfwSetWindowMonitor(m_Window, mon, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(m_Window, nullptr, 100, 100, 1280, 720, 0);
    }
}

bool UIManager::HasState(UIState state)
{
    return std::find(stack.begin(), stack.end(), state) != stack.end();
}

void UIManager::Push(UIState state)
{
    if (!HasState(state)) stack.push_back(state);
}

void UIManager::Pop()
{
    if (!stack.empty()) stack.pop_back();
}

void UIManager::Clear()
{
    stack.clear();
}

bool UIManager::Empty() const
{
    return stack.empty();
}

void UIManager::SetFPS(int fps)
{
    snprintf(fpsText, sizeof(fpsText), "FPS: %d", fps);
}

void UIManager::Render()
{
    if (stack.empty()) return;

    // Render all UI components
    for (int i = 0; i < stack.size(); i++)
    {
        switch (stack[stack.size() - i - 1])
        {
        case UIState::Options:
            RenderOptions();
            break;
        case UIState::MainMenu:
            RenderMainMenu();
            break;
        case UIState::HUD:
            RenderHUD();
            break;
        }
    }
}

void UIManager::RenderMainMenu()
{
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - 20, ImGui::GetIO().DisplaySize.y - 20));
    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    if (ImGui::Button("Play"))
    {
        Clear();
        Push(UIState::HUD);
    }

    if (ImGui::Button("Options"))
    {
        Push(UIState::Options);
    }

    if (ImGui::Button("Quit"))
    {
        if (m_Window) {
            glfwSetWindowShouldClose(m_Window, true);
        }
    }

    ImGui::End();
}

void UIManager::RenderOptions()
{
    ImGui::Begin("Options");

    ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f);

    if(ImGui::Checkbox("Fullscreen", &isFullscreen))
    {
        ToggleFullscreen();
    }

    ImGui::Checkbox("Show FPS", &showFPS);

    if (ImGui::Button("Main Menu"))
    {
        Clear();
        Push(UIState::MainMenu);
    }

    ImGui::End();
}

void UIManager::RenderHUD()
{
    // FPS WINDOW
    if (showFPS) {
        ImVec2 textSize = ImGui::CalcTextSize(fpsText);
        ImGui::SetNextWindowSize(ImVec2(0, 0));
        ImGui::SetNextWindowPos(ImVec2(5, 5));
        ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground);

        ImGui::SetCursorPos(ImVec2(0, 0));

        ImGui::SetWindowFontScale(0.5f);
        ImGui::Text(fpsText);

        ImGui::End();
    }
}
