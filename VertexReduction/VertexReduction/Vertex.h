#pragma once
#include "Vector3D.h"

/**
 *	@brief This class stores a vertex in a 3D space.
 */
class CVertex
{
public:

	/************************************************************************/
	/*                        Constructor & Destructor.						*/
	/************************************************************************/

	//! Default Constructor.
	CVertex();
	//! Default Destructor.
	~CVertex();
	//! Parameters Constructor.
	CVertex(CVector3D vPosition);

	

	/************************************************************************/
	/*						  Member Variables.								*/
	/************************************************************************/

	//! This variable stores a 3D position (X,Y,Z).
	CVector3D m_Position;
	//! This variable stores an ID for purposes of identification when using a vertex.
	int m_iID;

	/************************************************************************/
	/*						   Class Functions.								*/
	/************************************************************************/

	//! Function to initialize the variables.
	void Init();

	//! Function to realease memory and destroy objects.
	void Destroy();
};

