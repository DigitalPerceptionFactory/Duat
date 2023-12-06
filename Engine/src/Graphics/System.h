#pragma once
#include <map>
#include <Utility/Classes.h>
#include "DeviceEx.h"
#include "ContextEx.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ComputeShader.h"
#include "Texture2D.h"
#include "BlendState.h"
#include "SamplerState.h"
#include "RasterizerState.h"
#include "DepthStencilState.h"
#include "RenderTarget.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "StructuredBuffer.h"
#include <Geometry/Mesh.h>
#include "CompositionEx.h"
#include "Camera.h"
#include "Light.h"
#include "Object3D.h"


namespace Duat::Graphics {

	struct System {
		friend VertexShader;
		friend PixelShader;
		friend ComputeShader;
		friend Texture2D;
		friend VertexBuffer;
		friend IndexBuffer;
		friend ConstantBuffer;
		friend StructuredBuffer;
		friend SamplerState;
		friend RasterizerState;
		friend DepthStencilState;
		friend BlendState;
		friend RenderTarget;
		friend CompositionEx;
		friend Camera;

		void Init(HWND handle);
		void Update();
		void Exit();

		size_t AddDrawCall(const Geometry::Mesh& mesh,
			const std::string& vs = "Default",
			const std::string& ps = "Default",
			const std::string& cam = "Default",
			const Topology& tp = Topology::TriangleList,
			const std::string& bs = "Default",
			const std::string& rs = "Default",
			const std::string& dss = "Default"
		);
		size_t AddDrawCall(const GraphicsObject& object);
		size_t AddDrawCall(const Object3D& object);
		void RemoveDrawCall(size_t uniqueDrawCallIndex);
		void AddCamera(const std::string& name, Camera* pCamera);
		Camera* GetCamera(const std::string& name);
		void AddLight(const std::string& name, Light* pLight);
		Light* GetLight(const std::string& name);
		void RemoveCamera(const std::string& name);
		void AddBuffer(const std::string& name, Utility::HLSL::Layout layout);

		const RenderTarget& GetRT(const std::string& name);

		const RasterizerState& GetRS(const std::string& name) const;
		const RasterizerState& GetActiveRS() const;
		int GetActiveInstanceCount() const;
		int GetActiveCameraIndex() const;
		int GetLightCount() const;
	private:
		void InitShaders();
		void InitTextures();
		void InitStates();
		void InitRenderTargets();
		void InitBuffers();
		void UpdateBuffers();
		void ExecuteRequestQueue();

		void DrawShadows();
		void DrawSolid();
		void DrawTransparent();
		void DrawGizmos();

		struct DrawCall;
		void SetRT(const std::string& name);
		void SetRT(const DrawCall& settings);
		void SetVS(const std::string& name);
		void SetVS(const DrawCall& settings);
		void SetPS(const std::string& name);
		void SetPS(const DrawCall& settings);
		void SetCS(const std::string& name);
		void SetCS(const DrawCall& settings);
		void SetBS(const std::string& name);
		void SetBS(const DrawCall& settings);
		void SetRS(const std::string& name);
		void SetRS(const DrawCall& settings);
		void SetTP(const Topology& topology);
		void SetTP(const DrawCall& settings);
		void SetDSS(const std::string& name);
		void SetDSS(const DrawCall& settings);
		void SetVP(const std::string& cameraName);
		void SetVP(const DrawCall& settings);
		void SetVP(const D3D11_VIEWPORT& viewport);
		void SetVP(const std::vector<D3D11_VIEWPORT>& viewports);
		void SetCB(const std::string& name);
		void SetCB(const DrawCall& settings);
		void SetSS(const std::string& name);

		Utility::Result   m_result;
		Utility::HResult  m_hresult;
		DeviceEx          m_Device;
		ContextEx         m_Context;
		CompositionEx     m_Composition;
		HWND              m_window;
		DXGI_FORMAT       m_format;
		DrawCall*         m_ActiveDrawCall;

		struct DrawCall {
			std::string GetKey();
			std::string rt = "Default";
			std::string vs = "Default";
			std::string ps = "Default";
			std::string bs = "Default";
			std::string rs = "Default";
			std::string dss = "Default";
			std::string cam = "Default";
			Topology tp = Topology::TriangleList;
			VertexBuffer vb;
			IndexBuffer ib;
			std::vector<StructuredBuffer> sbArray;
			size_t instances = 1;
			size_t cameraIndex = -1;
			size_t id;
		};

		enum class RequestType {
			AddCamera, AddLight, RemoveCamera, RemoveLight, AddDrawCall
		};

		struct Request {
			RequestType type;
			int* pData;
			std::string text;
		};

		size_t uniqueDrawCallIndex;
		std::map<std::string, std::map<size_t, DrawCall>> m_drawCalls;
		std::vector<Request> m_requests;
		std::vector<RequestType> m_requestTypes;

		std::map<std::string, VertexShader>                    m_VS;
		std::map<std::string, PixelShader>                     m_PS;
		std::map<std::string, ComputeShader>                   m_CS;
		std::map<std::string, Texture2D>                       m_textures;
		std::map<std::string, BlendState>                      m_BS;
		std::map<std::string, RasterizerState>                 m_RS;
		std::map<std::string, SamplerState>                    m_SS;
		std::map<std::string, DepthStencilState>               m_DSS;
		std::map<std::string, RenderTarget>                    m_RT;
		std::map<std::string, ConstantBuffer>                  m_CB;
		std::map<std::string, StructuredBuffer>                m_SB;
		std::vector<std::pair<std::string, Camera*>>           m_Cameras;
		std::vector<std::pair<std::string, Light*>>           m_Lights;
		Texture2D m_shadowMap;
	};

}