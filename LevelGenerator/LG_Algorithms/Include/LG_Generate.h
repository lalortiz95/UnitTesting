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

		/**
		 *	@brief The current isoline being filled.
		 */
		LG_Isoline m_ActualIsoline;

		/**
		 *	@brief A pointer that define the actual tile.
		 */
		LG_Tile* m_pActualTile;

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
		 *	@brief This function check if exist other node with the same position that
		 */
		void GenerateIsoline();

	private:

		/**
		 *	@brief This function check if the position of the actual tile's nodes against the iterating tile's nodes.
		 *	@param LG_Node& StartNode: The first node of the iterating line.
		 *	@param LG_Node& EndNode: The end node of the iterating line.
		 *	@param int32 iIteratingLine: The number that defines the line that is being iterating.
		 *	@return true if one of the iterating nodes have the same position that one of the actual tile's node.
		 */
		bool CheckNodePosition(LG_Node& StartNode, LG_Node& EndNode, int32 iIteratingLine);
		
		/**
		 *	@brief This function check if the line isn't set yet.
		 *	@param LG_Line& IteratingLine: The iterating line.
		 *	@param int32 iIteratingLine: The number that defines the line that is being iterating.
		 *	@return true when two nodes shared position.
		 */
		bool CheckLineIsInside(LG_Line& IteratingLine, int32 iIteratingLine);

		/**
		 *	@brief This function check if the tile has already been checked.
		 *	@param LG_Line& IteratingLine: The iterating tile.
		 *	@param int32 iIteratingLine: The number that defines the line that is being iterating.
		 *	@return true when one or both lines of the tile have it's flag set as true.
		 */
		bool CheckTile(LG_Tile& IteratingTile, int32 iIteratingTile);

		/**
		 *	@brief This function tells if a isoline is finished.
		 *	@return true if the isoline is finished.
		 */
		bool CheckIfIsolineIsFinish();
	};
}