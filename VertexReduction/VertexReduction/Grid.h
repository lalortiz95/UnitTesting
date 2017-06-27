#pragma once
#include "Plane.h"


namespace LevelGenerator
{
	/**
	 *	@brief This class stores a bidimensional array of planes to generate a grid.
	 */
	class CGrid
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
		 *	@brief Const to define how many planes there will be.
		 */
		static const int m_kPlaneAmountCalculation;

		/**
		 *	@brief This variable stores the number of planes in x.
		 */
		int m_iNumberPlanesX;

		/**
		 *	@brief This variable stores the number of planes in y.
		 */
		int m_iNumberPlanesY;

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
	};
}

