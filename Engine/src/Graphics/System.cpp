#include "System.h"


using namespace DirectX;
using namespace Duat::Utility;

namespace Duat::Graphics {

	void System::Init(HWND handle)
	{
		uniqueDrawCallIndex = 0;
		m_window = handle;

		m_Device.Init();
		m_Context.Init(handle);

		m_hresult << D3D11CreateDevice(
			m_Device.GetAdapter(),
			D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			D3D11_CREATE_DEVICE_BGRA_SUPPORT,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			m_Device.GetAddressOf(),
			nullptr,
			m_Context.GetAddressOf()
		);

		m_hresult << m_Device.DXGI()->CreateSwapChainForComposition(
			m_Device.AsDXGI(), &m_Context.GetSwapChainDesc(), nullptr, m_Context.GetSwapChainAddressOf());

		m_Composition.Init(this);

		InitShaders();
		InitTextures();
		InitStates();
		m_RT["Default"].Init(this, m_Context.GetBackBuffer());
		m_Context.SetClearColor( 0,0,0, 1.0f );
	}

	void System::Update()
	{
		for (auto& rt : m_RT) m_Context.ClearRTV(rt.second);

		SetDSS("Default");
		for (auto& pass : m_drawCalls)
		{
			if (pass.second.size() != 0) 
			{
				SetRT(pass.second[0].rt);
				SetVS(pass.second[0].vs);
				SetPS(pass.second[0].ps);
				SetBS(pass.second[0].bs);
				SetRS(pass.second[0].rs);
				SetTP(pass.second[0].tp);
			}
			for (auto& drawCall : pass.second)
			{
				auto& settings = drawCall.second;

				// to be implemented
				// m_Context->VSSetConstantBuffers();
				// m_Context->PSSetConstantBuffers();
				// m_Context->VSSetShaderResources();
				// m_Context->PSSetShaderResources();

				static UINT offset = 0;
				m_Context->IASetVertexBuffers(0, 1, settings.vb.GetAddressOf(), &settings.vb.GetStride(), &offset);
				m_Context->IASetIndexBuffer(settings.ib.Get(), DXGI_FORMAT_R32_UINT, 0);
				m_Context->DrawIndexedInstanced((UINT)settings.ib.GetIndexCount(), (UINT)settings.instances, 0, 0, 0);
			}
		}
				
		m_Context.Present();
	}

	void System::Exit()
	{
	}

	size_t System::AddDrawCall(Geometry::Mesh* mesh, const std::string& vs, const std::string& ps, const std::string& rt, const Topology& tp, const std::string& bs, const std::string& rs)
	{
		DrawCall dc;
		dc.rt = rt;
		dc.vs = vs;
		dc.ps = ps;
		dc.bs = bs;
		dc.rs = rs;
		dc.tp = tp;
		dc.vb.TestInit(this, (void*)mesh->GetVertices().data(), mesh->GetVertices().size());
		dc.ib.TestInit(this, (void*)mesh->GetIndices().data(), mesh->GetIndices().size());
		dc.id = uniqueDrawCallIndex;

		m_drawCalls[dc.GetKey()][dc.id] = std::move(dc);

		++uniqueDrawCallIndex;
		return uniqueDrawCallIndex - 1;
	}

	void System::RemoveDrawCall(size_t uniqueDrawCallIndex)
	{
		for (auto& dc : m_drawCalls)
			dc.second.erase(uniqueDrawCallIndex);
	}

	void System::InitShaders()
	{
		if (IsDebuggerPresent())
		{
			for (const auto& entry : std::filesystem::directory_iterator("src/Shaders"))
			{
				if (entry.is_regular_file() && entry.path().extension() == ".hlsl")
				{
					std::string name = entry.path().filename().string();
					std::string shaderType = name.substr(name.length() - 8, 3);
					std::string just_name = name.substr(0, name.length() - 8);

					if ( shaderType == "_VS" ) m_VS[just_name].Compile(this, entry.path());
					else if ( shaderType == "_PS" ) m_PS[just_name].Compile(this, entry.path());
					else if ( shaderType == "_CS" ) m_CS[just_name].Compile(this, entry.path());
				}
			}
		}
		else
		{
			if (std::filesystem::exists("Shaders") && std::filesystem::is_directory("Shaders")) {}
			else std::filesystem::create_directory("Shaders");

			for (const auto& entry : std::filesystem::directory_iterator("Shaders"))
			{
				if (entry.is_regular_file() && entry.path().extension() == ".cso")
				{
					std::string name = entry.path().filename().string();
					std::string shaderType = name.substr(name.length() - 7, 3);
					std::string just_name = name.substr(0, name.length() - 7);

					if ( shaderType == "_VS" ) m_VS[just_name].Load(this, entry.path());
					else if ( shaderType == "_PS" ) m_PS[just_name].Load(this, entry.path());
					else if ( shaderType == "_CS" ) m_CS[just_name].Load(this, entry.path());
				}
			}
		}
	}

	void System::InitTextures()
	{
		if (IsDebuggerPresent())
		{
			for (const auto& entry : std::filesystem::directory_iterator("res/textures"))
			{
				if (entry.is_regular_file() && entry.path().extension() == ".cso")
				{
					std::string name = entry.path().filename().string();
					m_textures[name].Init(this, entry.path());
				}
			}
		}
		else
		{
			if (std::filesystem::exists("Textures") && std::filesystem::is_directory("Textures")) {}
			else std::filesystem::create_directory("Textures");

			for (const auto& entry : std::filesystem::directory_iterator("Textures"))
			{
				if (entry.is_regular_file() && entry.path().extension() == ".cso")
				{
					std::string name = entry.path().filename().string();
					m_textures[name].Init(this, entry.path());
				}
			}
		}
	}

	void System::InitStates()
	{
		// Rasterizer States
		m_RS["Default"].Init(this, false, Fill::Solid, Cull::Back, 
			GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		m_RS["Expensive"].Init(this, false, Fill::Solid, Cull::None, 
			GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

		// Depth Stencil States
		m_DSS["Default"].Init(this);

		// Blend States
		m_BS["Default"].Init(this);

		// Sampler States
		m_SS["Default"].Init(this);
	}
		
	void System::SetRT(const std::string& name)
	{
		m_Context->OMSetRenderTargets(1, m_RT[name].GetRTVAddressOf(), m_RT[name].GetDSV());
	}

	void System::SetVS(const std::string& name)
	{
		m_Context->VSSetShader(m_VS[name].Get(), 0, 0);
		m_Context->IASetInputLayout(m_VS[name].GetInputLayout());
	}

	void System::SetPS(const std::string& name)
	{
		m_Context->PSSetShader(m_PS[name].Get(), 0, 0);
	}

	void System::SetCS(const std::string& name)
	{
		m_Context->CSSetShader(m_CS[name].Get(), 0, 0);
	}

	void System::SetBS(const std::string& name)
	{
		m_Context->OMSetBlendState(m_BS[name].Get(), NULL, 0xFFFFFFFF);
	}

	void System::SetRS(const std::string& name)
	{
		m_Context->RSSetState(m_RS[name].Get());
		m_Context->RSSetViewports(1, m_RS[name].GetViewport());
	}

	void System::SetTP(const Topology& topology)
	{
		m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY(topology));
	}

	void System::SetDSS(const std::string& name)
	{
		m_Context->OMSetDepthStencilState(m_DSS[name].Get(), 0);
	}
		
	std::string System::DrawCall::GetKey()
	{
		return rt + vs + ps + rs + bs + std::to_string((int)tp);
	}

}