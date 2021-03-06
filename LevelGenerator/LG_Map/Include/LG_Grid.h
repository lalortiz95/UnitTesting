#pragma once
#include "LG_MapPrerequisites.h"
#include "LG_Tile.h"

#include <LG_Circle.h>
#include <LG_Isoline.h>


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
		 *	@var This variable stores the height of the grid.
		 */
		int32 m_iHeight;

		/**
		 *	@var This variable stores the width of the grid.
		 */
		int32 m_iWidth;

		/**
		 *	@var Bidimensional array that stores the tiles.
		 */
		LG_Tile** m_Grid;

		/**
		 *	@var This variable stores the map's center.
		 */
		 LG_Node m_MapCenter;

	private:

		/**
		 *	@var This variable stores the number of tiles in x.
		 */
		int32 m_iNumberPlanesX;

		/**
		 *	@var This variable stores the number of tiles in y.
		 */
		int32 m_iNumberPlanesY;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

	public:
		/**
		 *	@brief This function initialize all variables of the class.
		 *	@param int32 iWidth: The width of the grid.
		 *  @param int32 iHeight: The height of the grid.
		 */
		void Init(int32 iWidth, int32 iHeight);


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
		int32 GetTilesX();

		 /**
		  *	@brief This function returns the number of tiles in the grid, in the Y axis.
		  *	@return the number of tiles in the Y axis.
		  */
		int32 GetTilesY();
	};
}

