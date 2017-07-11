#include "LG_RDP.h"

namespace LevelGenerator
{
	//! Default constructor.
	LG_RDP::LG_RDP()
	{
		m_fGreaterDistance = 0.0f;
	}

	//! Default destructor.
	LG_RDP::~LG_RDP()
	{
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_RDP::Init(float fRange, LG_Isoline IsolineToReduce)
	{
		/// Store in member variables the values in the parametrs for future references.
		m_fRange = fRange;
		m_OriginalIsoline = IsolineToReduce;

		/// Check if the vector node in the isoline isn't empty.
		if (IsolineToReduce.m_NodeVector.size() != 0)
		{
			/// Assign the begin node and end node's values.
			m_Begin = IsolineToReduce.m_NodeVector.front();
			m_End = IsolineToReduce.m_NodeVector.back();
			m_ActualEndNode = m_End;
		}

		
		for (int i = 0; i < IsolineToReduce.m_NodeVector.size(); ++i)
		{
			// TODO: generar el rango.

		}

		/// Iterate through the original isoline.
		for (int i = 0; i < IsolineToReduce.m_NodeVector.size(); ++i)
		{
			LG_Node ActualNode = IsolineToReduce.m_NodeVector[i];
			CheckNodeDistance(ActualNode);
		}
	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_RDP::Destroy()
	{
		// TODO: Liberar memoria.
	}

	//! This function check the distance between the end node, the start node and the given node.
	void LG_RDP::CheckNodeDistance(LG_Node ActualNode)
	{
		/// We calculate the distance between the actual iterating node and the first node of the isoline.
		float fStartDistance = LG_Vector3D::StaticMagnitude(ActualNode.m_Position - m_Begin.m_Position);
		/// We calculate the distance between the actual iterating node and the last node of the isoline.
		float fEndDistance = LG_Vector3D::StaticMagnitude(ActualNode.m_Position - m_End.m_Position);
		/// We add both distances.
		float fFinalDistance = fStartDistance + fEndDistance;

		/// If the final distance is greater than the 
		if (fFinalDistance > m_fGreaterDistance)
		{
			/// We set the actual end node.
			m_ActualEndNode = ActualNode;
			/// We set the new greater distance between both vectors.
			m_fGreaterDistance = fFinalDistance;
		}
	}


	void LG_RDP::CreateBoundary()
	{

	}

	//! This function is the only one you need to generate Ramer-Douglas-Peucker algorithm.
	void LG_RDP::Run()
	{
		//TODO: sacar un vector entre el primer y el último nodo de la isolinea.
		//definir el rango que se va a tener.
		//ver si algun nodo está dentro del área delimitada por 2 vectores, simulando un rectangulo.
	}
}