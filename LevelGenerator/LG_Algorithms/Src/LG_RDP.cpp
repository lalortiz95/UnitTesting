#include "LG_RDP.h"
#include <LG_Rect.h>

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
	
	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_RDP::Destroy()
	{
		// TODO: Liberar memoria.
	}

	void LG_RDP::Run(float fRange, LG_Isoline Isoline)
	{
		/// Stores this variables for future references.
		m_fRange = fRange;
		m_OriginalIsoline = Isoline;

		/// The boundary to apply the range.
		LG_Rect Boundary;

		m_pStart = &m_OriginalIsoline.m_NodeVector.front();
		m_pEnd = &m_OriginalIsoline.m_NodeVector.back();
		
		std::vector<LG_Node> FinalList;

		bool bCanDeletedNodes = true;
		bool bChangeEnd = false;
		bool bListIsFalse = false;
		bool bQuit = true;

		int iCountEndNode = 0;
		int iCountStartNode = 0;

		float fDistance = 0;

		while (bQuit)
		{
			/// Reset values to default.
			bQuit = false;
			bListIsFalse = true;

			for (int i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
			{
				if (m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted)
				{
					float fNewDistance = CheckDistance(m_OriginalIsoline.m_NodeVector[i],
						*m_pStart, *m_pEnd);
					if (fNewDistance > fDistance)
					{
						fDistance = fNewDistance;
						m_pActualNode = &m_OriginalIsoline.m_NodeVector[i];
						bChangeEnd = true;
						iCountEndNode = i;
					}
				}
			}

			if (bChangeEnd)
				m_pEnd = m_pActualNode;

			Boundary.Init(m_pStart->m_Position, m_pEnd->m_Position, fRange);
			m_pStart->m_bCanDeleted = false;

			/// Sets the nodes that are after the temp end, as false.
			for (int i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
			{
				if (i >= iCountEndNode)
					m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted = false;
				if (m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted)
					bListIsFalse = false;
			}

			if (iCountStartNode >= m_OriginalIsoline.m_NodeVector.size() - 1)
			{
				bQuit = false;
				bCanDeletedNodes = false;
			}

			/// we check collision with the true nodes of the isoline.
			for (int i = 0; i < iCountEndNode; ++i)
			{
				/// If the list is all false, or we're ahead of the first node.
				if (i > iCountStartNode || bListIsFalse)
				{
					/// If it can be deleted, and is colliding with the boundary.
					if (m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted &&
						Boundary.CheckCollision(m_OriginalIsoline.m_NodeVector[i],
							*m_pStart))
						continue;
					else
					{
						///If not, we cant delete nodes :C
						bCanDeletedNodes = false;
						break;
					}
				}
			}

			/// Check if we can delete any nodes.
			if (bCanDeletedNodes)
			{
				for (int i = 0; i < iCountEndNode; ++i)
				{
					if (!m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted && !m_OriginalIsoline.m_NodeVector[i].m_bIsInside)
					{
						FinalList.push_back(m_OriginalIsoline.m_NodeVector[i]);
					}
				}

				for (int i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
				{
					m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted = true;
				}
				*m_pStart = *m_pEnd;
				m_pEnd = &m_OriginalIsoline.m_NodeVector.back();
			}

			/// Check that the whole list is false, this means that the end node
			/// is next to the start node.
			if (bListIsFalse && iCountStartNode < m_OriginalIsoline.m_NodeVector.size() - 1)
			{

				if (!m_pStart->m_bIsInside)
				{
					m_pStart->m_bIsInside = true;
					FinalList.push_back(*m_pStart);
				}
				//for (int i = 0; i < FinalList.size(); ++i)
				//{
				//	if (FinalList[i].m_Position != pStart->m_Position)
				//	{
				//		/// Insert the start as the new reduced line's first node.
				//		FinalList.push_back(*pStart);
				//		break;
				//	}
				//}

				/// assign as true, all the nodes beyond the start node.
				for (int i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
				{
					if (i > iCountStartNode)
						m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted = true;
				}

				/// Revision so that it doesn't go out of the array.
				if (iCountStartNode < m_OriginalIsoline.m_NodeVector.size() - 1)
				{
					/// Assign the new start node.
					iCountStartNode++;
					m_pStart = &m_OriginalIsoline.m_NodeVector[iCountStartNode];
				}
			}

			fDistance = 0;
			bCanDeletedNodes = true;
			bChangeEnd = false;
			for (int i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
			{
				if (m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted)
				{
					bQuit = true;
					break;
				}
			}
		}

		m_OriginalIsoline.m_NodeVector.clear();
		m_OriginalIsoline.m_NodeVector.resize(FinalList.size());
		m_OriginalIsoline.m_NodeVector = FinalList;
	}

	float LG_RDP::CheckDistance(LG_Node ActualNode, LG_Node nStart, LG_Node nEnd)
	{
		/// We calculate the distance between the actual iterating node and the first node of the isoline.
		float fStartDistance = LG_Vector3D::StaticMagnitude(ActualNode.m_Position - nStart.m_Position);
		/// We calculate the distance between the actual iterating node and the last node of the isoline.
		float fEndDistance = LG_Vector3D::StaticMagnitude(ActualNode.m_Position - nEnd.m_Position);
		/// We add both distances.
		return fStartDistance + fEndDistance;
	}

}