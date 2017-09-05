#include "LG_Visual.h"

//! Default constructor.
LG_Visual::LG_Visual()
{
	m_Window = nullptr;
	m_DisplayImage = nullptr;
	m_ScreenSurface = nullptr;
	m_sFileName = "Resources\\Textures\\HelloWorld.bmp";
}

//! Default destructor.
LG_Visual::~LG_Visual()
{
	Destroy();
}

//! This function initialize the SDL API.
bool LG_Visual::Init()
{
	/// Initialization flag
	bool success = true;
	/// 
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		/// No inicializó.
		std::cout << "SDL could not initialize! SDL_Error:"
			<< SDL_GetError() << std::endl;
		success = false;
	}

	else
	{
		/// Create window
		m_Window = SDL_CreateWindow(
			"Visual UnitTest",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (m_Window != nullptr)
		{
			m_ScreenSurface = SDL_GetWindowSurface(m_Window);

			SDL_FillRect(m_ScreenSurface, nullptr, SDL_MapRGB(
				m_ScreenSurface->format, 0x00, 0x00, 0x00));
		}
		else
		{
			std::cout << "Window could not be created! SDL_Error:"
				<< SDL_GetError() << std::endl;
			success = false;
		}
	}

	return success;
}

//! This function load a image from file.
bool LG_Visual::LoadImageFromFile(std::string sFileName)
{
	/// Loading success flag
	bool success = true;

	//Load splash image
	m_DisplayImage = SDL_LoadBMP(sFileName.c_str());

	if (m_DisplayImage == nullptr)
	{
		std::cout << "Unable to load image %s! SDL Error"
			<< SDL_GetError() << std::endl;
		success = false;
	}

	return success;
}

//! 
void LG_Visual::Destroy()
{
	/// Deallocate the image to display.
	SDL_FreeSurface(m_DisplayImage);
	m_DisplayImage = nullptr;

	/// Deallocate the screen surface.
	SDL_FreeSurface(m_ScreenSurface);
	m_ScreenSurface = nullptr;

	/// Destroy window
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	
	m_sFileName = "";

	/// Quit SDL subsystems
	SDL_Quit();
}

//! his function renderer the system.
void LG_Visual::Renderer()
{
}

//! This function update the system.
void LG_Visual::Update(float fTime)
{
	/// Update the surface
	SDL_UpdateWindowSurface(m_Window);

	/// Wait for the time given.
	SDL_Delay(fTime);
}

//! This function runs all the functions needed to have SDL working.
void LG_Visual::Run()
{
	/// We initialize SDL, and create a window.
	if (!Init())
	{
		std::cout << "Failed to Initialize SDL"
			<< std::endl;
	}
	else
	{
		/// An image is loaded.
		if (!LoadImageFromFile(m_sFileName))
		{
			std::cout << "Failed to LoadImage"
				<< std::endl;
		}
		else
		{
			///Apply the image
			SDL_BlitSurface(m_DisplayImage, nullptr, m_ScreenSurface, nullptr);
			Update(2000);
		}
	}

	/// Releases the memory.
	Destroy();
}
