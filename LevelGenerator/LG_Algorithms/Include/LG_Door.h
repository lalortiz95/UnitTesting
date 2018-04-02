#pragma once
#include "LG_AlgorithmsPrerequisites.h"

#include <LG_Node.h>

namespace LevelGenerator
{

	class LG_ALGORITHMS_EXPORT LG_Door
	{
	public:

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default constructor.
		 */
		LG_Door();

		/**
		 *	@brief Parameter constructor.
		 *	@param LG_Node* pFirstPosition: The first position of the door.
		 *	@param LG_Node* pSecondPosition: The second position of the door.
		 */
		LG_Door(LG_Node* pFirstPosition, LG_Node* pSecondPosition);

		/**
		 *	@brief Default destructor.
		 */
		~LG_Door();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@var This varible is used to define a ID it's unique.
		 */
		int32 m_iID;

		/**
		 *	@var This variable store the width of the door.
		 */
		float m_fWidth;

		/**
		 *	@var This variable store the height of the door.
		 */
		float m_fHeight;

		/**
		 *	@var This flag is used when filling the door and wall vectors.
		 */
		bool m_bIsChecked;

		/**
		 *	@var The first position of the door.
		 */
		LG_Node* m_pFirstPosition;

		/**
		 *	@var The second position of the door.
		 */
		LG_Node* m_pSecondPosition;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief This function release the memory of the object.
		 */
		void Destroy();
	};
}

