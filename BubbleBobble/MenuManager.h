#pragma once
#include <functional>
#include <vector>
#include <memory>
#include "Singleton.h"


namespace dae {
    class GameObject;

    class MenuManager : public Singleton<MenuManager>
    {
    public:
        void SetOptions(const std::vector<std::shared_ptr<dae::GameObject>>& options);
        void SetActions(const std::vector<std::function<void()>>& actions);
        void MoveUp();
        void MoveDown();
        void Select();

        int GetSelectedIndex() const;
        std::shared_ptr<dae::GameObject> GetSelectedOption() const;

    private:
        friend class Singleton<MenuManager>;

        std::vector<std::shared_ptr<dae::GameObject>> m_Options;
        std::vector<std::function<void()>> m_Actions{};
        int m_SelectedIndex{ 0 };
    };
}


