#pragma once
#include "Vector3D.h"

namespace LevelGenerator
{
	/**
	 *	@brief This class stores a vertex in a 3D space.
	 */
	class CVertex
	{
	public:

		///************************************************************************/
		///*                        Constructor & Destructor.					  */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		CVertex();

		/**
		 *	@brief Default Destructor.
		 */
		~CVertex();

		/**
		 *	@brief Parameters Constructor.
		 */
		CVertex(CVector3D vPosition);



		///************************************************************************/
		///*						  Member Variables.							  */
		///************************************************************************/

		/**
		 *	@brief This variable stores a 3D position (X,Y,Z).
		 */
		CVector3D m_Position;

		/**
		 *	@brief This variable detects if the vertex is inside of the scalar function given in the grid.
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
