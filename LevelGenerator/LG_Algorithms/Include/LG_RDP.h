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
		 *	@brief The original isoline which will be reduced.
		 */
		LG_Isoline m_OriginalIsoline;

		/**
		*	@brief The reduced isoline.
		*/
		LG_Isoline m_FinalIsoline;
	};
}