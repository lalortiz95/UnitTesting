#include "LG_Generate.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_Generate::LG_Generate()
	{

	}

	//! Default destructor.
	LG_Generate::~LG_Generate()
	{

	}

	//! This function initialize all variables of the class.
	void LG_Generate::Initialize()
	{

	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_Generate::Destroy()
	{

	}

	//! This calls all the algorithms and put them together to generate a procedural level.
	void LG_Generate::Run()
	{
		//TODO: with the generated cases make an isoiline.
		//we apply then, RDP algorithm to reduce that isoloine.
		//Now we have a reduced set of points, that will be used to 
		//Generate delaunay triangulation.
		/// A map to work with for our marching square algorithm.
		m_pMap = new LG_Grid();
		m_pMap->Init(20, 12);
		/// We run marching square with the generated grid.
		m_MS.Run(m_pMap);
	}
}