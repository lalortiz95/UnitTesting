#include "LG_Visual.h"
#include <LG_DelaunayTriangulation.h>
#include <LG_Vector2D.h>
#include <LG_Math.h>

//! Default constructor.
LG_Visual::LG_Visual()
{
	m_Window = nullptr;
	m_DisplayImage = nullptr;
	m_ScreenSurface = nullptr;
	m_Renderer = nullptr;

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
	srand((int32)time(NULL));
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
		//SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);

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

	/// We generate our algorithms.
	//m_AlgorithmGeneration.Run(50, LG_Vector3D(20, 20, 0), LG_Vector3D(70, 70, 0), 1);

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
	if (m_DisplayImage != nullptr)
	{
		SDL_FreeSurface(m_DisplayImage);
		m_DisplayImage = nullptr;
	}

	/// Deallocate the screen surface.
	if (m_ScreenSurface != nullptr)
	{
		SDL_FreeSurface(m_ScreenSurface);
		m_ScreenSurface = nullptr;
	}

	/// Destroy window
	if (m_Window != nullptr)
	{
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}

	m_sFileName = "";

	/// Quit SDL subsystems
	SDL_Quit();
	/// Quit SDL image subsystems.
	IMG_Quit();
}

//! his function renderer the system.
void LG_Visual::Renderer()
{
	/// Set the color.
	SDL_SetRenderDrawColor(m_Renderer, 45, 45, 48, 0xFF);
	///Clear screen
	SDL_RenderClear(m_Renderer);

	///// The class that generates all of the algorithms.
	LevelGenerator::LG_Generate AlgorithmGeneration;

	/// Temp Position
	LG_Vector3D FirstPos;
	LG_Vector3D SecondPos;

	/// Aqui rendereamos los ciruclos creados a partir de cada triangulo de la triangulacion.
	LG_Vector3D Color{ 0,255,0 };

	/// Set the color.
	SDL_SetRenderDrawColor(m_Renderer, 45, 45, 48, 0xFF);
	///Clear screen
	SDL_RenderClear(m_Renderer);

	/// Semilla bien chingona   41241  separacion 0
	/// We generate our algorithms.
	AlgorithmGeneration.Run(50, LG_Vector3D(40, 40, 0), LG_Vector3D(70, 70, 30), rand(), rand() % 11); //, 25346, 0);


	/*/// Aquí  se renderea el minimum spanning tree //////////////////////////////////////////////////
	for (int32 i = 0; i < AlgorithmGeneration.m_MST.m_FinalTree.size(); ++i)
	{
		FirstPos = AlgorithmGeneration.m_MST.m_FinalTree[i]->m_pFirstNode->m_Position;
		SecondPos = AlgorithmGeneration.m_MST.m_FinalTree[i]->m_pSecondNode->m_Position;
		SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 0);
		SDL_RenderDrawLine(m_Renderer, FirstPos.X, FirstPos.Y, SecondPos.X, SecondPos.Y);
	}*/

	//////// Aqui se renderean los cuartos
	//for (int32 i = 0; i < AlgorithmGeneration.m_RoomsVector.size(); ++i)
	//{
	//	/// Sets the color of the rectangle.
	//	SDL_SetRenderDrawColor(m_Renderer, 0, 255, 255, 0xFF);

	//	/// Draws the top line of the rectangle.
	//	FirstPos.X = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_TopLeft.m_Position.X;
	//	FirstPos.Y = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_TopLeft.m_Position.Y;

	//	SecondPos.X = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_TopRight.m_Position.X;
	//	SecondPos.Y = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_TopRight.m_Position.Y;

	//	SDL_RenderDrawLine(m_Renderer, (int32)FirstPos.X, (int32)FirstPos.Y, (int32)SecondPos.X, (int32)SecondPos.Y);

	//	/// Draws the bottom line of the rectangle.
	//	FirstPos.X = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_BottomLeft.m_Position.X;
	//	FirstPos.Y = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_BottomLeft.m_Position.Y;

	//	SecondPos.X = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_BottomRight.m_Position.X;
	//	SecondPos.Y = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_BottomRight.m_Position.Y;

	//	SDL_RenderDrawLine(m_Renderer, (int32)FirstPos.X, (int32)FirstPos.Y, (int32)SecondPos.X, (int32)SecondPos.Y);

	//	/// Draws the left line of the rectangle.
	//	FirstPos.X = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_BottomLeft.m_Position.X;
	//	FirstPos.Y = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_BottomLeft.m_Position.Y;

	//	SecondPos.X = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_TopLeft.m_Position.X;
	//	SecondPos.Y = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_TopLeft.m_Position.Y;

	//	SDL_RenderDrawLine(m_Renderer, (int32)FirstPos.X, (int32)FirstPos.Y, (int32)SecondPos.X, (int32)SecondPos.Y);

	//	/// Draws the right line of the rectangle.
	//	FirstPos.X = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_BottomRight.m_Position.X;
	//	FirstPos.Y = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_BottomRight.m_Position.Y;

	//	SecondPos.X = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_TopRight.m_Position.X;
	//	SecondPos.Y = AlgorithmGeneration.m_RoomsVector[i]->m_pFloor->m_TopRight.m_Position.Y;

	//	SDL_RenderDrawLine(m_Renderer, (int32)FirstPos.X, (int32)FirstPos.Y, (int32)SecondPos.X, (int32)SecondPos.Y);

	//}

	///// Aquí  se renderean los pasillos //////////////////////////////////////////////////
	//for (int i = 0; i < AlgorithmGeneration.m_HG.m_FinalHallways.size(); ++i)
	//{
	//	//pink.
	//	SDL_SetRenderDrawColor(m_Renderer, 255, 105, 180, 0xFF);

	//	for (int j = 0; j < AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pPolygon->m_pNodeVector.size(); ++j)
	//	{
	//		//Draws the top line of the rectangle.
	//		FirstPos.X = AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pPolygon->m_pNodeVector[j]->m_Position.X;
	//		FirstPos.Y = AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pPolygon->m_pNodeVector[j]->m_Position.Y;

	//		if (j + 1 >= AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pPolygon->m_pNodeVector.size())
	//		{
	//			SecondPos.X = AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pPolygon->m_pNodeVector[0]->m_Position.X;
	//			SecondPos.Y = AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pPolygon->m_pNodeVector[0]->m_Position.Y;
	//		}

	//		else
	//		{
	//			SecondPos.X = AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pPolygon->m_pNodeVector[j + 1]->m_Position.X;
	//			SecondPos.Y = AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pPolygon->m_pNodeVector[j + 1]->m_Position.Y;
	//		}
	//		SDL_RenderDrawLine(m_Renderer, (int32)FirstPos.X, (int32)FirstPos.Y, (int32)SecondPos.X, (int32)SecondPos.Y);
	//	}
	//}


	

	for (int i = 0; i < AlgorithmGeneration.m_HG.m_FinalHallways.size(); ++i)
	{
		
		//Draws the top line of the rectangle.
		SDL_SetRenderDrawColor(m_Renderer, 255, 105, 180, 0xFF);
		SDL_RenderDrawLine(	m_Renderer,
			(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pFirstDoor->m_pFirstPosition->m_Position.X,
			(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pFirstDoor->m_pFirstPosition->m_Position.Y,
			(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pFirstDoor->m_pSecondPosition->m_Position.X,
			(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pFirstDoor->m_pSecondPosition->m_Position.Y);

		SDL_RenderDrawLine(m_Renderer,
			(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pSecondDoor->m_pFirstPosition->m_Position.X,
			(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pSecondDoor->m_pFirstPosition->m_Position.Y,
			(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pSecondDoor->m_pSecondPosition->m_Position.X,
			(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_pSecondDoor->m_pSecondPosition->m_Position.Y);

		for (int j = 0; j < AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_Walls.size(); ++j)
		{
			//Draws the top line of the rectangle.
			SDL_SetRenderDrawColor(m_Renderer, rand() % 254, rand() % 254, rand() % 254, 0xFF);
			SDL_RenderDrawLine(
				m_Renderer,
				(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_Walls[j]->m_BottomLeft.m_Position.X,
				(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_Walls[j]->m_BottomLeft.m_Position.Y,
				(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_Walls[j]->m_BottomRight.m_Position.X,
				(int32)AlgorithmGeneration.m_HG.m_FinalHallways[i]->m_Walls[j]->m_BottomRight.m_Position.Y);
		}
	}

	/// Aquí voa renderear paredes, puertas y la verga es.
	for (int i = 0; i < AlgorithmGeneration.m_RoomsVector.size(); ++i)
	{
		
		SDL_SetRenderDrawColor(m_Renderer, 0, 255, 255, 0xFF);

		for (int j = 0; j < AlgorithmGeneration.m_RoomsVector[i]->m_Walls.size(); ++j)
		{
			
			//TODO: draw a line between the bottom nodes of each rect.
			SDL_RenderDrawLine(
				m_Renderer,
				(int32)AlgorithmGeneration.m_RoomsVector[i]->m_Walls[j]->m_BottomLeft.m_Position.X,
				(int32)AlgorithmGeneration.m_RoomsVector[i]->m_Walls[j]->m_BottomLeft.m_Position.Y,
				(int32)AlgorithmGeneration.m_RoomsVector[i]->m_Walls[j]->m_BottomRight.m_Position.X,
				(int32)AlgorithmGeneration.m_RoomsVector[i]->m_Walls[j]->m_BottomRight.m_Position.Y);
		}
	}

	///// Aqui se rendera los triangulos de la triangulacion.
	//for (LevelGenerator::int32 i = 0; i < AlgorithmGeneration.m_DT.m_pTrianglesVector.size(); ++i)
	//{
	//	for (LevelGenerator::int32 j = 0; j < NODES_PER_TRIANGLE; ++j)
	//	{
	//		posToSpawn = AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_pEdges[j]->m_pFirstNode->m_Position;
	//		Secondpos = AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_pEdges[j]->m_pSecondNode->m_Position;
	//		// Draw red line.
	//		SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
	//		// en la posición de cada nodo dibujar un punto con SDL.
	//		SDL_RenderDrawLine(m_Renderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
	//		///Update screen
	//		SDL_RenderPresent(m_Renderer);
	//	}
	//}
	///Update screen
	SDL_RenderPresent(m_Renderer);
	AlgorithmGeneration.Destroy();
}


//! This function update the system.
void LG_Visual::Update(float fTime)
{
	/// Update the surface
	if (m_Window != nullptr)
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
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				Update(200);
				Renderer();
			}
		}


		//Renderer();
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

//! Draws a circle.
void LG_Visual::DrawCircle(LG_Circle circle, LG_Vector3D color, LevelGenerator::uint32 sides)
{
	/// The return value for the draw line function.
	int ret;

	/// Sees how long is every line gonna be.
	if (sides == 0)
	{
		sides = (uint32)LevelGenerator::LG_Math::PI2 * (uint32)circle.m_fRadius / 2;
	}

	float d_a = LevelGenerator::LG_Math::PI2 / sides,
		angle = d_a;

	LevelGenerator::LG_Vector3D start, end;
	/// Calculate the end point to draw on the circle.
	end.X = circle.m_fRadius;
	end.Y = 0.0f;
	end.Z = 0.0f;
	/// Move it so that it's at the right position.
	end = end + circle.m_Position;

	/// draw all the lines.
	for (LevelGenerator::uint32 i = 0; i != sides; i++)
	{
		start = end;
		end.X = cos(angle) * circle.m_fRadius;
		end.Y = sin(angle) * circle.m_fRadius;
		end = end + circle.m_Position;
		angle += d_a;

		/// Set the color for the circle.
		SDL_SetRenderDrawColor(m_Renderer, (uint8)color.X, (uint8)color.Y, (uint8)color.Z, 0);

		/// Draw the lines that forms the circle.
		ret =
			SDL_RenderDrawLine(
				m_Renderer, // SDL_Renderer* renderer: the renderer in which draw 
				(int32)start.X,               // int x1: x of the starting point 
				(int32)start.Y,          // int y1: y of the starting point 
				(int32)end.X,                 // int x2: x of the end point 
				(int32)end.Y);           // int y2: y of the end point 
	}
}



void LG_Visual::FillRect(LG_Vector3D StartPosition, LG_Vector3D EndPosition, float fWidth)
{
	for (int32 i = 0; i < fWidth; ++i)
	{
		SDL_RenderDrawLine(m_Renderer, (int32)StartPosition.X + i, (int32)StartPosition.Y, (int32)EndPosition.X + i, (int32)EndPosition.Y);
	}

}
