EXE = Sokoban.exe

SRCS = play.c file_loader.c main.c

HEAD = sokoban.h

OUTO = *.o

all: $(EXE)

$(EXE): $(HEAD)
	@gcc $(SRCS) -lSDL -lSDL_image -o $(EXE)

clean:
	@/bin/rm -f $(OUTO)

fclean: clean
	@/bin/rm -f $(EXE)

re: fclean all
