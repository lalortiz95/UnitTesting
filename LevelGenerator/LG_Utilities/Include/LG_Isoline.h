#pragma once
#include "LG_UtilitiesPrerequisites.h"
#include "LG_Node.h"
#include <vector>

namespace LevelGenerator
{
	/** 
	 *	@brief This class creates a isoline by means of a list of points.
	 */
	class LG_UTILITIES_EXPORT LG_Isoline
	{
	public:
		
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_Isoline();

		/**
		 *	@brief Default Constructor.
		 */
		~LG_Isoline();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief This variable stores the series of points that make up this line.
		 */
		Vector<LG_Node> m_NodeVector;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief This function initialize all variables of the class.
		 */
		void Init();

		/**
		 *	@brief This function free all memory of the class.
		 */
		void Destroy();

		/**
		 *	@brief This function adds a node to the isoline in a given position.
		 *	@param LG_Vector3D position: the position to spawn the given vector.
		 */
		void AddNode(LG_Vector3D position);
	};
}


