#pragma once
#include "LG_GeometryPrerequisites.h"

namespace LevelGenerator
{
	/**
	*	@brief This class stores a triangle.
	*/
	class LG_GEOMETRY_EXPORT LG_Triangle
	{
	public:

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		*	@brief Default constructor.
		*/
		LG_Triangle();

		/**
		*	@brief Default destructor.
		*/
		~LG_Triangle();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		*	@brief
		*/

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		*  @brief This function initialize all variables of the class.
		*/
		void Init();

		/**
		*  @brief This function releases memory and clears the variables.
		*/
		void Destroy();
	};
}