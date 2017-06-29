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
		* @brief This function initilize all variables of the class.
		*/
		void Init();

		/**
		*	@brief This function free the memory of the class.
		*/
		void Destroy();

	};
}