#include "LG_Grid.h"
#include <random>

namespace LevelGenerator
{
	//! Default constructor.
	LG_Grid::LG_Grid()
	{

	}

	//! Default destructor.
	LG_Grid::~LG_Grid()
	{
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_Grid::Init(int iPlaneAmoutX, int iPlaneAmoutY)
	{
		/// Stores the width and height in the member variable for future references.
		m_iHeight = iPlaneAmoutX * LG_Tile::SIZE_OF_PLANE;
		m_iWidth = iPlaneAmoutY * LG_Tile::SIZE_OF_PLANE;

		/// First calculate the number of planes in x and y axis.
		m_iNumberPlanesX = iPlaneAmoutX;
		m_iNumberPlanesY = iPlaneAmoutY;

		/// Then we assing memory for each plane in x.
		m_Grid = new LG_Tile*[m_iNumberPlanesX];

		/// For each plane in x array, we assing a new plane in y.
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			m_Grid[i] = new LG_Tile[m_iNumberPlanesY];

		}

		LG_Vector3D tempVec(0, 0, 0);
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			for (int j = 0; j < m_iNumberPlanesY; ++j)
			{
				m_Grid[i][j].Init(tempVec);
				tempVec.Y += LG_Tile::SIZE_OF_PLANE;
			}
			tempVec.X += LG_Tile::SIZE_OF_PLANE;
		}	

		LG_Vector3D tempPos(0, 0, 0);
		tempPos.X = rand() % m_iWidth;
		tempPos.Y = rand() % m_iHeight;

		float fTempRadius = 100;
		m_Cricle.Init(tempPos, fTempRadius);
	}

	//! This function free all memory and deletes the objects.
	void LG_Grid::Destroy()
	{
		/// If the memory of the array of planes isn't nullptr.
		if (m_Grid != nullptr)
		{
			for (int i = m_iNumberPlanesX; i > 0; --i)
			{
				for (int j = m_iNumberPlanesY; i > 0; --j)
				{
					/// If the memory of the pointer isn't nullptr.
					if (m_Grid[i] != nullptr)
					{

						m_Grid[i][j].Destroy();
					}
				}
			}
		}
	}

	//! Calls necessary functions to generate the algorithm.
	void LG_Grid::MarchingSquare()
	{
		///We go through the TileMap, checking each one of it's vertices with the scalar function of a circle.
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			for (int j = 0; j < m_iNumberPlanesY; ++j)
			{
				/// We iterate through every vertex in the plane.
				for (int k = 0; k < LG_Tile::NUM_VERTEX_PER_PLANE; ++k)
				{
					/// We assign the flag, that if inside it's true, otherwise it's false.
					m_Grid[i][j].m_Vertices[k].m_bIsInside = CalculatePlaneCase(m_Grid[i][j].m_Vertices[k].m_Position);
					
				}
			}
		}

		/// We create a temporal vector to store planes that interact with the line.
		std::vector<LG_Tile> tempPlaneVect;

		/// We store the planes that have at least one of their vertices as true.
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			for (int j = 0; j < m_iNumberPlanesY; ++j)
			{
				for (int k = 0; k < LG_Tile::NUM_VERTEX_PER_PLANE; ++k)
				{
					if (m_Grid[i][j].m_Vertices[k].m_bIsInside)
					{
						tempPlaneVect.push_back(m_Grid[i][j]);
					}
				}
			}
		}
		tempPlaneVect = tempPlaneVect;
	}

	//! This function Calculates each plane's case. It's done comparing a scalar function with each vertice's position.
	bool LG_Grid::CalculatePlaneCase(LG_Vector3D vPosition)
	{
		/// Check if the magnitud bettewn the circle position and the position of the vertex is
		/// less than the radius.
		if (vPosition.Magnitud(m_Cricle.m_Position - vPosition) < m_Cricle.m_fRadius)
		{
			/// If that is the case we return true.
			return true;
		}
	
		return false;
	}

	//! This function returns the number of planes in the grid, in the X axis.
	int LG_Grid::GetPlanesX()
	{
		/// The number of planes in X Axis.
		return m_iNumberPlanesX;
	}

	//! This function returns the number of planes in the grid, in the Y axis.
	int LG_Grid::GetPlanesY()
	{
		/// The number of planes in Y Axis.
		return m_iNumberPlanesY;
	}
}