#pragma once
#include "LG_AlgorithmsPrerequisites.h"

namespace LevelGenerator
{
	/**
	 *	@brief This class manages and unificates all the algorithms in the project.
	 */
	class LG_ALGORITHMS_EXPORT LG_DelaunayTriangulation
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default constructor.
		 */
		LG_DelaunayTriangulation();

		/**
		 *	@brief Default destructor.
		 */
		~LG_DelaunayTriangulation();

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
		 *  @brief This function initialize all variables of the class.
		 */
		void Init();

		/**
		*  @brief This function releases memory and clears the variables.
		*/
		void Destroy();

		/**
		 *  @brief This function performs the algorithm.
		 */
		void Run();
	};
}