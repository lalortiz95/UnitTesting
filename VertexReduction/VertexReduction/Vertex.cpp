#include "Vertex.h"


/**
 *	@brief Default Constructor.
 */
CVertex::CVertex()
{
}


/**
 *	@brief Default Destructor.
 */
CVertex::~CVertex()
{
	//! Calls the destroy function.
	Destroy();
}

/**
 *	@brief Parameter Constructor.
 *	@param CVector3D Is the wanted position for the vertex.
 */
CVertex::CVertex(CVector3D vPosition)
{
	m_Position = vPosition;
}

/**
 *	@brief Initialize resources of the vertex.
 */
void CVertex::Init()
{
}


/**
 *	@brief Free and delete memory.
 */
void CVertex::Destroy()
{
}




