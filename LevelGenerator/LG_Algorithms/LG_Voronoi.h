#pragma once
#include "LG_AlgorithmsPrerequisites.h"

namespace LevelGenerator
{
	/**
	 *	@brief This class generates voronio Algorithm.
	 */
	class LG_ALGORITHMS_EXPORT LG_Voronoi
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_Voronoi();

		/**
		 *	@brief Default destructor.
		 */
		~LG_Voronoi();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief
		 */

		 ///************************************************************************/
		 ///*						   Class Functions.							  */
		 ///************************************************************************/

		/**
		 *  @brief 
		 */
		void Init();

		/**
		 *  @brief
		 */
		void Destroy();

		/**
		 *  @brief
		 *	@param float fDelta: the time for each frame.
		 */
		void Update(float fDelta);

		/**
		 *  @brief
		 */
		void Run();
	};
}