#include "Texture2DArray.h"

/*
namespace Duat::Graphics {

	void Texture2DArray::Init(System& gfx, size_t arraySize, const Texture2D& tex2DTemplate)
	{
		Init(&gfx, arraySize, tex2DTemplate);
	}

	void Texture2DArray::Init(System* pGFX, size_t arraySize, const Texture2D& tex2DTemplate)
	{
        D3D11_TEXTURE2D_DESC texDesc;
        ZeroMemory(&texDesc, sizeof(texDesc));

        // Get the description from one of the textures (assuming all textures are the same)
        textures[0]->GetDesc(&texDesc);

        // Update description for Texture2DArray
        texDesc.ArraySize = static_cast<UINT>(textures.size());
        texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        texDesc.MiscFlags = 0;
        texDesc.MipLevels = 1;
        texDesc.SampleDesc.Count = 1;
        texDesc.SampleDesc.Quality = 0;
        texDesc.Usage = D3D11_USAGE_DEFAULT;

        ID3D11Texture2D* texture2DArray = nullptr;
        HRESULT hr = device->CreateTexture2D(&texDesc, nullptr, &texture2DArray);
        if (FAILED(hr))
        {
            // Handle error
            return nullptr;
        }

        // Copy the data from individual textures to the array
        for (UINT i = 0; i < textures.size(); ++i)
        {
            // Use the ID3D11DeviceContext::CopySubresourceRegion method to copy each texture to the array
            device->GetImmediateContext()->CopySubresourceRegion(
                texture2DArray,
                i, // Destination subresource (index of the array slice)
                0, 0, 0, // Destination position (x, y, z)
                textures[i],
                0, // Source subresource (index of the mipmap level)
                nullptr
            );
        }

        return texture2DArray
	}

}*/