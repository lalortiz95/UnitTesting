#pragma once
#include "LG_MapPrerequisites.h"
#include "LG_Node.h"

namespace LevelGenerator
{

	/**
	 * @brief Tile class. Stores it's 4 nodes, it's width, and height.
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
		 *	@brief This value is used to identification the case of the tile.
		 */
		int m_iCase; 

		/**
		 *	@brief The top node on the left of the tile.
		 */
		LG_Node* m_pTopLeft;

		/**
		 *	@brief The top node on the right of the tile.
		 */
		LG_Node* m_pTopRight;
		
		/**
		 *	@brief The bottom node on the right of the tile.
		 */
		LG_Node* m_pBottomRight;

		/**
		 *	@brief The bottom node on the left of the tile.
		 */
		LG_Node* m_pBottomLeft;
		
		 /**
		  *	@brief An array of nodes, one for each corner of the tile.
		  */
		LG_Node m_Nodes[4];

		
		/**
		 *	@brief The constant that define the size per tile..
		 */
		static const int SIZE_OF_TILE;

		/**
		 *	@brief The constant that define the number of nodes in the tile.
		 */
		static const int NUM_NODES_PER_TILE;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 * @brief Function needed to initialize the variables of the tile class.
		 * @param CVetor3D vPosition: The position that will be assigned to the first node of the tiles array.
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