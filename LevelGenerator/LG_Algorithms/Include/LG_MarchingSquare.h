#pragma once
#include "LG_AlgorithmsPrerequisites.h"
#include <LG_Grid.h>
#include <LG_Circle.h>

namespace LevelGenerator
{
	/**
	 * @enum An enumerator to define all posible cases from marching squares.
	 */
	enum eTileCase
	{
		CASE_0 = 0,
		CASE_1 = 1,
		CASE_2 = 2,
		CASE_3 = 3,
		CASE_4 = 4,
		CASE_5 = 5,
		CASE_6 = 6,
		CASE_7 = 7,
		CASE_8 = 8,
		CASE_9 = 9,
		CASE_10 = 10,
		CASE_11 = 11,
		CASE_12 = 12,
		CASE_13 = 13,
		CASE_14 = 14,
		CASE_15 = 15,
	};

	/**
	 *	@brief This class generates marching square. 
	 */
	class LG_ALGORITHMS_EXPORT LG_MarchingSquare
	{
	public:
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
		 *	@var A LG_Grid pointer in which we are realizing the algorithm.
		 */
		LG_Grid* m_pMap;

		/**
		 *	@var This vector stores a circles class objects.
		 */
		Vector<LG_Circle>m_CircleList;

		/**
		*	@var This variable stores in a vector the reference of the tiles that have a case different than 0.
		*/
		Vector<LG_Tile*> m_pTilesWithCase;

		/**
		*	@var This variable stores in a vector the reference of the tiles that have a case different than 0 and 15.
		*/
		Vector<LG_Tile*> m_pEdgeTiles;

		/**
		 *	@var The contour of the generated shape.
		 */
		LG_Isoline m_Outline;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *  @brief This function initialize all variables of the class.
		 */
		void Init(LG_Grid* gridToWorkWith);

		/**
		 *  @brief This function initialize all variables of the class.
		 *	@param int32 iCircleAmount: The amount of circles to create.
		 *	@param int32 tilesX: the amount of tiles in X for the grid.
		 *	@param int32 tilesY: the amount of tiles in Y for the grid.
		 */
		void Init(int32 iCircleAmount, int32 tilesX, int32 tilesY);

		/**
		 *	@brief This function free the memory of the class, and destroys it's variables.
		 */
		void Destroy();

		/**
		 *	@brief This function is the only one you need to generate marching squares algorithm.
		 */
		 void Run(LG_Grid* gridToWorkWith);

		 /**
		  *	@brief This function is the only one you need to generate marching squares algorithm.
		  *	@param int32 iCircleAmount: The amount of circles to create.
		  *	@param int32 iNumTilesX: The amount of tiles to be created in the X Axis.	
		  * @param int32 iNumTilesY: The amount of tiles to be created in the Y Axis.
		  */
		 void Run(int32 iCircleAmount, int32 iNumTilesX, int32 iNumTilesY);

	private:
		 /**
		  *	@brief This function Calculates each tile case, Calculated through the flags on it's nodes.
		  */
		void SetTilesCases();
		
		/**
		 *	@brief This function tells us wether or not, a tile's node is inside of a list of circles.
		 *	@param LG_Node ActualNode: The node to compare with the scalar function.
		 *	@return true if it's inside, otherwise false.
		 */
		bool IsTilesInsideOfCircles(LG_Node ActualNode);

		/**
		 *	@brief This function set a random number of circles.
		 *	@param int32 iCircleAmount: The amount of circles to create.
		 */
		void SetCircles(int32 iCircleAmount);

		/**
		 *	@brief This function set a random number of circles.
		 *	@param int32 iCircleAmount: The amount of circles to create.
		 */
		void SetCircles();
	};
}