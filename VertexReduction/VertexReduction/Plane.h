#pragma once
#include "Vertex.h"

//!Const that defines the number of vertex that plane has.

/**
 * @brief Plane class. Stores it's 4 vertices, it's width, and height.
 */
class CPlane
{
public:

	/************************************************************************/
	/*                            Constructor & Destructor.                 */
	/************************************************************************/

	//! Default Constructor.
	CPlane();
	//! Default Destructor.
	~CPlane();

	/************************************************************************/
	/*						  Member Variables.								*/
	/************************************************************************/

	//! An array of vertices, one for each corner of the plane.
	CVertex m_Vertices[4];

	//! The witdth given to the plane.
	float m_fWidth;
	//! The height given to the plane.
	float m_fHeight;

	/************************************************************************/
	/*						   Class Functions.								*/
	/************************************************************************/

	/**
	 * @brief Function needed to initialize the variables of the Plane class.
	 * @param CVetor3D vPosition: The position that will be assigned to the first vertex of the plane's array.
	 * @param float fWidth: The width that will be asigned to the plane.
	 * @param float fHeight: The Height that will be asigned to the plane.
	 */
	void Init(CVector3D vPosition, float fWidth, float fHeight);

	/**
	 *	@brief This function changes the position of one vertex of this plane.
	 *	@param int iIndex: The index of vertex in this plane that we want to move.
	 *	@param CVector3D newPosition: The new position to move the vertex.
	 */
	void MoveVertex(int iIndex, CVector3D newPosition);

};

