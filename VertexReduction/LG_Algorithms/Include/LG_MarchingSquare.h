#pragma once
#include "LG_AlgorithmsPrerequisites.h"
#include <LG_Grid.h>

namespace LevelGenerator
{
	/**
	 * @brief An enumerator to define all posible cases from marching squares.
	 */
	enum eTileCase
	{
		CASE_0  = 0x00,
		CASE_1  = 0x01,
		CASE_2  = 0x02,
		CASE_3  = 0x03,
		CASE_4  = 0x04,
		CASE_5  = 0x05,
		CASE_6  = 0x06,
		CASE_7  = 0x07,
		CASE_8  = 0x08,
		CASE_9  = 0x09,
		CASE_10 = 0x10,
		CASE_11 = 0x11,
		CASE_12 = 0x12,
		CASE_13 = 0x13,
		CASE_14 = 0x14,
		CASE_15 = 0x15,
	};

	/**
	 *	@brief This class generates marching square. 
	 */
	class LG_ALGORITHMS_EXPORT LG_MarchingSquare
	{
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
		 *	@brief the grid in which we are realizing the algorithm.
		 */
		
		LG_Grid* m_pMap;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 * @brief This function initialize all variables of the class.
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

		 /**
		 *	@brief This function Calculates each tile case. It's done comparing a scalar function with each vertice's position.
		 *	@param LG_Vector3D vPosition: the position of the scalar function origin's.
		 *	@return if its or not inside of the scalar function. True when its inside.
		 */
		bool GenerateTileCase(LG_Vector3D vPosition);
		
		/**
		 * @brief This function generates a vector of tiles that have cases different than 0.
		 */
		void SetTilesInsideOfScalarFunction();
	};
}