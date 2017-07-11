#pragma once
#include "LG_AlgorithmsPrerequisites.h"
#include "LG_Isoline.h"

namespace LevelGenerator
{
	/**
	 *	@brief This class generates Ramer-Douglas-Peucker Algorithm.
	 */
	class LG_ALGORITHMS_EXPORT LG_RDP
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_RDP();

		/**
		 *	@brief Default Destructor.
		 */
		~LG_RDP();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief This node stores when the isoline begin.
		 */
		LG_Node m_Begin;

		/**
		 *	@brief This node stores when the isoline end.
		 */
		LG_Node m_End;

		/**
		 *	@brief This node stores a temporal node.
		 */
		LG_Node m_ActualEndNode;

		/**
		 *	@brief The original isoline which will be reduced.
		 */
		LG_Isoline m_OriginalIsoline;

		/**
		 *	@brief The reduced isoline.
		 */
		LG_Isoline m_FinalIsoline;

		/**
		 *	@brief The range to reduce nodes.
		 */
		float m_fRange;

		/**
		 *	@brief The actual distance between 2 vectors.
		 */
		float m_fGreaterDistance;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *  @brief This function initialize all variables of the class.
		 *	@param float fRange: the range that will be used to reduce the nodes.
		 *	@param LG_Isoline IsolineToReduce: The isoline to be reduced.
		 */
		void Init(float fRange, LG_Isoline IsolineToReduce);

		/**
		 *	@brief This function free the memory of the class, and destroys it's variables.
		 */
		void Destroy();

		/**
		 *	@brief This function check the distance between the end node, the start node and the given node.
		 *	@param LG_Node ActualNode: The node to that we have check.
		 */
		void CheckNodeDistance(LG_Node ActualNode);

		/**
		 *	@brief This function create the boundary for check if a node is inside of this. 
		 */
		void CreateBoundary();

		/**
		 *	@brief This function is the only one you need to generate Ramer-Douglas-Peucker algorithm.
		 */
		void Run();
	};
}