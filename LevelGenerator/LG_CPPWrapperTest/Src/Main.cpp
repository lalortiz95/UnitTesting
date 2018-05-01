#include <LG_CPPWrap.h>
#include <LG_Generate.h>


int main()
{
	LevelGenerator::LG_Generate* newLevel = reinterpret_cast<LevelGenerator::LG_Generate*>(GenerateLevel(20, 25, 25, 35, 35, 10, 1818, 0, 5));

	LevelGenerator::LG_Generate* newLevelNotWrapp;
	newLevelNotWrapp = new LevelGenerator::LG_Generate();
	newLevelNotWrapp->Run(20, LevelGenerator::LG_Vector3D(25, 25, 0), LevelGenerator::LG_Vector3D(35, 35, 10), 1818, 0, 5);


	int Quepedo = newLevelNotWrapp->m_RoomsVector[15]->m_Walls.size();
	int Quepedox2 = newLevel->m_RoomsVector[15]->m_Walls.size();
	int QUepedox3 = GetRoomWallsAmount(newLevel, 15);
	int Quepedox4 = GetRoomWallsAmount(reinterpret_cast<void*>(newLevelNotWrapp), 15);

	for (int j = 0; j < GetRoomAmount(newLevel); ++j)
	{
		if (j == 15)
			int walls = GetRoomWallsAmount(newLevel, j);
		int walls = GetRoomWallsAmount(newLevel, j);

		for (int i = 0; i < walls; ++i)
		{
			int asddsa = 0;
			asddsa = j;
		}
	}
	return 0;
}