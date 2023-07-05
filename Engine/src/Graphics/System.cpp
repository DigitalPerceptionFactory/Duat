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
			D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG,
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
		InitRenderTargets();

		m_Context.SetClearColor( 0,0,0,0 );
	}

	void System::Update()
	{
		for (auto& rt : m_RT) m_Context.ClearRT(rt.second);

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
				SetVP(pass.second[0].cam);
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

	size_t System::AddDrawCall(Geometry::Mesh* mesh, const std::string& vs, const std::string& ps, const std::string& cam, const Topology& tp, const std::string& bs, const std::string& rs)
	{
		DrawCall dc;
		dc.rt = m_Cameras[cam].GetRT();
		dc.cam = cam;
		dc.vs = vs;
		dc.ps = ps;
		dc.bs = bs;
		dc.rs = rs;
		dc.tp = tp;

		HLSL::Layout vbLayout("VertexBuffer");
		for (int i = 0; i < mesh->GetVertices().size(); ++i)
		{
			vbLayout[i] = HLSL::Struct(
				{
					HLSL::Assign(mesh->GetVertices()[i].position),
					HLSL::Assign(mesh->GetVertices()[i].texCoord),
					HLSL::Assign(mesh->GetVertices()[i].color),
					HLSL::Assign(mesh->GetVertices()[i].normal)
				}
			);
		}

		HLSL::Layout ibLayout("IndexBuffer");
		for (int i = 0; i < mesh->GetIndices().size(); ++i)
			ibLayout[i] = (int)(mesh->GetIndices()[i]);

		dc.vb.Init(this, vbLayout);
		dc.ib.Init(this, ibLayout);
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

	void System::AddCamera(const std::string& cameraName, const std::string& rtName, UINT topLeftX, UINT topLeftY, UINT width, UINT height)
	{
		if (m_RT.count(rtName) <= 0) {
			m_result << "Render target \"" + rtName + "\" doesn't exist.";
			return;
		}

		if (width == 0) width = m_RT[rtName].GetWidth();
		if (height == 0) height = m_RT[rtName].GetHeight();
		m_Cameras[cameraName].Init(rtName, topLeftX, topLeftY, width, height);
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

	void System::InitRenderTargets()
	{
		m_RT["Default"].Init(this, m_Context.GetBackBuffer());
		AddCamera("Default", "Default");
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
	}

	void System::SetTP(const Topology& topology)
	{
		m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY(topology));
	}

	void System::SetDSS(const std::string& name)
	{
		m_Context->OMSetDepthStencilState(m_DSS[name].Get(), 0);
	}

	void System::SetVP(const std::string& cameraName)
	{
		SetVP(m_Cameras[cameraName].GetViewports());
	}

	void System::SetVP(const D3D11_VIEWPORT& viewport)
	{
		m_Context->RSSetViewports(1, &viewport);
	}

	void System::SetVP(const std::vector<D3D11_VIEWPORT>& viewports)
	{
		m_Context->RSSetViewports(viewports.size(), &viewports[0]);
	}
		
	std::string System::DrawCall::GetKey()
	{
		return rt + vs + ps + rs + bs + cam + std::to_string((int)tp);
	}

}