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
		static float Sqrt(float fValue);
		static float InvSqrt(float fValue);
		static float Exp(float fValue);
		static float Pow(float fValueA, float fValueB);
		static float Loge(float fValue);
		static float LogX(float fBase, float fValue);

		static int Trunc(float fValue);
		static float TruncFloat(float fValue);
		static int Floor(float fValue);
		static int Round(float fValue);
		static int Ceil(float fValue);

		///************************************************************************/
		///*				Trigonometric Functions.							  */
		///************************************************************************/


		static float Sin(float fValue);
		static float Cos(float fValue);
		static float Tan(float fValue);

		static float Asin(float fValue);
		static float Acos(float fValue);
		static float Atan(float fValue);

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/


		/**
		 *
		 */
		template< class T >
		static T Abs(const T A)
		{
			return (A >= (T)0) ? A : -A;
		}

		/************************************************************************/
		/* Funcion para sacar el valor maximo entre 2 valores					*/
		/************************************************************************/
		template< class T >
		static T Max(const T A, const T B)
		{
			return (A >= B) ? A : B;
		}
		/************************************************************************/
		/*Saca el valor minimo entre 2 valores									*/
		/************************************************************************/
		template< class T >
		static T Min(const T A, const T B)
		{
			return (A <= B) ? A : B;
		}

		/************************************************************************/
		/*Saca el valor maximo de 3 valores										*/
		/************************************************************************/
		template< class T >
		static T Max3(const T A, const T B, const T C)
		{
			return Max(Max(A, B), C);
		}

		/************************************************************************/
		/*Saca el valor minimo de 3 valores										*/
		/************************************************************************/
		template< class T >
		static T Min3(const T A, const T B, const T C)
		{
			return Min(Min(A, B), C);
		}
		/************************************************************************/
		/* Funcion clamp														*/
		/************************************************************************/
		template< class T >
		static T Clamp(const T X, const T Min, const T Max)
		{
			return X < Min ? Min : X < Max ? X : Max;
		}
		/************************************************************************/
		/* Funcion para interpolacion lineal									*/
		/************************************************************************/
		template<class T>
		static T Lerp(const T A, const T B, const T Time)
		{
			return A + (B - A)* Time;
		}
		/************************************************************************/
		/* Funcion para interpolacion esferica									*/
		/************************************************************************/
		template<class T>
		static T Slerp(const T A, const T B, const T Time)
		{
			return Sqrt(A) + (Sqrt(B) - Sqrt(A))* Time;
		}



	};
}
