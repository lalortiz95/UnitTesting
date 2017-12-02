#pragma once
#include "LG_CPPWrapperPrerequisites.h"
#include <LG_Generate.h>


#define LG_WRAPPER_EXPORT __declspec(dllexport)

class  LG_CPPWrap
{
public:
	LG_CPPWrap();
	~LG_CPPWrap();

	/*	/// This functions is gonna fill all the information needed to then be asked through the get functions.
		void Run(int iRoomAmount);

		///
		int GetRoomID(int iPlaceInArray);

		///
		void GetRoomPosition(int iPlaceInArray, float& fx, float& fy, float& fz);*/
};


LevelGenerator::LG_Generate g_generate;

extern "C"
{
	//LG_WRAPPER_EXPORT void* MyClass();

	LG_WRAPPER_EXPORT int multiplyvalue(int ivalue);
	
	/// This functions is gonna fill all the information needed to then be asked through the get functions. 
	LG_WRAPPER_EXPORT void Run(int iRoomAmount);

	///
	LG_WRAPPER_EXPORT int GetRoomID(int iPlaceInArray);

	///
	LG_WRAPPER_EXPORT void GetRoomPosition(int iPlaceInArray, float& fx, float& fy, float& fz);

}