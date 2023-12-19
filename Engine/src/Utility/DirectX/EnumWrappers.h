#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <array>


enum class Fill {
	Solid = D3D11_FILL_SOLID,
	Wireframe = D3D11_FILL_WIREFRAME
};

enum class Cull {
	Back = D3D11_CULL_BACK,
	Front = D3D11_CULL_FRONT,
	None = D3D11_CULL_NONE
};

enum class Usage {
	Default = D3D11_USAGE_DEFAULT,
	Dynamic = D3D11_USAGE_DYNAMIC,
	Immutable = D3D11_USAGE_IMMUTABLE,
	Staging = D3D11_USAGE_STAGING
};

enum class Access {
	None = 0,
	Write = D3D11_CPU_ACCESS_WRITE,
	Read = D3D11_CPU_ACCESS_READ,
	All = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ
};

enum class Blend {
	Zero = D3D11_BLEND_ZERO,
	One = D3D11_BLEND_ONE,
	SrcColor = D3D11_BLEND_SRC_COLOR,
	InvSrcColor = D3D11_BLEND_INV_SRC_COLOR,
	SrcAlpha = D3D11_BLEND_SRC_ALPHA,
	InvSrcAlpha = D3D11_BLEND_INV_SRC_ALPHA,
	DestAlpha = D3D11_BLEND_DEST_ALPHA,
	InvDestAlpha = D3D11_BLEND_INV_DEST_ALPHA,
	DestColor = D3D11_BLEND_DEST_COLOR,
	InvDestColor = D3D11_BLEND_INV_DEST_COLOR,
	SrcAlphaSAT = D3D11_BLEND_SRC_ALPHA_SAT,
	BlenFactor = D3D11_BLEND_BLEND_FACTOR,
	InvBlendFactor = D3D11_BLEND_INV_BLEND_FACTOR,
	Src1Color = D3D11_BLEND_SRC1_COLOR,
	InvSrc1Color = D3D11_BLEND_INV_SRC1_COLOR,
	Src1Alpha = D3D11_BLEND_SRC1_ALPHA,
	InvSrc1Alpha = D3D11_BLEND_INV_SRC1_ALPHA
};

enum class BlendOp {
	Add = D3D11_BLEND_OP_ADD,
	Sub = D3D11_BLEND_OP_SUBTRACT,
	RevSub = D3D11_BLEND_OP_REV_SUBTRACT,
	Min = D3D11_BLEND_OP_MIN,
	Max = D3D11_BLEND_OP_MAX
};

enum class ColorWriteMask {
	EnableAll = D3D11_COLOR_WRITE_ENABLE_ALL,
	EnableAlpha = D3D11_COLOR_WRITE_ENABLE_ALPHA,
	EnableRed = D3D11_COLOR_WRITE_ENABLE_RED,
	EnableGreen = D3D11_COLOR_WRITE_ENABLE_GREEN,
	EnableBlue = D3D11_COLOR_WRITE_ENABLE_BLUE,
	EnableRGB = EnableRed | EnableGreen | EnableBlue
};

enum class DepthWriteMask {
	All = D3D11_DEPTH_WRITE_MASK_ALL,
	None = D3D11_DEPTH_WRITE_MASK_ZERO
};

enum class Comparison {
	Never = D3D11_COMPARISON_NEVER,
	Less = D3D11_COMPARISON_LESS,
	Equal = D3D11_COMPARISON_EQUAL,
	LessEqual = D3D11_COMPARISON_LESS_EQUAL,
	Greater = D3D11_COMPARISON_GREATER,
	NotEqual = D3D11_COMPARISON_NOT_EQUAL,
	GreaterEqual = D3D11_COMPARISON_GREATER_EQUAL,
	Always = D3D11_COMPARISON_ALWAYS,
};

enum class Topology {
	TriangleList = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	TriangleListAdj = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
	TriangleStrip = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
	TriangleStripAdj = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
	LineList = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
	LineListAdj = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
	LineStrip = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
	LineStripAdj = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
	PointList = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
	Undefined = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED
};

enum class Address {
	Wrap = D3D11_TEXTURE_ADDRESS_WRAP,
	Border = D3D11_TEXTURE_ADDRESS_BORDER,
	Clamp = D3D11_TEXTURE_ADDRESS_CLAMP,
	Mirror = D3D11_TEXTURE_ADDRESS_MIRROR,
	MirrorOnce = D3D11_TEXTURE_ADDRESS_MIRROR_ONCE,
};

enum class Filter {
	Linear, Point, Anisotropic
};
enum class FilterMode {
	Default, Minimum, Maximum, Comparison
};
struct TextureFiltering {
	TextureFiltering() = default;
	TextureFiltering(Filter min_mag_mip, FilterMode mode = FilterMode::Default);
	TextureFiltering(Filter min, Filter mag, Filter mip, FilterMode mode = FilterMode::Default);
	D3D11_FILTER GetFilter();
	Filter GetMin();
	Filter GetMag();
	Filter GetMip();
	void SetMin(Filter min);
	void SetMag(Filter mag);
	void SetMip(Filter mip);
	void SetMode(FilterMode mode);
	void Set(Filter min_mag_mip, FilterMode mode = FilterMode::Default);
	void Set(Filter min, Filter mag, Filter mip, FilterMode mode = FilterMode::Default);
private:
	D3D11_FILTER filter;
	Filter min, mag, mip;
	FilterMode mode;
};

enum class StencilOp {
	Keep = D3D11_STENCIL_OP_KEEP,
	Zero = D3D11_STENCIL_OP_ZERO,
	Replace = D3D11_STENCIL_OP_REPLACE,
	IncrSat = D3D11_STENCIL_OP_INCR_SAT,
	DecrSat = D3D11_STENCIL_OP_DECR_SAT,
	Invert = D3D11_STENCIL_OP_INVERT,
	Increment = D3D11_STENCIL_OP_INCR,
	Decrement = D3D11_STENCIL_OP_DECR
};

struct Stencil {
	Stencil() = default;
	Stencil(const D3D11_DEPTH_STENCIL_DESC& desc);
	Stencil(StencilOp frontFail, StencilOp frontDepthFail, StencilOp frontPass, Comparison frontComp,
		StencilOp backFail, StencilOp backDepthFail, StencilOp backPass, Comparison backComp,
		UINT8 readMask = 0xFF, UINT8 writeMask = 0xFF);

	StencilOp GetFrontFail();
	StencilOp GetFrontDepthFail();
	StencilOp GetFrontPass();
	Comparison GetFrontComparison();
	StencilOp GetBackFail();
	StencilOp GetBackDepthFail();
	StencilOp GetBackPass();
	Comparison GetBackComparison();
	UINT8 GetWriteMask();
	UINT8 GetReadMask();

	void Set(const D3D11_DEPTH_STENCIL_DESC& desc);
	void SetFrontFail(StencilOp op);
	void SetFrontDepthFail(StencilOp op);
	void SetFrontPass(StencilOp op);
	void SetFrontComparison(Comparison comp);
	void SetBackFail(StencilOp op);
	void SetBackDepthFail(StencilOp op);
	void SetBackPass(StencilOp op);
	void SetBackComparison(Comparison comp);
	void SetWriteMask(UINT8 mask);
	void SetReadMask(UINT8 mask);

private:
	UINT8 readMask;
	UINT8 writeMask;
	StencilOp frontFail;
	StencilOp frontDepthFail;
	StencilOp frontPass;
	Comparison frontComp;
	StencilOp backFail;
	StencilOp backDepthFail;
	StencilOp backPass;
	Comparison backComp;
};

enum class Scanline {
	Unspecified = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
	Progressive = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE,
	Lower = DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST,
	Upper = DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST
};

enum class DXGIUsage {
	BackBuffer = DXGI_USAGE_BACK_BUFFER,
	Discard = DXGI_USAGE_DISCARD_ON_PRESENT,
	ReadOnly = DXGI_USAGE_READ_ONLY,
	Output = DXGI_USAGE_RENDER_TARGET_OUTPUT,
	Input = DXGI_USAGE_SHADER_INPUT,
	Shared = DXGI_USAGE_SHARED,
	Unordered = DXGI_USAGE_UNORDERED_ACCESS
};

enum class SwapEffect {
	Discard = DXGI_SWAP_EFFECT_DISCARD,
	FlipDiscard = DXGI_SWAP_EFFECT_FLIP_DISCARD,
	Sequential = DXGI_SWAP_EFFECT_SEQUENTIAL,
	FlipSequential = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL
};

enum class Scaling {
	AspectRatioStretch = DXGI_SCALING_ASPECT_RATIO_STRETCH,
	None = DXGI_SCALING_NONE,
	Stretch = DXGI_SCALING_STRETCH
};

enum class ModeScaling {
	Unspecified = DXGI_MODE_SCALING_UNSPECIFIED,
	Centered = DXGI_MODE_SCALING_CENTERED,
	Stretched = DXGI_MODE_SCALING_STRETCHED
};