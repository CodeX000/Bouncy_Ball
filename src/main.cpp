#define OLC_PGE_APPLICATION
#include "../include/olcPixelGameEngine.h"
#include <stdlib.h>

class MapGenerator : public olc::PixelGameEngine
{
public:
	MapGenerator()
	{
		sAppName = "Galactic Map";
	}
public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        for (int x = 0; x < ScreenWidth(); x++)
            for (int y = 0; y < ScreenHeight(); y++)
                Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));
		return true;
	}
	
	bool OnUserDestroy() override
	{
		return true;
	}
};

int main() {
	int screenPixelsX = 512 / 2;
	int screenPixelsY = 384 / 2;

	MapGenerator map;
	if (map.Construct(screenPixelsX, screenPixelsY, 1, 1, false, true))
		map.Start();

	return 0;
}
