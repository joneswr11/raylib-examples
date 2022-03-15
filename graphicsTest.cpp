#include "graphicsExamples.h"

#include <iostream>

#define BASICTEST 1
#define SCISSORTEST 2
#define BALLMOVINGTEST 3
#define ANIMATEDTEXTTEST 4
#define BOXMOVECOLLISIONTEST 5
#define TEXTUREBOXCOLLISIONTEST 6
#define CHANGINGSCREENSTEST 7
#define CAMERA2D 8

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		changingScreens();
		return EXIT_SUCCESS;
	}

	try
	{
		bool isNumber = true;
		char *input = argv[1];
		while (*input)
		{
			if (!isdigit(*input))
			{
				isNumber = false;
				break;
			}
			*input++;
		}
		if (!isNumber) 
			throw - 1;

		int testToRun = atoi(argv[1]);
		switch (testToRun)
		{
		case BASICTEST:
			basicTest();
			break;
		case SCISSORTEST:
			scissorTest();
			break;
		case BALLMOVINGTEST:
			moveBallWithArrowKeys();
			break;
		case ANIMATEDTEXTTEST:
			animatedText();
			break;
		case BOXMOVECOLLISIONTEST:
			moveBoxWithCollisions();
			break;
		case TEXTUREBOXCOLLISIONTEST:
			moveTextureBoxWithCollisions();
			break;
		case CHANGINGSCREENSTEST:
			changingScreens();
			break;
		case CAMERA2D:
			camera2d();
			break;
		default:
			std::cout << "Invalid Number\n";
			break;
		}
		return EXIT_SUCCESS;
	}
	catch (int e)
	{
		std::cout<< "Error: "<<e<<" Invalid number\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

