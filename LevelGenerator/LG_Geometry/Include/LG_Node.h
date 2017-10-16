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
		///*                        Constructors & Destructors.					  */
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
		 *	@brief Copy constructor.
		 */
		LG_Node(LG_Node *node);

		/**
		 *	@brief Parameters Constructor.
		 */
		LG_Node(LG_Vector3D vPosition);

		/**
		 *	@brief Parameter Constructor.
		 */
		LG_Node(float fx, float fy, float fz);

		///************************************************************************/
		///*						  Member Variables.							  */
		///************************************************************************/

		/**
		 *	@var Pointer of node that defines what node is the parent. 
		 */

		/**
		 *	@var This variable stores a 3D position (X,Y,Z).
		 */
		LG_Vector3D m_Position;

		/**
		 *	@var This flag determinate if the node is On or Off.
		 */
		bool m_bIsInside;

		/**
		 *	@var This flag determinate if this node can be deleted.
		 */
		bool m_bCanDeleted;

		/**
		 *	@var This flag determinates if the node has already been used.
		 */
		bool m_bIsChecked;

		/**
		 *	@var This variable store's an ID.
		 */
		int32 m_iID;

		/**
		 *	@var This variable store's the weight of the node.
		 */
		float m_fWeight;

		/**
		 *	@var This vector stores a pointer of nodes.
		 */
		Vector<LG_Node*> m_PointerNodes;


		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *	@brief Function to initialize the variables.
		 */
		void Init();

		/**
		 *	@brief Function to release memory and destroy objects.
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

		///************************************************************************/
		///*					Compound Assignment Operators.				      */
		///************************************************************************/

		/**
		 *	@brief This operator compares that 2 Nodes are the same.
		 *	@param const LG_Triangle& OtherNode: The Node to compare with this.
		 *	@return true if the Node is the same that this, otherwise false.
		 */
		bool operator==(const LG_Node& OtherNode) const;

		//TODO: Crear funciones accesoras set y get para poder poner privada la posicion del nodo.
	};
}
