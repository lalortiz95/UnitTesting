#pragma once
#include "PrerequisitesLevelGenerator.h"
#include "Circle.h"
#include "Plane.h"

#include <vector>

namespace LevelGenerator
{
	/**
	 *	@brief This class stores a bidimensional array of planes to generate a grid.
	 */
	class LG_EXPORT CGrid
	{
	public:
		///************************************************************************/
		///*                            Constructor & Destructor.                 */
		///************************************************************************/

		/**
		*	@brief Default Constructor.
		*/
		CGrid();

		/**
		*	@brief Default Destructor.
		*/
		~CGrid();

		///**************************************************************************/
		///*						  Member Variables.								*/
		///**************************************************************************/

		/**
		 *	@brief This variable stores the height of the grid.
		 */
		int m_iHeight;

		/**
		 *	@brief This variable stores the width of the grid.
		 */
		int m_iWidth;

		/**
		 *	@brief Bidimensional array that stores the planes.
		 */
		CPlane** m_ppPlane;

	private:

		/**
		 *	@brief This variable stores the number of planes in x.
		 */
		int m_iNumberPlanesX;

		/**
		 *	@brief This variable stores the number of planes in y.
		 */
		int m_iNumberPlanesY;


		/**
		 *	@brief Circle.
		 */
		CCircle m_Cricle;

		///************************************************************************/
		///*						   Class Functions.							  */
		///************************************************************************/

	public:
		/**
		 *	@brief This function initialize all variables of the class.
		 *	@param int iWidth: The width of the grid.
		 *  @param int iHeight: The height of the grid.
		 */
		void Init(int iWidth, int iHeight);


		/**
		 *	@brief This function realeases the memory of the class.
		 */
		void Destroy();

		/**
	  	 *	@brief Calls necessary functions to generate the algorithm.
		 */
		void MarchingSquare();

		/**
		 *	@brief This function Calculates each plane's case. It's done comparing a scalar function with each vertice's position.
		 *	@param CVector3D vPosition: the position of the scalar function origin's.
		 *	@return if its or not inside of the scalar function. True when its inside.
		 */
		bool CalculatePlaneCase(CVector3D vPosition);

		///************************************************************************/
		///*						   Accessors.								  */
		///************************************************************************/

		/**
		 *	@brief This function returns the number of planes in the grid, in the X axis.
		 *	@return the number of planes in the X axis.
		 */
		int GetPlanesX();

		 /**
		  *	@brief This function returns the number of planes in the grid, in the Y axis.
		  *	@return the number of planes in the Y axis.
		  */
		int GetPlanesY();
	};
}

