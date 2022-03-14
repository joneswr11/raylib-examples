#pragma once

#include "raylib.h"

class PlayerCharacter
{
public:
	void loadPlayer();
	void unload();
	void setXPos(float x);
	void setYPos(float x);
	void setXFrameRec(float x);
	void setYFrameRec(float y);
	Texture2D getPlayer();
	Rectangle getFrameRec();
	Vector2 getPosition();
private:
	Texture2D player;
	Rectangle frameRec;
	Vector2 position;

};

class GamePlay
{
public:
	void drawGamePlay();
	void loadGamePlayScreen();
	void updateGamePlayScreen(int &framesCounter, int FPS);
	void unloadGamePlayScreen();
private:
	PlayerCharacter player;
	int currentFrame;
	int framesSpeed;            // Number of spritesheet frames shown by second
};

class Screens
{
public:
	void drawLoading();
	void drawTitle(int screenWidth, int screenHeight);
	void drawEnding(int screenWidth, int screenHeight);
	GamePlay gamePlay;
};