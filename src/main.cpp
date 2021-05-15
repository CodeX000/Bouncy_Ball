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
    //Accel = speed/frame
    const double PI = 3.1415926;
    double gravityAccel = 0.4;
    double resistance = 0.08;
    double friction = .2;

    double ballMass = 10.0; //Not used yet

    double ballXPos = 32.0;
    double ballXVelocity = 0;
    double ballXAccel = .5;

    double ballYPos = 32.0;
    double ballYVelocity = 0;

    double ballAngle = 0;

    int ballSize = 10;

public:
    double getMomentum(){ //Not used yet
        return ballMass * (ballXVelocity);
    }/*
    void bounce(double objectAngle){
        double adjustedAngle = (2 * PI) - objectAngle;
        double exitAngle = adjustedAngle - 2 * objectAngle;
    }*/

public:
    bool OnUserCreate() override
    {
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        /* Modification Options */
        /* Changing the Size of the Ball Live */
        if (GetKey(olc::Key::R).bHeld) {
            if (ballSize < 100.0)
                ballSize += 1;
        }
        if (GetKey(olc::Key::F).bHeld) {
            if (ballSize > 1)
                ballSize -= 1;
        }
        /* Modifying Gravity */
        if (GetKey(olc::Key::T).bHeld) {
            if (gravityAccel < 1)
                gravityAccel += .01;
        }
        if (GetKey(olc::Key::G).bHeld) {
            if (gravityAccel > -.1)
                gravityAccel -= .01;
        }


        /* Horizontal Traverse */
        if (GetKey(olc::Key::A).bHeld) {
            ballXVelocity -= ballXAccel;
        }
        if (GetKey(olc::Key::D).bHeld) {
            ballXVelocity += ballXAccel;
        }


        /* Jump */
        if (GetKey(olc::Key::SPACE).bHeld && ballXPos > (double)ScreenWidth() - 11 - ballSize) {
            ballXVelocity += 8.0;
        }

        if (ballXPos > (double)ScreenWidth() - 10 - ballSize) {//Makes sure operation occurs at right wall level
            ballXPos = (double)ScreenWidth() - 10.0 - ballSize;
            ballXVelocity = (ballXVelocity) * friction * -1.0;
        }

        if (ballXPos < 10 + ballSize) {//Makes sure operation occurs at left wall level
            ballXPos = 10.0 + ballSize;
            ballXVelocity = (ballXVelocity) * friction * -1.0;
        }

        if (ballYPos > (double)ScreenHeight() - 10 - ballSize) {//Makes sure operation occurs at ground level
            ballYPos = (double)ScreenHeight() - 10 - ballSize;
            ballYVelocity = (ballYVelocity) * friction * -1.0;
            if (GetKey(olc::Key::SPACE).bHeld) {
                ballYVelocity += 15.0;
            }
        }

        //Todo: fix these so they only modify the pos up to the location being bounced on and no further
        ballYPos -= ballYVelocity;
        ballXPos += ballXVelocity;

        /* General Resistance + Gravity */

        if(ballYPos < (double)ScreenHeight() - 11.0 - ballSize){//Todo: add terminal velocity based on resist and gravity
            ballYVelocity -= gravityAccel; //Positive Y is up
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
