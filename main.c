#include "sokoban.h"

int	main(int ac, char **av)
{
	SDL_Surface	*screen;
	SDL_Surface	*menu;
	SDL_Event	event;
	SDL_Rect	p_menu;
	int		pass;

	pass = 1;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetIcon(IMG_Load("sprites/caisse.jpg"), NULL);
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Mario Sokoban", NULL);
	menu = IMG_Load("sprites/menu.jpg");
	p_menu.x = 0;
	p_menu.y = 0;

	while (pass)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				pass = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						pass = 0;
						break;
					case SDLK_KP1:
						play(screen);
						break;
					case SDLK_KP2:
						edit(screen);
						break;
				}
				break;
		}
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(menu, NULL, screen, &p_menu);
		SDL_Flip(screen);
	}

	SDL_FreeSurface(menu);
	SDL_Quit();

	return EXIT_SUCCESS;
}
