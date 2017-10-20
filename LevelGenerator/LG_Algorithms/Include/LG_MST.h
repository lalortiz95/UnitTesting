#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Edge.h>

namespace LevelGenerator
{
	class LG_Triangle;

	/**
	 *	@brief This class generates Minimum Spanning Tree Algorithm.
	 */
	class LG_ALGORITHMS_EXPORT LG_MST
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_MST();

		/**
		 *	@brief Default Destructor.
		 */
		~LG_MST();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@var Stores the final result of the algorithm.
		 */
		Vector<LG_Edge*> m_FinalTree;

		/**
		 *	@var The edges ordered from lower to higher cost.
		 */
		Vector<LG_Edge*> m_OrderedEdges;

		/**
		 *	@var The triangles generated by Delaunay Triangulation.
		 */
		Vector<LG_Triangle*> m_Triangulation;

		 ///************************************************************************/
		 ///*						   Class Functions.							  */
		 ///************************************************************************/

		/**
		 *	@brief Initializes the member variables of the class.
		 *	@param 
		 */
		void Init();

		/**
		 *	@brief This function free the memory of the class, and destroys it's variables.
		 */
		void Destroy();

		/**
		 *	@brief This function is the only one you need to generate Minimum Spanning Tree algorithm.
		 *	@param Vector<LG_Edge*> InitialNet: the edges taken to find the minimum paths available. 
		 *	@param Vector<LG_Triangle*> Triangulation: the triangulation used to see if we can add an edge to the final tree.
		 */
		void Run(Vector<LG_Edge*> InitialNet, Vector<LG_Triangle*> Triangulation);

		/** 
		 *	@brief Sorts the initial vector of edges, from lower to higher cost.
		 *	@param Vector<LG_Edge*> InitialNet, a copy of the initial net.
		 */
		void Sort(Vector<LG_Edge*> InitialNet);
	};
}