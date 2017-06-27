#include "Grid.h"

#include <random>

namespace LevelGenerator
{
	//! Default constructor.
	CGrid::CGrid()
	{

	}

	//! Default destructor.
	CGrid::~CGrid()
	{
		Destroy();
	}

	//! This function initialize all variables of the class.
	void CGrid::Init(int iPlaneAmoutX, int iPlaneAmoutY)
	{
		/// Stores the width and height in the member variable for future references.
		m_iHeight = iPlaneAmoutX * CPlane::m_iSize;
		m_iWidth = iPlaneAmoutY * CPlane::m_iSize;

		/// First calculate the number of planes in x and y axis.
		m_iNumberPlanesX = iPlaneAmoutX;
		m_iNumberPlanesY = iPlaneAmoutY;

		/// Then we assing memory for each plane in x.
		m_ppPlane = new CPlane*[m_iNumberPlanesX];

		/// For each plane in x array, we assing a new plane in y.
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			m_ppPlane[i] = new CPlane[m_iNumberPlanesY];

		}

		CVector3D tempVec(0, 0, 0);
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			for (int j = 0; j < m_iNumberPlanesY; ++j)
			{
				m_ppPlane[i][j].Init(tempVec);
				tempVec.Y += CPlane::m_iSize;
			}
			tempVec.X += CPlane::m_iSize;
		}

		//float fTempRadius = rand() % 50;

		CVector3D tempPos(0, 0, 0);
		tempPos.X = rand() % m_iWidth;
		tempPos.Y = rand() % m_iHeight;

		float fTempRadius = 100;
		//fTempRadius = sqrt(pow(tempPos.X, 2) + pow(tempPos.Y, 2));
		m_Cricle.Init(tempPos, fTempRadius);
	}

	//! This function free all memory and deletes the objects.
	void CGrid::Destroy()
	{
		/// If the memory of the array of planes isn't nullptr.
		if (m_ppPlane != nullptr)
		{
			for (int i = m_iNumberPlanesX; i > 0; --i)
			{
				for (int j = m_iNumberPlanesY; i > 0; --j)
				{
					/// If the memory of the pointer isn't nullptr.
					if (m_ppPlane[i] != nullptr)
					{

						m_ppPlane[i][j].Destroy();
					}
				}
			}
		}
	}
	//! Calls necessary functions to generate the algorithm.
	void CGrid::MarchingSquare()
	{
		float fResult = 0;
		///We go through the TileMap, checking each one of it's vertices with the scalar function of a circle.
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			for (int j = 0; j < m_iNumberPlanesY; ++j)
			{
				//TODO: hacer constante de numer de indices.
				for (int k = 0; k < 3; ++k)
				{
					m_ppPlane[i][j].m_Vertices[k].m_bIsInside = CalculatePlaneCase(m_ppPlane[i][j].m_Vertices[k].m_Position);
				}
			}
		}

		std::vector<CPlane> tempPlaneVect;
		for (int i = 0; i < m_iNumberPlanesX; ++i)
		{
			for (int j = 0; j < m_iNumberPlanesY; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					if (m_ppPlane[i][j].m_Vertices[k].m_bIsInside)
					{
						tempPlaneVect.push_back(m_ppPlane[i][j]);
					}
				}
			}
		}
		tempPlaneVect = tempPlaneVect;
	}

	//! This function Calculates each plane's case. It's done comparing a scalar function with each vertice's position.
	bool CGrid::CalculatePlaneCase(CVector3D vPosition/*, float fRadius*/)
	{
		//float fRadiusSquared = pow(m_Cricle.m_fRadius, 2);
		//float fXSquared = pow(vPosition.X - m_Cricle.m_Position.X, 2);
		//float fYSquared = pow(vPosition.Y - m_Cricle.m_Position.Y, 2);
		if (vPosition.Magnitud(m_Cricle.m_Position - vPosition) < m_Cricle.m_fRadius)
		{
			return true;
		}
		//if ((fXSquared + fYSquared) < fRadiusSquared)
		//{
		//	return true;
		//}
		return false;

		/*return fXSquared + fYSquared - fRadiusSquared;*/
	}

	//! This function returns the number of planes in the grid, in the X axis.
	int CGrid::GetPlanesX()
	{
		return m_iNumberPlanesX;
	}

	//! This function returns the number of planes in the grid, in the Y axis.
	int CGrid::GetPlanesY()
	{
		return m_iNumberPlanesY;
	}
}