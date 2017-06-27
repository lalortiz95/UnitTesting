#pragma once
#include "Vertex.h"

namespace LevelGenerator
{

	/**
	 * @brief Plane class. Stores it's 4 vertices, it's width, and height.
	 */
	class CPlane
	{
	public:

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		CPlane();

		/**
		 *	@brief Default Destructor.
		 */
		~CPlane();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief An array of vertices, one for each corner of the plane.
		 */
		CVertex m_Vertices[4];

		/**
		 *	@brief The size of all lines that the plane has.
		 */
		static const int m_iSize;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 * @brief Function needed to initialize the variables of the Plane class.
		 * @param CVetor3D vPosition: The position that will be assigned to the first vertex of the plane's array.
		 */
		void Init(CVector3D vPosition);

		/**
		 *	@brief This function realeases the memory of the class.
		 */
		void Destroy();

	};

}