#pragma once
#include <vector>
#include <algorithm>

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

        void Init(GLFWwindow* window);

    private:
        std::vector<UIState> stack;

        GLFWwindow* m_Window = nullptr;

        void RenderMainMenu();
        void RenderOptions();
        void RenderHUD();
};
