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
		LG_Node* m_pStart;

		/**
		 *	@brief This node stores when the isoline end.
		 */
		LG_Node* m_pEnd;

		/**
		 *	@brief This node stores a temporal node.
		 */
		LG_Node* m_pActualNode;

		/**
		 *	@brief The original isoline which will be reduced.
		 */
		LG_Isoline m_OriginalIsoline;

		/**
		 *	@brief The reduced set of nodes.
		 */
		LG_Isoline m_FinalIsoline;

		/**
		 *	@brief The range to reduce nodes.
		 */
		float m_fRange;

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
		 *	@brief This function is the only one you need to generate Ramer-Douglas-Peucker algorithm.
		 *	@param float fRange: The range to reduce nodes.
		 *	@param LG_Isoline IsolineToReduce: The isoline that we want to reduce.
		 */
		void Run(float fRange, LG_Isoline Isoline);

	private:
		/**
		 *	@brief This function check the distance between the end node, the start node and the given node.
		 */
		void SetFurthestNode();

		/**
		 *	@brief This function set the flags according to the start and end nodes. 
		 */
		void SetFlags();

		/**
		 *	@brief Set the node's IDs.
		 */
		void SetIsolineID();

		/**
		 *	@brief Adds a node to the final isoline, and changes the start and end.
		 */
		void AddNodeToFinalIsoline();

		/**
		 *	@brief When the start node is next to the end node, we change the start and end nodes.
		 */
		void ListIsFalse();
	};
}