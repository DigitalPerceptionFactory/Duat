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
		InitBuffers();

		static Camera defaultCamera;
		defaultCamera.Init(this, "Default");
		defaultCamera.SetPosition({ 0, 0, -1 });
		AddCamera("Default", &defaultCamera);
		
		HID::Focus = &defaultCamera;

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
				auto& settings = pass.second[0];
				SetRT(settings);
				SetVS(settings);
				SetPS(settings);
				SetBS(settings);
				SetRS(settings);
				SetTP(settings);
				SetVP(settings);
			}
			for (auto& drawCall : pass.second)
			{
				auto& settings = drawCall.second;
				SetDefaultCB(settings);

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
		if (m_Cameras.count(cam) > 0)
		{
			dc.rt = m_Cameras[cam]->GetRT();
			dc.cam = cam;
		}
		else m_result << "Camera \"" + cam + "\" doesn't exist.";

		if (m_VS.count(vs) > 0) dc.vs = vs;
		else m_result << "VertexShader \"" + vs + "\" doesn't exist.";

		if (m_PS.count(ps) > 0) dc.ps = ps;
		else m_result << "PixelShader \"" + ps + "\" doesn't exist.";

		if (m_BS.count(bs) > 0) dc.bs = bs;
		else m_result << "BlendState \"" + bs + "\" doesn't exist.";

		if (m_RS.count(rs) > 0) dc.rs = rs;
		else m_result << "RasterizerState \"" + rs + "\" doesn't exist.";

		dc.tp = tp;

		HLSL::Layout vbLayout("VertexBuffer");
		vbLayout["Position"] = XMFLOAT4();
		vbLayout["TexCoord"] = XMFLOAT4();
		vbLayout["Color"] = XMFLOAT4();
		vbLayout["Normal"] = XMFLOAT4();
		vbLayout["Shadow"] = XMFLOAT4();
		vbLayout.Replicate(mesh->GetVertices().size());

		for (int i = 0; i < mesh->GetVertices().size(); ++i)
		{
			vbLayout[i]["Position"] = mesh->GetVertices()[i].position;
			vbLayout[i]["TexCoord"] = mesh->GetVertices()[i].texCoord;
			vbLayout[i]["Color"] = mesh->GetVertices()[i].color;
			vbLayout[i]["Normal"] = mesh->GetVertices()[i].normal;

			/*vbLayout[i]["Pos"] = HLSL::Struct(
				{
					HLSL::Assign(mesh->GetVertices()[i].position),
					HLSL::Assign(mesh->GetVertices()[i].texCoord),
					HLSL::Assign(mesh->GetVertices()[i].color),
					HLSL::Assign(mesh->GetVertices()[i].normal),
					HLSL::Assign(XMFLOAT4()),
					HLSL::Assign(XMFLOAT4())
				}
			);*/
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

	void System::AddCamera(const std::string& name, Camera* pCamera)
	{
		if (pCamera == nullptr)
		{
			m_result << "Camera pointer is nullptr";
			return;
		}
		if (m_Cameras.count(name) > 0) {
			m_result << "Camera with name \"" + name + "\" already exists.";
			return;
		}
		
		m_Cameras[name] = pCamera;
	}

	void System::RemoveCamera(const std::string& name)
	{
		m_Cameras.erase(name);
		for (auto& pass : m_drawCalls)
			if (pass.second.size() > 0 && pass.second[0].cam == name) m_drawCalls.erase(pass.first);
	}

	void System::AddBuffer(const std::string& name, Utility::HLSL::Layout layout)
	{
		m_CB[name].Init(this, layout);
	}

	const RenderTarget& System::GetRT(const std::string& name)
	{
		if (m_RT.count(name) > 0) return m_RT[name];
		else m_result << "RenderTarget \"" + name + "\" doesn't exist.";
		
		static RenderTarget nullReference;
		return nullReference;
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
	}

	void System::InitBuffers()
	{
		HLSL::Layout layout;
		layout["DeltaTime"] = HLSL::Function([](){ return (float)Time::DeltaTime; });
		layout["IsClockwise"] = false;
		layout["InstanceCount"] = 1;
		layout["LightCount"] = 1;
		layout["ViewMatrix"] = XMMatrixIdentity();
		layout["ProjectionMatrix"] = XMMatrixIdentity();
		m_CB["Default"].Init(this, layout, 1);

		layout.Reset();
		layout["ModelMatrix"] = XMMatrixIdentity();
		layout.Replicate(100);
		m_SB["Default"].Init(this, layout, 1);

		layout.Reset();
		layout["Position"] = XMFLOAT3(10, 10, 10);
		layout["Intensity"] = 1.0f;
		layout["Direction"] = XMFLOAT3(-1,-1,-1);
		layout["Color"] = XMFLOAT3(1,1,1);
		layout["ViewMatrix"] = XMMatrixIdentity();
		layout["ProjectionMatrix"] = XMMatrixIdentity();
		layout.Replicate(1);
		m_SB["Light"].Init(this, layout, 1);
	}
		
	void System::SetRT(const std::string& name)
	{
		m_Context->OMSetRenderTargets(1, m_RT[name].GetRTVAddressOf(), m_RT[name].GetDSV());
	}

	void System::SetRT(const DrawCall& settings)
	{
		SetRT(settings.rt);
	}

	void System::SetVS(const std::string& name)
	{
		m_Context->VSSetShader(m_VS[name].Get(), 0, 0);
		m_Context->IASetInputLayout(m_VS[name].GetInputLayout());
	}

	void System::SetVS(const DrawCall& settings)
	{
		SetVS(settings.vs);
	}

	void System::SetPS(const std::string& name)
	{
		m_Context->PSSetShader(m_PS[name].Get(), 0, 0);
	}

	void System::SetPS(const DrawCall& settings)
	{
		SetPS(settings.ps);
	}

	void System::SetCS(const std::string& name)
	{
		m_Context->CSSetShader(m_CS[name].Get(), 0, 0);
	}

	void System::SetCS(const DrawCall& settings)
	{
		m_result << "Not implemented yet.";
	}

	void System::SetBS(const std::string& name)
	{
		m_Context->OMSetBlendState(m_BS[name].Get(), NULL, 0xFFFFFFFF);
	}

	void System::SetBS(const DrawCall& settings)
	{
		SetBS(settings.bs);
	}

	void System::SetRS(const std::string& name)
	{
		m_Context->RSSetState(m_RS[name].Get());
	}

	void System::SetRS(const DrawCall& settings)
	{
		SetRS(settings.rs);
	}

	void System::SetTP(const Topology& topology)
	{
		m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY(topology));
	}

	void System::SetTP(const DrawCall& settings)
	{
		SetTP(settings.tp);
	}

	void System::SetDSS(const std::string& name)
	{
		m_Context->OMSetDepthStencilState(m_DSS[name].Get(), 0);
	}

	void System::SetVP(const std::string& cameraName)
	{
		SetVP(m_Cameras[cameraName]->GetViewports());
	}

	void System::SetVP(const DrawCall& settings)
	{
		SetVP(settings.cam);
	}

	void System::SetVP(const D3D11_VIEWPORT& viewport)
	{
		m_Context->RSSetViewports(1, &viewport);
	}

	void System::SetVP(const std::vector<D3D11_VIEWPORT>& viewports)
	{
		m_Context->RSSetViewports(viewports.size(), &viewports[0]);
	}

	void System::SetCB(const std::string& name)
	{
		m_result << "Not implemented yet.";
	}

	void System::SetCB(const DrawCall& settings)
	{
		m_result << "Not implemented yet.";
	}

	void System::SetDefaultCB(const DrawCall& settings)
	{
		m_CB["Default"]["IsClockwise"] = m_RS[settings.rs].IsClockwise();
		m_CB["Default"]["InstanceCount"] = (int)settings.instances;
		m_CB["Default"]["ViewMatrix"] = m_Cameras[settings.cam]->GetViewMatrix();
		m_CB["Default"]["ProjectionMatrix"] = m_Cameras[settings.cam]->GetProjectionMatrix();
		m_CB["Default"].Update();
		m_Context->VSSetConstantBuffers(0, 1, m_CB["Default"].GetAddressOf());
		m_Context->PSSetConstantBuffers(0, 1, m_CB["Default"].GetAddressOf());

		m_SB["Default"][HLSL::Index(0)]["ModelMatrix"] = XMMatrixIdentity();
		m_SB["Default"].Update();
		m_Context->VSSetShaderResources(0, 1, m_SB["Default"].GetSRVAddressOf());
		m_Context->PSSetShaderResources(0, 1, m_SB["Default"].GetSRVAddressOf());

		m_Context->VSSetShaderResources(1, 1, m_SB["Light"].GetSRVAddressOf());
		m_Context->PSSetShaderResources(1, 1, m_SB["Light"].GetSRVAddressOf());
	}
		
	std::string System::DrawCall::GetKey()
	{
		return rt + vs + ps + rs + bs + cam + std::to_string((int)tp);
	}

}