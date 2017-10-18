#include "LG_MST.h"

#include <LG_Math.h>
#include <LG_Triangle.h>

namespace LevelGenerator
{
	//! Default constructor.
	LG_MST::LG_MST()
	{

	}

	//! Default destructor.
	LG_MST::~LG_MST()
	{

	}

	//! Initializes the member variables of the class.
	void LG_MST::Init()
	{

	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_MST::Destroy()
	{
	}

	//! This function is the only one you need to generate Minimum Spanning Tree algorithm.
	void LG_MST::Run(Vector<LG_Edge*> InitialNet, Vector<LG_Triangle*> Triangulation)
	{
		/// 
		//bool bBreakFirstFor = false;
		/// A copy of the vector to not affect the original one.
		Vector<LG_Edge*> Initial = InitialNet;
		/// We sort the edges from lower to higher value.
		Sort(Initial);

		for (int32 i = 0; i < m_OrderedEdges.size(); ++i)
		{
			for (int32 j = 0; j < Triangulation.size(); ++j)
			{
				/// See if the triangle contains the edge that we want.
				if (Triangulation[j]->HasEdgeInside(m_OrderedEdges[i]))
				{
					/// If we are in the triangle that contains the edge, we see that the triangle doesn't have more
					/// than 2 edges as checked.
					if (Triangulation[j]->m_pEdges[0]->m_bIsChecked && Triangulation[j]->m_pEdges[1]->m_bIsChecked ||
						Triangulation[j]->m_pEdges[1]->m_bIsChecked && Triangulation[j]->m_pEdges[2]->m_bIsChecked ||
						Triangulation[j]->m_pEdges[0]->m_bIsChecked && Triangulation[j]->m_pEdges[2]->m_bIsChecked)
					{
						//Aquí no va a meter a la lista final el edge. 
						//bBreakFirstFor = true;
						break;
					}
					else
					{
						m_FinalTree.push_back(m_OrderedEdges[i]);
						m_OrderedEdges[i]->m_bIsChecked = true;
						break;
					}
				}
			}
		}

		m_FinalTree = m_FinalTree;
		// agregarlos al tree final, siempre y cuando no formen un ciclo.
		// sería bueno conocer la lista de triangulos, e iterar buscando que triangulo contiene el edge acutal
		// y al insertarlo en la lista final marcar dicho edge como marcado, cuando un triangulo tenga 2 edges 
		// checados ya no mete a otro del mismo triangulo a la final.
	}

	//! Sorts the initial vector of edges, from lower to higher cost.
	void LG_MST::Sort(Vector<LG_Edge*> InitialNet)
	{
		/// The edge with the smallest magnitude.
		Vector<LG_Edge*>::iterator temp;
		/// Where we store the minimum distance of the edge vectos.
		float fSmallestMag = LG_Math::INFINITE_NUM;
		/// The initial size of the net.
		int32 iInitialSize = InitialNet.size();
		/// 

		while (m_OrderedEdges.size() != iInitialSize)
		{
			fSmallestMag = LG_Math::INFINITE_NUM;
			/// 
			for (Vector<LG_Edge*>::iterator itt = InitialNet.begin(); itt != InitialNet.end(); ++itt)
			{
				///
				if ((*itt)->m_fDistance < fSmallestMag)
				{
					/// 
					fSmallestMag = (*itt)->m_fDistance;
					///
					temp = itt;
				}
			}
			m_OrderedEdges.push_back((*temp));
			InitialNet.erase(temp);
		}
	}
}