#include "Camera.h"


namespace Duat::Graphics {

    void Camera::Init(const std::string& rtName, UINT topLeftX, UINT topLeftY, UINT width, UINT height)
    {
        m_RT = rtName;
        D3D11_VIEWPORT vp;
        vp.TopLeftX = topLeftX;
        vp.TopLeftY = topLeftY;
        vp.Width = width;
        vp.Height = height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;

        m_viewports.push_back(vp);
    }

    void Camera::SetRT(const std::string& name)
    {
        m_RT = name;
    }

    std::string Camera::GetRT()
    {
        return m_RT;
    }

    const std::vector<D3D11_VIEWPORT>& Camera::GetViewports() const
    {
        return m_viewports;
    }

}