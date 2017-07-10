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

		/**
		 *	@brief The range to reduce nodes.
		 */
		float m_fRange;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *  @brief This function initialize all variables of the class.
		 */
		void Init();

		/**
		 *	@brief This function free the memory of the class, and destroys it's variables.
		 */
		void Destroy();

		/**
		 *	@brief This function is the only one you need to generate Ramer-Douglas-Peucker algorithm.
		 */
		void Run();
	};
}