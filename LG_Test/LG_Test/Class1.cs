using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

public struct LG_Vector3D
{
    /// @var Variables to store the positions in X, Y, and Z axis.
    float X;
    float Y;
    float Z;

    /// Parameter constructor.
    public LG_Vector3D(float x, float y, float z)
    {
        X = x;
        Y = y;
        Z = z;
    }
}

public struct LG_Matrix3D
{
    float X0, Y0, Z0,
        X1, Y1, Z1,
        X2, Y2, Z2;
}

public class LG_Node
{
    LG_Node()
    {

    }

    ~LG_Node()
    {

    }

    /**
     *	@var This variable store's an ID.
     */
    int m_iID;

    /**
     *	@var This variable stores a 3D position (X,Y,Z).
     */
    LG_Vector3D m_Position;

    /**
     *	@var This variable store's the weight of the node.
     */
    float m_fWeight;

    /**
     *	@var This flag determinate if the node is On or Off.
     */
    bool m_bIsInside;

    /**
     *	@var This flag determinate if this node can be deleted.
     */
    bool m_bCanDeleted;

    /**
     *	@var This flag determinates if the node has already been used.
     */
    bool m_bIsChecked;

    /**
     *	@var Pointer of node that defines what node is the parent.
     */
    LG_Node m_pParentNode;

    /**
     *	@var This vector stores a pointer of nodes.
     */
    LG_Node[] m_PointerNodes;
}

public struct LG_Rect
{
    /**
     *	@var This variable stores the width of the rect.
     */
    float m_fWidth;

    /**
     *	@var This variable stores the height of the rect.
     */
    float m_fHeight;

    /**
     *	@var The center node of the rectangle.
     */
    LG_Node m_CenterNode;

    /**
     *	@var The vector that define a direction.
     */
    LG_Vector3D m_Direction;

    /**
     *	@var This matrix is used to check collisions easily.
     */
    LG_Matrix3D m_RotationMatrix;

    /**
     *	@var The top node on the left of the tile.
     */
    LG_Node m_TopLeft;

    /**
     *	@var The top node on the right of the tile.
     */
    LG_Node m_TopRight;

    /**
     *	@var The bottom node on the right of the tile.
     */
    LG_Node m_BottomRight;

    /**
     *	@var The bottom node on the left of the tile.
     */
    LG_Node m_BottomLeft;
}

public class TestCSharpLib
{
    [DllImport("LG_Algorithms.dll")]
    public static extern IntPtr GenerateLevel(int RoomsAmount, LG_Vector3D minSizeRoom, LG_Vector3D maxSizeRoom);

    [DllImport("LG_Algorithms.dll")]
    public static extern LG_Rect[] GetRooms();

    //Returns a LGGenerate Object whose store the level information. Such as rooms positions.
    public static IntPtr SharpGenerateLevel(int RoomsAmount, LG_Vector3D minSizeRoom, LG_Vector3D maxSizeRoom)
    {
        return GenerateLevel(RoomsAmount, minSizeRoom, maxSizeRoom);
    }

    //! This function returns a vector where we store the rooms.
    public static LG_Rect[] SharpGetRooms()
    {
        return GetRooms();
    }
}


