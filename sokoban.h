#ifndef SOKOBAN_H
#define	SOKOBAN_H

# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# define BOX_SIZE 34
# define N_WIDTH 12
# define N_HEIGHT 12
# define WIDTH	BOX_SIZE * N_WIDTH
# define HEIGHT	BOX_SIZE * N_HEIGHT

enum {UP, DOWN, LEFT, RIGHT};
enum {NONE, WALL, BOX, GOAL, MARIO, BOX_OK};
void	edit(SDL_Surface *screen);
void	play(SDL_Surface *screen);
void	move_player(int map[][N_HEIGHT], SDL_Rect *p, int way);
int	save_lvl(int lvl[][N_WIDTH]);
int	load_lvl(int lvl[][N_WIDTH]);
void	move_box(int *first, int *second);

#endif
