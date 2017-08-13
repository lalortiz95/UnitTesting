#include "LG_RDP.h"
#include <LG_Rect.h>

namespace LevelGenerator
{
	//! Default constructor.
	LG_RDP::LG_RDP()
	{
		/// Initializes the variables with default values.
		m_pStart = nullptr;
		m_pEnd = nullptr;
		m_pActualNode = nullptr;
	}

	//! Default destructor.
	LG_RDP::~LG_RDP()
	{
		/// Releases memory
		Destroy();
	}

	//! This function initialize all variables of the class.
	void LG_RDP::Init(float fRange, LG_Isoline IsolineToReduce)
	{
		/// Call destroy function to release all memory.
		Destroy();

		/// Store in member variables the values in the parametrs for future references.
		m_fRange = fRange;
		m_OriginalIsoline = IsolineToReduce;

		/// Assign the start and end nodes.
		m_pStart = &m_OriginalIsoline.m_NodeVector.front();
		m_pEnd = &m_OriginalIsoline.m_NodeVector.back();

		/// Set the isoline's node's ids.
		SetIsolineID();

		/// Set which nodes can or cannot be deleted.
		SetFlags();

	}

	//! This function free the memory of the class, and destroys it's variables.
	void LG_RDP::Destroy()
	{
		m_FinalIsoline.m_NodeVector.clear();
		/// If this pointer is diferent than nullptr it calls it's destroy function and frees memory.
		if (m_pActualNode != nullptr)
		{
			m_pActualNode->Destroy();
			m_pActualNode = nullptr;
		}

		/// If this pointer is diferent than nullptr it calls it's destroy function and frees memory.
		if (m_pEnd != nullptr)
		{
			m_pEnd->Destroy();
			m_pEnd = nullptr;
		}

		/// If this pointer is diferent than nullptr it calls it's destroy function and frees memory.
		if (m_pStart != nullptr)
		{
			m_pStart->Destroy();
			m_pStart = nullptr;
		}
	}

	void LG_RDP::Run(float fRange, LG_Isoline Isoline)
	{
		/// Declaration of the boundary to apply the range.
		LG_Rect Boundary;
		/// Flag that indicates if we can delete the nodes between the start and end.
		bool bCanDelete = true;

		/// Call the init function.
		Init(fRange, Isoline);

		bool bQuit = false;


		while (!bQuit)
		{
			/// Reset the flag so that it can get inside again.
			bCanDelete = true;
			/// Checks if the whole isoline is false, if so it changes the start and end nodes.
			ListIsFalse();

			/// Initialize the boundary.
			Boundary.Init(m_pStart->m_Position, m_pEnd->m_Position, m_fRange);

			/// we check collision with the true nodes of the isoline.
			for (int32 i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
			{
				/// If we're ahead of the first node.
				if (i > m_pStart->m_iID && i < m_pEnd->m_iID)
				{
					/// If it can be deleted, and is colliding with the boundary.
					if (m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted &&
						Boundary.CheckCollision(m_OriginalIsoline.m_NodeVector[i],
							*m_pStart))
						continue;
					else
					{
						bCanDelete = false;
						break;
					}
				}
			}

			/// If we can delete nodes in between the start and end nodes.
			if (bCanDelete)
			{
				/// Adds the start to the final isoline, and sets the new start and end nodes.
				AddNodeToFinalIsoline();
			}
			else
			{
				/// If not, we calculate the furthest node, and set it as the end node.
				SetFurthestNode();
			}

			/// If we went through the whole list, it's over.
			if (m_pStart->m_iID == m_pEnd->m_iID)
			{
				m_FinalIsoline.m_NodeVector.push_back(*m_pStart);
				bQuit = true;
			}
		}
	}

	void LG_RDP::SetFurthestNode()
	{
		float fDistance = 0;
		float fStartDistance = 0;
		float fEndDistance = 0;
		float fNewDistance = 0;
		bool bChangeEnd = false;

		/// We iterate thorugh the vector.
		for (int32 i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
		{
			/// Check if it can be deleted.
			if (m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted)
			{
				/// We calculate the distance between the actual iterating node and the first node of the isoline.
				fStartDistance = LG_Vector3D::StaticMagnitude(m_OriginalIsoline.m_NodeVector[i].m_Position - m_pStart->m_Position);
				/// We calculate the distance between the actual iterating node and the last node of the isoline.
				fEndDistance = LG_Vector3D::StaticMagnitude(m_OriginalIsoline.m_NodeVector[i].m_Position - m_pEnd->m_Position);
				/// We add both distances.
				fNewDistance = fStartDistance + fEndDistance;

				if (fNewDistance > fDistance)
				{
					fDistance = fNewDistance;
					m_pActualNode = &m_OriginalIsoline.m_NodeVector[i];
					bChangeEnd = true;
				}
			}
		}

		/// Check if we need to change the end node.
		if (bChangeEnd)
		{
			/// We change the end node.
			m_pEnd = m_pActualNode;
			/// Set the flags accordingly.
			SetFlags();
		}
	}

	//! This function set the flags according to the start and end nodes. 
	void LG_RDP::SetFlags()
	{
		/// Iterate the vector and set the flag.
		for (int32 i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
		{
			/// If the iterating node is before the start node, or after the end node
			/// we set it's flag to false. Otherwise, meaning it's in between, we set
			/// it as true.
			if (i <= m_pStart->m_iID || i >= m_pEnd->m_iID)
			{
				m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted = false;
			}
			else
				m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted = true;
		}
	}

	//! Set the node's IDs.
	void LG_RDP::SetIsolineID()
	{
		for (int32 i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
		{
			m_OriginalIsoline.m_NodeVector[i].m_iID = i;
		}
	}

	void LG_RDP::AddNodeToFinalIsoline()
	{
		/// Add to the final isoline.
		m_FinalIsoline.m_NodeVector.push_back(*m_pStart);

		/// Set The start as the actual end.
		m_pStart = m_pEnd;
		/// Set the end as the original isoline's end.
		m_pEnd = &m_OriginalIsoline.m_NodeVector.back();

		/// Change the flags accordingly.
		SetFlags();
	}

	void LG_RDP::ListIsFalse()
	{
		bool bListFalse = true;

		for (int32 i = 0; i < m_OriginalIsoline.m_NodeVector.size(); ++i)
		{
			if (m_OriginalIsoline.m_NodeVector[i].m_bCanDeleted)
			{
				bListFalse = false;
				break;
			}
		}

		if (bListFalse)
		{
			AddNodeToFinalIsoline();
		}
	}
}
