#include "EnumWrappers.h"

TextureFiltering::TextureFiltering(Filter min_mag_mip, FilterMode mode)
{
	filter = {};
	Set(min_mag_mip, mode);
}

TextureFiltering::TextureFiltering(Filter min, Filter mag, Filter mip, FilterMode mode)
{
	filter = {};
	Set(min, mag, mip, mode);
}

D3D11_FILTER TextureFiltering::GetFilter()
{
	return filter;
}

Filter TextureFiltering::GetMin()
{
	return min;
}

Filter TextureFiltering::GetMag()
{
	return mag;
}

Filter TextureFiltering::GetMip()
{
	return mip;
}

void TextureFiltering::SetMin(Filter min)
{
	Set(min, this->mag, this->mip, this->mode);
}

void TextureFiltering::SetMag(Filter mag)
{
	Set(this->min, mag, this->mip, this->mode);
}

void TextureFiltering::SetMip(Filter mip)
{
	Set(this->min, this->mag, mip, this->mode);
}

void TextureFiltering::SetMode(FilterMode mode)
{
	Set(this->min, this->mag, this->mip, mode);
}

void TextureFiltering::Set(Filter min_mag_mip, FilterMode mode)
{
	this->min = min_mag_mip;
	this->mag = min_mag_mip;
	this->mip = min_mag_mip;
	this->mode = mode;

	switch (mode)
	{
	case FilterMode::Default:
		switch (min_mag_mip)
		{
		case Filter::Point: filter = D3D11_FILTER_MIN_MAG_MIP_POINT; break;
		case Filter::Linear: filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; break;
		case Filter::Anisotropic: filter = D3D11_FILTER_ANISOTROPIC; break;
		} break;
	case FilterMode::Minimum:
		switch (min_mag_mip)
		{
		case Filter::Point: filter = D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT;  break;
		case Filter::Linear: filter = D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR; break;
		case Filter::Anisotropic: filter = D3D11_FILTER_MINIMUM_ANISOTROPIC; break;
		} break;
	case FilterMode::Maximum:
		switch (min_mag_mip)
		{
		case Filter::Point: filter = D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT; break;
		case Filter::Linear: filter = D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR; break;
		case Filter::Anisotropic: filter = D3D11_FILTER_MAXIMUM_ANISOTROPIC; break;
		} break;
	case FilterMode::Comparison:
		switch (min_mag_mip)
		{
		case Filter::Point: filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT; break;
		case Filter::Linear: filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR; break;
		case Filter::Anisotropic: filter = D3D11_FILTER_COMPARISON_ANISOTROPIC; break;
		} break;
	}
}

void TextureFiltering::Set(Filter min, Filter mag, Filter mip, FilterMode mode)
{
	this->min = min;
	this->mag = mag;
	this->mip = mip;
	this->mode = mode;

	if (min == Filter::Anisotropic || mag == Filter::Anisotropic || mip == Filter::Anisotropic)
	{
		switch (mode)
		{
		case FilterMode::Default: filter = D3D11_FILTER_ANISOTROPIC; break;
		case FilterMode::Minimum: filter = D3D11_FILTER_MINIMUM_ANISOTROPIC; break;
		case FilterMode::Maximum: filter = D3D11_FILTER_MAXIMUM_ANISOTROPIC; break;
		case FilterMode::Comparison: filter = D3D11_FILTER_COMPARISON_ANISOTROPIC; break;
		}
		return;
	}

	switch (mode)
	{
	case FilterMode::Default:
		switch (min)
		{
		case Filter::Point:
			switch (mag)
			{
			case Filter::Point:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_MIN_MAG_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR; break;
				} break;
			case Filter::Linear:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR; break;
				}  break;
			}  break;
		case Filter::Linear:
			switch (mag)
			{
			case Filter::Point:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR; break;
				}  break;
			case Filter::Linear:
				switch (mip)
				{
				case Filter::Point: D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT; break;
				case Filter::Linear: D3D11_FILTER_MIN_MAG_MIP_LINEAR; break;
				}  break;
			}  break;
		}  break;
	case FilterMode::Minimum:
		switch (min)
		{
		case Filter::Point:
			switch (mag)
			{
			case Filter::Point:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR; break;
				}  break;
			case Filter::Linear:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR; break;
				}  break;
			}  break;
		case Filter::Linear:
			switch (mag)
			{
			case Filter::Point:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR; break;
				}  break;
			case Filter::Linear:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR; break;
				}  break;
			}  break;
		}  break;
	case FilterMode::Maximum:
		switch (min)
		{
		case Filter::Point:
			switch (mag)
			{
			case Filter::Point:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR; break;
				}  break;
			case Filter::Linear:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR; break;
				}  break;
			}
		case Filter::Linear:
			switch (mag)
			{
			case Filter::Point:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR; break;
				}  break;
			case Filter::Linear:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR; break;
				}  break;
			}  break;
		}  break;
	case FilterMode::Comparison:
		switch (min)
		{
		case Filter::Point:
			switch (mag)
			{
			case Filter::Point:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR; break;
				}  break;
			case Filter::Linear:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR; break;
				}  break;
			}  break;
		case Filter::Linear:
			switch (mag)
			{
			case Filter::Point:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR; break;
				}  break;
			case Filter::Linear:
				switch (mip)
				{
				case Filter::Point: filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT; break;
				case Filter::Linear: filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR; break;
				}  break;
			}  break;
		}  break;

	}
}

Stencil::Stencil(StencilOp frontFail, StencilOp frontDepthFail, StencilOp frontPass, Comparison frontComp, StencilOp backFail, StencilOp backDepthFail, StencilOp backPass, Comparison backComp, UINT8 readMask, UINT8 writeMask)
	: frontFail(frontFail), frontDepthFail(frontDepthFail), frontPass(frontPass), frontComp(frontComp),
	backFail(backFail), backDepthFail(backDepthFail), backPass(backPass), backComp(backComp), readMask(readMask), writeMask(writeMask)
{
}

StencilOp Stencil::GetFrontFail()
{
	return frontFail;
}

StencilOp Stencil::GetFrontDepthFail()
{
	return frontDepthFail;
}

StencilOp Stencil::GetFrontPass()
{
	return frontPass;
}

Comparison Stencil::GetFrontComparison()
{
	return frontComp;
}

StencilOp Stencil::GetBackFail()
{
	return backFail;
}

StencilOp Stencil::GetBackDepthFail()
{
	return backDepthFail;
}

StencilOp Stencil::GetBackPass()
{
	return backPass;
}

Comparison Stencil::GetBackComparison()
{
	return backComp;
}

UINT8 Stencil::GetWriteMask()
{
	return writeMask;
}

UINT8 Stencil::GetReadMask()
{
	return readMask;
}

void Stencil::SetFrontFail(StencilOp op)
{
	frontFail = op;
}

void Stencil::SetFrontDepthFail(StencilOp op)
{
	frontDepthFail = op;
}

void Stencil::SetFrontPass(StencilOp op)
{
	frontPass = op;
}

void Stencil::SetFrontComparison(Comparison comp)
{
	frontComp = comp;
}

void Stencil::SetBackFail(StencilOp op)
{
	backFail = op;
}

void Stencil::SetBackDepthFail(StencilOp op)
{
	backDepthFail = op;
}

void Stencil::SetBackPass(StencilOp op)
{
	backPass = op;
}

void Stencil::SetBackComparison(Comparison comp)
{
	backComp = comp;
}

void Stencil::SetWriteMask(UINT8 mask)
{
	writeMask = mask;
}

void Stencil::SetReadMask(UINT8 mask)
{
	readMask = mask;
}

