using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace MiddleWrappCSharp
{
    public struct LG_Vector3D
    {
        public float X, Y, Z;
    };

    public class LG_Node
    {
        public LG_Node() { }
        ~LG_Node() { }

        public LG_Vector3D m_Position;
        public float m_fValue;
        public int m_iID;
        public LG_Node m_pParent;
        public LG_Node[] m_Pointers;
    };

    public class Wrapp_CSharp
    {
        // From c++ Dll (unmanaged)
        [DllImport("MiddleWrappC++")]
        public static extern float TestMultiply(float a, float b);

        // From c++ Dll (unmanaged)
        [DllImport("MiddleWrappC++")]
        public static extern float TestDivide(float a, float b);

        [DllImport("MiddleWrappC++")]
        public static extern LG_Node TestNode();

        [DllImport("MiddleWrappC++")]
        public static extern void TestPosition(ref LG_Node rNode, LG_Vector3D Position);

        [DllImport("MiddleWrappC++")]
        public static extern LG_Node[] TestVectorNodes(LG_Node pNode);


        public static LG_Node SharpTestNode()
        {
            return TestNode();
        }

        public static void SharpTestPosition(ref LG_Node rNode, LG_Vector3D Position)
        {
            TestPosition(ref rNode, Position);
        }

        public static LG_Node[] SharpVectorNode(LG_Node pNode)
        {
            return TestVectorNodes(pNode);
        }

        public static float SharpMultiply(float a, float b)
        {
            return TestMultiply(a, b);//(a * b);
        }

        public static float SharpDivide(float a, float b)
        {
            if (b == 0)
            {
                return 0;
            }

            return TestDivide(a, b); // (a / b);
        }
    }
}
