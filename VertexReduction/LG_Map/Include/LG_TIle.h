#pragma once
#include "LG_MapPrerequisites.h"
#include "LG_Node.h"

namespace LevelGenerator
{

	/**
	 * @brief Plane class. Stores it's 4 vertices, it's width, and height.
	 */
	class LG_MAP_EXPORT LG_Tile
	{
	public:

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_Tile();

		/**
		 *	@brief Default Destructor.
		 */
		~LG_Tile();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief This value is used to identification the case of the plane.
		 */
		int m_iCase; 

		/**
		 *	@brief An array of Nodes, one for each corner of the plane.
		 */
		LG_Node m_Vertices[4];

		
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
		void Init(LG_Vector3D vPosition);

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