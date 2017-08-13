#pragma once
#include "LG_GeometryPrerequisites.h"
#include "LG_Node.h"

namespace LevelGenerator
{
	/** 
	 *	@brief This class creates a isoline by means of a list of points.
	 */
	class LG_GEOMETRY_EXPORT LG_Isoline
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
		 *	@brief This function adds a node in the back of the isoline.
		 *	@param LG_Vector3D position: the position to spawn the given vector.
		 */
		void AddNodeBack(LG_Vector3D position);

		/**
		*	@brief This function adds a node in the front of the isoline.
		*	@param LG_Vector3D position: the position to spawn the given vector.
		*/
		void AddNodeFront(LG_Vector3D position);
	};
}


