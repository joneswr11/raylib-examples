// more examples can be found here:
// https://www.raylib.com/examples.html
// https://github.com/raysan5/raylib/tree/master/examples

#include "raylib.h"
#include <iostream>

#define BASICTEST 1
#define SCISSORTEST 2
#define BALLMOVINGTEST 3
#define ANIMATEDTEXTTEST 4
#define BOXMOVECOLLISIONTEST 5
#define TEXTUREBOXCOLLISIONTEST 6
#define TESTTORUN TEXTUREBOXCOLLISIONTEST

void basicTest()
{
	InitWindow(800, 450, "Graphics Test");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RED);
		DrawText("This actually works", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}

	CloseWindow();
}

void scissorTest()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - scissor test");

	Rectangle scissorArea = { 0, 0, 300, 300 };
	bool scissorMode = true;

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		if (IsKeyPressed(KEY_S)) scissorMode = !scissorMode;

		// Centre the scissor area around the mouse position
		scissorArea.x = GetMouseX() - scissorArea.width / 2;
		scissorArea.y = GetMouseY() - scissorArea.height / 2;
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if (scissorMode) BeginScissorMode((int)scissorArea.x, (int)scissorArea.y, (int)scissorArea.width, (int)scissorArea.height);

		// Draw full screen rectangle and some text
		// NOTE: Only part defined by scissor area will be rendered
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), RED);
		DrawText("Move the mouse around to reveal this text!", 190, 200, 20, LIGHTGRAY);

		if (scissorMode) EndScissorMode();

		DrawRectangleLinesEx(scissorArea, 1, BLACK);
		DrawText("Press S to toggle scissor test", 10, 10, 20, BLACK);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

}

void moveBallWithArrowKeys()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - keyboard input");

	Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		float movingSpeed = 2.0f;
		// simulate running
		if (IsKeyDown(KEY_B))
			movingSpeed = 4.0f;

		// Only able to move in one direction at a time
		if (IsKeyDown(KEY_RIGHT)) ballPosition.x += movingSpeed;
		else if (IsKeyDown(KEY_LEFT)) ballPosition.x -= movingSpeed;
		else if (IsKeyDown(KEY_UP)) ballPosition.y -= movingSpeed;
		else if (IsKeyDown(KEY_DOWN)) ballPosition.y += movingSpeed;

		// Able to move in any direction
		//if (IsKeyDown(KEY_RIGHT)) ballPosition.x += movingSpeed;
		//if (IsKeyDown(KEY_LEFT)) ballPosition.x -= movingSpeed;
		//if (IsKeyDown(KEY_UP)) ballPosition.y -= movingSpeed;
		//if (IsKeyDown(KEY_DOWN)) ballPosition.y += movingSpeed;
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

		DrawCircleV(ballPosition, 50, MAROON);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

}

void animatedText()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [text] example - text writing anim");

	std::string stringMessages[2] = {
		"This sample illustrates a text writing\nanimation effect! Check it out! ;)",
		"This is a second message that will be\ndisplayed after the first"
	};

	int framesCounter = 0;
	int messageToDisplay = 0;
	const int defaultSpeed = 10;
	Rectangle textBox = { 200, 150, 400, 75 }; // sets size for text box

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_B)) framesCounter += 8;
		else framesCounter++;

		if (IsKeyPressed(KEY_A) && (framesCounter / defaultSpeed) >= static_cast<int>(stringMessages[messageToDisplay].length()))
		{
			if (messageToDisplay == 0) messageToDisplay = 1;
			else messageToDisplay = 0;
			framesCounter = 0;
		}

		if (IsKeyPressed(KEY_ENTER))
		{
			if ((framesCounter / defaultSpeed) >= static_cast<int>(stringMessages[messageToDisplay].length()))
			{
				if (messageToDisplay == 0) messageToDisplay = 1;
				else messageToDisplay = 0;
			}
			framesCounter = 0;
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawRectangleLinesEx(textBox, 2, BLACK); // Draws a black text box around text
		DrawText(TextSubtext(stringMessages[messageToDisplay].c_str(), 0, framesCounter / defaultSpeed), 210, 160, 20, BLACK);

		DrawText("PRESS [ENTER] to RESTART!", 240, 260, 20, LIGHTGRAY);
		DrawText("HOLD [A] or [B] to SPEED UP!", 239, 300, 20, LIGHTGRAY);
		DrawText("Press [A] to GO TO NEXT MESSAGE!", 239, 340, 20, LIGHTGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
}

void moveBoxWithCollisions()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "example - keyboard input and collision");

	Rectangle box = { (float)screenWidth / 2, (float)screenHeight / 2, 30, 30 };


	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		float movingSpeed = 2.0f;
		// simulate running
		if (IsKeyDown(KEY_B))
			movingSpeed = 4.0f;

		// Only able to move in one direction at a time
		if (IsKeyDown(KEY_RIGHT)) box.x += movingSpeed;
		else if (IsKeyDown(KEY_LEFT)) box.x -= movingSpeed;
		else if (IsKeyDown(KEY_UP)) box.y -= movingSpeed;
		else if (IsKeyDown(KEY_DOWN)) box.y += movingSpeed;

		// Able to move in any direction
		//if (IsKeyDown(KEY_RIGHT)) box.x += movingSpeed;
		//if (IsKeyDown(KEY_LEFT)) box.x -= movingSpeed;
		//if (IsKeyDown(KEY_UP)) box.y -= movingSpeed;
		//if (IsKeyDown(KEY_DOWN)) box.y += movingSpeed;

		// Make sure Box does not go out of move area limits
		if ((box.x + box.width) >= GetScreenWidth()) box.x = GetScreenWidth() - box.width;
		else if (box.x <= 0) box.x = 0;

		if ((box.y + box.height) >= GetScreenHeight()) box.y = GetScreenHeight() - box.height;
		else if (box.y <= 0) box.y = 0;

		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("move the Box with arrow keys", 10, 10, 20, DARKGRAY);

		DrawRectangleRec(box, RED);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

}

void moveTextureBoxWithCollisions()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;
	const int FPS = 60;
	//const int MAX_FRAME_SPEED = 15;
	//const int MIN_FRAME_SPEED = 1;

	InitWindow(screenWidth, screenHeight, "raylib [texture] example - texture rectangle");

	// NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
	Texture2D player = LoadTexture("resources/run.png");        // Texture loading

	Vector2 position = { 350.0f, 280.0f };
	Rectangle frameRec = { 0.0f, 0.0f, (float)player.width / 8, (float)player.height };
	int currentFrame = 0;

	int framesCounter = 0;
	int framesSpeed = 8;            // Number of spritesheet frames shown by second

	SetTargetFPS(FPS);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		float movingSpeed = 2.0f;
		// simulate running
		if (IsKeyDown(KEY_B))
			movingSpeed = 4.0f;

		// Only able to move in one direction at a time
		if (IsKeyDown(KEY_RIGHT)) position.x += movingSpeed;
		else if (IsKeyDown(KEY_LEFT)) position.x -= movingSpeed;
		else if (IsKeyDown(KEY_UP)) position.y -= movingSpeed;
		else if (IsKeyDown(KEY_DOWN)) position.y += movingSpeed;

		// makes the sprite move faster or slower along with the actual movement of the box
		framesSpeed = (int)movingSpeed * 3;

		// Make sure player does not go out of move area limits
		if ((position.x + frameRec.width) >= GetScreenWidth()) position.x = GetScreenWidth() - frameRec.width;
		else if (position.x <= 0) position.x = 0;

		if ((position.y + frameRec.height) >= GetScreenHeight()) position.y = GetScreenHeight() - frameRec.height;
		else if (position.y <= 0) position.y = 0;

		framesCounter++;

		// if the player is moving, it moves moves to the next sprite character in the file and display's it
		if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_UP))
		{
			if (framesCounter >= (FPS / framesSpeed))
			{
				framesCounter = 0;
				currentFrame++;

				if (currentFrame > 7) currentFrame = 0;

				frameRec.x = (float)currentFrame*(float)player.width / 8;
			}
		}
		// if the player is not moving it reverts back to the first sprite character in the file
		else
		{
			currentFrame = 0;
			frameRec.x = (float)currentFrame*(float)player.width / 8;
		}

		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawTextureRec(player, frameRec, position, WHITE);  // Draw part of the texture

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadTexture(player);       // Texture unloading

	CloseWindow();                // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

}

int main(int argc, char** argv[])
{

#if TESTTORUN==BASICTEST
	basicTest();
#elif TESTTORUN==SCISSORTEST
	scissorTest();
#elif TESTTORUN==BALLMOVINGTEST
	moveBallWithArrowKeys();
#elif TESTTORUN==ANIMATEDTEXTTEST
	animatedText();
#elif TESTTORUN==BOXMOVECOLLISIONTEST
	moveBoxWithCollisions();
#elif TESTTORUN==TEXTUREBOXCOLLISIONTEST
	moveTextureBoxWithCollisions();
#endif

	return 0;
}

