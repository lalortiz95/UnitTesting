#pragma once
#include "LG_AlgorithmsPrerequisites.h"
#include <LG_Rect.h>

namespace LevelGenerator
{
	class LG_ALGORITHMS_EXPORT LG_Wall : public LG_Rect
	{
	public:

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_Wall();

		///**
		// *	@brief Parameter Constructor.
		// */
		//LG_Wall(LG_Node CenterNode, float fWidth, float fHeight);

		/**
		 *	@brief Default Destructor.
		 */
		~LG_Wall();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@var A flag to see if the wall is horizontal or vertical when seen ffrom above.
		 */
		bool m_bIsHorizontal;


		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		///**
		//*	@brief This function initialize el area of the wall.
		//*	@param LG_Node CenterNode: The position of the wall.
		//*	@param float fWidth: The width of the wall.
		//*	@param float fHeight: The height of the wall.
		//*/
		//void Init(LG_Node CenterNode, float fWidth, float fHeight);

		/**
		*	@brief This function release the memory that was using in the room.
		*/
		void Destroy();
	};
}