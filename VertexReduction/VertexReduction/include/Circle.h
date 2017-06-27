#pragma once
#include "Vector3D.h"

namespace LevelGenerator
{
	/**
	*	@brief This class has a vector3D which stores it's position. And a float for it's radius.
	*/
	class CCircle
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		CCircle();

		/**
		 *	@brief Default destructor.
		 */
		~CCircle();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief This variable stores the position of the circle.
		 */
		CVector3D m_Position;

		/**
		 *	@brief This variable stores the radius of the circle.
		 */
		float m_fRadius;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief This function initialize all variables of the class.
		 *	@param CVector3D vPosition: The circle's position in a 3 dimensional space.
		 *  @param float fRadius: The given radius for the circle.
		 */
		void Init(CVector3D vPosition, float fRadius);

		/**
		 *	@brief This function frees all the memory, and deletes the member variables. 
		 */
		void Destroy();
	};

}