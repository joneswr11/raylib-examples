#pragma once

#include "raylib.h"

const int NUMTREES = 6;
struct spriteData{
	int up; // Row in the file where the sprite is facing up
	int down; // Row in the file where the sprite is facing down
	int left; // Row in the file where the sprite is facing left
	int right; // Row in the file where the sprite is facing right
	int numSpritesX; // How many sprites are in a given sequence
	int numSpritesY; // How many sprites sequences are there
};

struct spriteObject
{
	Rectangle frameRec;
	Rectangle spriteRec;
	Vector2 position;
	Texture2D sprite;
};

struct Background
{
	RenderTexture2D imageTexture;
	Rectangle src;
	Rectangle dest;
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
	spriteData getSprite();

	Texture2D getPlayer();
	Rectangle getFrameRec();
	Vector2 getPosition();

private:
	Texture2D player;
	Rectangle frameRec;
	Vector2 position;
	spriteData sprite;

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
	spriteObject trees[NUMTREES];
	Background background;
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