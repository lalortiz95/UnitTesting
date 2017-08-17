#pragma once
#include <LG_UtilitiesPrerequisites.h>

#define FIRST_NODE 0			/// Number that define the first node of the line, or triangle.
#define SECOND_NODE 1			/// Number that define the second node of the line, or triangle.
#define THIRD_NODE 2			/// A third node, used in a triangle.

#define FIRST_ARISTA 0
#define SECOND_ARISTA 1	
#define THIRD_ARISTA 2	

#define NODES_PER_LINE 2		/// Define a number of nodes per line.
#define VERTEX_PER_TRIANGLE 3	/// Define a number of vertex per triangles.

#if defined(LG_GEOMETRY_EXPORTS)
#	define LG_GEOMETRY_EXPORT __declspec(dllexport)
#elif defined(LG_GEOMETRY_STATIC)
#	define LG_GEOMETRY_EXPORT 
#else
#	define LG_GEOMETRY_EXPORT __declspec(dllimport)
#endif