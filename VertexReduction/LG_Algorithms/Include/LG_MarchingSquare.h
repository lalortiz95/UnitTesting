#pragma once
#include "LG_AlgorithmsPrerequisites.h"
#include <LG_Grid.h>
#include <LG_Circle.h>

namespace LevelGenerator
{
	/**
	 * @brief An enumerator to define all posible cases from marching squares.
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
		 *	@brief A LG_Grid pointer in which we are realizing the algorithm.
		 */
		LG_Grid* m_pMap;

		/**
		 *	@brief This vector stores a circles class objects.
		 */
		std::vector<LG_Circle>m_CircleList;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *  @brief This function initialize all variables of the class.
		 *	@param The grid.
		 */
		void Init();

		/**
		 *	@brief This function free the memory of the class.
		 */
		void Destroy();
		
		/**
		 *	@brief This function is the only one you need to generate marching squares algorithm.
		 */
		 void Run();

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
		 */
		void SetCircles();			
	};
}