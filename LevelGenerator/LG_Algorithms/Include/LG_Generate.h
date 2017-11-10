#pragma once
#include "LG_AlgorithmsPrerequisites.h"
#include "LG_DelaunayTriangulation.h"
#include "LG_HallwayGeneration.h"
#include "LG_MarchingSquare.h"
#include "LG_Dijkstra.h"
#include "LG_Voronoi.h"
#include "LG_RDP.h"
#include "LG_MST.h"

#include <LG_Rect.h>
#include <LG_Grid.h>

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

		/**
		 *	@brief Singleton class.
		 */
		static LG_Generate& instance()
		{
			static LG_Generate INSTANCE;
			return INSTANCE;
		}

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@var Constant that define the force separation.
		 */
		static const int32 SEPARATION_FORCE;

		/**
		 *	@var Constant that define a Max Force.
		 */
		static const int32 MAX_FORCE;

		/**
		 *	@var Constant that define a Min Force.
		 */
		static const int32 MIN_FORCE;

		/**
		 *	@var Constant that define the area of the spawn zone.
		 */
		static const int32 SPAWN_ZONE;

		/**
		 *	@var Flag that determinate when we can insert a node in front or back of the isoline.
		 */
		bool m_bInsertFront;

		/**
		 *	@var Spawn Zone
		 */
		LG_Rect* m_pSpawnZone;

		/**
		 *	@var An object of the marching square class. It's used to run the algorithm.
		 */
		LG_MarchingSquare m_MS;

		/**
		 *	@var An object of the Ramer-Douglas-Peucker class. It's used to run it's algorithm.
		 */
		LG_RDP m_RDP;

		/**
		 *	@var An object of the Minimum spanning tree class. It's used to run it's algorithm.
		 */
		LG_MST m_MST;

		/**
		 *	@var An object of the delaunay triangulation class. It's used to run it's algorithm.
		 */
		LG_DelaunayTriangulation m_DT;

		/**
		 *	@var The interface used to generate the hallways.
		 */
		LG_HallwayGeneration m_HG;

		/**
		 *	@var A vector of isolines where we store the marching square output.
		 */
		Vector<LG_Isoline> m_IsolineVector;

		/**
		 *	@var A vector of final isolines.
		 */
		Vector<LG_Isoline> m_FinalIsolineVector;

		/**
		 *	@var A vector of pointer nodes that stores our roomms, and it's used to triangulate.
		 */
		Vector<LG_Node*> m_RoomsNodesCloud;

		/**
		 *	@var A vector that stores the nodes generated by marching square, and RDP.
		 */
		Vector<LG_Node*> m_ReducedNoudCloud;

		/**
		 *	@var A vector of tiles where we store the tiles inside of marching square.
		 */
		Vector<LG_Tile*> m_TileVector;

		/**
		 *	@var Were we store our rooms.
		 */
		Vector<LG_Rect*> m_RoomsVector;

		/**
		 *	@var The current isoline being filled.
		 */
		LG_Isoline m_ActualIsoline;

		/**
		 *	@var A pointer that define the actual tile.
		 */
		LG_Tile* m_pActualTile;

	private:
		/**
		 *	@var Singleton instance. Used for the wrapping functions.
		 */
		static LG_Generate* m_pIsntance;

	public:

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
		 *	@param uint32 uiRoomAmount: The number of rooms that are going to be created.
		 *	@param LG_Vector3D MinSize: the minimum available sizes for the rooms.
		 *	@param LG_Vector3D MaxSize: the maximum available sizes for the rooms.
		 */
		void Run(uint32 uiRoomAmount, LG_Vector3D MinSize, LG_Vector3D MaxSize);

		/**
		 *	@brief This function separate the rooms object.
		 *	@param float fDelta: The time to actualize.
		 * 	@return true if we need to separate at least one rect, otherwise false.
		 */
		bool SeparationRooms(float fDelta);

		/**
		 *	@brief This function generate a isoline from Marching Square Cases.
		 */
		void GenerateIsoline();

	private:

		///************************************************************************/
		///*						   Assist Functions.						  */
		///************************************************************************/

		/**
		 *	@brief This function check if the position of the actual tile's nodes against the iterating tile's nodes.
		 *	@param int32 iCountLine: The number that defines the line that is being iterating.
		 *	@param int32 iCountNode: The number that defines the node that is being iterating.
		 *	@param LG_Node& NodeToCheck: The first node of the iterating line.
		 *	@return true if one of the iterating nodes have the same position that one of the actual tile's node.
		 */
		bool CheckNodePosition(int32 iCountLine, int32 iCountNode, LG_Node& NodeToCheck);

		/**
		 *	@brief This function check if the line isn't set yet.
		 *	@param int32 iCountLine: The number of lines being iterating.
		 *	@param LG_Line& IteratingLine: The iterating line.
		 *	@return true when two nodes shared position.
		 */
		bool CheckLineIsInside(int32 iCountLine, LG_Line& IteratingLine);

		/**
		 *	@brief This function check if the tile has already been checked.
		 *	@param LG_Line& IteratingLine: The iterating tile.
		 *	@return true when one or both lines of the tile have it's flag set as true.
		 */
		bool CheckTile(LG_Tile& IteratingTile);

		/**
		 *	@brief This function check if a isoline is finished.
		 *	@param int32 iCountLine: The number of line in the iterating tile.
		 *	@return true if the actual tile change in this function, otherwise false.
		 */
		bool CheckIfIsolineIsFinished(int32 iCountLine);

		/**
		 *	@brief This function check if all tiles in the vector are checked.
		 *	@return true if all tiles in the vector are checked, otherwise false.
		 */
		bool AllTilesAreChecked();

		/**
		 *	@brief This functions inserts the edge node of a isoline.
		 *	@param int32 iCountLine: The number of line in the actual tile.
		 */
		void InsertEdgeNode(int32 iCountLine);

		/**
		 *	@brief Generates random positions for the rectangles, and separates them.
		 *	@param uint32 uiRoomAmount: The number of rooms that are going to be created.
		 *	@param LG_Vector3D MinSize: the minimum available sizes for the rooms.
		 *	@param LG_Vector3D MaxSize: the maximum available sizes for the rooms.
		 */
		void GenerateRooms(uint32 uiRoomAmount, LG_Vector3D MinSize, LG_Vector3D MaxSize);

		/**
		 *	@brief This function sets a new actual tile.
		 */
		void SetActualTile();

		/**
		 *	@brief This function that sets a line as true if the 2 nodes of the line are true.
		 *	@param LG_Line& LineToChangeFlag: The line that we want to change it's flag.
		 */
		void SetLineAs(LG_Line& LineToChangeFlag);

		/**
		 *	@brief This function set a tile as true if 1 or 2 lines of the tile are true.
		 *	@param LG_Tile& TileToChangeFlag: The tile that we want to change it's flag.
		 */
		void SetTileAs(LG_Tile& TileToChangeFlag);

		/**
		 *	@brief This function get the average of rooms that are colliding with the actual rect.
		 *	@param LG_Rect* pActualRect: The actual rect.
		 */
		void AverageRoom(LG_Rect* pActualRect);

		/**
		 *	@brief This function reduce the nodes in the isolines.
		 */
		void ReducedIsolines();

		/**
		 *	@brief This function obtain a cloud nodes from the isolines vector.
		 */
		void GetNoudesCloud();

		/**
		 *	@brief fills the rectangle's connections vector.
		 */
		void GenerateRoomsConnections();

		/**
		 *	@brief This function limits the strength of a given vector.
		 *	@param LG_Vector3D VectorTruncate: The vector that we want to truncate.
		 *	@return the vector truncate.
		 */
		LG_Vector3D TruncateVector(LG_Vector3D VectorTruncate);

	};
}

//extern "C" EXPORT_FOR_UNITY LevelGenerator::LG_Generate* g_pGenerateLevel;

extern "C" LG_ALGORITHMS_EXPORT LevelGenerator::LG_Generate* GenerateLevel(LevelGenerator::int32 iRoomsAmount,
	LevelGenerator::LG_Vector3D MinSize,
	LevelGenerator::LG_Vector3D MaxSize);

extern "C" LG_ALGORITHMS_EXPORT LevelGenerator::LG_Rect** GetRooms();

