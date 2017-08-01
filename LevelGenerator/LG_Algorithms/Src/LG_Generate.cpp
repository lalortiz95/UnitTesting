#include "LG_Generate.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_Generate::LG_Generate()
	{

	}

	//! Default destructor.
	LG_Generate::~LG_Generate()
	{

	}

	//! This function initialize all variables of the class.
	void LG_Generate::Initialize()
	{

	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_Generate::Destroy()
	{

	}

	//! This calls all the algorithms and put them together to generate a procedural level.
	void LG_Generate::Run()
	{
		//TODO: with the generated cases make an isoiline.
		//we apply then, RDP algorithm to reduce that isoloine.
		//Now we have a reduced set of points, that will be used to 
		//Generate delaunay triangulation.
		/// A map to work with for our marching square algorithm.
		m_pMap = new LG_Grid();
		m_pMap->Init(20, 12);
		/// We run marching square with the generated grid.
		m_MS.Run(m_pMap);

		//TODO: tomar los casos de marching square y con sus isolineas de los casos generados, ir acomodandolas desde un inicio hasta un fin.
		// hacer lo mismo por todas las isolineas que tengamos.

		m_MS.m_pMap->m_pListTilesInside;
		//TODO:
		//		En el primer lugar de la lista de tiles dentro, ver su isolinea, y guardar el
		//		primer punto.
		//		y buscamos dentro de las isolineas del resto de los tiles, si es que hay
		//		algún otro nodo que comparta posición. Encontrado dicho nodo, se guarda el 
		//		primer punto, y se busca uno que comparta posición con el segundo de la 
		//		isolinea. //esto ya se repitió ojo.
		//		Al no haber quien comparta posición con nuestro nodo actual, dicho nodo
		//		se vuelve el nodo final, y se buscan más isolineas por formar.
		//		Si por otro lado el nodo vuelve a tener la misma posición que la inicial
		//		ese se guarda como el último nodo. y se buscan más isolineas.
		//		Cuando se hayan generado todas las isolineas, les aplicamos RDP a cada una.
		//		Al final debemos tener una lista de isolineas reducidas.
	}
}