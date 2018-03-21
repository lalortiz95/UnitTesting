#pragma once
#include "LG_GeometryPrerequisites.h"
#include <LG_Vector3D.h>

namespace LevelGenerator
{
	/**
	*	@brief This class has a vector3D which stores it's position. And a float for it's radius.
	*/
	class LG_GEOMETRY_EXPORT LG_Circle
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_Circle();

		/**
		 *	@brief Default destructor.
		 */
		~LG_Circle();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@var This variable stores the position of the circle.
		 */
		LG_Vector3D m_Position;

		/**
		 *	@var This variable stores the radius of the circle.
		 */
		float m_fRadius;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief This function initialize all variables of the class.
		 *	@param LG_Vector3D vPosition: The circle's position in a 3 dimensional space.
		 *  @param float fRadius: The given radius for the circle.
		 */
		void Init(LG_Vector3D vPosition, float fRadius);

		/**
		 *	@brief This function frees all the memory, and deletes the member variables. 
		 */
		void Destroy();

		/**
		 *	@brief Checks if there is a dot inside of the circle.
		 *	@param LG_Vector3D dotToCheck:  the node that we want to know if it's inside.
		 *	@return true when the dot was inside.
		 */
		bool IsDotInside(LG_Vector3D dotToCheck);

	};

}