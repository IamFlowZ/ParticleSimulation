// FinalProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <SDL.h>
#include "Screen.h"
#include "Swarm.h"


using namespace std;

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Screen screen;

	if (screen.init() == false)
	{
		cout << "Error on init." << endl;
	}

	srand(time(NULL));
	Swarm swarm;
	

	//check word for word, that youre doing what youre trying to do. for the love of god.
	while (true)
	{
		int elapsed = SDL_GetTicks();

		if (elapsed % 100 == 0)
		{
			screen.pause();
		}

		swarm.update(elapsed);

		

		unsigned char red = (1 + sin(elapsed * 0.001)) * 128;
		unsigned char green = (1 + sin(elapsed * 0.002)) * 128;
		unsigned char blue = (1 + sin(elapsed * 0.003)) * 128;

		const Particle * const pParticles = swarm.getParticles();
		for (int i = 0; i < Swarm::N_PARTICLES; i++)
		{
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;
			//SDL_Log("x: %i, y: %i", x, y);

			SDL_Event mouseEvent;
			while (SDL_PollEvent(&mouseEvent))
			{
				//particle.mouseEvent(mouseEvent.motion);
				screen.pause();
			}

			screen.setPixel(x, y, red, green, blue);
		}

		//screen.boxBlur();

		

		screen.update();

		if (screen.processEvents() == false)
		{
			break;
		}
	}


	screen.close();

	return 0;
}


