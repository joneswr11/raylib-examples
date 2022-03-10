// more examples can be found here:
// https://www.raylib.com/examples.html
// https://github.com/raysan5/raylib/tree/master/examples

#include "raylib.h"
#include <iostream>

#define BASICTEST 1
#define SCISSORTEST 2
#define BALLMOVINGTEST 3
#define ANIMATEDTEXTTEST 4
#define TESTTORUN ANIMATEDTEXTTEST

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

		DrawText(TextSubtext(stringMessages[messageToDisplay].c_str(), 0, framesCounter / defaultSpeed), 210, 160, 20, MAROON);

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
#endif

	return 0;
}

