#include "RasterizerState.h"
#include "System.h"


namespace Duat::Graphics {

    RasterizerState::RasterizerState()
    {
        ZeroMemory(&m_desc, sizeof(m_desc));
    }

    HRESULT RasterizerState::Init(System& gfx, D3D11_RASTERIZER_DESC rsDesc, std::vector<D3D11_VIEWPORT> vpDesc)
    {
        return Init(&gfx, rsDesc, vpDesc);
    }

    HRESULT RasterizerState::Init(System* pGFX, D3D11_RASTERIZER_DESC rsDesc, std::vector<D3D11_VIEWPORT> vpDesc)
    {
        m_pGFX = pGFX;
        m_desc = rsDesc;
        m_VPcache = vpDesc;

        return m_pGFX->m_Device->CreateRasterizerState(&m_desc, ReleaseAndGetAddressOf());
    }

    HRESULT RasterizerState::Init(System& gfx, bool isClockwise, Fill fill, Cull cull, float width, float height, float normalizedWidth, float normalizedHeight, float minDepth, float maxDepth, DirectX::XMFLOAT2 ndcPosition)
    {
        return Init(&gfx, isClockwise, fill, cull, width, height, normalizedWidth, normalizedHeight, minDepth, maxDepth, ndcPosition);
    }

    HRESULT RasterizerState::Init(System* pGFX, bool isClockwise, Fill fill, Cull cull, float width, float height, float normalizedWidth, float normalizedHeight, float minDepth, float maxDepth, DirectX::XMFLOAT2 ndcPosition)
    {
        m_pGFX = pGFX;
        m_normalizedWidth[0] = normalizedWidth;
        m_normalizedHeight[0] = normalizedHeight;
        m_viewports[0].MinDepth = minDepth;
        m_viewports[0].MaxDepth = maxDepth;
        m_ndcPosition[0] = ndcPosition;
        m_width[0] = width;
        m_height[0] = height;
        UpdateViewports();

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

    D3D11_VIEWPORT* RasterizerState::GetViewports()
    {
        return m_VPcache.data();
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

    float RasterizerState::GetNormalizedWidth(int viewportIndex) const
    {
        return m_normalizedWidth.at(viewportIndex);
    }

    float RasterizerState::GetNormalizedHeight(int viewportIndex) const
    {
        return m_normalizedHeight.at(viewportIndex);
    }

    float RasterizerState::GetMinDepth(int viewportIndex) const
    {
        return m_viewports.at(viewportIndex).MinDepth;
    }

    float RasterizerState::GetMaxDepth(int viewportIndex) const
    {
        return m_viewports.at(viewportIndex).MaxDepth;
    }

    DirectX::XMFLOAT2 RasterizerState::GetNDCPosition(int viewportIndex) const
    {
        return m_ndcPosition.at(viewportIndex);
    }

    float RasterizerState::GetWidth(int viewportIndex) const
    {
        return m_width.at(viewportIndex);
    }

    float RasterizerState::GetHeight(int viewportIndex) const
    {
        return m_height.at(viewportIndex);
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

    void RasterizerState::SetNormalizedWidth(float normalizedWidth, int viewportIndex)
    {
        m_normalizedWidth[viewportIndex] = std::clamp(normalizedWidth, 0.0f, 1.0f);;
        UpdateViewports();
    }

    void RasterizerState::SetNormalizedHeight(float normalizedHeight, int viewportIndex)
    {
        m_normalizedHeight[viewportIndex] = std::clamp(normalizedHeight, 0.0f, 1.0f);
        UpdateViewports();
    }

    void RasterizerState::SetMinDepth(float minDepth, int viewportIndex)
    {
        m_viewports[viewportIndex].MinDepth = minDepth;
    }

    void RasterizerState::SetMaxDepth(float maxDepth, int viewportIndex)
    {
        m_viewports[viewportIndex].MaxDepth = maxDepth;
    }

    void RasterizerState::SetNDCPosition(DirectX::XMFLOAT2 ndcPosition, int viewportIndex)
    {
        m_ndcPosition[viewportIndex] = {
            std::clamp(ndcPosition.x, 0.0f, 1.0f),
            std::clamp(ndcPosition.y, 0.0f, 1.0f)
        };
        UpdateViewports();
    }

    void RasterizerState::SetWidth(float width, int viewportIndex)
    {
        m_width[viewportIndex] = width;
        UpdateViewports();
    }

    void RasterizerState::SetHeight(float height, int viewportIndex)
    {
        m_height[viewportIndex] = height;
        UpdateViewports();
    }

    void RasterizerState::SetDepthBias(int bias)
    {
        m_desc.DepthBias = bias;
    }

    void RasterizerState::SetDepthBiasClamp(float depthClamp)
    {
        m_desc.DepthBiasClamp = depthClamp;
    }

    void RasterizerState::SetSlopeScaledDepthBias(float slope)
    {
        m_desc.SlopeScaledDepthBias = slope;
    }

    void RasterizerState::SetScissorEnable(bool flag)
    {
        m_desc.ScissorEnable = flag;
    }

    void RasterizerState::SetAntialiasedLineEnable(bool flag)
    {
        m_desc.AntialiasedLineEnable = flag;
    }

    void RasterizerState::SetDepthClipEnable(bool flag)
    {
        m_desc.DepthClipEnable = flag;
    }

    void RasterizerState::UpdateViewports()
    {
        m_VPcache.resize(0);
        for (auto& vp : m_viewports)
        {
            float width = m_width[vp.first];
            float height = m_height[vp.first];
            float normalizedWidth =  m_normalizedWidth[vp.first];
            float normalizedHeight = m_normalizedHeight[vp.first];
            DirectX::XMFLOAT2 ndcPosition = m_ndcPosition[vp.first];

            if (ndcPosition.x + normalizedWidth > 1.0f)
            {
                normalizedWidth += 1.0f - ndcPosition.x + normalizedWidth;
                ndcPosition.x = 1.0f - normalizedWidth;
            }
            else if (ndcPosition.x - normalizedWidth < -1.0f)
            {
                normalizedWidth -= 1.0f + ndcPosition.x - normalizedWidth;
                ndcPosition.x = -1.0f + normalizedWidth;
            }

            if (ndcPosition.y + normalizedHeight > 1.0f)
            {
                normalizedHeight += 1.0f - ndcPosition.y + normalizedHeight;
                ndcPosition.y = 1.0f - normalizedHeight;
            }
            else if (ndcPosition.y - normalizedHeight < -1.0f)
            {
                normalizedHeight -= 1.0f + ndcPosition.y - normalizedHeight;
                ndcPosition.y = -1.0f + normalizedHeight;
            }

            float u = (ndcPosition.x + 1) / 2;
            float v = (ndcPosition.y + 1) / 2;

            vp.second.TopLeftX = u * width - normalizedWidth * width;
            vp.second.TopLeftY = v * height + normalizedHeight * height;
            vp.second.TopLeftX = 0;
            vp.second.TopLeftY = 0;
            vp.second.Width = normalizedWidth * width;
            vp.second.Height = normalizedHeight * height;
            m_VPcache.push_back(vp.second);
        }
    }




}