#include "sokoban.h"

void	edit(SDL_Surface *screen)
{
	SDL_Surface	*mur;
	SDL_Surface	*caisse;
	SDL_Surface	*objectif;
	SDL_Surface	*mario;
	SDL_Rect	p;
	SDL_Event	event;
	int		pass;
	int		is_click_left;
	int		is_click_right;
	int		obj_now;
	int		carte[N_HEIGHT][N_WIDTH] = {0};
	int		i;
	int		j;

	pass = 1;
	is_click_left = 0;
	is_click_right = 0;
	obj_now = WALL;
	i = 0;
	j = 0;
	mur = IMG_Load("sprites/mur.jpg");
	caisse = IMG_Load("sprites/caisse.jpg");
	objectif = IMG_Load("sprites/objectif.png");
	mario = IMG_Load("sprites/mario_bas.gif");

	if (!load_lvl(carte))
		exit(EXIT_FAILURE);

	while (pass)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				pass = 0;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					carte[event.button.y/BOX_SIZE][event.button.x/BOX_SIZE] = obj_now;
					is_click_left = 1;
				}
				else if (event.button.button == SDL_BUTTON_RIGHT)
				{
					carte[event.button.y/BOX_SIZE][event.button.x/BOX_SIZE] = NONE;
					is_click_right = 1;
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
					is_click_left = 0;
				else if (event.button.button == SDL_BUTTON_RIGHT)
					is_click_right = 0;
				break;
			case SDL_MOUSEMOTION:
				if (is_click_left)
					carte[event.motion.y/BOX_SIZE][event.motion.x/BOX_SIZE] = obj_now;
				else if (is_click_right)
					carte[event.motion.y/BOX_SIZE][event.motion.x/BOX_SIZE] = NONE;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						pass = 0;
						break;
					case SDLK_s:
						save_lvl(carte);
						break;
					case SDLK_c:
						load_lvl(carte);
						break;
					case SDLK_KP1:
						obj_now = WALL;
						break;
					case SDLK_KP2:
						obj_now = BOX;
						break;
					case SDLK_KP3:
						obj_now = GOAL;
						break;
					case SDLK_KP4:
						obj_now = MARIO;
						break;
				}
				break;
		}
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

		for (i = 0 ; i < N_HEIGHT ; i++)
		{
			for (j = 0 ; j < N_WIDTH ; j++)
			{
				p.y = i * BOX_SIZE;
				p.x = j * BOX_SIZE;

				switch(carte[i][j])
				{
					case WALL:
						SDL_BlitSurface(mur, NULL, screen, &p);
						break;
					case BOX:
						SDL_BlitSurface(caisse, NULL, screen, &p);
						break;
					case GOAL:
						SDL_BlitSurface(objectif, NULL, screen, &p);
						break;
					case MARIO:
						SDL_BlitSurface(mario, NULL, screen, &p);
						break;
				}
			}
		}
		SDL_Flip(screen);
	}
	SDL_FreeSurface(mur);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(objectif);
	SDL_FreeSurface(mario);
}

int	load_lvl(int lvl[][N_WIDTH])
{
	FILE	*file;
	char	inline_file[N_WIDTH * N_HEIGHT + 1];
	int	i;
	int	j;

	i = -1;
	file = NULL;
	file = fopen("level/level.lvl", "r");
	if (file == NULL)
		return 0;
	fgets(inline_file, N_WIDTH * N_HEIGHT + 1, file);
	while (++i < N_HEIGHT)
	{
		j = -1;
		while (++j < N_WIDTH)
		{
			switch (inline_file[i * N_WIDTH + j])
			{
				case '0':
					lvl[i][j] = 0;
					break;
				case '1':
					lvl[i][j] = 1;
					break;
				case '2':
					lvl[i][j] = 2;
					break;
				case '3':
					lvl[i][j] = 3;
					break;
				case '4':
					lvl[i][j] = 4;
					break;
			}
		}
	}
	fclose(file);
	return 1;
}

int	save_lvl(int lvl[][N_WIDTH])
{
	FILE	*file;
	int	i;
	int	j;

	file = fopen("level/level.lvl", "w+");
	if (file == NULL)
		return 0;
	i = -1;
	while (++i < N_HEIGHT)
	{
		j = -1;
		while (++j < N_WIDTH)
			fprintf(file, "%d", lvl[i][j]);
	}
	fclose(file);
	return 1;
}
