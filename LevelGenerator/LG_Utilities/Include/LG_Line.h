#pragma once
#include "LG_UtilitiesPrerequisites.h"
#include "LG_Node.h"

namespace LevelGenerator
{
	/**
	 *	@brief This class store 2 nodes that define a line.
	 */
	class LG_UTILITIES_EXPORT LG_Line
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_Line();

		/**
		 *	@brief Default destructor.
		 */
		~LG_Line();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief This variable stores the start and end nodes of the line.
		 */
		LG_Node m_Nodes[2];


		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief This function initialize all variables of the class.
		 */
		void Init();

		/**
		 *	@brief This function frees all the memory, and deletes the member variables.
		 */
		void Destroy();

	};
}
