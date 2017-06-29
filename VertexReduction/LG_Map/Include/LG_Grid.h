#pragma once
#include "LG_MapPrerequisites.h"
#include "LG_Circle.h"
#include "LG_Tile.h"

#include <vector>

namespace LevelGenerator
{
	/**
	 *	@brief This class stores a bidimensional array of planes to generate a grid.
	 */
	class LG_MAP_EXPORT LG_Grid
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		*	@brief Default Constructor.
		*/
		LG_Grid();

		/**
		*	@brief Default Destructor.
		*/
		~LG_Grid();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief This variable stores the height of the grid.
		 */
		int m_iHeight;

		/**
		 *	@brief This variable stores the width of the grid.
		 */
		int m_iWidth;

		/**
		 *	@brief Bidimensional array that stores the planes.
		 */
		LG_Tile** m_Grid;

	private:

		/**
		 *	@brief This variable stores the number of planes in x.
		 */
		int m_iNumberPlanesX;

		/**
		 *	@brief This variable stores the number of planes in y.
		 */
		int m_iNumberPlanesY;


		/**
		 *	@brief Circle.
		 */
		LG_Circle m_Cricle;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

	public:
		/**
		 *	@brief This function initialize all variables of the class.
		 *	@param int iWidth: The width of the grid.
		 *  @param int iHeight: The height of the grid.
		 */
		void Init(int iWidth, int iHeight);


		/**
		 *	@brief This function realeases the memory of the class.
		 */
		void Destroy();

		/**
	  	 *	@brief Calls necessary functions to generate the algorithm.
		 */
		void MarchingSquare();

		/**
		 *	@brief This function Calculates each plane's case. It's done comparing a scalar function with each vertice's position.
		 *	@param LG_Vector3D vPosition: the position of the scalar function origin's.
		 *	@return if its or not inside of the scalar function. True when its inside.
		 */
		bool CalculatePlaneCase(LG_Vector3D vPosition);

		///************************************************************************/
		///*						   Accessors.								  */
		///************************************************************************/

		/**
		 *	@brief This function returns the number of planes in the grid, in the X axis.
		 *	@return the number of planes in the X axis.
		 */
		int GetPlanesX();

		 /**
		  *	@brief This function returns the number of planes in the grid, in the Y axis.
		  *	@return the number of planes in the Y axis.
		  */
		int GetPlanesY();
	};
}

