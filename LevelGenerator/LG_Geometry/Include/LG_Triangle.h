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
		/**
		*	@brief The triangle's arista.
		*/
		class LG_Arista
		{
		public:
			///************************************************************************/
			///*                            Constructor & Destructor.                 */
			///************************************************************************/

			/**
			 *	@brief Default constructor.
			 */
			LG_Arista();
	
			/**
			 *	@brief Parameter constructor.
			 *	@param LG_Node* pFirstNode: The first pointer node of the arista.
			 *	@param LG_Node* pSecondNode: The second pointer node of the arista.
			 */
			LG_Arista(LG_Node* FirstNode, LG_Node* SecondNode);

			/**
			 *	@brief Default destructor.
			 */
			~LG_Arista();

			///************************************************************************/
			///*                           Member Variables.		                  */
			///************************************************************************/

			/**
			 *	@brief First node pointer of the arista.
			 */
			LG_Node* m_pFirstNode;

			/**
			 *	@brief Second node pointer of the arista.
			 */
			LG_Node* m_pSecondNode;

			/**
			 *	@brief The arista's magnitude.
			 */
			float m_fDistance;

			///************************************************************************/
			///*                           Class Functions.						      */
			///************************************************************************/

			/**
			 *  @brief This function initialize all variables of the class.
			 *	@param LG_Node* pFirstNode: The first pointer node of the arista.
			 *	@param LG_Node* pSecondNode: The second pointer node of the arista.
			 */
			void Init(LG_Node* pFirstNode, LG_Node* pSecondNode);

			/**
			 *	@brief This function realeases memory.
			 */
			void Destroy();

		};

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
		Vector<LG_Node*> m_pVertices;
		
		/**
		 *	@brief Where we store all of the triangle's aristas.
		 */
		LG_Arista m_Aristas[3];

		/**
		 *	@brief True when all of the triangles inside of the triangle have already been checked.
		 */
		bool m_bIsChecked;

		/**
		 *	@brief The triangle's  ID.
		 */
		int32 m_iID;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

		/**
		 *  @brief This function initialize all variables of the class.
		 *	@param LG_Node* pFirstNode: The first node of the triangle.
		 *	@param LG_Node* pSecondNode: The second node of the triangle.
		 *	@param LG_Node* pThirdNode: The third node of the triangle.
		 */
		void Init(LG_Node* pFirstNode, LG_Node* pSecondNode, LG_Node* pThirdNode);

		/**
		 *  @brief This function releases memory and clears the variables.
		 */
		void Destroy();

		/**
		 *  @brief This function tells if a given node is inside of the triangle.
		 *	@param LG_Node* pPointToCompare: The point that we want to know if is inside.
		 *	@return true if the node was inside, false otherwise.
		 */
		bool IsPointInside(LG_Node* pPointToCompare);

	private:

		/**
		 *  @brief Perfroms a cross product between the aristas.
		 *	@param LG_Node* pNodeToCompare: Node that doesn't belong to the triangle.
		 *	@param LG_Node* pNode1: First node taken from the triangle.
		 *	@param LG_Node* pNode2: Second node taken from the triangle.
		 *	@return The cross product of a 2D vector.
		 */
		float Sign(LG_Node* pNodeToCompare, LG_Node* pNode1, LG_Node* pNode2);
	};
}