#pragma once
#include "LG_MapPrerequisites.h"
#include <LG_Line.h>

#define FIRST_LINE 0		/// Number that define the first line of the tile.
#define SECOND_LINE 1		/// Number that define the second line of the tile.

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
		 *	@var This value is used to identify the case of the tile.
		 */
		int32 m_iCase; 

		/**
		 *	@var An identifier to the tile.
		 */
		int32 m_iID;

		/**
		 *	@var An array of nodes, one for each corner of the tile.
		 */
		LG_Node m_Nodes[4];

		/**
		 *	@var An array of nodes, that define when we can draw a line that depending if it's true or false.
		 */
		LG_Node m_LinesNodes[4];

		/**
		 *	@var A vector of lines, that depending on the tile's case it's lengh could be 1 or 2.
		 */
		Vector<LG_Line> m_LinesVector;

		/**
		 *	@var true when we have already added it to a final isoline in generate algorithm.
		 */
		bool m_bIsChecked;

		///**************************************************************************/
		///*						  Member Pointers.								*/
		///**************************************************************************/

		/**
		 *	@var The top node on the left of the tile.
		 */
		LG_Node* m_pTopLeft;

		/**
		 *	@var The top node on the right of the tile.
		 */
		LG_Node* m_pTopRight;
		
		/**
		 *	@var The bottom node on the right of the tile.
		 */
		LG_Node* m_pBottomRight;

		/**
		 *	@var The bottom node on the left of the tile.
		 */
		LG_Node* m_pBottomLeft;

		/**
		 *	@var The Up node that define when we can draw a line, that depending if it's true or false.
		 */
		LG_Node* m_pUp;

		/**
		 *	@var The Left node that define when we can draw a line, that depending if it's true or false.
		 */
		LG_Node* m_pLeft;

		/**
		 *	@var The Right node that define when we can draw a line, that depending if it's true or false.
		 */
		LG_Node* m_pRight;

		/**
		 *	@var The Down node that define when we can draw a line, that depending if it's true or false.
		 */
		LG_Node* m_pDown;
		
		///**************************************************************************/
		///*						 Static Member Variables.						*/
		///**************************************************************************/


		/**
		 *	@var The constant that define the size per tile..
		 */
		static const int32 SIZE_OF_TILE;

		/**
		 *	@var The constant that define the number of nodes in the tile.
		 */
		static const int32 NUM_NODES_PER_TILE;

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
		 *	@brief This function create a line of the tile, that depending of the tile's case.
		 *	@param LG_Node StartNode: The node that have the start position of the line.
		 *	@param LG_Node EndNode: The node that have the end position of the line.
		 */
		void CreateLine(LG_Node StartNode, LG_Node EndNode);

		/**
		*	@brief This function create a line of the tile, that depending of the tile's case.
		*	@param LG_Node StartNode: The node that have the start position of the first line.
		*	@param LG_Node EndNode: The node that have the end position of the first line.
		*	@param LG_Node StartNode_2: The node that have the start position of the second line.
		*	@param LG_Node EndNode_2: The node that have the end position of the second line.
		*/
		void CreateLine(LG_Node StartNode, LG_Node EndNode,LG_Node StartNode_2, LG_Node EndNode_2);
	};

}