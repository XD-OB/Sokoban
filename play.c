#include "sokoban.h"

void	play(SDL_Surface *screen)
{
	SDL_Surface	*mario[4];
	SDL_Surface	*mur;
	SDL_Surface	*caisse;
	SDL_Surface	*caisseOK;
	SDL_Surface	*marioActuel;
	SDL_Surface	*objectif;
	SDL_Rect	p;
	SDL_Rect	p_J;
	SDL_Event	event;
	int		pass;
	int		obj_rest;
	int		i;
	int		j;
	int		map[N_HEIGHT][N_WIDTH];

	pass = 1;
	obj_rest = 0;

	mur = IMG_Load("sprites/mur.jpg");
	caisse = IMG_Load("sprites/caisse.jpg");
	caisseOK = IMG_Load("sprites/caisse_ok.jpg");
	objectif = IMG_Load("sprites/objectif.png");
	mario[DOWN] = IMG_Load("sprites/mario_bas.gif");
	mario[LEFT] = IMG_Load("sprites/mario_gauche.gif");
	mario[UP] = IMG_Load("sprites/mario_haut.gif");
	mario[RIGHT] = IMG_Load("sprites/mario_droite.gif");

	marioActuel = mario[DOWN];

	if (!load_lvl(map))
		exit(EXIT_FAILURE);

	for (i=0; i<N_HEIGHT; i++)
	{
		for (j=0; j<N_WIDTH; j++)
		{
			if (map[i][j] == MARIO)
			{
				p_J.y = i;
				p_J.x = j;
				map[i][j] = NONE;
				break;
			}
		}
	}

	SDL_EnableKeyRepeat(50, 50);
	while (pass)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				pass = 0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						pass = 0;
						break;
					case SDLK_UP:
						marioActuel = mario[UP];
						move_player(map, &p_J, UP);
						break;
					case SDLK_DOWN:
						marioActuel = mario[DOWN];
						move_player(map, &p_J, DOWN);
						break;
					case SDLK_RIGHT:
						marioActuel = mario[RIGHT];
						move_player(map, &p_J, RIGHT);
						break;
					case SDLK_LEFT:
						marioActuel = mario[LEFT];
						move_player(map, &p_J, LEFT);
						break;
				}
				break;
		}
		
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
		obj_rest = 0;
		for (i=0; i<N_HEIGHT; i++)
		{
			for (j=0; j<N_WIDTH; j++)
			{
				p.y = i * BOX_SIZE;
				p.x = j * BOX_SIZE;
				switch (map[i][j])
				{
					case WALL:
						SDL_BlitSurface(mur, NULL, screen, &p);
						break;
					case BOX:
						SDL_BlitSurface(caisse, NULL, screen, &p);
						break;
					case BOX_OK:
						SDL_BlitSurface(caisseOK, NULL, screen, &p);
						break;
					case GOAL:
						SDL_BlitSurface(objectif, NULL, screen, &p);
						obj_rest = 1;
						break;
				}
			}
		}
		if (!obj_rest)
			pass = 0;
		p.x = p_J.x * BOX_SIZE;
		p.y = p_J.y * BOX_SIZE;
		SDL_BlitSurface(marioActuel, NULL, screen, &p);
		SDL_Flip(screen);
	}


	SDL_EnableKeyRepeat(0, 0);
	SDL_FreeSurface(mur);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(caisseOK);
	SDL_FreeSurface(objectif);
	i = -1;
	while (++i < 4)
		SDL_FreeSurface(mario[i]);
}

void	move_player(int map[][N_HEIGHT], SDL_Rect *p, int way)
{
	switch (way)
	{
		case UP:
			if (p->y < 1)
				break;
			if (map[p->y - 1][p->x] == WALL)
				break;
			if ((map[p->y-1][p->x] == BOX || map[p->y-1][p->x] == BOX_OK) && (p->y-2 < 0 || map[p->y-2][p->x] == WALL || map[p->y-2][p->x] == BOX || map[p->y-2][p->x] == BOX_OK))
				break;
			move_box(&map[p->y-1][p->x], &map[p->y-2][p->x]);
			p->y--;
			break;
		case DOWN:
			if (p->y > 10)
				break;
			if (map[p->y + 1][p->x] == WALL)
				break;
			if ((map[p->y+1][p->x] == BOX || map[p->y+1][p->x] == BOX_OK) && (p->y+2 < 0 || map[p->y+2][p->x] == WALL || map[p->y+2][p->x] == BOX || map[p->y+2][p->x] == BOX_OK))
				break;
			move_box(&map[p->y+1][p->x], &map[p->y+2][p->x]);
			p->y++;
			break;
		case LEFT:
			if (p->x < 1)
				break;
			if (map[p->y][p->x - 1] == WALL)
				break;
			if ((map[p->y][p->x-1] == BOX || map[p->y][p->x-1] == BOX_OK) && (p->x-2 < 0 || map[p->y][p->x-2] == WALL || map[p->y][p->x-2] == BOX || map[p->y][p->x-2] == BOX_OK))
				break;
			move_box(&map[p->y][p->x-1], &map[p->y][p->x-2]);
			p->x--;
			break;
		case RIGHT:
			if (p->x > 10)
				break;
			if (map[p->y][p->x + 1] == WALL)
				break;
			if ((map[p->y][p->x+1] == BOX || map[p->y][p->x+1] == BOX_OK) && (p->x+2 < 0 || map[p->y][p->x+2] == WALL || map[p->y][p->x+2] == BOX || map[p->y][p->x+2] == BOX_OK))
				break;
			move_box(&map[p->y][p->x+1], &map[p->y][p->x+2]);
			p->x++;
			break;
	}
}

void	move_box(int *first, int *second)
{
	if (*first == BOX || *first == BOX_OK)
	{
		if (*second == GOAL)
			*second = BOX_OK;
		else
			*second = BOX;
		if (*first == BOX_OK)
			*first = GOAL;
		else
			*first = NONE;
	}
}
