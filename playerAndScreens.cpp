#include "playerAndScreens.h"

//void Screens::drawLoading()
//{
//	DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
//	DrawText("Loading Game...", 290, 220, 20, GRAY);
//}

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

void GamePlay::loadGamePlayScreen()
{
	player.loadPlayer();
	currentFrame = 0;
	framesSpeed = 8;
}

void GamePlay::unloadGamePlayScreen()
{
	player.unload();
}

void GamePlay::updateGamePlayScreen(int &framesCounter, int FPS)
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

void GamePlay::drawGamePlay()
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

void LoadingScreen::initLoadingScreen(int screenWidth, int screenHeight)
{
	logoPositionX = screenWidth / 2 - 128;
	logoPositionY = screenHeight / 2 - 128;

	lettersCount = 0;

	topSideRecWidth = 16;
	leftSideRecHeight = 16;

	bottomSideRecWidth = 16;
	rightSideRecHeight = 16;

	state = 0;                  // Tracking animation states (State Machine)
	alpha = 1.0f;             // Useful for fading
}

int LoadingScreen::updateState(int &framesCounter)
{
	if (state == 0)                 // State 0: Small box blinking
	{
		framesCounter++;

		if (framesCounter == 120)
		{
			state = 1;
			framesCounter = 0;      // Reset counter... will be used later...
		}
	}
	else if (state == 1)            // State 1: Top and left bars growing
	{
		topSideRecWidth += 4;
		leftSideRecHeight += 4;

		if (topSideRecWidth == 256) state = 2;
	}
	else if (state == 2)            // State 2: Bottom and right bars growing
	{
		bottomSideRecWidth += 4;
		rightSideRecHeight += 4;

		if (bottomSideRecWidth == 256) state = 3;
	}
	else if (state == 3)            // State 3: Letters appearing (one by one)
	{
		framesCounter++;

		if (framesCounter / 12)       // Every 12 frames, one more letter!
		{
			lettersCount++;
			framesCounter = 0;
		}

		if (lettersCount >= 10)     // When all letters have appeared, just fade out everything
		{
			alpha -= 0.02f;

			if (alpha <= 0.0f)
			{
				alpha = 0.0f;
				state = 4;
			}
		}
	}
	else if (state == 4)            // State 4: Reset and Replay
	{
		return 1;
		//if (IsKeyPressed(KEY_R))
		//{
		//	framesCounter = 0;
		//	lettersCount = 0;

		//	topSideRecWidth = 16;
		//	leftSideRecHeight = 16;

		//	bottomSideRecWidth = 16;
		//	rightSideRecHeight = 16;

		//	alpha = 1.0f;
		//	state = 0;          // Return to State 0
		//}
	}
	return 0;
}

void LoadingScreen::drawLoadingScreen(int &framesCounter)
{
	if (state == 0)
	{
		if ((framesCounter / 15) % 2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
	}
	else if (state == 1)
	{
		DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
		DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
	}
	else if (state == 2)
	{
		DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
		DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

		DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
		DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
	}
	else if (state == 3)
	{
		DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
		DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

		DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
		DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

		DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, alpha));

		DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(BLACK, alpha));
	}
	DrawText("Loading Game...", GetScreenWidth() / 2 - 75, GetScreenHeight() - 50, 20, GRAY);
}