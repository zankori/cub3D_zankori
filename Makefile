src = get_next_line/get_next_line.c main.c get_next_line/get_next_line_utils.c

all :
	cc $(src) -lmlx -lXext -lX11 -lm 