#pragma once
#include <iostream>
#include <LG_UtilitiesPrerequisites.h>
#include <string.h>
#include <SDL.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

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
	 *	@brief A pointer to the SDL_Window object.
	 */
	SDL_Window* m_Window;

	/**
	 *	@brief A Pointer to the SDL_Surface object.
	 */
	SDL_Surface* m_ScreenSurface;

	/**
	 *	@brief A Pointer to the SDL_Surface object.
	 */
	SDL_Surface* m_DisplayImage;

	/**
	 *	@brief The file name.
	 */
	std::string m_sFileName;

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
};