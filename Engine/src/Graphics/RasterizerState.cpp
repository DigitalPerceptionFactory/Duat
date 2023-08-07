#include "RasterizerState.h"
#include "System.h"


namespace Duat::Graphics {
        
    HRESULT RasterizerState::Init(System& gfx, bool isClockwise, Fill fill, Cull cull, float width, float height, float normalizedWidth, float normalizedHeight, float minDepth, float maxDepth, DirectX::XMFLOAT2 ndcPosition)
    {
        return Init(&gfx, isClockwise, fill, cull, width, height, normalizedWidth, normalizedHeight, minDepth, maxDepth, ndcPosition);
    }

    HRESULT RasterizerState::Init(System* pGFX, bool isClockwise, Fill fill, Cull cull, float width, float height, float normalizedWidth, float normalizedHeight, float minDepth, float maxDepth, DirectX::XMFLOAT2 ndcPosition)
    {
        m_pGFX = pGFX;
        m_normalizedWidth = normalizedWidth;
        m_normalizedHeight = normalizedHeight;
        m_viewport.MinDepth = minDepth;
        m_viewport.MaxDepth = maxDepth;
        m_ndcPosition = ndcPosition;
        m_width = width;
        m_height = height;
        UpdateViewport();

        ZeroMemory(&m_desc, sizeof(D3D11_RASTERIZER_DESC));
        m_desc.FillMode = D3D11_FILL_MODE(fill);
        m_desc.CullMode = D3D11_CULL_MODE(cull);
        m_desc.FrontCounterClockwise = !isClockwise;

        return m_pGFX->m_Device->CreateRasterizerState(&m_desc, ReleaseAndGetAddressOf());
    }

    HRESULT RasterizerState::Update()
    {
        return m_pGFX->m_Device->CreateRasterizerState(&m_desc, ReleaseAndGetAddressOf());
    }

    D3D11_VIEWPORT* RasterizerState::GetViewport()
    {
        return &m_viewport;
    }

    bool RasterizerState::IsClockwise() const
    {
        return !m_desc.FrontCounterClockwise;
    }

    Fill RasterizerState::GetFill() const
    {
        return Fill(m_desc.FillMode);
    }

    Cull RasterizerState::GetCull() const
    {
        return Cull(m_desc.CullMode);
    }

    float RasterizerState::GetNormalizedWidth() const
    {
        return m_normalizedWidth;
    }

    float RasterizerState::GetNormalizedHeight() const
    {
        return m_normalizedHeight;
    }

    float RasterizerState::GetMinDepth() const
    {
        return m_viewport.MinDepth;
    }

    float RasterizerState::GetMaxDepth() const
    {
        return m_viewport.MaxDepth;
    }

    DirectX::XMFLOAT2 RasterizerState::GetNDCPosition() const
    {
        return m_ndcPosition;
    }

    float RasterizerState::GetWidth() const
    {
        return m_width;
    }

    float RasterizerState::GetHeight() const
    {
        return m_height;
    }

    void RasterizerState::SetClockwise(bool flag)
    {
        m_desc.FrontCounterClockwise = !flag;
    }

    void RasterizerState::SetFill(Fill fill)
    {
        m_desc.FillMode = D3D11_FILL_MODE(fill);
    }

    void RasterizerState::SetCull(Cull cull)
    {
        m_desc.CullMode = D3D11_CULL_MODE(cull);
    }

    void RasterizerState::SetNormalizedWidth(float normalizedWidth)
    {
        m_normalizedWidth = std::clamp(normalizedWidth, 0.0f, 1.0f);;
        UpdateViewport();
    }

    void RasterizerState::SetNormalizedHeight(float normalizedHeight)
    {
        m_normalizedHeight = std::clamp(normalizedHeight, 0.0f, 1.0f);
        UpdateViewport();
    }

    void RasterizerState::SetMinDepth(float minDepth)
    {
        m_viewport.MinDepth = minDepth;
    }

    void RasterizerState::SetMaxDepth(float maxDepth)
    {
        m_viewport.MaxDepth = maxDepth;
    }

    void RasterizerState::SetNDCPosition(DirectX::XMFLOAT2 ndcPosition)
    {
        m_ndcPosition = {
            std::clamp(ndcPosition.x, 0.0f, 1.0f),
            std::clamp(ndcPosition.y, 0.0f, 1.0f)
        };
        UpdateViewport();
    }

    void RasterizerState::SetWidth(float width)
    {
        m_width = width;
        UpdateViewport();
    }

    void RasterizerState::SetHeight(float height)
    {
        m_height = height;
        UpdateViewport();
    }

    void RasterizerState::UpdateViewport()
    {
        if (m_ndcPosition.x + m_normalizedWidth > 1.0f)
        {
            m_normalizedWidth += 1.0f - m_ndcPosition.x + m_normalizedWidth;
            m_ndcPosition.x = 1.0f - m_normalizedWidth;
        }
        else if (m_ndcPosition.x - m_normalizedWidth < -1.0f)
        {
            m_normalizedWidth -= 1.0f + m_ndcPosition.x - m_normalizedWidth;
            m_ndcPosition.x = -1.0f + m_normalizedWidth;
        }

        if (m_ndcPosition.y + m_normalizedHeight> 1.0f)
        {
            m_normalizedHeight += 1.0f - m_ndcPosition.y + m_normalizedHeight;
            m_ndcPosition.y = 1.0f - m_normalizedHeight;
        }
        else if (m_ndcPosition.y - m_normalizedHeight < -1.0f)
        {
            m_normalizedHeight -= 1.0f + m_ndcPosition.y - m_normalizedHeight;
            m_ndcPosition.y = -1.0f + m_normalizedHeight;
        }

        float u = (m_ndcPosition.x + 1) / 2;
        float v = (m_ndcPosition.y + 1) / 2;

        m_viewport.TopLeftX = u * m_width - m_normalizedWidth * m_width;
        m_viewport.TopLeftY = v * m_height + m_normalizedHeight * m_height;
        m_viewport.TopLeftX = 0;
        m_viewport.TopLeftY = 0;
        m_viewport.Width = m_normalizedWidth * m_width;
        m_viewport.Height = m_normalizedHeight * m_height;
    }




}