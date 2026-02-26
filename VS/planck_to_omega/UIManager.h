#pragma once
#include <vector>
#include <algorithm>
#include "Camera.h"

struct GLFWwindow;

enum class UIState
{
    MainMenu,
    Options,
    HUD
};

class UIManager
{
    public:
        void Push(UIState state);
        void Pop();
        void Clear();
        bool HasState(UIState state);

        void Render();

        bool Empty() const;

        void SetFPS(int fps);

        void Init(GLFWwindow* window, Camera* cam);

        float volume = 0.5f;
        bool showFPS = true;
        bool isFullscreen = true;
    private:
        std::vector<UIState> stack;

        GLFWwindow* m_Window = nullptr;
        Camera* camera = nullptr;

        void RenderMainMenu();
        void RenderOptions();
        void RenderHUD();

        void ToggleFullscreen();
};
