#pragma once
#include "PrerequisitesLevelGenerator.h"
#include "Vertex.h"

namespace LevelGenerator
{

	/**
	 * @brief Plane class. Stores it's 4 vertices, it's width, and height.
	 */
	class LG_EXPORT CPlane
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
		 *	@brief This value is used to identification the case of the plane.
		 */
		int m_iCase; 

		/**
		 *	@brief An array of vertices, one for each corner of the plane.
		 */
		CVertex m_Vertices[4];

		
		/**
		 *	@brief The size of all lines that the plane has.
		 */
		static const int SIZE_OF_PLANE;

		/**
		 *	@note: The given value is 3 because we start counting on 0. Example: 0, 1, 2, 3.
		 *	@brief The constant that define the number of vertices in the plane.
		 */
		static const int NUM_VERTEX_PER_PLANE;

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

		/**
		 * @brief This function assign the
		 */
		void CheckPlaneCase();

	};

}