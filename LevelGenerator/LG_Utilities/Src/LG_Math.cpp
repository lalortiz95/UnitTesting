#include "LG_Math.h"
#include <cmath>
#include <limits>

namespace LevelGenerator
{
	/// TODO: Comentar la clase.
	/// Constant Definitions.
	const float LG_Math::PI = std::atan(1.0f) * 4.0f;
	const float LG_Math::EULERS = (2.71828182845904523536f);
	const float LG_Math::PI_HALF = LG_Math::PI / 2.0f;
	const float LG_Math::PI2 = LG_Math::PI * 2;
	const float LG_Math::INFINITE_NUM = std::numeric_limits<float>::infinity();
	const float LG_Math::DELTA = 0.00001f;
	const float LG_Math::EPSILON = std::numeric_limits<float>::epsilon();
	const float LG_Math::MAX_FLOAT_PRESITION = 0.00000001f;

	LG_Math::LG_Math()
	{
	}

	LG_Math::~LG_Math()
	{
	}

	float LG_Math::Sqrt(float fValue)
	{
		return sqrtf(fValue);
	}

	float LG_Math::InvSqrt(float fValue)
	{
		return 1.0f / sqrtf(fValue);
	}

	float LG_Math::Exp(float fValue)
	{
		return expf(fValue);
	}

	float LG_Math::Pow(float fValueA, float fValueB)
	{
		return powf(fValueA, fValueB);
	}

	float LG_Math::Loge(float fValue)
	{
		return logf(fValue);
	}

	float LG_Math::LogX(float fBase, float fValue)
	{
		return Loge(fValue) / Loge(fBase);
	}

	int32 LG_Math::Trunc(float fValue)
	{
		return (int32)fValue;
	}

	float LG_Math::TruncFloat(float fValue)
	{
		return (float)Trunc(fValue);
	}

	int32 LG_Math::Floor(float fValue)
	{
		return Trunc(floorf(fValue));
	}

	int32 LG_Math::Round(float fValue)
	{
		return Floor(fValue + 0.5f);
	}

	int32 LG_Math::Ceil(float fValue)
	{
		{ return Trunc(ceilf(fValue)); }
	}

	float LG_Math::Sin(float fValue)
	{
		return sinf(fValue);
	}

	float LG_Math::Cos(float fValue)
	{
		return cosf(fValue);
	}

	float LG_Math::Tan(float fValue)
	{
		return tanf(fValue);
	}

	float LG_Math::Asin(float fValue)
	{
		return asinf((fValue < -1.f) ? -1.f : ((fValue < 1.f) ? fValue : 1.f));
	}

	float LG_Math::Acos(float fValue)
	{
		return acosf((fValue < -1.f) ? -1.f : ((fValue < 1.f) ? fValue : 1.f));
	}

	float LG_Math::Atan(float fValue)
	{
		return atanf(fValue);
	}

}