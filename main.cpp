#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <stdlib.h>

class MapGenerator : public olc::PixelGameEngine
{
public:
	MapGenerator()
	{
		sAppName = "Galactic Map";
	}
public:
	//Accel = speed/frame
	double gravityAccel = 0.4;

	double ballXPos = 32.0;
	double ballYPos = 32.0;

	double ballVertSpeed = 0;

	int ballSize = 10;
	//star::Star stars[NUMBER_OF_STARS];

public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		/* Horizontal Traverse */
		if (GetKey(olc::Key::A).bHeld) {
			if (ballXPos < 10.0)
				ballXPos = ScreenWidth() - 10.0;
			else
				ballXPos -= 4.0;
		}
		if (GetKey(olc::Key::D).bHeld) {
			if (ballXPos > ScreenWidth() - 10.0)
				ballXPos = 10.0;
			else
				ballXPos += 4.0;
		}

		ballYPos -= ballVertSpeed;

		/* Jump */
		if (ballYPos > (double)ScreenHeight() - 11 - ballSize) {//Makes sure operation occurs at ground level
			ballYPos = (double)ScreenHeight() - 10.0 - ballSize;
			ballVertSpeed = (ballVertSpeed * .4) * -1.0;
			if (GetKey(olc::Key::W).bHeld) {
				ballVertSpeed += 8.0;
			}
		}
		if (ballYPos < (double)ScreenHeight() - 10.0 - ballSize) {
			ballVertSpeed -= gravityAccel;
		}


		Clear(olc::BLACK);

		DrawLine(10, 10, ScreenWidth() - 10, 10, olc::WHITE);
		DrawLine(10, ScreenHeight() - 10, 10, 10, olc::WHITE);
		DrawLine(10, ScreenHeight() - 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::WHITE);
		DrawLine(ScreenWidth() - 10, 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::WHITE);

		FillCircle(ballXPos, ballYPos, ballSize, olc::WHITE);
		return true;
	}
	
	bool OnUserDestroy() override
	{
		return true;
	}
};

int main() {
	int screenPixelsX = 512 * 2;
	int screenPixelsY = 384 * 2;

	MapGenerator map;
	if (map.Construct(screenPixelsX, screenPixelsY, 1, 1, false, true))
		map.Start();

	return 0;
}
