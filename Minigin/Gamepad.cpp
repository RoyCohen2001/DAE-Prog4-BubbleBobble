#include "Gamepad.h"
#include <XInput.h>

namespace dae {
    class Gamepad::Impl {
    public:
        Impl(int idx) :
            m_ControllerIndex(idx)
        {
            ZeroMemory(&m_State, sizeof(m_State));
            ZeroMemory(&m_PreviousState, sizeof(m_PreviousState));
        }

        void Update()
        {
            m_PreviousState = m_State;
            XInputGetState(m_ControllerIndex, &m_State);
        }

        bool IsPressed(Button button) const
        {
            return m_State.Gamepad.wButtons & static_cast<WORD>(button);
        }

        bool IsDownThisFrame(Button button) const
        {
            WORD mask = static_cast<WORD>(button);
            bool wasDown = (m_PreviousState.Gamepad.wButtons & mask) != 0;
            bool isDown = (m_State.Gamepad.wButtons & mask) != 0;
            return !wasDown && isDown;
        }

        bool IsUpThisFrame(Button button) const
        {
            WORD mask = static_cast<WORD>(button);
            bool wasDown = (m_PreviousState.Gamepad.wButtons & mask) != 0;
            bool isDown = (m_State.Gamepad.wButtons & mask) != 0;
            return wasDown && !isDown;
        }
    private:
        int m_ControllerIndex;
        XINPUT_STATE m_State{};
        XINPUT_STATE m_PreviousState{};
    };
    
    
    // PIMPL
    Gamepad::Gamepad(int controllerIndex) :
		m_pImpl(std::make_unique<Impl>(controllerIndex))
    {
    }
    
	void Gamepad::Update()
    {
	    m_pImpl->Update();
    }
	bool Gamepad::IsPressed(Button button) const
    {
        return m_pImpl->IsPressed(button);
    }
	bool Gamepad::IsDownThisFrame(Button button) const
	{
		return m_pImpl->IsDownThisFrame(button);
	}
    bool Gamepad::IsUpThisFrame(Button button) const
    {
	    return m_pImpl->IsUpThisFrame(button);
    }
}
