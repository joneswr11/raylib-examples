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

class LoadingScreen
{
public:
	void initLoadingScreen(int screenWidth, int screenHeight);
	int updateState(int &framesCounter);
	void drawLoadingScreen(int &framesCounter);
private:
	int logoPositionX;
	int logoPositionY;

	int lettersCount;

	int topSideRecWidth;
	int leftSideRecHeight;

	int bottomSideRecWidth;
	int rightSideRecHeight;

	int state;                  // Tracking animation states (State Machine)
	float alpha;             // Useful for fading


};

class Screens
{
public:
	void drawTitle(int screenWidth, int screenHeight);
	void drawEnding(int screenWidth, int screenHeight);
	LoadingScreen loadingScreen;
	GamePlay gamePlay;
};