#include <stdio.h>
#include <mlx.h>
#include <sys/types.h>
#include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"
#include <math.h>
// -lmlx -lXext -lX11 

#define WIDTH 1280
#define LENGTH 720
#define SIZE    80
#define player_size (( 20 * SIZE) /100)
#define length_direction 50
#define speed_move  6
#define PI 3.14159265359
#define radian 0.0174532925
#define speed_rotate 0.05
#define ray_casting_angle 0.01


# define ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_S 115
# define KEY_D 100
# define KEY_A 97
# define KEY_Q 113

typedef struct vector{
    int     x;
    int     y;
}Vector_2D;

typedef struct our_data{
    char    **map;
    int     length;
    int     width;

    int     place_x;
    int     place_y;

    void    *mlx_cnx;
    void    *mlx_win;

    double     angle_player;

    int     distance;
    int     height_wall;

    Vector_2D position_wall;
    Vector_2D position_player;
}t_data;


void    delete_direction(t_data *info);
void    ray_casting(t_data *info);