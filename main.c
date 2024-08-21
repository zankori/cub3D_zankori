#include "header.h"

char    **map;
int     length;
int     width;

typedef struct Vector_2
{
    int x;
    int y;
}Vector_2D;


char    **store_map(char **argv)
{
    int i = 0;
    char *str;
    int store = 0;

    int fd = open(argv[1], O_RDWR, 0644);
    str = get_next_line(fd);
    while (str)
    {
        free(str);
        if (store < strlen(str))
            store = strlen(str);
        i++;
        str = get_next_line(fd); 
    }

    length = store;
    width = i;

    char **make_map;

    make_map = malloc(sizeof(char *) * (width + 1));
    i = 0;
    close(fd);
    fd = open(argv[1], O_RDWR, 0644);
    while (i < width)
    {
        make_map[i] = get_next_line(fd);
        i++;
    }
    make_map[i] = NULL;
    return (make_map);
}

void    get_posi_player(Vector_2D *posi_player)
{

    for (int y = 0; map[y]; y++)
    {
        for(int x = 0; map[y][x]; x++)
        {
            if (map[y][x] == 'N')
            {
                posi_player->x = x;
                posi_player->y = y;
                return ;
            }
        }
    }
}

void    equal_vector(Vector_2D *will_change, Vector_2D *by)
{
    will_change->x = by->x;
    will_change->y = by->y;
}

void    go_ray_straight(Vector_2D *ray_straight)
{
    while (map[ray_straight->y][ray_straight->x] != '1')
        ray_straight->y--;
}

int get_distance_two_vector(Vector_2D *vector_1, Vector_2D *vector_2)
{
    return (sqrt(pow(vector_1->x - vector_2->x, 2)
     + pow(vector_1->y - vector_2->y, 2)));
}

void    go_ray_right(Vector_2D *ray_right)
{
    while (map[ray_right->y][ray_right->x] != '1')
    {
        ray_right->y--;
        ray_right->x++;
    }
}

void    go_ray_left(Vector_2D *ray_left)
{
    while (map[ray_left->y][ray_left->x] != '1')
    {
        ray_left->y--;
        ray_left->x--;
    }
}



int main(int argc, char **argv)
{



    map = store_map(argv);


    Vector_2D posi_player;
    get_posi_player(&posi_player);

    Vector_2D ray_straight;
    equal_vector(&ray_straight, &posi_player);
    go_ray_straight(&ray_straight);
    int distance_straight = get_distance_two_vector(&posi_player, &ray_straight);

    Vector_2D ray_right;
    equal_vector(&ray_right, &posi_player);
    go_ray_right(&ray_right);
    int distance_right = get_distance_two_vector(&posi_player, &ray_right);


    Vector_2D ray_left;
    equal_vector(&ray_left, &posi_player);
    go_ray_left(&ray_left);
    int distance_left = get_distance_two_vector(&posi_player, &ray_left);


    printf("distance bettwen player and straight wall : %d\n", distance_straight);
    printf("distance bettwen player and right wall : %d\n", distance_right);
    printf("distance bettwen player and left wall : %d\n", distance_left);


    void    *mlx_cnx = mlx_init();
    void    *mlx_win = mlx_new_window(mlx_cnx, 1280 , 720 , "test");

    void    *our_img = mlx_new_image(mlx_cnx, 400, 400);
    

    mlx_put_image_to_window(mlx_cnx, mlx_win, our_img, 0 , 10);
    mlx_loop(mlx_cnx);
}