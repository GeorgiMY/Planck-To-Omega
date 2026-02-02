#include "UIManager.h"
#include <imgui.h>

char fpsText[5 + sizeof(int) * 8] = "FPS: ";

void UIManager::Push(UIState state)
{
    if (!HasStateExceptLast(state)) stack.push_back(state);
}

void UIManager::Pop()
{
    if (!stack.empty()) stack.pop_back();
}

void UIManager::Clear()
{
    stack.clear();
}

bool UIManager::HasStateExceptLast(UIState state) const
{
    return std::find(stack.begin(), stack.end(), state) != stack.end();
}

//bool UIManager::HasState(UIState state) const
//{
//    //return std::find(stack.begin(), stack.end(), state);
//}

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
        case UIState::Pause:
            RenderPause();
            break;
        case UIState::HUD:
            RenderHUD();
            break;
        }
    }
}

void UIManager::RenderMainMenu()
{
    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoResize);

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
        //glfwSetWindowShouldClose(window, true);
    }

    ImGui::End();
}

void UIManager::RenderOptions()
{
    ImGui::Begin("Options");

    static float volume = 0.5f;
    static bool fullscreen = false;

    ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f);
    ImGui::Checkbox("Fullscreen", &fullscreen);

    if (ImGui::Button("Back")) Pop();

    ImGui::End();
}

void UIManager::RenderPause()
{
    ImGui::Begin("Paused");

    if (ImGui::Button("Resume"))
        Pop();

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
    ImGui::SetNextWindowSize(ImVec2(160, 120));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    ImVec2 textSize = ImGui::CalcTextSize(fpsText);
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2 - textSize.x, ImGui::GetWindowHeight() / 2 - textSize.y));
    ImGui::Text(fpsText);

    ImGui::End();

    // Random test window
    ImGui::SetNextWindowSize(ImVec2(640, 480));
    ImGui::SetNextWindowPos(ImVec2(500, 500));
    ImGui::Begin("Planck To Omega Initial!", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    ImGui::Text("Gameplay HUD");
    ImGui::Text("Press ESC to pause");

    ImGui::End();
}
