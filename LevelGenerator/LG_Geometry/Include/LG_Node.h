#pragma once
#include "LG_GeometryPrerequisites.h"
#include <LG_Vector3D.h>

namespace LevelGenerator
{
	/**
	 *	@brief This class stores a node in a 3D space.
	 */
	class LG_GEOMETRY_EXPORT LG_Node
	{
	public:

		///************************************************************************/
		///*                        Constructor & Destructor.					  */
		///************************************************************************/

		/**
		 *	@brief Default Constructor.
		 */
		LG_Node();

		/**
		 *	@brief Default Destructor.
		 */
		~LG_Node();

		/**
		 *	@brief Parameters Constructor.
		 */
		LG_Node(LG_Vector3D vPosition);



		///************************************************************************/
		///*						  Member Variables.							  */
		///************************************************************************/

		/**
		 *	@brief This variable stores a 3D position (X,Y,Z).
		 */
		LG_Vector3D m_Position;

		/**
		 *	@brief This flag determinate if the node is On or Off.
		 */
		bool m_bIsInside;

		/**
		 *	@brief This flag determinate if this node can be deleted.
		 */
		bool m_bCanDeleted;

		/**
		 *	@brief This variable store's an ID.
		 */
		int32 m_iID;


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

		///************************************************************************/
		///*						  Assignment Operator.						  */
		///************************************************************************/
		
		/**
		 *	@brief This operator assigns the values from other node to this node.
		 *	@param const LG_Node& OtherNode: The node that we want to assign it's values.
		 *	@return the new values for this node.
		 */
		LG_Node& operator=(const LG_Node& OtherNode);

		//TODO: Crear funciones accesoras set y get para poder poner privada la posicion del nodo.
	};
}
