#pragma once

#include "raylib.h"

struct spriteOrientation{
	int up;
	int down;
	int left;
	int right;
};

class PlayerCharacter
{
public:
	void loadPlayer();
	void unload();
	void setXPos(float x);
	void setYPos(float x);
	void setXFrameRec(float x);
	void setYFrameRec(float y);
	int getNumSpritesX();
	int getNumSpritesY();
	spriteOrientation getSpriteDirection();

	Texture2D getPlayer();
	Rectangle getFrameRec();
	Vector2 getPosition();

private:
	Texture2D player;
	Rectangle frameRec;
	Vector2 position;
	int numSpritesX;
	int numSpritesY;
	spriteOrientation sprite;

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
	Rectangle block;
	int currentFrame;
	int framesSpeed;            // Number of spritesheet frames shown by second
	Camera2D camera;
};

class LoadingScreen
{
public:
	void initLoadingScreen();
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
	float blinkingAlpha;
	bool fading;


};

class Screens
{
public:
	void drawTitle();
	void drawEnding();
	LoadingScreen loadingScreen;
	GamePlay gamePlay;
};