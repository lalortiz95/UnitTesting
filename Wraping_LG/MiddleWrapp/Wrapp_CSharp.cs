using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace MiddleWrappCSharp
{
    [StructLayout(LayoutKind.Sequential)]
    public struct LG_Vector3D
    {
        public LG_Vector3D(float fx, float fy, float fz)
        {
            X = fx;
            Y = fy;
            Z = fz;
        }

        public float X, Y, Z;
    };

    public class LG_Node
    {
        public LG_Node() { }
        ~LG_Node() { }
        
        public int m_iID;
        
        public float m_fValue;
        
        public LG_Vector3D m_Position;
       
        public LG_Node m_pParent;
        
        public LG_Node[] m_Pointers;
    };

    public class Wrapp_CSharp
    {
        // From c++ Dll (unmanaged)
        [DllImport("MiddleWrappC++", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Start(int iNodeID, float fNodeValue, float NodePosition, int iParentNodeID, int iSizeNodeConections, ref float pos);

        // From c++ Dll (unmanaged)
        [DllImport("MiddleWrappC++")]
        public static extern float TestMultiply(float a, float b);

        // From c++ Dll (unmanaged)
        [DllImport("MiddleWrappC++")]
        public static extern float TestDivide(float a, float b);

        // From c++ Dll (unmanaged)
        [DllImport("MiddleWrappC++")]
        public static extern float TestGlobalVar();

        public static float SharpMultiply(float a, float b)
        {
            return TestMultiply(a, b);
        }
        
        public static float SharpDivide(float a, float b)
        {
            return TestDivide(a, b);
        }

        public static void SharpStart(int iNodeID, float fNodeValue, float NodePosition, int iParentNodeID, int iSizeNodeConections, ref float FinalPos)
        {
            Start(iNodeID, fNodeValue, NodePosition, iParentNodeID, iSizeNodeConections, ref FinalPos);
        }
        public float SharpValue()
        {
            return TestGlobalVar();
        }
    }
}
