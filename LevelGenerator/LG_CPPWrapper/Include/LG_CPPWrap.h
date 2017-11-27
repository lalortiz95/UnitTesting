#pragma once
#include "LG_CPPWrapperPrerequisites.h"

#include <LG_Generate.h>

extern "C"
{
	class LG_WRAPPER_EXPORT LG_CPPWrap
	{
	public:
		LG_CPPWrap();
		~LG_CPPWrap();
		
		/// This functions is gonna fill all the information needed to then be asked through the get functions. 
		void Run(int iRoomAmount);

		///
		int GetRoomID(int iPlaceInArray);

		/// 
		void GetRoomPosition(float& fx, float& fy, float& fz);
	};
}

LevelGenerator::LG_Generate g_generate;

