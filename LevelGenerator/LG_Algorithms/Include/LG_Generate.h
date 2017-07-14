#pragma once
#include "LG_AlgorithmsPrerequisites.h"
#include "LG_MarchingSquare.h"
#include "LG_RDP.h"
#include <LG_Grid.h>

namespace LevelGenerator
{
	/**
	 *	@brief This class manages and unificates all the algorithms in the project.
	 */
	class LG_ALGORITHMS_EXPORT LG_Generate
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default constructor.
		 */
		LG_Generate();
		/**
		 *	@brief Default destructor.
		 */
		~LG_Generate();
	
		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief An object of the marching square class. It's used to run the algorithm.
		 */
		LG_MarchingSquare m_MS;

		/**
		 *	@brief A map where we generate marching square.
		 */
		LG_Grid* m_pMap;
		 ///************************************************************************/
		 ///*						   Class Functions.							  */
		 ///************************************************************************/

		 /**
		  *  @brief This function initialize all variables of the class.
		  */
		 void Initialize();

		 /**
		  *	@brief This function free the memory of the class, and destroys it's variables.
		  */
		 void Destroy();

		 /**
		  *	@brief This calls all the algorithms and put them together to generate a procedural level.
		  */
		 void Run();
	};
}