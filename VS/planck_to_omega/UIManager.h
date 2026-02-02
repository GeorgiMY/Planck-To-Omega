#pragma once
#include <vector>
#include <algorithm>

enum class UIState
{
    MainMenu,
    Options,
    Pause,
    HUD
};

class UIManager
{
    public:
        void Push(UIState state);
        void Pop();
        void Clear();
        bool HasStateExceptLast(UIState state) const;
        //bool HasState(UIState state) const;

        void Render();

        bool Empty() const;

        void SetFPS(int fps);
        

    private:
        std::vector<UIState> stack;

        void RenderMainMenu();
        void RenderOptions();
        void RenderPause();
        void RenderHUD();
};
