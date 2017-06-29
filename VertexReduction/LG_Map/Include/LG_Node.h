#pragma once
#include "LG_MapPrerequisites.h"
#include <LG_Vector3D.h>

namespace LevelGenerator
{
	/**
	 *	@brief This class stores a node in a 3D space.
	 */
	class LG_MAP_EXPORT LG_Node
	{
	public:

		///************************************************************************/
		///*                        Constructor & Destructor.					  */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_Node();

		/**
		 *	@brief Default Destructor.
		 */
		~LG_Node();

		/**
		 *	@brief Parameters Constructor.
		 */
		LG_Node(LG_Vector3D vPosition);



		///************************************************************************/
		///*						  Member Variables.							  */
		///************************************************************************/

		/**
		 *	@brief This variable stores a 3D position (X,Y,Z).
		 */
		LG_Vector3D m_Position;

		/**
		 *	@brief This flag determinate if the node is On or Off.
		 */
		bool m_bIsInside;


		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief Function to initialize the variables.
		 */
		void Init();

		/**
		 *	@brief Function to realease memory and destroy objects.
		 */
		void Destroy();
	};
}
