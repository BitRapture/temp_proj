#include "util.h"

#include <SDL2/SDL.h>

#include <iostream>

SDL_Surface* image, *brick;
SDL_Surface* icon;
util::Spritesheet* player;

int pX = 200, pY = 200,
	cX = 0;
	
bool dir = true,
	running = false;
int runningSpr = 0;

void on_load()
{
	image = util::load_image("resources/player.png");
	player = util::SpritesheetLoad("resources/player_ss.png", 4, 4);
	brick = util::load_image("resources/brick.png");
	icon = util::load_image("resources/icon.png");
}

void on_update()
{
	running = false;
	if (util::sdl_keydown(SDL_SCANCODE_RIGHT))
	{
		if (pX > 600)
			cX--;
		else
			pX++;
		dir = false;
		running = true;
	}
	if (util::sdl_keydown(SDL_SCANCODE_LEFT))
	{
		if (pX < 100)
			cX++;
		else
			pX--;
		dir = true;
		running = true;
	}
	
	if (running)
	{
		runningSpr++;
		if (runningSpr > 3)
			runningSpr = 0;
	}
	else
	{
		runningSpr = 0;
	}
}

void on_draw()
{
	util::sdl_clearscreen(254, 222, 0);

	//util::sdl_blit(image, util::sdl_screen, 200, 200);
	
	util::SpritesheetBlit(player, runningSpr, dir + (running * 2), util::sdl_screen, pX, pY);
	
	for (int i = 0; i < 10; ++i)
		util::sdl_blit(brick, util::sdl_screen, (155 * i) + cX, 448);

	SDL_UpdateWindowSurface(util::sdl_window);
}

void on_cleanup()
{
	SDL_FreeSurface(image);
	SDL_FreeSurface(brick);
	SDL_FreeSurface(icon);
	util::SpritesheetFree(player);
}

int main(int argc, char* args[])
{
	util::sdl_initialize("Crusty Mario Knock-off bruh", 800, 600);

	on_load();
	SDL_SetWindowIcon(util::sdl_window, icon);

	while (!util::window_closed)
	{
		util::sdl_poll();
		on_update();
		on_draw();
		SDL_Delay(5);
	}

	on_cleanup();

	return 0;
}
