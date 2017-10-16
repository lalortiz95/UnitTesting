#pragma once
#include <LG_UtilitiesPrerequisites.h>

#define FIRST_NODE 0			/// Number that define the first node of the line, or triangle.
#define SECOND_NODE 1			/// Number that define the second node of the line, or triangle.
#define THIRD_NODE 2			/// A third node, used in a triangle.

#define FIRST_EDGE 0
#define SECOND_EDGE 1	
#define THIRD_EDGE 2	

#define FIRST_INDEX 0
#define SECOND_INDEX 1
#define THIRD_INDEX 2

#define FIRST_ANGLE 0
#define SECOND_ANGLE 1
#define THIRD_ANGLE 2

#define INDEX_PER_EDGE 2

#define NODES_PER_LINE 2		/// Define a number of nodes per line.
#define NODES_PER_EDGE 2		/// Define a number of nodes per edge.

#define EDGES_PER_TRIANGLE  3	/// Define a number of edges per triangle.
#define NODES_PER_TRIANGLE  3	/// Define a number of vertex per triangle.
#define INDEX_PER_TRIANGLE  3   /// Define a number of index per triangle.
#define ANGLES_PER_TRIANGLE 3	/// Defines the number of angles per triangle.

#if defined(LG_GEOMETRY_EXPORTS)
#	define LG_GEOMETRY_EXPORT __declspec(dllexport)
#elif defined(LG_GEOMETRY_STATIC)
#	define LG_GEOMETRY_EXPORT 
#else
#	define LG_GEOMETRY_EXPORT __declspec(dllimport)
#endif