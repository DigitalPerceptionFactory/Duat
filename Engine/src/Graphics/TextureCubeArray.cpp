#include "TextureCubeArray.h"
#include "System.h"


using namespace DirectX;

namespace Duat::Graphics {

	TextureCubeArray::TextureCubeArray()
	{
		m_type = Type::CubeArray;
		m_desc.Width = m_desc.Height = 4096;
		m_desc.Usage = D3D11_USAGE_DEFAULT;
		m_desc.ArraySize = 6;
		m_desc.SampleDesc.Count = 1;
		m_desc.MipLevels = 1;
		m_desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
		m_desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	}

	TextureCubeArray::TextureCubeArray(System& gfx, size_t arraySize, size_t cubeFaceWidth)
		: TextureCubeArray(&gfx, arraySize)
	{
	}

	TextureCubeArray::TextureCubeArray(System* pGFX, size_t arraySize, size_t cubeFaceWidth)
	{
		m_type = Type::CubeArray;
		m_desc.Width = m_desc.Height = cubeFaceWidth;
		m_desc.Usage = D3D11_USAGE_DEFAULT;
		m_desc.ArraySize = 6 * arraySize;
		m_desc.SampleDesc.Count = 1;
		m_desc.MipLevels = 1;
		m_desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
		m_desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

		// resize 7 because [6] is reserved for entire object view (TextureCube View)
		// only SRV since there is no point to create DSV and RTV different than Texture2D
		m_faceSRV.resize(arraySize);
		for (auto& srv : m_faceSRV) srv.resize(6);
		m_faceDSV.resize(arraySize);
		for (auto& dsv : m_faceDSV) dsv.resize(6);
		m_faceRTV.resize(arraySize);
		for (auto& rtv : m_faceRTV) rtv.resize(6);

		Update(pGFX);
	}

	void TextureCubeArray::ForceResize(System& gfx, size_t newSize)
	{
		ForceResize(&gfx, newSize);
	}

	void TextureCubeArray::ForceResize(System* pGFX, size_t newSize)
	{
		// resize 7 because [6] is reserved for entire object view (TextureCube View)
		// only SRV does that because there is no point to create DSV and RTV other than Texture2D
		m_faceSRV.resize(newSize);
		for (auto& srv : m_faceSRV) srv.resize(7);
		m_faceDSV.resize(newSize);
		for (auto& dsv : m_faceDSV) dsv.resize(6);
		m_faceRTV.resize(newSize);
		for (auto& rtv : m_faceRTV) rtv.resize(6);

		m_desc.ArraySize = 6 * newSize;
		m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, nullptr, ReleaseAndGetAddressOf());
		Update(pGFX);
	}

	void TextureCubeArray::ClearDSV(System& gfx, bool clearDepth, float depthValue, bool clearStencil, float stencilValue)
	{
		ClearDSV(&gfx, clearDepth, depthValue, clearStencil, stencilValue);
	}

	void TextureCubeArray::ClearDSV(System* pGFX, bool clearDepth, float depthValue, bool clearStencil, float stencilValue)
	{
		UINT clearFlags = 0;
		if (clearDepth) clearFlags |= D3D11_CLEAR_DEPTH;
		if (clearStencil) clearFlags |= D3D11_CLEAR_STENCIL;

		for (auto& cube : m_faceDSV)
		{
			for (int i = 0; i < 6; ++i)
				pGFX->m_Context->ClearDepthStencilView(cube[i].Get(), clearFlags, depthValue, stencilValue);
		}
	}

	void TextureCubeArray::ClearDSV(System& gfx, size_t dsvIndex, bool clearDepth, float depthValue, bool clearStencil, float stencilValue)
	{
		ClearDSV(&gfx, dsvIndex, clearDepth, depthValue, clearStencil, stencilValue);
	}

	void TextureCubeArray::ClearDSV(System* pGFX, size_t dsvIndex, bool clearDepth, float depthValue, bool clearStencil, float stencilValue)
	{
		UINT clearFlags = 0;
		if (clearDepth) clearFlags |= D3D11_CLEAR_DEPTH;
		if (clearStencil) clearFlags |= D3D11_CLEAR_STENCIL;

		size_t cubeIndex = (float)dsvIndex / 6.0f >= 1.0f ? dsvIndex / 6 : 0;
		size_t faceIndex = dsvIndex % 6;
		pGFX->m_Context->ClearDepthStencilView(m_faceDSV[cubeIndex][faceIndex].Get(), clearFlags, depthValue, stencilValue);
	}

	void TextureCubeArray::ClearRTV(System& gfx, DirectX::XMFLOAT4 color)
	{
		ClearRTV(&gfx, color);
	}

	void TextureCubeArray::ClearRTV(System* pGFX, DirectX::XMFLOAT4 color)
	{
		for (auto& cube : m_faceRTV)
		{
			for (int i = 0; i < 6; ++i)
				pGFX->m_Context->ClearRenderTargetView(cube[i].Get(), (FLOAT*)(&color));
		}
	}

	void TextureCubeArray::Load(System& gfx, const std::filesystem::path& path)
	{
	}

	void TextureCubeArray::Load(System* pGFX, const std::filesystem::path& path)
	{
	}

	void TextureCubeArray::Load(System& gfx, const std::filesystem::path& path, size_t index)
	{
	}

	void TextureCubeArray::Load(System* pGFX, const std::filesystem::path& path, size_t index)
	{
	}

	void TextureCubeArray::Save(System& gfx, const std::filesystem::path& path)
	{
	}

	void TextureCubeArray::Save(System* pGFX, const std::filesystem::path& path)
	{
	}

	void TextureCubeArray::Save(System& gfx, const std::filesystem::path& path, size_t index)
	{
	}

	void TextureCubeArray::Save(System* pGFX, const std::filesystem::path& path, size_t index)
	{
	}

	void TextureCubeArray::Update(System& gfx)
	{
		Update(&gfx);
	}

	void TextureCubeArray::Update(System* pGFX)
	{
		if (!Get())
			m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, nullptr, ReleaseAndGetAddressOf());

		if (m_desc.BindFlags & D3D11_BIND_SHADER_RESOURCE && m_srvFormat != DXGI_FORMAT_UNKNOWN)
		{
			// first step - make srv for entire resource (entire array)
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			ZeroMemory(&srvDesc, sizeof(srvDesc));
			srvDesc.Format = m_srvFormat;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;
			srvDesc.TextureCubeArray.MostDetailedMip = 0;
			srvDesc.TextureCubeArray.MipLevels = 1;
			srvDesc.TextureCubeArray.First2DArrayFace = 0;
			srvDesc.TextureCubeArray.NumCubes = m_faceSRV.size();
			m_hresult << pGFX->m_Device->CreateShaderResourceView(Get(), &srvDesc, m_SRV.ReleaseAndGetAddressOf());

			for (int cubeIndex = 0; cubeIndex < m_faceSRV.size(); ++cubeIndex)
			{
				// second step - make srv for each individual cube in the array (packed as 7th face, in slot [6])
				srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
				srvDesc.TextureCube.MipLevels = -1;
				m_hresult << pGFX->m_Device->CreateShaderResourceView(Get(), &srvDesc,
					m_faceSRV[cubeIndex][6].ReleaseAndGetAddressOf());

				srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
				srvDesc.Texture2DArray.ArraySize = 1;
				srvDesc.Texture2DArray.MipLevels = -1;
				// third step - make srv for each face of each cube
				for (int i = 0; i < 6; ++i)
				{
					srvDesc.Texture2DArray.FirstArraySlice = i + cubeIndex * 6;
					m_hresult << pGFX->m_Device->CreateShaderResourceView(Get(), &srvDesc,
						m_faceSRV[cubeIndex][i].ReleaseAndGetAddressOf());
				}
			}
		}

		if (m_desc.BindFlags & D3D11_BIND_DEPTH_STENCIL && m_dsvFormat != DXGI_FORMAT_UNKNOWN)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
			ZeroMemory(&dsvDesc, sizeof(dsvDesc));
			dsvDesc.Format = m_dsvFormat;
			dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
			dsvDesc.Texture2DArray.ArraySize = 1;
			// making dsv for each face of each cube (dsv for cube or array is useless, because can't be bound to pipeline)
			for (int cubeIndex = 0; cubeIndex < m_faceSRV.size(); ++cubeIndex)
			{
				for (int i = 0; i < 6; ++i)
				{
					dsvDesc.Texture2DArray.FirstArraySlice = i + cubeIndex * 6;
					m_hresult << pGFX->m_Device->CreateDepthStencilView(Get(), &dsvDesc,
						m_faceDSV[cubeIndex][i].ReleaseAndGetAddressOf());
				}
			}
		}

		if (m_desc.BindFlags & D3D11_BIND_RENDER_TARGET && m_rtvFormat != DXGI_FORMAT_UNKNOWN)
		{
			// TextureCubeArray does not support RTV yet.
		}
	}

	ID3D11ShaderResourceView* TextureCubeArray::GetSRV(size_t arrayIndex, size_t faceIndex)
	{
		return m_faceSRV[arrayIndex][faceIndex].Get();
	}

	ID3D11ShaderResourceView** TextureCubeArray::GetSRVAddressOf(size_t arrayIndex, size_t faceIndex)
	{
		return m_faceSRV[arrayIndex][faceIndex].GetAddressOf();
	}

	ID3D11ShaderResourceView** TextureCubeArray::ReleaseSRVAndGetAddressOf(size_t arrayIndex, size_t faceIndex)
	{
		return m_faceSRV[arrayIndex][faceIndex].ReleaseAndGetAddressOf();
	}

	ID3D11DepthStencilView* TextureCubeArray::GetDSV(size_t arrayIndex, size_t faceIndex)
	{
		return m_faceDSV[arrayIndex][faceIndex].Get();
	}

	ID3D11DepthStencilView** TextureCubeArray::GetDSVAddressOf(size_t arrayIndex, size_t faceIndex)
	{
		return m_faceDSV[arrayIndex][faceIndex].GetAddressOf();
	}

	ID3D11DepthStencilView** TextureCubeArray::ReleaseDSVAndGetAddressOf(size_t arrayIndex, size_t faceIndex)
	{
		return m_faceDSV[arrayIndex][faceIndex].ReleaseAndGetAddressOf();
	}

	ID3D11RenderTargetView* TextureCubeArray::GetRTV(size_t arrayIndex, size_t faceIndex)
	{
		return m_faceRTV[arrayIndex][faceIndex].Get();
	}

	ID3D11RenderTargetView** TextureCubeArray::GetRTVAddressOf(size_t arrayIndex, size_t faceIndex)
	{
		return m_faceRTV[arrayIndex][faceIndex].GetAddressOf();
	}

	ID3D11RenderTargetView** TextureCubeArray::ReleaseRTVAndGetAddressOf(size_t arrayIndex, size_t faceIndex)
	{
		return m_faceRTV[arrayIndex][faceIndex].ReleaseAndGetAddressOf();
	}

	void TextureCubeArray::SetWidth(UINT width)
	{
		m_desc.Width = m_desc.Height = width;
	}

	void TextureCubeArray::SetHeight(UINT height)
	{
		m_desc.Width = m_desc.Height = height;
	}

}