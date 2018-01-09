#pragma once

#include <LG_UtilitiesPrerequisites.h>
#include <LG_Vector3D.h>
#include <string.h>

#include <LG_Generate.h>

#include <LG_Triangle.h>
#include <LG_Circle.h>

#include <SDL.h>
#include <SDL_image.h>

#include <time.h>
#include <iostream>

using namespace LevelGenerator;


#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

class LG_Generate;

//TODO: cambiar el string de std por el nuestro.

/**
 *	@brief This class shows a visual representation of the algorithms' functionality.
 */
class LG_Visual
{
public:

	///************************************************************************/
	///*                            Constructor & Destructor.                 */
	///************************************************************************/

	/**
	 *	@brief Default Constructor.
	 */
	LG_Visual();

	/**
	 *	@brief Default Destructor.
	 */
	~LG_Visual();

	///**************************************************************************/
	///*						  Member Variables.								*/
	///**************************************************************************/

	/**
	 *	@var A pointer to the SDL_Window object.
	 */
	SDL_Window* m_Window;

	/**
	 *	@var A Pointer to the SDL_Surface object.
	 */
	SDL_Surface* m_ScreenSurface;

	/**
	 *	@var A Pointer to the SDL_Surface object.
	 */
	SDL_Surface* m_DisplayImage;

	/**
	 *	@var The file name.
	 */
	std::string m_sFileName;

	/**
	 *	@var The SDL renderer.
	 */
	SDL_Renderer* m_Renderer;

	///************************************************************************/
	///*						   Class Functions.							  */
	///************************************************************************/

	/**
	 *	@brief This function initialize the SDL API.
	 *	@return true if the initialization has success, otherwise false.
	 */
	bool Init();

	/**
	 *	@brief This function load a image from file.
	 *	@param string sFileName: Name of the file to load.
	 *	@return true if the image loaded correctly, otherwise false.
	 */
	bool LoadImageFromFile(std::string sFileName);

	/**
	 *	@brief This function releases all memory of the SDL.
	 */
	void Destroy();

	/**
	 *	@brief This function renderer the system.
	 */
	void Renderer();

	/**
	 *	@brief This function update the system.
	 *	@param float fTime: Time to update.
	 */
	void Update(float fTime);

	/**
	 *	@brief This function runs all the functions needed to have SDL working.
	 */
	void Run();

private:

	/**
	 *	@var The algorithm generation var.
	 */
	LevelGenerator::LG_Generate m_AlgorithmGeneration;

	/**
	 *	@brief Loads individual image as texture.
	 */
	SDL_Texture* loadTexture(std::string path);

	/**
	 *	@brief Draws a circle.
	 *	@param LG_Circle circle: the circle that is going to be drawn.
	 *	@param LG_Vector3D color: the color that will have the circle.
	 *	@param uint32 sides: the sides that the triangle will have.
	 */
	void DrawCircle(LG_Circle circle, LG_Vector3D color, LevelGenerator::uint32 sides);

	/**
	 *	@brief Draws a circle.
	 *	@param LG_Vector3D StartPosition: 
	 *	@param LG_Vector3D EndPosition:
	 *	@param float fWidth:
	 */
	void FillRect(LG_Vector3D StartPosition, LG_Vector3D EndPosition, float fWidth);
};