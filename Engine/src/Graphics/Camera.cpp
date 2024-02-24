#include "Camera.h"
#include "System.h"


using namespace DirectX;

namespace Duat::Graphics {

    void Camera::Init(System& gfx, const std::string& rtName, UINT topLeftX, UINT topLeftY, UINT width, UINT height, float fovAngleY, float nearZ, float farZ)
    {
        Init(&gfx, rtName, topLeftX, topLeftY, width, height, fovAngleY, nearZ, farZ);
    }

    void Camera::Init(System* pGFX, const std::string& rtName, UINT topLeftX, UINT topLeftY, UINT width, UINT height, float fovAngleY, float nearZ, float farZ)
    {
        if (pGFX == nullptr)
        {
            Utility::Result result;
            result << "Graphics System pointer can't be nullptr. Please pass valid pointer.";
            return;
        }
        else m_pGFX = pGFX;

        if (pGFX->m_RT.count(rtName) > 0)
            m_rtName = rtName;
        else
        {
            Utility::Result result;
            result << "RenderTarget \"" + rtName + "\" doesn't exist.";
            return;
        }

        D3D11_VIEWPORT vp;
        vp.TopLeftX = topLeftX;
        vp.TopLeftY = topLeftY;
        vp.Width = width > 0 ? width : pGFX->m_RT[rtName].m_targetTexture.GetWidth();
        vp.Height = height > 0 ? height : pGFX->m_RT[rtName].m_targetTexture.GetHeight();;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        m_viewports.push_back(vp);  

        m_pojectionMatrix = XMMatrixPerspectiveFovLH(
            XMConvertToRadians(fovAngleY), (float)vp.Width / (float)vp.Height, nearZ, farZ
        );

        UpdateViewMatrix();
    }

    void Camera::Interact(Keyboard& kbd, Mouse& mouse)
    {
        if (kbd.IsKeyDown('S'))
            TranslateZ(-m_moveSpeed * (float)Time::DeltaTime);
        if (kbd.IsKeyDown('W'))
            TranslateZ(m_moveSpeed * (float)Time::DeltaTime);
        if (kbd.IsKeyDown('Q'))
            TranslateX(-m_moveSpeed * (float)Time::DeltaTime);
        if (kbd.IsKeyDown('E')) 
            TranslateX(m_moveSpeed * (float)Time::DeltaTime);
        if (kbd.IsKeyDown(VK_SPACE))
            TranslateY(m_moveSpeed * (float)Time::DeltaTime);
        if (kbd.IsKeyDown('Z'))
            TranslateY(-m_moveSpeed * (float)Time::DeltaTime);

        if (mouse.IsRightDown())
        {
            if (kbd.IsKeyDown('A'))
                RotateX(-m_rotationSpeed * (float)Time::DeltaTime);
            if (kbd.IsKeyDown('D'))
                RotateX(m_rotationSpeed * (float)Time::DeltaTime);

            RotateY(mouse.GetRawX() * m_rotationSpeed * (float)Time::DeltaTime);
            RotateX(mouse.GetRawY() * m_rotationSpeed * (float)Time::DeltaTime);
        }
        else
        {
            if (kbd.IsKeyDown('A'))
                RotateY(-20 * m_rotationSpeed * (float)Time::DeltaTime);
            if (kbd.IsKeyDown('D'))
                RotateY(20 * m_rotationSpeed * (float)Time::DeltaTime);
        }
    }

    void Camera::SetRT(const std::string& name)
    {
        // set and bind if rtName was valid name
        if (m_pGFX->m_RT.count(name) > 0) {
            // unbind camera from previous render target
            if (m_rtName != "")
            {
                auto& bound_cameras = m_pGFX->m_RT[m_rtName].m_cameras;
                for (int i = 0; i < bound_cameras.size(); ++i)
                    if (bound_cameras[i] == this) {
                        bound_cameras.erase(bound_cameras.begin() + i);
                        break;
                    }
            }
            m_rtName = name;
            m_pGFX->m_RT[m_rtName].m_cameras.push_back(this);
        }
        else {
            Utility::Result result;
            result << "RenderTarget with name + \"" + name + "\" doesn't exist.";
        }
        
    }

    void Camera::SetFocus(DirectX::XMFLOAT3* pFocus)
    {
        m_focus = pFocus;
    }

    std::string Camera::GetNameRT()
    {
        return m_rtName;
    }

    const std::vector<D3D11_VIEWPORT>& Camera::GetViewports() const
    {
        return m_viewports;
    }

    DirectX::XMMATRIX Camera::GetViewMatrix()
    {
        return m_viewMatrix;
    }

    DirectX::XMMATRIX Camera::GetProjectionMatrix()
    {
        return m_pojectionMatrix;
    }

    DirectX::XMMATRIX Camera::GetMVP(const DirectX::XMMATRIX& modelMatrix)
    {
        return GetProjectionMatrix() * GetViewMatrix() *modelMatrix;
    }

    void Camera::SetProjectionMatrix(float fovAngleY, float aspectRatio, float nearZ, float farZ)
    {
        m_pojectionMatrix = XMMatrixPerspectiveFovLH(
            XMConvertToRadians(fovAngleY), aspectRatio, nearZ, farZ
        );
    }

    void Camera::TransformFF()
    {
        UpdateViewMatrix();
    }

    void Camera::UpdateViewMatrix()
    {
        if (m_focus != nullptr) {
            m_viewMatrix = XMMatrixLookAtLH(GetPosition(), *m_focus, { 0,1,0 });
        }
        else {
            static XMFLOAT3 forward = { 0,0,1 };
            m_viewMatrix = XMMatrixLookAtLH(GetPosition(),
                GetPosition() + XMFloat3Transform(forward, GetRotationMatrix()), 
                {0,1,0});
        }
    }

}