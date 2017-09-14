#include <LG_Circle.h>
#include <LG_Isoline.h>
#include <LG_Line.h>
#include <LG_Rect.h>
#include <LG_Triangle.h>

#include <gtest/gtest.h>

using namespace LevelGenerator;

TEST(GeometryUnitTest, NotNameStill)
{
	int32 iID = 0;
	LG_Triangle triangle;
	triangle.Init(new LG_Node(0, 0, 0), new LG_Node(7, 3, 0), new LG_Node(3, 5, 0), iID, iID);

	EXPECT_FALSE(triangle.IsPointInside(new LG_Node(5, 1, 0)));
	EXPECT_TRUE(triangle.IsPointInside(new LG_Node(2, 3, 0)));
	EXPECT_TRUE(triangle.IsPointInside(new LG_Node(4, 3, 0)));
}