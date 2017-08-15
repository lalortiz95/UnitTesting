#include "LG_Triangle.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_Triangle::LG_Triangle()
	{

	}

	//! Default destructor.
	LG_Triangle::~LG_Triangle()
	{
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_Triangle::Init(LG_Node FirstNode, LG_Node SecondNode, LG_Node ThirdNode)
	{
		/// We give an inital value to the triangle's vertices.
		m_Vertices[0] = FirstNode;
		m_Vertices[1] = SecondNode;
		m_Vertices[2] = ThirdNode;
	}

	//! This function releases memory and clears the variables.
	void LG_Triangle::Destroy()
	{

	}
}