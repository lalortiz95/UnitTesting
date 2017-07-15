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
		/// This variable is used to assign the ID's.
		int iCount = 0;

		/// Check if the vector node in the isoline isn't empty.
		if (m_OriginalIsoline.m_NodeList.size() != 0)
		{
			/// Assign the begin node and end node's values.
			m_pBegin = &m_OriginalIsoline.m_NodeList.front();
			m_pEnd = &m_OriginalIsoline.m_NodeList.back();
			m_pActualEndNode = &m_OriginalIsoline.m_NodeList.back();
		}

		for (std::list<LG_Node>::iterator itt = m_OriginalIsoline.m_NodeList.begin();
			itt != m_OriginalIsoline.m_NodeList.end(); ++itt)
		{
			/// This flag indicates if the node will be deleted.
			/// this happens when thery're before the actual en node.
			(*itt).m_bIsInside = true;
			(*itt).m_iID = iCount;
			iCount++;
		}
	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_RDP::Destroy()
	{
		// TODO: Liberar memoria.
	}

	//! This function check the distance between the end node, the start node and the given node.
	void LG_RDP::CheckNodeDistance(LG_Node ActualNode, LG_Node& newEndNode, int Id)
	{

		/// We calculate the distance between the actual iterating node and the first node of the isoline.
		float fStartDistance = LG_Vector3D::StaticMagnitude(ActualNode.m_Position - m_pBegin->m_Position);
		/// We calculate the distance between the actual iterating node and the last node of the isoline.
		float fEndDistance = LG_Vector3D::StaticMagnitude(ActualNode.m_Position - m_pActualEndNode->m_Position);
		/// We add both distances.
		float fFinalDistance = fStartDistance + fEndDistance;
		//TODO: Generar un nodo temporal para hacer el calculo de esto.
		/// If the final distance is greater than the 
		if (fFinalDistance > m_fGreaterDistance)
		{
			/// We set the actual end node.
			newEndNode = ActualNode;
			newEndNode.m_iID = Id;
			/// We set the new greater distance between both vectors.
			m_fGreaterDistance = fFinalDistance;
		}
	}

	void LG_RDP::RunVec(float fRange, LG_Isoline Isoline)
	{
		/// Stores this variables for future references.
		m_fRange = fRange;
		m_OriginalIsoline = Isoline;

		/// The boundary to apply the range.
		LG_Rect Boundary;

		/// A node that points at what we consider the first node of the isoline.
		LG_Node* pStart = &m_OriginalIsoline.m_NodeVector.front();
		/// A node that points at what we onsider the last node of the isoline.
		LG_Node* pEnd = &m_OriginalIsoline.m_NodeVector.back();
		/// A node used to iterate.
		LG_Node* pActualNode;
		/// The reduced isoline.
		std::vector<LG_Node> FinalList;

		/// This flag is true when when all the nodes that can be deleted are inside
		/// The range given.
		bool bCanDeletedNodes = true;
		///
		bool bChangeEnd = false;
		/// This flag is true when all the nodes of the isoline are false.
		bool bListIsFalse = false;
		/// Flag that allow us, to end the agorithm loop.
		bool bQuit = true;

		int iCountEndNode = 0;
		int iCountStartNode = 0;

		float fDistance = 0;

		while (bQuit)
		{
			/// Reset values to default.
			bQuit = false;
			bListIsFalse = true;

			/// We iterate the vector.
			for (int i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
			{
				/// Check if we can delete the node, to set the new and, as the
				/// furthest node.
				if (m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted)
				{
					/// Calculate the distance between both begin and end node.
					/// and every other node of the isoline.
					float fNewDistance = CheckDistance(m_OriginalIsoline.m_NodeVector[i],
						*pStart, *pEnd);

					/// If it's greater than the previous greater, it becomes the new greater distance.
					if (fNewDistance > fDistance)
					{
						/// Assign the new further distance.
						fDistance = fNewDistance;
						/// Save that node.
						pActualNode = &m_OriginalIsoline.m_NodeVector[i];
						/// Set the changes made.
						bChangeEnd = true;
						/// We store that node's position in the vector.
						iCountEndNode = i;
					}
				}
			}

			/// If changes where made, we change the end node to the furthest.
			if (bChangeEnd)
				pEnd = pActualNode;

			/// Create a boundary with the given range to see if any nodes are inside
			/// of it.
			Boundary.Init(pStart->m_Position, pEnd->m_Position, fRange);
			/// Assign that the first node cannot be deleted.
			pStart->m_bCanDeleted = false;

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
							*pStart))
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
				for (int i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
				{
					if (!m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted && 
						!m_OriginalIsoline.m_NodeVector[i].m_bIsInside)
					{
						m_OriginalIsoline.m_NodeVector[i].m_bIsInside = true;
						FinalList.push_back(m_OriginalIsoline.m_NodeVector[i]);
					}
				}

				for (int i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
				{
					m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted = true;
				}
				*pStart = *pEnd;
				pEnd = &m_OriginalIsoline.m_NodeVector.back();
			}

			/// Check that the whole list is false, this means that the end node
			/// is next to the start node.
			if (bListIsFalse && 
				iCountStartNode < m_OriginalIsoline.m_NodeVector.size() - 1)
			{

				if (!pStart->m_bIsInside)
				{
					pStart->m_bIsInside = true;
					FinalList.push_back(*pStart);
				}

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
					pStart = &m_OriginalIsoline.m_NodeVector[iCountStartNode];
					pEnd = &m_OriginalIsoline.m_NodeVector.back();
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

	//! This function is the only one you need to generate Ramer-Douglas-Peucker algorithm.
	void LG_RDP::Run(float fRange, LG_Isoline IsolineToReduce)
	{
		/// We initialize the variables of the class.
		Init(fRange, IsolineToReduce);
		/// The flag used to break the loop.
		bool bQuit = false;
		/// This variable is used to count.
		int iCount = 0;

		std::list<LG_Node>::iterator itt;

		/// A temporal node to asign the new end node.
		LG_Node FurthestNode;
		/// The current iterating node.
		LG_Node ActualNode;
		/// Then rectangle used as boundary to detect if we should delete nodes.
		LG_Rect rect;

		/// A counter that tells us how many nodes are inside the range.
		int iNodesInside = 0;

		/// The amount of iterations that have passed.
		int iCountIterator = 0;


		/// Now we iterate.
		while (!bQuit)
		{
			iNodesInside = 0;
			/// Reset the distance's value to 0.
			m_fGreaterDistance = 0;


			/// Iterate through the original isoline.
			for (itt = m_OriginalIsoline.m_NodeList.begin(),
				iCount = 0; iCount < m_pActualEndNode->m_iID; ++itt, ++iCount)
			{
				///Actual node used to check if its inside of the range.
				ActualNode = (*itt);
				(*itt).m_bIsInside = true;
				CheckNodeDistance(ActualNode, FurthestNode, iCount);
			}

			/// The new end node is assigned as the furthest point.
			*m_pActualEndNode = FurthestNode;

			/// we generate that recatangle.
			rect.Init(m_pBegin->m_Position, m_pActualEndNode->m_Position, m_fRange);

			/// We go through the list.
			for (itt = m_OriginalIsoline.m_NodeList.begin(), iCount = 0;
				itt != m_OriginalIsoline.m_NodeList.end(); ++itt)
			{
				/// Change the flag to false of the nodes behind the end node.
				if (iCount >= m_pActualEndNode->m_iID)
					(*itt).m_bIsInside = false;
				/// add to the counter.
				iCount++;
			}

			/// we iterate trhough the list.
			for (itt = m_OriginalIsoline.m_NodeList.begin();
				itt != m_OriginalIsoline.m_NodeList.end(); ++itt)
			{
				/// We check that the node we're checking is before the actual end node.
				if ((*itt).m_bIsInside)
				{
					/// Checking if the node was inside of the rectangle.
					if (rect.CheckCollision((*itt), *m_pBegin))
					{
						/// Add the amount of nodes inside.
						iNodesInside++;
					}
				}
				else
				{
					/// Breaks out of the loop, because they're all false after the
					/// actual end node.
					break;
				}
			}

			/// If the amount of nodes inside of the range, is the number of nodes until
			/// the actual end, it means we gotta delete them.
			if (iNodesInside == m_pActualEndNode->m_iID - 1)
			{


				for (itt = m_OriginalIsoline.m_NodeList.begin(), iCount = 1;
					itt != m_OriginalIsoline.m_NodeList.end(); ++itt)
				{
					if (iCount < m_pActualEndNode->m_iID)
					{
						/// The values between both iterators it's gonna be deleted.
						m_OriginalIsoline.m_NodeList.erase(itt);
					}
					iCount++;
				}

				/// Asign in the redused nodes to the final isoline.
				m_FinalIsoline.m_NodeList.push_back(*m_pBegin);
				m_FinalIsoline.m_NodeList.push_back(*m_pActualEndNode);

				///We check if we've come all the way to the last node.
				bQuit = (m_pBegin->m_iID == m_OriginalIsoline.m_NodeList.size());

				/// Asign the new begin. 
				m_pBegin = m_pActualEndNode;

			}

			iCountIterator++;
		}

	}
}