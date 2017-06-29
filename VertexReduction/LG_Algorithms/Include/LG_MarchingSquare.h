#pragma once
#include "LG_AlgorithmsPrerequisites.h"

namespace LevelGenerator
{
	/**
	 *	@brief This class generates marching square. 
	 */
	class LG_ALGORITHMS_EXPORT LG_MarchingSquare
	{
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		*	@brief Default Constructor.
		*/
		LG_MarchingSquare();

		/**
		*	@brief Default Destructor.
		*/
		~LG_MarchingSquare();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		*	@brief This value is used to identification the case of the plane.
		*/
		

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		* @brief Function needed to initialize the variables of the Plane class.
		* @param CVetor3D vPosition: The position that will be assigned to the first vertex of the plane's array.
		*/
		void Init();

		/**
		*	@brief This function realeases the memory of the class.
		*/
		void Destroy();

	

	};
}