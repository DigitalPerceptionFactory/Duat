#include "CompositionEx.h"
#include "System.h"


namespace Duat::Graphics {

	void CompositionEx::Init(System& gfx)
	{
		Init(&gfx);
	}

	void CompositionEx::Init(System* pGFX)
	{
		m_hresult << DCompositionCreateDevice(pGFX->m_Device.AsDXGI(), __uuidof(IDCompositionDevice), (void**)GetAddressOf());
		m_hresult << Get()->CreateTargetForHwnd(pGFX->m_window, true, m_target.GetAddressOf());
		m_hresult << Get()->CreateVisual(m_visual.GetAddressOf());
		m_hresult << m_visual->SetContent(pGFX->m_Context.GetSwapChain());
		m_hresult << m_target->SetRoot(m_visual.Get());
		m_hresult << Get()->Commit();
	}

}