#include "System.h"


using namespace DirectX;
using namespace Duat::Utility;

namespace Duat::Graphics {

	void System::Init(HWND handle, UINT msaaCount, UINT msaaQuality)
	{
		uniqueDrawCallIndex = 0;
		m_window = handle;
		m_format = DXGI_FORMAT_R16G16B16A16_FLOAT;
		m_MSAACount = msaaCount;
		m_MSAAQuality = msaaQuality;

		m_Device.Init();
		m_Context.Init(handle, m_format);

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

		static DrawCall nullActiveDrawCall;
		m_ActiveDrawCall = &nullActiveDrawCall;

		InitShaders();
		InitTextures();
		InitStates();
		InitRenderTargets();
		InitBuffers();
		InitCameras();
		
		m_Context.SetClearColor(0, 0, 0, 0);
	}

	void System::Update()
	{
		ExecuteRequestQueue();

		for (auto& sb : m_SB) sb.second.Update();

		m_Context->VSSetShaderResources(DEFAULT_RESOURCE_SLOT_OFFSET, 1, m_SB["Cameras"].GetSRVAddressOf());
		m_Context->PSSetShaderResources(DEFAULT_RESOURCE_SLOT_OFFSET, 1, m_SB["Cameras"].GetSRVAddressOf());

		m_Context->VSSetShaderResources(DEFAULT_RESOURCE_SLOT_OFFSET + 1, 1, m_SB["Lights"].GetSRVAddressOf());
		m_Context->PSSetShaderResources(DEFAULT_RESOURCE_SLOT_OFFSET + 1, 1, m_SB["Lights"].GetSRVAddressOf());

		m_Context->PSSetSamplers(0, 1, m_SS["Default"].GetAddressOf());
		//m_Context->PSSetShaderResources(4, 1, m_textures["whatever"].GetSRVAddressOf());

		DrawShadows();
		DrawSolid();
		DrawTransparent();

		m_Context->ResolveSubresource(
			m_Context.GetBackBuffer(), 0, m_RT["Default"].GetTarget().Get(), 0, m_format);
		m_Context.Present();
	}

	void System::Exit()
	{
	}

	void System::SetMSAA(UINT count, UINT quality)
	{
		// must figure out how to rebuild render target at runtime
		m_result << "Not supported yet.";
		m_MSAACount = count;
		m_MSAAQuality = quality;
	}
		
	size_t System::AddDrawCall(const Geometry::Mesh& mesh, const GraphicsObject& object)
	{
		return AddDrawCall(Object3D(this, mesh, object));
	}

	size_t System::AddDrawCall(const Object3D& object)
	{
		Learn(object);

		DrawCall* pDC = new DrawCall();
		pDC->vs = object.GetVS();
		pDC->ps = object.GetPS();
		pDC->bs = object.GetBS();
		pDC->rs = object.GetRS();
		pDC->dss = object.GetDSS();
		pDC->cam = object.GetCamera();
		pDC->tp = object.GetTopology();
		pDC->textures = object.GetTextures();
		// pDC->samplers =
		pDC->instances = 1;
		pDC->id = uniqueDrawCallIndex;

		auto& mesh = static_cast<const Geometry::Mesh>(object);

		HLSL::Layout vbLayout;
		vbLayout["Position"];
		vbLayout["TexCoord"];
		vbLayout["Color"];
		vbLayout["Normal"];
		vbLayout["Shadow"] = XMFLOAT4();
		vbLayout.Replicate(mesh.GetVertices().size());

		for (int i = 0; i < mesh.GetVertices().size(); ++i)
		{
			vbLayout[i]["Position"] = mesh.GetVertices()[i].position;
			vbLayout[i]["TexCoord"] = mesh.GetVertices()[i].texCoord;
			vbLayout[i]["Color"] = mesh.GetVertices()[i].color;
			vbLayout[i]["Normal"] = mesh.GetVertices()[i].normal;
		}

		HLSL::Layout ibLayout;
		for (int i = 0; i < mesh.GetIndices().size(); ++i)
			ibLayout[i] = (int)(mesh.GetIndices()[i]);

		pDC->vb.Init(this, vbLayout);
		pDC->ib.Init(this, ibLayout);

		HLSL::Function fp_getMatrix = HLSL::Function(
			[&object]() -> HLSL::HLSLDataType {
				return object.GetMatrix();
			});

		HLSL::Layout sbLayout;
		sbLayout["Matrix"] = fp_getMatrix;
		sbLayout.Replicate(1);
		StructuredBuffer sb(this, sbLayout, 1);
		pDC->sbArray.push_back(sb);

		Request req;
		req.pData = reinterpret_cast<int*>(pDC);
		req.type = RequestType::AddDrawCall;
		object.GetBS_IsBlendEnabled() ? req.text = "Transparent" : req.text = "";
		m_requests.push_back(req);
		++uniqueDrawCallIndex;
		return uniqueDrawCallIndex - 1;
	}

	void System::RemoveDrawCall(size_t uniqueDrawCallIndex)
	{
		Request req;
		req.type = RequestType::RemoveDrawCall;
		req.pData = new int(uniqueDrawCallIndex);
		m_requests.push_back(req);
	}

	void System::AddCamera(const std::string& name, Camera* pCamera)
	{
		Request req;
		req.text = name;
		req.pData = (int*)pCamera;
		req.type = RequestType::AddCamera;
		m_requests.push_back(req);
	}

	Camera* System::GetCamera(const std::string& name)
	{
		for (const auto& cam : m_Cameras) if (cam.first == name) return cam.second;

		m_result << "Camera with name \"" + name + "\" doesn't exist.";
		return nullptr;
	}

	void System::AddLight(const std::string& name, Light* pLight)
	{
		Request req;
		req.text = name;
		req.pData = reinterpret_cast<int*>(pLight);
		req.type = RequestType::AddLight;
		m_requests.push_back(req);
	}

	Light* System::GetLight(const std::string& name)
	{
		for (const auto& light : m_Lights) if (light.first == name) return light.second;

		m_result << "Light with name \"" + name + "\" doesn't exist.";
		return nullptr;
	}

	void System::RemoveCamera(const std::string& name)
	{
		//m_Cameras.erase(name);
		//for (auto& pass : m_drawCalls)
		//	if (pass.second.size() > 0 && pass.second[0].cam == name) m_drawCalls.erase(pass.first);
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

	const RasterizerState& System::GetRS(const std::string& name) const
	{
		return m_RS.at(name);
	}

	const RasterizerState& System::GetActiveRS() const
	{
		if (m_RS.count(m_ActiveDrawCall->rs) <= 0)
		{
			Utility::Result result;
			result << "There is no RS matching ActiveDrawCall settings.";
		}

		return m_RS.at(m_ActiveDrawCall->rs);
	}

	int System::GetActiveInstanceCount() const
	{
		return m_ActiveDrawCall->instances;
	}

	int System::GetActiveCameraIndex() const
	{
		return m_ActiveDrawCall->cameraIndex;
	}

	int System::GetLightCount() const
	{
		if (m_SB.count("Lights") > 0)
			return m_SB.at("Lights").GetRootElementCount();
		return 0;
	}
		
	void System::InitCameras()
	{
		static Camera defaultCamera;
		defaultCamera.Init(this, "Default");
		defaultCamera.SetPosition({ 0, 0, -5 });
		AddCamera("Default", &defaultCamera);

		HID::Selection = &defaultCamera;
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

					if (shaderType == "_VS") m_VS[just_name].Compile(this, entry.path());
					else if (shaderType == "_PS") m_PS[just_name].Compile(this, entry.path());
					else if (shaderType == "_CS") m_CS[just_name].Compile(this, entry.path());
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

					if (shaderType == "_VS") m_VS[just_name].Load(this, entry.path());
					else if (shaderType == "_PS") m_PS[just_name].Load(this, entry.path());
					else if (shaderType == "_CS") m_CS[just_name].Load(this, entry.path());
				}
			}
		}
	}

	void System::InitTextures()
	{
		std::string tex2Dfolder = "textures2d";
		std::string texCubefolder = "textures3d";

		if (IsDebuggerPresent())
		{
			for (const auto& entry : std::filesystem::directory_iterator("res/" + tex2Dfolder))
			{
				if (entry.is_regular_file())
				{
					std::string name = entry.path().filename().string();
					name = name.substr(0, name.length() - entry.path().extension().string().length());
					m_textures[name].Init(this, entry.path(), TexType::Tex2D);
				}
			}

			for (const auto& entry : std::filesystem::directory_iterator("res/" + texCubefolder))
			{
				if (entry.is_regular_file())
				{
					std::string name = entry.path().filename().string();
					name = name.substr(0, name.length() - entry.path().extension().string().length());
					if (name[name.length() - 1] == '0')
						m_textures[name.substr(0, name.length() - 1)].Init(this, entry.path(), TexType::Cube);
				}
			}
		}
		else
		{
			if (std::filesystem::exists("Resources") && std::filesystem::is_directory("Resources")) {}
			else std::filesystem::create_directory("Resources");

			if (std::filesystem::exists("Resources/" + tex2Dfolder) && std::filesystem::is_directory("Resources/" + tex2Dfolder)) {}
			else std::filesystem::create_directory("Resources/" + tex2Dfolder);

			if (std::filesystem::exists("Resources/" + texCubefolder) && std::filesystem::is_directory("Resources/" + texCubefolder)) {}
			else std::filesystem::create_directory("Resources/" + texCubefolder);

			for (const auto& entry : std::filesystem::directory_iterator("Resources/" + tex2Dfolder))
			{
				if (entry.is_regular_file())
				{
					std::string name = entry.path().filename().string();
					name = name.substr(0, name.length() - entry.path().extension().string().length());
					m_textures[name].Init(this, entry.path(), TexType::Tex2D);
				}
			}

			/*for (const auto& entry : std::filesystem::directory_iterator("Resources/" + texCubefolder))
			{
				if (entry.is_regular_file())
				{
					std::string name = entry.path().filename().string();
					name = name.substr(0, name.length() - entry.path().extension().string().length());
					if(name[name.length() - 1] == '0')
						m_textures[name].Init(this, entry.path(), TexType::Cube);
				}
			}*/
		}
	}

	void System::InitStates()
	{
		GraphicsObject temp;
		Learn(temp);
		m_ActiveDrawCall->bs = temp.GetBS();
		m_ActiveDrawCall->rs = temp.GetRS();
		m_ActiveDrawCall->dss = temp.GetDSS();

		/*
		// Rasterizer States
		m_RS["Default"].Init(this, false, Fill::Solid, Cull::Back,
			GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		m_RS["Billboard"].Init(this, false, Fill::Solid, Cull::Front,
			GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
		m_RS["Expensive"].Init(this, false, Fill::Solid, Cull::None,
			GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

		// Depth Stencil States
		//m_DSS["Default"].Init(this, true, DepthWriteMask::All, Comparison::GreaterEqual);
		m_DSS["Default"].Init(this);
		m_DSS["Always"].Init(this, true, DepthWriteMask::All, Comparison::Always);

		// Blend States
		m_BS["Default"].Init(this);
		m_BS["Disabled"].Init(this, false);
		*/
		// Sampler States
		m_SS["Default"].Init(this);
	}

	void System::InitRenderTargets()
	{
		m_RT["Null"].Init(this, 1, 1, m_format);

		D3D11_TEXTURE2D_DESC desc;
		m_Context.GetBackBuffer()->GetDesc(&desc);
		m_RT["Default"].Init(this, desc);
		m_RT["Default"].SetTargetSample(m_MSAACount, m_MSAAQuality);
		m_RT["Default"].SetDepthSample(m_MSAACount, m_MSAAQuality);
	}

	void System::InitBuffers()
	{

		HLSL::Layout input;
		input["pGFX"] = reinterpret_cast<int*>(this);
		HLSL::Function fp_isClockwise = HLSL::Function(input,
			[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
				System* pGFX = reinterpret_cast<System*>((int*)param["pGFX"]);
				return pGFX->GetActiveRS().IsClockwise();
			}
		);
		HLSL::Function fp_getInstanceCount = HLSL::Function(input,
			[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
				System* pGFX = reinterpret_cast<System*>((int*)param["pGFX"]);
				return pGFX->GetActiveInstanceCount();
			}
		);
		HLSL::Function fp_getLightCount = HLSL::Function(input,
			[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
				System* pGFX = reinterpret_cast<System*>((int*)param["pGFX"]);
				return pGFX->GetLightCount();
			}
		);
		HLSL::Function fp_getCameraIndex = HLSL::Function(input,
			[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
				System* pGFX = reinterpret_cast<System*>((int*)param["pGFX"]);
				return pGFX->GetActiveCameraIndex();
			}
		);

		HLSL::Layout layout;
		layout["DeltaTime"] = HLSL::Function([]() { return (float)Time::DeltaTime; });
		layout["IsClockwise"] = fp_isClockwise;
		layout["InstanceCount"] = fp_getInstanceCount;
		layout["LightCount"] = fp_getLightCount;
		layout["CameraIndex"] = fp_getCameraIndex;
		m_CB["DrawCallBuffer"].Init(this, layout, 1);
	}

	void System::UpdateBuffers()
	{
		for (auto& sb : m_SB)
			sb.second.Update();
	}

	void System::ExecuteRequestQueue()
	{
		if (m_requests.size() != 0)
		{
			// Buffers are immutable so we are taking their Layouts, edit them and recreate StructuredBuffers with them
			HLSL::Layout cameras = m_SB["Cameras"].GetLayout();
			HLSL::Layout lights = m_SB["Lights"].GetLayout();

			if (cameras.GetRootType() == HLSL::Type::Array)
			{
				if (((HLSL::Array)cameras.GetRoot()).elements.size() == 0)
					cameras.GetRoot() = HLSL::Array(0, HLSL::Struct());
			}
			else if (cameras.GetRootType() != HLSL::Type::Array)
				cameras.GetRoot() = HLSL::Array(0, HLSL::Struct());

			if (lights.GetRootType() == HLSL::Type::Array)
			{
				if (((HLSL::Array)lights.GetRoot()).elements.size() == 0)
					lights.GetRoot() = HLSL::Array(0, HLSL::Struct());
			}
			else if (lights.GetRootType() != HLSL::Type::Array)
				lights.GetRoot() = HLSL::Array(0, HLSL::Struct());

			for (auto& req : m_requests)
			{
				switch (req.type)
				{
				case RequestType::AddCamera: {
					if (req.pData == nullptr)
					{
						m_result << "Camera pointer is nullptr";
						break;
					}
					if (std::find_if(m_Cameras.begin(), m_Cameras.end(),
						[&req](const auto& pair) { return pair.first == req.text; }) != m_Cameras.end()) {
						m_result << "Camera with name \"" + req.text + "\" already exists.";
						break;
					}

					HLSL::Layout input(HLSL::Assign(req.pData));
					HLSL::Function fp_getTranslationMatrix = HLSL::Function(input,
						[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
							int* int_ptr = (int*)param.GetRoot();
							return reinterpret_cast<Camera*>(int_ptr)->GetTranslationMatrix();
						});
					HLSL::Function fp_getRotationMatrix = HLSL::Function(input,
						[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
							int* int_ptr = (int*)param.GetRoot();
							return reinterpret_cast<Camera*>(int_ptr)->GetRotationMatrix();
						});
					HLSL::Function fp_getViewMatrix = HLSL::Function(input,
						[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
							int* int_ptr = (int*)param.GetRoot();
							return reinterpret_cast<Camera*>(int_ptr)->GetViewMatrix();
						});
					HLSL::Function fp_getProjMatrix = HLSL::Function(input,
						[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
							int* int_ptr = (int*)param.GetRoot();
							return reinterpret_cast<Camera*>(int_ptr)->GetProjectionMatrix();
						});
					
					// does it make sense ???
					bool cameraExists = false;
					for (auto& cam : m_Cameras)
						if (cam.first == req.text)
						{
							cam.second = reinterpret_cast<Camera*>(req.pData);
							cameraExists = true;
							break;
						}
					if (!cameraExists)
						m_Cameras.push_back({ req.text, reinterpret_cast<Camera*>(req.pData) });

					cameras[req.text]["TranslationMatrix"] = fp_getTranslationMatrix;
					cameras[req.text]["RotationMatrix"] = fp_getRotationMatrix;
					cameras[req.text]["ViewMatrix"] = fp_getViewMatrix;
					cameras[req.text]["ProjectionMatrix"] = fp_getProjMatrix;
					break;
				}
				case RequestType::AddLight: {
					HLSL::Layout input(HLSL::Assign(req.pData));
					HLSL::Function fp_getPosition = HLSL::Function(input,
						[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
							int* int_ptr = (int*)param.GetRoot();
							return reinterpret_cast<Light*>(int_ptr)->GetPosition();
						});
					HLSL::Function fp_getIntensity = HLSL::Function(input,
						[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
							int* int_ptr = (int*)param.GetRoot();
							return reinterpret_cast<Light*>(int_ptr)->GetIntensity();
						});
					HLSL::Function fp_getRotation = HLSL::Function(input,
						[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
							int* int_ptr = (int*)param.GetRoot();
							return reinterpret_cast<Light*>(int_ptr)->GetRotation();
						});
					HLSL::Function fp_getColor = HLSL::Function(input,
						[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
							int* int_ptr = (int*)param.GetRoot();
							return reinterpret_cast<Light*>(int_ptr)->GetColor();
						});
					HLSL::Function fp_getViewMatrix = HLSL::Function(input,
						[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
							int* int_ptr = (int*)param.GetRoot();
							return reinterpret_cast<Light*>(int_ptr)->GetViewMatrix();
						});
					HLSL::Function fp_getProjMatrix = HLSL::Function(input,
						[](HLSL::Buffer& param) -> HLSL::HLSLDataType {
							int* int_ptr = (int*)param.GetRoot();
							return reinterpret_cast<Light*>(int_ptr)->GetProjectionMatrix();
						});

					bool lightExists = false;
					for (auto& light : m_Lights)
						if (light.first == req.text)
						{
							light.second = reinterpret_cast<Light*>(req.pData);
							lightExists = true;
							break;
						}
					if (!lightExists)
						m_Lights.push_back({ req.text, reinterpret_cast<Light*>(req.pData) });

					lights[req.text]["Position"] = fp_getPosition;
					lights[req.text]["Intensity"] = fp_getIntensity;
					lights[req.text]["Rotation"] = fp_getRotation;
					lights[req.text]["Color"] = fp_getColor;
					lights[req.text]["ViewMatrix"] = fp_getViewMatrix;
					lights[req.text]["ProjectionMatrix"] = fp_getProjMatrix;

					D3D11_TEXTURE2D_DESC desc;
					m_Lights[0].second->GetShadowmap().GetDepth().Get()->GetDesc(&desc);
					desc.ArraySize = static_cast<UINT>(m_Lights.size());

					m_shadowMap.Init(this, desc, DXGI_FORMAT_R32_FLOAT, DXGI_FORMAT_D32_FLOAT);
					break;
				}
				case RequestType::RemoveCamera: {
					for (int i = m_Cameras.size() - 1; i >= 0; --i)
						if (m_Cameras[i].first == req.text)
						{
							m_Cameras.erase(m_Cameras.begin() + i);
							for (auto& pass : m_drawCalls)
							{
								if (!pass.second.empty()) {
									// if camera set for that pass is the one we want to remove then erase such pass completely
									if (pass.second.begin()->second.cam == req.text)
										m_drawCalls.erase(pass.first);
									else if (pass.second.begin()->second.cameraIndex > i)
									{
										for (auto& drawCall : pass.second)
											--drawCall.second.cameraIndex;
									}
								}
							}
							break;
						}
					cameras.GetRoot().Erase(req.text);
					break;
				}
				case RequestType::RemoveLight: {
					for (int i = m_Lights.size() - 1; i >= 0; --i)
						if (m_Lights[i].first == req.text)
						{
							m_Lights.erase(m_Lights.begin() + i);
							break;
						}

					lights.GetRoot().Erase(req.text);
					break;
				}
				case RequestType::AddDrawCall: {
					DrawCall* pDC = reinterpret_cast<DrawCall*>(req.pData);

					auto findCamera = std::find_if(m_Cameras.begin(), m_Cameras.end(),
						[pDC](const auto& pair) { return pair.first == pDC->cam; });

					if (findCamera != m_Cameras.end())
					{
						pDC->rt = findCamera->second->GetNameRT();
						pDC->cameraIndex = std::distance(m_Cameras.begin(), findCamera);
					}
					else {
						m_result << "Camera \"" + pDC->cam + "\" doesn't exist.";
						delete pDC;
						break;
					}
					if (m_VS.count(pDC->vs) <= 0)
					{
						m_result << "VertexShader \"" + pDC->vs + "\" doesn't exist.";
						delete pDC;
						break;
					}
					if (m_PS.count(pDC->ps) <= 0)
					{
						m_result << "PixelShader \"" + pDC->ps + "\" doesn't exist.";
						delete pDC;
						break;
					}
					if (m_BS.count(pDC->bs) <= 0)
					{
						m_result << "BlendState \"" + pDC->bs + "\" doesn't exist.";
						delete pDC;
						break;
					}
					if (m_RS.count(pDC->rs) <= 0)
					{
						m_result << "RasterizerState \"" + pDC->rs + "\" doesn't exist.";
						delete pDC;
						break;
					}

					if (req.text == "Transparent")
						m_transparentDrawCalls[pDC->GetKey()][pDC->id] = *pDC;
					else
						m_drawCalls[pDC->GetKey()][pDC->id] = *pDC;
					delete pDC;
					break;
				}
				case RequestType::RemoveDrawCall:
				{
					for (auto& dc : m_drawCalls)
						dc.second.erase(*req.pData);
					for (auto& dc : m_transparentDrawCalls)
						dc.second.erase(*req.pData);
					delete req.pData;
					break;
				}
				}
			}

			// erase from map if buffer is empty
			if (((HLSL::Array)cameras.GetRoot()).elements.size() > 0)
				m_SB["Cameras"].Init(this, cameras, 1);
			else m_SB.erase("Cameras");

			if (((HLSL::Array)lights.GetRoot()).elements.size() > 0)
				m_SB["Lights"].Init(this, lights, 1);
			else m_SB.erase("Lights");

			m_requests.resize(0);
		}
	}

	void System::DrawShadows()
	{
		for (auto& light : m_Lights)
		{
			m_Context->ClearDepthStencilView(light.second->GetShadowmap().GetDepth().GetDSV(),
				D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		}

		SetVS("Shadow");
		UnbindPS();
		UnbindSRV(DEFAULT_BUFFER_SLOT_OFFSET + 2);

		SetDSS("Default");
		for (auto& pass : m_drawCalls)
		{
			if (pass.second.size() != 0)
			{
				auto& settings = pass.second.begin()->second;
				SetBS(settings);
				SetRS(settings);
				SetTP(settings);
				for (auto& drawCall : pass.second)
				{
					m_ActiveDrawCall = &drawCall.second;

					for (int i = 0; i < m_ActiveDrawCall->sbArray.size(); ++i)
					{
						m_ActiveDrawCall->sbArray[i].Update();
						m_Context->VSSetShaderResources(m_SB.size() + 1 + i, 1, m_ActiveDrawCall->sbArray[i].GetSRVAddressOf());
					}

					static UINT offset = 0;
					m_Context->IASetVertexBuffers(0, 1, settings.vb.GetAddressOf(), &settings.vb.GetStride(), &offset);
					m_Context->IASetIndexBuffer(settings.ib.Get(), DXGI_FORMAT_R32_UINT, 0);

					size_t restoreCameraIndex = m_ActiveDrawCall->cameraIndex;
					m_ActiveDrawCall->cameraIndex = 0;
					for (auto& light : m_Lights)
					{
						m_CB["DrawCallBuffer"].Update();
						m_Context->VSSetConstantBuffers(0, 1, m_CB["DrawCallBuffer"].GetAddressOf());

						m_Context->OMSetRenderTargets(1, light.second->GetShadowmap().GetTarget().GetRTVAddressOf(),
							light.second->GetShadowmap().GetDepth().GetDSV());
						m_Context->RSSetViewports(1, light.second->GetViewport());
						m_Context->DrawIndexedInstanced((UINT)settings.ib.GetIndexCount(), (UINT)settings.instances, 0, 0, 0);
						++m_ActiveDrawCall->cameraIndex;
					}
					m_ActiveDrawCall->cameraIndex = restoreCameraIndex;
				}
			}
		}

		m_Context->OMSetRenderTargets(0, nullptr, nullptr);
		m_Context->VSSetShaderResources(DEFAULT_RESOURCE_SLOT_OFFSET + 2, 1, m_Lights[0].second->GetShadowmap().GetDepth().GetSRVAddressOf());
		m_Context->PSSetShaderResources(DEFAULT_RESOURCE_SLOT_OFFSET + 2, 1, m_Lights[0].second->GetShadowmap().GetDepth().GetSRVAddressOf());
	}

	void System::DrawSolid()
	{
		for (auto& rt : m_RT) m_Context.ClearRT(rt.second);

		for (auto& pass : m_drawCalls)
		{
			if (pass.second.size() != 0)
			{
				auto& settings = pass.second.begin()->second;
				SetRT(settings);
				SetVS(settings);
				SetPS(settings);
				SetBS(settings);
				SetRS(settings);
				SetDSS(settings);
				SetTP(settings);
				SetVP(settings);

				for (auto& drawCall : pass.second)
				{
					m_ActiveDrawCall = &drawCall.second;

					m_CB["DrawCallBuffer"].Update();
					m_Context->VSSetConstantBuffers(0, 1, m_CB["DrawCallBuffer"].GetAddressOf());
					m_Context->PSSetConstantBuffers(0, 1, m_CB["DrawCallBuffer"].GetAddressOf());

					SetSRV(m_ActiveDrawCall->sbArray, DEFAULT_RESOURCE_SLOT_OFFSET + 3);

					for (int i = 0; i < m_ActiveDrawCall->samplers.size(); ++i)
					{
						m_Context->PSSetSamplers(i, 1,
							m_SS.at(m_ActiveDrawCall->samplers[i]).GetAddressOf());
					}
					for (int i = 0; i < std::min<size_t>(m_ActiveDrawCall->textures.size(), 10); ++i)
					{
						m_Context->PSSetShaderResources(i, 1, 
							m_textures.at(m_ActiveDrawCall->textures[i]).GetSRVAddressOf());
					}
					
					static UINT offset = 0;
					m_Context->IASetVertexBuffers(0, 1, settings.vb.GetAddressOf(), &settings.vb.GetStride(), &offset);
					m_Context->IASetIndexBuffer(settings.ib.Get(), DXGI_FORMAT_R32_UINT, 0);
					m_Context->DrawIndexedInstanced((UINT)settings.ib.GetIndexCount(), (UINT)settings.instances, 0, 0, 0);
				}
			}
		}
	}

	void System::DrawTransparent()
	{
		for (auto& pass : m_transparentDrawCalls)
		{
			if (pass.second.size() != 0)
			{
				auto& settings = pass.second.begin()->second;
				SetRT(settings);
				SetVS(settings);
				SetPS(settings);
				SetBS(settings);
				SetRS(settings);
				SetDSS(settings);
				SetTP(settings);
				SetVP(settings);

				for (auto& drawCall : pass.second)
				{
					m_ActiveDrawCall = &drawCall.second;

					m_CB["DrawCallBuffer"].Update();
					m_Context->VSSetConstantBuffers(0, 1, m_CB["DrawCallBuffer"].GetAddressOf());
					m_Context->PSSetConstantBuffers(0, 1, m_CB["DrawCallBuffer"].GetAddressOf());

					SetSRV(m_ActiveDrawCall->sbArray, DEFAULT_RESOURCE_SLOT_OFFSET + 3);

					for (int i = 0; i < m_ActiveDrawCall->samplers.size(); ++i)
					{
						m_Context->PSSetSamplers(i, 1,
							m_SS.at(m_ActiveDrawCall->samplers[i]).GetAddressOf());
					}
					for (int i = 0; i < std::min<size_t>(m_ActiveDrawCall->textures.size(), 10); ++i)
					{
						m_Context->PSSetShaderResources(i, 1,
							m_textures.at(m_ActiveDrawCall->textures[i]).GetSRVAddressOf());
					}

					static UINT offset = 0;
					m_Context->IASetVertexBuffers(0, 1, settings.vb.GetAddressOf(), &settings.vb.GetStride(), &offset);
					m_Context->IASetIndexBuffer(settings.ib.Get(), DXGI_FORMAT_R32_UINT, 0);
					m_Context->DrawIndexedInstanced((UINT)settings.ib.GetIndexCount(), (UINT)settings.instances, 0, 0, 0);
				}
			}
		}
	}

	void System::DrawGizmos()
	{
	}

	void System::Learn(const GraphicsObject& object)
	{
		if (m_BS.find(object.GetBS()) == m_BS.end())
			m_BS[object.GetBS()].Init(this, object.GetBS_DESC());
		if (m_DSS.find(object.GetDSS()) == m_DSS.end())
			m_DSS[object.GetDSS()].Init(this, object.GetDSS_DESC());
		if (m_RS.find(object.GetRS()) == m_RS.end())
			m_RS[object.GetRS()].Init(this, object.GetRS_DESC(), object.GetVP_DESC());
	}

	void System::SetRT(const std::string& name)
	{
		m_Context->OMSetRenderTargets(1, m_RT[name].GetTarget().GetRTVAddressOf(),
			m_RT[name].GetDepth().GetDSV());
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

	void System::SetDSS(const DrawCall& settings)
	{
		SetDSS(settings.dss);
	}

	void System::SetVP(const std::string& cameraName)
	{
		for (auto& cam : m_Cameras)
			if (cam.first == cameraName)
				SetVP(cam.second->GetViewports());
	}

	void System::SetVP(const DrawCall& settings)
	{
		SetVP(m_Cameras[settings.cameraIndex].second->GetViewports());
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

	void System::SetSS(const std::string& name)
	{

	}

	void System::SetSRV(std::vector<StructuredBuffer>& resources, size_t offset)
	{
		for (int i = 0; i < resources.size(); ++i)
		{
			m_ActiveDrawCall->sbArray[i].Update();
			m_Context->VSSetShaderResources(offset + i, 1, resources[i].GetSRVAddressOf());
			m_Context->PSSetShaderResources(offset + i, 1, resources[i].GetSRVAddressOf());
		}
	}

	void System::UnbindRT()
	{
		static ID3D11RenderTargetView* nullRTV = nullptr;
		m_Context->OMSetRenderTargets(0, &nullRTV, nullptr);
	}

	void System::UnbindVS()
	{
		m_Context->VSSetShader(nullptr, 0, 0);
	}

	void System::UnbindPS()
	{
		m_Context->PSSetShader(nullptr, 0, 0);
	}

	void System::UnbindSRV(size_t slot)
	{
		static ID3D11ShaderResourceView* nullSRV = nullptr;
		m_Context->VSSetShaderResources(slot, 1, &nullSRV);
		m_Context->PSSetShaderResources(slot, 1, &nullSRV);
	}

	std::string System::DrawCall::GetKey()
	{
		return rt + vs + ps + rs + bs + cam + std::to_string((int)tp);
	}

}