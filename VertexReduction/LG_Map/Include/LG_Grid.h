#pragma once
#include "LG_MapPrerequisites.h"
#include "LG_Circle.h"
#include "LG_Tile.h"

#include <vector>

namespace LevelGenerator
{
	/**
	 *	@brief This class stores a bidimensional array of tiles to generate a grid.
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
		 *	@brief Bidimensional array that stores the tiles.
		 */
		LG_Tile** m_Grid;

		/**
		 *	@brief This variable stores in a vector the tiles that have case diferent than 0.
		 */
		std::vector<LG_Tile> m_ListTilesInside;

	private:

		/**
		 *	@brief This variable stores the number of tiles in x.
		 */
		int m_iNumberPlanesX;

		/**
		 *	@brief This variable stores the number of tiles in y.
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

		///************************************************************************/
		///*						   Accessors.								  */
		///************************************************************************/

		/**
		 *	@brief This function returns the number of tiles in the grid, in the X axis.
		 *	@return the number of tiles in the X axis.
		 */
		int GetTilesX();

		 /**
		  *	@brief This function returns the number of tiles in the grid, in the Y axis.
		  *	@return the number of tiles in the Y axis.
		  */
		int GetTilesY();
	};
}

