#pragma once
#include "Vertex.h"

#include <vector>


/**
* @brief Isoline class. stores a vector of Vertices.
*/
class CIsoline
{
public:

	/************************************************************************/
	/*                            Constructor & Destructor.                 */
	/************************************************************************/

	//!Default constructor and destructor.
	CIsoline();
	~CIsoline();

	/************************************************************************/
	/*                       Class' functions                               */
	/************************************************************************/
	
	/**
	 * @brief Initialize function allocates if needed, memory for it's variables.
	 */
	void Initialize();
	/**
	* @brief Releases memory, and deletes it's variables.
	*/
	void Destroy();

	/************************************************************************/
	/*						  Member Variables.								*/
	/************************************************************************/

	//!Array to store the lines.
	std::vector<CVertex> m_VertexVector;
};

