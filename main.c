#include "header.h"


char    **store_map(char **argv, t_data *info)
{
    int i = 0;
    char *str;
    int store = 0;
    char **make_map;
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

    info->length = store;
    info->width = i;

    

    make_map = malloc(sizeof(char *) * (info->width + 1));
    i = 0;
    close(fd);
    fd = open(argv[1], O_RDWR, 0644);
    while (i < info->width)
    {
        make_map[i] = get_next_line(fd);
        i++;
    }
    make_map[i] = NULL;
    return (make_map);
}

// void    get_posi_player(Vector_2D *posi_player)
// {

//     for (int y = 0; map[y]; y++)
//     {
//         for(int x = 0; map[y][x]; x++)
//         {
//             if (map[y][x] == 'N')
//             {
//                 posi_player->x = x;
//                 posi_player->y = y;
//                 return ;
//             }
//         }
//     }
// }


void    draw_wall(t_data *info)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < SIZE)
    {
        y = 0;
        while (y < SIZE)
        {
            mlx_pixel_put(info->mlx_cnx, info->mlx_win, x +info->place_x, y + info->place_y, 16777215);
            y++;
        }
        x++;
    }
    
}

void    draw_player(t_data *info)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < player_size)
    {
        y = 0;
        while (y < player_size)
        {
            mlx_pixel_put(info->mlx_cnx, info->mlx_win, x +info->place_x, y + info->place_y, 16776960);
            y++;
        }
        x++;
    }

}

void    draw_map(t_data *info)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (info->map[i])
    {
        j = 0;
        while (info->map[i][j])
        {
            if (info->map[i][j] == '1')
                draw_wall(info);
            else if (info->map[i][j] == 'N')
                draw_player(info);
            j++;
            info->place_x += SIZE;
        }
        i++;
        info->place_x = 0;
        info->place_y += SIZE;
    }
}

void    inti(t_data *info)

{
    info->place_x = 0;
    info->place_y = 0;
}

int     move(int key_pressed, t_data *info)
{
    if (key_pressed == KEY_UP)
    {
        
    }
    else if (key_pressed == KEY_DOWN)
    {

    }
    return (0);
}


int main(int argc, char **argv)
{
    t_data info;


    info.map = store_map(argv, &info);
    inti(&info);
    info.mlx_cnx = mlx_init();
    info.mlx_win = mlx_new_window(info.mlx_cnx, WIDTH, LENGTH, "cub3d");


    draw_map(&info);
    mlx_hook(info.mlx_win, KeyPress, KeyPressMask, move, &info);

    mlx_loop(info.mlx_cnx);



}