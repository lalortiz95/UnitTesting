#include "LG_Visual.h"
#include <LG_DelaunayTriangulation.h>
#include <LG_Generate.h>

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

		/// Create the renderer.
		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

		if (m_Renderer == nullptr)
		{
			std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
				success = false;
			}
		}

		if (m_Window != nullptr)
		{
			m_ScreenSurface = SDL_GetWindowSurface(m_Window);

			SDL_FillRect(m_ScreenSurface, nullptr, SDL_MapRGB(
				m_ScreenSurface->format, 0xFF, 0xFF, 0xFF));
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
	/// Quit SDL image subsystems.
	IMG_Quit();
}

//! his function renderer the system.
void LG_Visual::Renderer()
{
	///Clear screen
	SDL_RenderClear(m_Renderer);

	/// The class that generates all of the algorithms.
	LevelGenerator::LG_Generate AlgorithmGeneration;

	/// We generate our algorithms.
	AlgorithmGeneration.Run();

	LevelGenerator::LG_Vector3D posToSpawn;
	LevelGenerator::LG_Vector3D Secondpos;
	///We draw a dot wherever there is a node, as an output of the performed Delaunay Triangulation algorithm.
	for (LevelGenerator::int32 i = 0; i < AlgorithmGeneration.m_DT.m_NodesCloud.size(); ++i)
	{
		posToSpawn = AlgorithmGeneration.m_DT.m_NodesCloud[i].m_Position;
		// Draw red dot
		SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
		// en la posición de cada nodo dibujar un punto con SDL.
		SDL_RenderDrawPoint(m_Renderer, posToSpawn.X, posToSpawn.Y);

		//if (i < AlgorithmGeneration.m_DT.m_NodesCloud.size() - 1)
		//{
		//	Secondpos = AlgorithmGeneration.m_DT.m_NodesCloud[i + 1].m_Position;
		//	// Draw red dot
		//	SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0xFF, 0xFF);
		//	// en la posición de cada nodo dibujar un punto con SDL.
		//	SDL_RenderDrawLine(m_Renderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
		//}
	}

	//TODO: con la lista de aristas que nos da DT dibujar los triangulos.
	for (LevelGenerator::int32 i = 0; i < AlgorithmGeneration.m_DT.m_TrianglesVector.size(); ++i)
	{
		for (LevelGenerator::int32 j = 0; j < 3; ++j)
		{
			posToSpawn = AlgorithmGeneration.m_DT.m_TrianglesVector[i].m_Aristas[j].m_pFirstNode->m_Position;
			Secondpos = AlgorithmGeneration.m_DT.m_TrianglesVector[i].m_Aristas[j].m_pSecondNode->m_Position;

			// Draw red dot
			SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
			// en la posición de cada nodo dibujar un punto con SDL.
			SDL_RenderDrawLine(m_Renderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
		}
	}

	///Update screen
	SDL_RenderPresent(m_Renderer);
}

//! This function update the system.
void LG_Visual::Update(float fTime)
{
	/// Update the surface
	SDL_UpdateWindowSurface(m_Window);
}

//! This function runs all the functions needed to have SDL working.
void LG_Visual::Run()
{
	///Event handler
	SDL_Event e;
	/// Let us know, when to end the application loop.
	bool bQuit = false;

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
			//SDL_BlitSurface(m_DisplayImage, nullptr, m_ScreenSurface, nullptr);
		}
	}

	//TODO: revisar porque no se pintan los puntos.
	while (!bQuit)
	{
		///Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			///User requests quit
			if (e.type == SDL_QUIT)
			{
				bQuit = true;
			}
		}

		Update(2000);
		Renderer();	
	}

	/// Releases the memory.
	Destroy();
}

//! Loads individual image as texture.
SDL_Texture * LG_Visual::loadTexture(std::string path)
{
	///The final texture
	SDL_Texture* newTexture = nullptr;

	///Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		std::cout << "Unable to load image " << path.c_str() << "SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		///Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
		if (newTexture == nullptr)
		{
			std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
		}

		///Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	///Returns the texture we've just created.
	return newTexture;
}
