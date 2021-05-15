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
    double resistance = 0.05;
    double friction = 0.2;

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

        /* Resistance Calculations */
        if(ballYVelocity > 0){
            ballYVelocity = ballYVelocity * (1 - resistance * ((ballSize + 30) / 35));
        }
        if(ballXVelocity != 0){
            ballXVelocity = ballXVelocity * (1 - resistance * ((ballSize + 30) / 35));
        }
        /* Modification Options */
        /* Changing the Size of the Ball Live */
        if (GetKey(olc::Key::R).bHeld) {
            if (ballSize < 100.0)
                ballSize += 1;
                ballYPos -= 1;
        }
        if (GetKey(olc::Key::F).bHeld) {
            if (ballSize > 1)
                ballSize -= 1;
                ballYPos += 1;
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
        /* Modifying Resistance */
        if (GetKey(olc::Key::Y).bHeld) {
            if (resistance < .2)
                resistance += .0005;
        }
        if (GetKey(olc::Key::H).bHeld) {
            if (resistance > -.01)
                resistance -= .0005;
        }


        /* Horizontal Traverse */
        if (GetKey(olc::Key::A).bHeld) {
            ballXVelocity -= ballXAccel;
        }
        if (GetKey(olc::Key::D).bHeld) {
            ballXVelocity += ballXAccel;
        }


        /* Jump */
        if (ballXPos > (double)ScreenWidth() - 10 - ballSize) {//Makes sure operation occurs at right wall level
            ballXPos = (double)ScreenWidth() - 10.0 - ballSize;
            ballXVelocity = (ballXVelocity) * (1 - friction) * -1.0;
        }

        if (ballXPos < 10 + ballSize) {//Makes sure operation occurs at left wall level
            ballXPos = 10.0 + ballSize;
            ballXVelocity = (ballXVelocity) * (1 - friction) * -1.0;
        }


        if (ballYPos > (double)ScreenHeight() - 10.1 - ballSize) {//Makes sure operation occurs at ground level
            if(ballYVelocity < 1 && ballYVelocity > -1) {
                ballYPos = (double) ScreenHeight() - 10 - ballSize;
            }
            ballYVelocity = (ballYVelocity) * (1 - friction) * -1.0;
            if (GetKey(olc::Key::SPACE).bHeld) {
                ballYVelocity += 20.0;
            }
        }

        if (ballYPos < 10.1 + ballSize) {//Makes sure operation occurs at ceiling level
            ballYPos = 10.0 + ballSize;
            ballYVelocity = (ballYVelocity) * (1 - friction) * -1.0;
        }

        //Todo: fix these so they only modify the pos up to the location being bounced on and no further
        ballYPos -= ballYVelocity;
        ballXPos += ballXVelocity;

        /* General Resistance + Gravity */

        if(ballYPos < (double)ScreenHeight() - 11.0 - ballSize){//Todo: add terminal velocity based on resist and gravity
            ballYVelocity -= gravityAccel; //Positive Y is up
        }


        Clear(olc::DARK_CYAN);

        DrawLine(10, 10, ScreenWidth() - 10, 10, olc::WHITE);
        DrawLine(10, ScreenHeight() - 10, 10, 10, olc::WHITE);
        DrawLine(10, ScreenHeight() - 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::WHITE);
        DrawLine(ScreenWidth() - 10, 10, ScreenWidth() - 10, ScreenHeight() - 10, olc::WHITE);

        DrawString(ScreenWidth() - 225, 25,
                   "X Position: " + std::to_string(ballXPos) + "\n"+
                   "Y Position: " + std::to_string(ballYPos) + "\n"+
                   "Y - Velocity: " + std::to_string(ballYVelocity) + "\n"+
                   "X - Velocity: " + std::to_string(ballXVelocity) + "\n"+
                   "Ball Size: " + std::to_string(ballSize) + "\n"+
                   "Air Resist: " + std::to_string(resistance) + "\n"+
                   "Gravity: " + std::to_string(gravityAccel));
        FillCircle(ballXPos, ballYPos, ballSize, olc::WHITE);
        return true;
    }

    bool OnUserDestroy() override
    {
        return true;
    }
};

int main() {
    int screenPixelsX = 1280;
    int screenPixelsY = 720;

    MapGenerator map;
    if (map.Construct(screenPixelsX, screenPixelsY, 1, 1, false, true))
        map.Start();

    return 0;
}
