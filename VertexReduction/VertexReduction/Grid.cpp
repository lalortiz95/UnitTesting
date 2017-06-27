#include "Grid.h"

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