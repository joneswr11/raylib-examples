#include "playerAndScreens.h"

void Screens::drawLoading()
{
	DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
	DrawText("Loading Game...", 290, 220, 20, GRAY);
}

void Screens::drawTitle(int screenWidth, int screenHeight)
{
	DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
	DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
	DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
}

void Screens::drawEnding(int screenWidth, int screenHeight)
{
	DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
	DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
	DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
}

void Screens::loadGamePlayScreen()
{
	player.loadPlayer();
	currentFrame = 0;
	framesSpeed = 8;
}

void Screens::updateGamePlayScreen(int &framesCounter, int FPS)
{

	float movingSpeed = 2.0f;
	// simulate running
	if (IsKeyDown(KEY_B))
		movingSpeed = 4.0f;

	// Only able to move in one direction at a time
	if (IsKeyDown(KEY_RIGHT)) player.setXPos(player.getPosition().x + movingSpeed);
	else if (IsKeyDown(KEY_LEFT)) player.setXPos(player.getPosition().x - movingSpeed);
	else if (IsKeyDown(KEY_UP)) player.setYPos(player.getPosition().y - movingSpeed);
	else if (IsKeyDown(KEY_DOWN)) player.setYPos(player.getPosition().y + movingSpeed);

	// makes the sprite move faster or slower along with the actual movement of the box
	framesSpeed = (int)movingSpeed * 3;

	// Make sure player does not go out of move area limits
	if ((player.getPosition().x + player.getFrameRec().width) >= GetScreenWidth()) player.setXPos(GetScreenWidth() - player.getFrameRec().width);
	else if (player.getPosition().x <= 0) player.setXPos(0);

	if ((player.getPosition().y + player.getFrameRec().height) >= GetScreenHeight()) player.setYPos(GetScreenHeight() - player.getFrameRec().height);
	else if (player.getPosition().y <= 0) player.setYPos(0);

	framesCounter++;

	// if the player is moving, it moves moves to the next sprite character in the file and display's it
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_UP))
	{
		if (framesCounter >= (FPS / framesSpeed))
		{
			framesCounter = 0;
			currentFrame++;

			if (currentFrame > 7) currentFrame = 0;

			player.setXFrameRec((float)currentFrame*(float)player.getPlayer().width / 8);
		}
	}
	// if the player is not moving it reverts back to the first sprite character in the file
	else
	{
		currentFrame = 0;
		player.setXFrameRec((float)currentFrame*(float)player.getPlayer().width / 8);
	}
}

void Screens::drawGamePlay()
{
	DrawTextureRec(player.getPlayer(), player.getFrameRec(), player.getPosition(), WHITE);
}

void PlayerCharacter::loadPlayer()
{
	player = LoadTexture("resources/run.png");        // Texture loading

	position = { 350.0f, 280.0f };
	frameRec = { 0.0f, 0.0f, (float)player.width / 8, (float)player.height };
}

void PlayerCharacter::unload()
{
	UnloadTexture(player);
}

void PlayerCharacter::setXPos(float x)
{
	position.x = x;
}

void PlayerCharacter::setYPos(float y)
{
	position.y = y;
}

void PlayerCharacter::setXFrameRec(float x)
{
	frameRec.x = x;
}

void PlayerCharacter::setYFrameRec(float y)
{
	frameRec.y = y;
}

Texture2D PlayerCharacter::getPlayer()
{
	return player;
}

Rectangle PlayerCharacter::getFrameRec()
{
	return frameRec;
}

Vector2 PlayerCharacter::getPosition()
{
	return position;
}