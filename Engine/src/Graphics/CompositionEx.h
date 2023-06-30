#pragma once
#include <wrl.h>
#include <dcomp.h>
#include <Utility/ErrorHandling.h>


namespace Duat::Graphics {

	struct System;
	struct CompositionEx : public Microsoft::WRL::ComPtr<IDCompositionDevice> {
		void Init(System& gfx);
		void Init(System* pGFX);
	private:
		Utility::HResult m_hresult;
		Microsoft::WRL::ComPtr<IDCompositionTarget> m_target;
		Microsoft::WRL::ComPtr<IDCompositionVisual> m_visual;
	};

}