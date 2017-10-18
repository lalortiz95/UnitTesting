#include "LG_Visual.h"
#include <LG_DelaunayTriangulation.h>
#include <LG_Generate.h>
#include <LG_Vector2D.h>
#include <LG_Math.h>

//! Default constructor.
LG_Visual::LG_Visual()
{
	m_Window = nullptr;
	m_DisplayImage = nullptr;
	m_ScreenSurface = nullptr;
	m_Renderer = nullptr;

	m_SecondWindow = nullptr;
	m_SecondDisplayImage = nullptr;
	m_SecondScreenSurface = nullptr;
	m_SecondRenderer = nullptr;

	m_bInitSecondWindow = false;
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
	srand(time(NULL));
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

		//////////////////////////////////////////////////////////////////////////
		if (m_bInitSecondWindow)
		{
			/// Create Second window
			m_SecondWindow = SDL_CreateWindow(
				"Visual UnitTest",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN);

			/// Create the renderer.
			m_SecondRenderer = SDL_CreateRenderer(m_SecondWindow, -1, SDL_RENDERER_ACCELERATED);

			if (m_SecondRenderer == nullptr)
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(m_SecondRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
					success = false;
				}
			}

			if (m_SecondWindow != nullptr)
			{
				m_SecondScreenSurface = SDL_GetWindowSurface(m_SecondWindow);

				SDL_FillRect(m_SecondScreenSurface, nullptr, SDL_MapRGB(
					m_SecondScreenSurface->format, 0xFF, 0xFF, 0xFF));
			}
			else
			{
				std::cout << "Window could not be created! SDL_Error:"
					<< SDL_GetError() << std::endl;
				success = false;
			}
			for (int32 i = 0; i < 20; ++i)
			{
				LG_Node newNode;
				newNode.m_Position = LG_Vector3D(rand() % (SCREEN_WIDTH / 4), rand() % (SCREEN_HEIGHT / 4), 0);
				m_NodesCloud.push_back(newNode);
			}

		}


		//////////////////////////////////////////////////////////////////////////
	}


	//////////////////////////////////////////////////////////////////////////

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

	/// Deallocate the image to display.
	if (m_SecondDisplayImage != nullptr)
	{
		SDL_FreeSurface(m_SecondDisplayImage);
		m_SecondDisplayImage = nullptr;
	}

	/// Deallocate the screen surface.
	if (m_SecondScreenSurface != nullptr)
	{
		SDL_FreeSurface(m_SecondScreenSurface);
		m_SecondScreenSurface = nullptr;
	}

	/// Destroy window
	if (m_SecondWindow != nullptr)
	{
		SDL_DestroyWindow(m_SecondWindow);
		m_SecondWindow = nullptr;
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
	///Clear screen
	SDL_RenderClear(m_Renderer);

	/// The class that generates all of the algorithms.
	LevelGenerator::LG_Generate AlgorithmGeneration;

	/// We generate our algorithms.
	AlgorithmGeneration.Run();

	LevelGenerator::LG_Vector3D posToSpawn;
	LevelGenerator::LG_Vector3D Secondpos;
	LevelGenerator::LG_Vector3D CircumCenter;

	LevelGenerator::LG_Dijkstra Pathfinding;
	Pathfinding.Init(&AlgorithmGeneration.m_DT.m_NodesCloud, &AlgorithmGeneration.m_DT.m_NodesCloud[2], &AlgorithmGeneration.m_DT.m_NodesCloud[8]);
	Pathfinding.Run();

	/// Aqui se renderea la isolinea resultante de MS y RDP.
	//for (LevelGenerator::int32 i = 0; i < AlgorithmGeneration.m_DT.m_NodesCloud.size(); ++i)
	//{
	//	posToSpawn = AlgorithmGeneration.m_DT.m_NodesCloud[i].m_Position;

	//	if (i < AlgorithmGeneration.m_DT.m_NodesCloud.size() - 1)
	//	{
	//		Secondpos = AlgorithmGeneration.m_DT.m_NodesCloud[i + 1].m_Position;
	//		//Draw blue line
	//		SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0xFF, 0xFF);
	//		//en la posición de cada nodo dibujar un punto con SDL.
	//		SDL_RenderDrawLine(m_Renderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
	//	}
	//}

	/// Aqui rendereamos los ciruclos creados a partir de cada triangulo de la triangulacion.
	LG_Vector3D Color{ 0,255,0 };

	/// Aqui se rendera los triangulos de la triangulacion.
	for (LevelGenerator::int32 i = 0; i < AlgorithmGeneration.m_DT.m_pTrianglesVector.size(); ++i)
	{

		for (LevelGenerator::int32 j = 0; j < NODES_PER_TRIANGLE; ++j)
		{
			posToSpawn = AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_pEdges[j]->m_pFirstNode->m_Position;
			Secondpos = AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_pEdges[j]->m_pSecondNode->m_Position;

			// Draw red line.
			SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
			// en la posición de cada nodo dibujar un punto con SDL.
			SDL_RenderDrawLine(m_Renderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
			///Update screen
			SDL_RenderPresent(m_Renderer);
			//SDL_Delay(300);
		}
		//DrawCircle(AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_CircumcircleCircumference,
		//	Color,
		//	50);
		/////Update screen
		//SDL_RenderPresent(m_Renderer);
	}

	/// Aqui se rendere al pathfinding. //////////////////////////////////////////////////
	for (LevelGenerator::int32 i = 0; i < Pathfinding.m_PathNodes.size(); ++i)
	{
		posToSpawn = Pathfinding.m_PathNodes[i]->m_Position;
		
		// Black
		SDL_SetRenderDrawColor(m_Renderer, 255, 0, 0, 0);
		// en la posición de cada nodo dibujar un punto con SDL.
		SDL_RenderDrawPoint(m_Renderer, posToSpawn.X, posToSpawn.Y);
		///Update screen
		SDL_RenderPresent(m_Renderer);
	}

	
		posToSpawn = Pathfinding.m_pStartNode->m_Position;
		Secondpos = Pathfinding.m_pEndNode->m_Position;

		// Black
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 255, 0);
		// en la posición de cada nodo dibujar un punto con SDL.
		SDL_RenderDrawPoint(m_Renderer, posToSpawn.X, posToSpawn.Y);
		// en la posición de cada nodo dibujar un punto con SDL.
		SDL_RenderDrawPoint(m_Renderer, Secondpos.X, Secondpos.Y);
		///Update screen
		SDL_RenderPresent(m_Renderer);
	

	for (LevelGenerator::int32 i = 0; i < Pathfinding.m_BesthPath.size(); ++i)
	{
		if ((i + 1) < Pathfinding.m_BesthPath.size())
		{
			posToSpawn = Pathfinding.m_BesthPath[i]->m_Position;
			Secondpos = Pathfinding.m_BesthPath[i + 1]->m_Position;

			// Green
			SDL_SetRenderDrawColor(m_Renderer, 0, 255, 0, 0);
			// en la posición de cada nodo dibujar un punto con SDL.
			SDL_RenderDrawLine(m_Renderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
			///Update screen
			SDL_RenderPresent(m_Renderer);
			SDL_Delay(400);
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////

	// ///Aqui se rendera los triangulos malos de la triangulacion.
	//for (LevelGenerator::int32 i = 0; i < AlgorithmGeneration.m_DT.m_pBadTriangles.size(); ++i)
	//{
	//	for (LevelGenerator::int32 j = 0; j < 3; ++j)
	//	{
	//		posToSpawn = AlgorithmGeneration.m_DT.m_pBadTriangles[i]->m_pEdges[j]->m_pFirstNode->m_Position;
	//		Secondpos = AlgorithmGeneration.m_DT.m_pBadTriangles[i]->m_pEdges[j]->m_pSecondNode->m_Position;

	//		// Draw blue line.
	//		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 255, 0xFF);
	//		// en la posición de cada nodo dibujar un punto con SDL.
	//		SDL_RenderDrawLine(m_Renderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
	//	}
	//}

	///// Aqui rendereamos el polygono.
	//for (LevelGenerator::int32 i = 0; i < AlgorithmGeneration.m_DT.m_Polygon.m_pEdgeVector.size(); ++i)
	//{
	//	posToSpawn = AlgorithmGeneration.m_DT.m_Polygon.m_pEdgeVector[i]->m_pFirstNode->m_Position;
	//	Secondpos = AlgorithmGeneration.m_DT.m_Polygon.m_pEdgeVector[i]->m_pSecondNode->m_Position;

	//	// Draw red line.
	//	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0);
	//	// en la posición de cada nodo dibujar un punto con SDL.
	//	SDL_RenderDrawLine(m_Renderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
	//}

	/*///We draw a dot wherever there is a node, as an output of the performed Delaunay Triangulation algorithm.
	for (LevelGenerator::int32 i = 0; i < AlgorithmGeneration.m_DT.m_TrianglesVector.size(); ++i)
	{
		/// Aqui rendereamos los vertices de cada triangulo.
		for (LevelGenerator::int32 j = 0; j < 3; ++j)
		{
			/// the position of the trianle's vertices.
			posToSpawn = AlgorithmGeneration.m_DT.m_TrianglesVector[i].m_pVertices[j]->m_Position;

			/// Draw red dot
			SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0);
			/// en la posición de cada nodo dibujar un punto con SDL.
			SDL_RenderDrawPoint(m_Renderer, posToSpawn.X, posToSpawn.Y);
		}

		/// Aqui se renderea los circuncentros de cada triangulo.
		CircumCenter = AlgorithmGeneration.m_DT.m_TrianglesVector[i].m_Circumcenter;
		/// Draw red dot
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0);
		/// en la posición de cada nodo dibujar un punto con SDL.
		SDL_RenderDrawPoint(m_Renderer, CircumCenter.X, CircumCenter.Y);

	}*/
	///Update screen
	SDL_RenderPresent(m_Renderer);
}

void LG_Visual::RenderDelaunay()
{
	///Clear screen
	SDL_RenderClear(m_Renderer);
	///Clear screen second render
	SDL_RenderClear(m_SecondRenderer);

	/// The class that generates all of the algorithms.
	LevelGenerator::LG_Generate AlgorithmGeneration;

	/// We generate our algorithms.
	AlgorithmGeneration.Run();

	LevelGenerator::LG_Vector3D posToSpawn;
	LevelGenerator::LG_Vector3D Secondpos;
	LevelGenerator::LG_Vector3D CircumCenter;


	/// Aqui rendereamos los ciruclos creados a partir de cada triangulo de la triangulacion.
	LG_Vector3D Color{ 0,255,0 };

	/// Aqui se rendera los triangulos de la triangulacion.
	for (LevelGenerator::int32 i = 0; i < AlgorithmGeneration.m_DT.m_pTrianglesVector.size(); ++i)
	{

		for (LevelGenerator::int32 j = 0; j < NODES_PER_TRIANGLE; ++j)
		{
			posToSpawn = AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_pEdges[j]->m_pFirstNode->m_Position;
			Secondpos = AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_pEdges[j]->m_pSecondNode->m_Position;

			// Draw red line.
			SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0x00, 0x00, 0xFF);
			// en la posición de cada nodo dibujar un punto con SDL.
			SDL_RenderDrawLine(m_Renderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
			///Update screen
			SDL_RenderPresent(m_Renderer);
			SDL_Delay(50);
		}
		//DrawCircle(AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_CircumcircleCircumference,
		//	Color,
		//	50);
		/////Update screen
		//SDL_RenderPresent(m_Renderer);
	}

	/// Creates the nodes' pointers to change it's values.
	LG_Node* pFirstNode = nullptr;
	LG_Node* pSecondNode = nullptr;

	/// Creates the triangles' pointers to change it's values.
	LG_Triangle* pFirstTriangle = nullptr;
	LG_Triangle* pSecondTriangle = nullptr;

	/// Create a edge's pointer to legalize before.
	LG_Edge* pActualEdge = nullptr;
	LG_Triangle* pActualTriangle = AlgorithmGeneration.m_DT.m_pTrianglesVector.front();
	bool bCanStop = false;

	while (!bCanStop)
	{
		bCanStop = true;
		for (int32 i = 0; i < AlgorithmGeneration.m_DT.m_pTrianglesVector.size(); ++i)
		{
			if (!AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_bIsChecked)
			{
				pActualTriangle = AlgorithmGeneration.m_DT.m_pTrianglesVector[i];
				break;
			}
		}

		for (int32 j = 0; j < EDGES_PER_TRIANGLE; ++j)
		{

			pActualEdge = pActualTriangle->m_pEdges[j];
			if (AlgorithmGeneration.m_DT.FindTrianglesToLegalize(pActualEdge, &pFirstTriangle, &pSecondTriangle))
			{
				/// 
				AlgorithmGeneration.m_DT.FindNodesToCreatePolygon(pActualEdge, pFirstTriangle, pSecondTriangle, &pFirstNode, &pSecondNode);
				/// If at least one of the nodes was inside the circle we change the arista for a legal one.
				if (pSecondTriangle->m_CircumcircleCircumference.IsDotInside(pFirstNode->m_Position) ||
					pFirstTriangle->m_CircumcircleCircumference.IsDotInside(pSecondNode->m_Position))
				{

					for (LevelGenerator::int32 k = 0; k < NODES_PER_TRIANGLE; ++k)
					{
						Secondpos = pFirstTriangle->m_pEdges[k]->m_pSecondNode->m_Position;
						posToSpawn = pFirstTriangle->m_pEdges[k]->m_pFirstNode->m_Position;

						// Draw red line.
						SDL_SetRenderDrawColor(m_SecondRenderer, 255, 0, 0, 0xFF);
						// en la posición de cada nodo dibujar un punto con SDL.
						SDL_RenderDrawLine(m_SecondRenderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
						///Update screen
						SDL_RenderPresent(m_SecondRenderer);
						SDL_Delay(100);
					}

					for (LevelGenerator::int32 k = 0; k < NODES_PER_TRIANGLE; ++k)
					{
						Secondpos = pSecondTriangle->m_pEdges[k]->m_pSecondNode->m_Position;
						posToSpawn = pSecondTriangle->m_pEdges[k]->m_pFirstNode->m_Position;

						// Draw red line.
						SDL_SetRenderDrawColor(m_SecondRenderer, 255, 0, 0, 0xFF);
						// en la posición de cada nodo dibujar un punto con SDL.
						SDL_RenderDrawLine(m_SecondRenderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
						///Update screen
						SDL_RenderPresent(m_SecondRenderer);
						SDL_Delay(100);
					}

					LG_Triangle* pNewFirstTriangle = AlgorithmGeneration.m_DT.CreateTriangle(pFirstNode, pSecondNode, pActualEdge->m_pFirstNode);
					for (LevelGenerator::int32 k = 0; k < NODES_PER_TRIANGLE; ++k)
					{
						Secondpos = pNewFirstTriangle->m_pEdges[k]->m_pSecondNode->m_Position;
						posToSpawn = pNewFirstTriangle->m_pEdges[k]->m_pFirstNode->m_Position;

						// Draw red line.
						SDL_SetRenderDrawColor(m_SecondRenderer, 0, 0, 255, 0xFF);
						// en la posición de cada nodo dibujar un punto con SDL.
						SDL_RenderDrawLine(m_SecondRenderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
						///Update screen
						SDL_RenderPresent(m_SecondRenderer);
						SDL_Delay(300);
					}

					LG_Triangle* pNewSecondTriangle = AlgorithmGeneration.m_DT.CreateTriangle(pFirstNode, pSecondNode, pActualEdge->m_pSecondNode);

					for (LevelGenerator::int32 k = 0; k < NODES_PER_TRIANGLE; ++k)
					{
						posToSpawn = pNewSecondTriangle->m_pEdges[k]->m_pFirstNode->m_Position;
						Secondpos = pNewSecondTriangle->m_pEdges[k]->m_pSecondNode->m_Position;

						// Draw red line.
						SDL_SetRenderDrawColor(m_SecondRenderer, 0, 0, 255, 0xFF);
						// en la posición de cada nodo dibujar un punto con SDL.
						SDL_RenderDrawLine(m_SecondRenderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
						///Update screen
						SDL_RenderPresent(m_SecondRenderer);
						SDL_Delay(300);
					}

					// with red line.
					SDL_SetRenderDrawColor(m_SecondRenderer, 255, 255, 255, 0xFF);
					///Clear screen second render
					SDL_RenderClear(m_SecondRenderer);


					//pNewFirstTriangle->m_bIsChecked = true;
					//pNewSecondTriangle->m_bIsChecked = true;
					AlgorithmGeneration.m_DT.m_pTrianglesVector.push_back(pNewFirstTriangle);
					AlgorithmGeneration.m_DT.m_pTrianglesVector.push_back(pNewSecondTriangle);

					/// Erases the triangle that belongs to the legalized edge.
					for (Vector<LG_Triangle*>::iterator itt = AlgorithmGeneration.m_DT.m_pTrianglesVector.begin();
						itt != AlgorithmGeneration.m_DT.m_pTrianglesVector.end(); ++itt)
					{
						if ((*itt) == pFirstTriangle)
						{
							LG_Triangle* pTemp = *itt;
							AlgorithmGeneration.m_DT.m_pTrianglesVector.erase(itt);
							delete pTemp;
							pTemp = nullptr;
							break;
						}
					}

					for (Vector<LG_Triangle*>::iterator itt = AlgorithmGeneration.m_DT.m_pTrianglesVector.begin();
						itt != AlgorithmGeneration.m_DT.m_pTrianglesVector.end(); ++itt)
					{
						if ((*itt) == pSecondTriangle)
						{
							LG_Triangle* pTemp = *itt;
							AlgorithmGeneration.m_DT.m_pTrianglesVector.erase(itt);
							delete pTemp;
							pTemp = nullptr;
							break;
						}
					}

					for (Vector<LG_Edge*>::iterator itt = AlgorithmGeneration.m_DT.m_pEdgeVector.begin();
						itt != AlgorithmGeneration.m_DT.m_pEdgeVector.end(); ++itt)
					{
						if ((*itt) == pActualEdge)
						{
							LG_Edge* pTemp = *itt;
							AlgorithmGeneration.m_DT.m_pEdgeVector.erase(itt);
							delete pTemp;
							pTemp = nullptr;
							break;
						}
					}
					break;

				}
			}
		}

		pActualTriangle->m_bIsChecked = true;
		bCanStop = AlgorithmGeneration.m_DT.CheckIfAllTrianglesAreTrue();
	}

	/// Eliminate the edges of the big triangle from de edges' vector.
	AlgorithmGeneration.m_DT.EliminateEdgesBigTriangle();
	/// Eliminate the triangles that shares position with the big triangle.
	while (AlgorithmGeneration.m_DT.EliminateTriangles());
	/// Eliminate the edges that shares position with the big triangle.
	while (AlgorithmGeneration.m_DT.EliminateEdges());

	// with red line.
	SDL_SetRenderDrawColor(m_SecondRenderer, 255, 255, 255, 0xFF);
	///Clear screen second render
	SDL_RenderClear(m_SecondRenderer);

	/// Aqui se rendera los triangulos de la triangulacion.
	for (LevelGenerator::int32 i = 0; i < AlgorithmGeneration.m_DT.m_pTrianglesVector.size(); ++i)
	{

		for (LevelGenerator::int32 j = 0; j < NODES_PER_TRIANGLE; ++j)
		{
			posToSpawn = AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_pEdges[j]->m_pFirstNode->m_Position;
			Secondpos = AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_pEdges[j]->m_pSecondNode->m_Position;

			// Draw red line.
			SDL_SetRenderDrawColor(m_SecondRenderer, 0xFF, 0x00, 0x00, 0xFF);
			// en la posición de cada nodo dibujar un punto con SDL.
			SDL_RenderDrawLine(m_SecondRenderer, posToSpawn.X, posToSpawn.Y, Secondpos.X, Secondpos.Y);
			///Update screen
			SDL_RenderPresent(m_SecondRenderer);
			SDL_Delay(200);
		}
		//DrawCircle(AlgorithmGeneration.m_DT.m_pTrianglesVector[i]->m_CircumcircleCircumference,
		//	Color,
		//	50);
		/////Update screen
		//SDL_RenderPresent(m_Renderer);
	}
}

//! This function update the system.
void LG_Visual::Update(float fTime)
{
	/// Update the surface
	if (m_Window != nullptr)
		SDL_UpdateWindowSurface(m_Window);
	/// Update the second window
	if (m_SecondWindow != nullptr)
		SDL_UpdateWindowSurface(m_SecondWindow);
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
		}

		Update(2000);

		if (m_bInitSecondWindow)
		{
			RenderDelaunay();
		}
		else
		{
			Renderer();
		}
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
		sides = LevelGenerator::LG_Math::PI2 * circle.m_fRadius / 2;
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
	for (LevelGenerator::int32 i = 0; i != sides; i++)
	{
		start = end;
		end.X = cos(angle) * circle.m_fRadius;
		end.Y = sin(angle) * circle.m_fRadius;
		end = end + circle.m_Position;
		angle += d_a;

		/// Set the color for the circle.
		SDL_SetRenderDrawColor(m_Renderer, color.X, color.Y, color.Z, 0);

		/// Draw the lines that forms the circle.
		ret =
			SDL_RenderDrawLine(
				m_Renderer, // SDL_Renderer* renderer: the renderer in which draw 
				start.X,               // int x1: x of the starting point 
				start.Y,          // int y1: y of the starting point 
				end.X,                 // int x2: x of the end point 
				end.Y);           // int y2: y of the end point 
	}
}
