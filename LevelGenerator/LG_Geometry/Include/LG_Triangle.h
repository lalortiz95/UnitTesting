#pragma once
#include "LG_GeometryPrerequisites.h"
#include "LG_Node.h"

namespace LevelGenerator
{
	/**
	*	@brief This class stores a triangle.
	*/
	class LG_GEOMETRY_EXPORT LG_Triangle
	{
	public:

		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		 *	@brief Default constructor.
		 */
		LG_Triangle();

		/**
		 *	@brief Default destructor.
		 */
		~LG_Triangle();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief each vertex that makes the triangle.
		 */
		LG_Node m_Vertices[3];

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *  @brief This function initialize all variables of the class.
		 */
		void Init(LG_Node FirstNode, LG_Node SecondNode, LG_Node ThirdNode);

		/**
		 *  @brief This function releases memory and clears the variables.
		 */
		void Destroy();
	};
}