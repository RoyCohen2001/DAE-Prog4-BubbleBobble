#include "MenuManager.h"
#include <algorithm>
#include "SceneManager.h"

using namespace dae;

void MenuManager::SetOptions(const std::vector<std::shared_ptr<dae::GameObject>>& options)
{
    m_Options = options;
    m_SelectedIndex = 0;
}

void MenuManager::MoveUp()
{
    if (m_Options.empty()) return;
    m_SelectedIndex = (m_SelectedIndex - 1);
}

void MenuManager::MoveDown()
{
    if (m_Options.empty()) return;
    m_SelectedIndex = (m_SelectedIndex + 1);
}

void MenuManager::SetActions(const std::vector<std::function<void()>>& actions)
{
    m_Actions = actions;
}

void MenuManager::Select()
{
    if (m_Actions[m_SelectedIndex]) {
        m_Actions[m_SelectedIndex]();
    }
}

int MenuManager::GetSelectedIndex() const
{
    return m_SelectedIndex;
}

std::shared_ptr<dae::GameObject> MenuManager::GetSelectedOption() const
{
    if (m_Options.empty()) return nullptr;
    return m_Options[m_SelectedIndex];
}
