#pragma once
#include "LG_UtilitiesPrerequisites.h"

namespace LevelGenerator
{
	/**
	*	@brief This class is a mathematical library.
	*/
	class LG_UTILITIES_EXPORT LG_Math
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		*	@brief Default Constructor.
		*/
		LG_Math();

		/**
		*	@brief Default Destructor.
		*/
		~LG_Math();

		///**************************************************************************/
		///*						  Member Constants.								*/
		///**************************************************************************/

		/**
		 *	@brief Stores the value of PI.
		 */
		static const float PI;

		/**
		 *	@brief Stores the value of Euler.
		 */
		static const float EULERS;

		/**
		 *	@brief Stores half of the value of PI.
		 */
		static const float PI_HALF;

		/**
		 *	@brief Stores the double value of PI.
		 */
		static const float PI2;

		/**
		 *	@brief This constant represent a big number that we'll take as infinite.
		 */
		static const float INFINITE_NUM;

		/**
		 *	@brief This constant stores a aproximation to 0.
		 */
		static const float DELTA;

		/**
		 *	@brief This constant stores the smallest number that we can have.
		 */
		static const float EPSILON;

		/**
		 *	@brief This constant stores the maximum presition that we'll have on floats.
		 */
		static const float MAX_FLOAT_PRESITION;


		///************************************************************************/
		///*				Wrapped Functions.									  */
		///************************************************************************/

		/// TODO: Comentar todas las funciones.
		/**
		 *	@brief The square root of a given value.
		 *	@params float fValue: the value given to calculate it's square root.
		 */

		static float Sqrt(float fValue);

		/**
		 *	@brief The inverse square root of a given value.
		 *	@params float fValue: the value given to calculate it's inverse square root.
		 */
		static float InvSqrt(float fValue);

		/**
		 *	@brief The exponentian function of a given value.
		 *	@params float fValue: the value given to calculate it's exponential function.
		 */
		static float Exp(float fValue);

		/**
		 *	@brief This function elevates a given number to a given power.
		 *	@params float fValueA: the value that will be elevated.
		 *	@params float fValueB: the power to elevate valueA.
		 */
		static float Pow(float fValueA, float fValueB);

		/**
		 *	@brief The float Logarithm of e.
		 *	@params float fValue: e.
		 */
		static float Loge(float fValue);


		/**
	 	 *	@brief A division between two logarithms
		 *	@params float fBase: dividend logarithm..
		 *	@params float fValue: the divider logarithm.
		 */
		static float LogX(float fBase, float fValue);

		/**
		 *	@brief Truncates from a float value.
		 *	@params float fValue: the value to truncate. 
		 */
		static int Trunc(float fValue);

		/**
		 *	@brief Truncates to a float value.
		 *	@params float fValue: the value to truncate.
		 */
		static float TruncFloat(float fValue);

		/**
		 *	@brief Rounds down a value.
		 *	@params float fValue: the value to round.
		 */
		static int Floor(float fValue);

		/**
		 *	@brief Rounds a value.
		 *	@params float fValue: the value to round.
		 */
		static int Round(float fValue);

		/**
		 *	@brief Rounds up a value.
		 *	@params float fValue: the value to round.
		 */
		static int Ceil(float fValue);

		///************************************************************************/
		///*				Trigonometric Functions.							  */
		///************************************************************************/

		/**
		 *	@brief Calculates the sine of an angle.
		 *	@params float fValue: the angle to calculate the sin.
		 */
		static float Sin(float fValue);

		/**
		 *	@brief Calculates the cosine of an angle.
		 *	@params float fValue: the angle to calculate the cosine.
		 */
		static float Cos(float fValue);

		/**
		 *	@brief Calculates the tangent of an angle.
		 *	@params float fValue: the angle to calculate the tangent.
		 */
		static float Tan(float fValue);

		/**
		 *	@brief Calculates the arc sine of an x expressed in radians.
		 *	@params float fValue: the angle to calculate the arc sine.
		 */
		static float Asin(float fValue);

		/**
		 *	@brief Calculates the arc cosine of an angle.
		 *	@params float fValue: the angle to calculate the cosine.
		 */
		static float Acos(float fValue);

		/**
		 *	@brief Calculates the arc tangent of an x expressed in radians.
		 *	@params float fValue: the angle to calculate the arc tangent.
		 */
		static float Atan(float fValue);

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/


		/**
		 *	@ brief calculates the absolute value of a template.
		 *	@ params T A: a template variable to calculate it's absolute.
		 */
		template< class T >
		static T Abs(const T A)
		{
			return (A >= (T)0) ? A : -A;
		}

		/**
		 *	@ brief calculates the maximum value between 2 given numbers.
		 *	@ params T A: first given value.
		 *	@ params T B: second given value.
		 */
		template< class T >
		static T Max(const T A, const T B)
		{
			return (A >= B) ? A : B;
		}

		/**
		 *	@ brief calculates the minimum value between 2 given numbers.
		 *	@ params T A: first given value.
		 *	@ params T B: second given value.
		 */
		template< class T >
		static T Min(const T A, const T B)
		{
			return (A <= B) ? A : B;
		}

		/**
		 *	@ brief calculates the maximum value between 3 given numbers.
		 *	@ params T A: first given value.
		 *	@ params T B: second given value.
		 *	@ params T C: third given value.
		 */
		template< class T >
		static T Max3(const T A, const T B, const T C)
		{
			return Max(Max(A, B), C);
		}

		/**
		 *	@ brief calculates the minimum value between 3 given numbers.
		 *	@ params T A: first given value.
		 *	@ params T B: second given value.
		 *	@ params T C: third given value.
		 */
		template< class T >
		static T Min3(const T A, const T B, const T C)
		{
			return Min(Min(A, B), C);
		}

		/**
		 *	@ brief clamps a given value between two boundaries.
		 *	@ params T X: The value to clamp.
		 *	@ params T Min: smaller number to clamp to.
		 *	@ params T Max: bigger number to clamp to.
		 */
		template< class T >
		static T Clamp(const T X, const T Min, const T Max)
		{
			return X < Min ? Min : X < Max ? X : Max;
		}

		/**
		 *	@ brief Performs a linear interpolation function.
		 *	@ params T A: The final position.
		 *	@ params T B: The initial position.
		 *	@ params T Time: the percentaje to calculate linear interpolation.
		 */
		template<class T>
		static T Lerp(const T A, const T B, const T Time)
		{
			return A + (B - A) * Time;
		}

		/**
		 *	@ brief Performs a squared root linear interpolation function.
		 *	@ params T A: The final position.
		 *	@ params T B: The initial position.
		 *	@ params T Time: the percentaje to calculate linear interpolation.
		 */
		template<class T>
		static T Slerp(const T A, const T B, const T Time)
		{
			return Sqrt(A) + (Sqrt(B) - Sqrt(A))* Time;
		}
	};
}
