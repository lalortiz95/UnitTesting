#pragma once
#include "LG_AlgorithmsPrerequisites.h"
#include "LG_MarchingSquare.h"
#include "LG_RDP.h"
#include <LG_Grid.h>

#define ERROR_CODE 666

namespace LevelGenerator
{
	/**
	 *	@brief This class manages and unificates all the algorithms in the project.
	 */
	class LG_ALGORITHMS_EXPORT LG_Generate
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default constructor.
		 */
		LG_Generate();
		/**
		 *	@brief Default destructor.
		 */
		~LG_Generate();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief An object of the marching square class. It's used to run the algorithm.
		 */
		LG_MarchingSquare m_MS;

		/**
		*	@brief An object of the Ramer-Douglas-Peucker class. It's used to run it's algorithm.
		*/
		LG_RDP m_RDP;

		/**
		 *	@brief A map where we generate marching square.
		 */
		LG_Grid* m_pMap;

		/**
		 *	@brief A vector of isolines where we store the marching square output.
		 */
		Vector<LG_Isoline> m_IsolineVector;

		/**
		 *	@brief A vector of tiles where we store the tiles inside of marching square.
		 */
		Vector<LG_Tile*> m_TileVector;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *  @brief This function initialize all variables of the class.
		 */
		void Initialize();

		/**
		 *	@brief This function free the memory of the class, and destroys it's variables.
		 */
		void Destroy();

		/**
		 *	@brief This calls all the algorithms and put them together to generate a procedural level.
		 */
		void Run();

		/**
		 *	@brief compares a node with all of the others to see which one compares position.
		 *	@param LG_Line ActualLine: A line that will compare it's node's position against the other nodes.
		 *	@param LG_Isoline ActualIsoline: The isoline wwhere we store the sharing position nodes.
		 *	@param int32 iteratingTile: The place in the vector of the tile being iterating.
		 *	@return The ID of the new actual tile.
		 */
		int32 CompareTilesPosition(LG_Line ActualLine, LG_Isoline& ActualIsoline, int32 iteratingTile);


		/**
		 *	@brief This function check if exist other node with the same position that
		 */
	};
}