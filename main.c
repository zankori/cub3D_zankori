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
        if (store < strlen(str))
            store = strlen(str);
        i++;
        free(str);
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

// void    get_posi_player(t_data *info)
// {

//     for (int y = 0; info->map[y]; y++)
//     {
//         for(int x = 0; info->map[y][x]; x++)
//         {
//             if (info->map[y][x] == 'N')
//             {
//                 info->position_player.x = x;
//                 info->position_player.y = y;
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
    while (x < SIZE + 1)
    {
        y = 0;
        while (y < SIZE + 1)
        {
            if ((x + info->place_x) % SIZE == 0 || (y + info->place_y) % SIZE == 0)
                mlx_pixel_put(info->mlx_cnx, info->mlx_win, x +info->place_x, y + info->place_y, 255);
            else
                mlx_pixel_put(info->mlx_cnx, info->mlx_win, x +info->place_x, y + info->place_y, 19321);
            y++;
        }
        x++;
    }

    
}


void    check_hit_wall(t_data *info, int *hit_wall, int all_x, int all_y)
{
            int i = 0;
            int j = 0;
            int place_x = 0;
            int place_y = 0;
            int x_te = 0;
            int y_te = 0;

            while (info->map[i])
            {
                j = 0;
                while (info->map[i][j])
                {
                    x_te = 0;
                    y_te = 0;

                    while (x_te < SIZE + 1)
                    {
                        y_te = 0;
                        while (y_te < SIZE + 1)
                        {
                            if (place_x + x_te == all_x && place_y + y_te == all_y)
                            {
                                if (info->map[i][j] == '1')
                                {
                                    *hit_wall = 1;
                                    return ;
                                }
                            }
                            y_te++;
                        }
                        x_te++;
                    }
                    j++;
                    place_x += SIZE;
                }
                i++;
                place_x = 0;
                place_y += SIZE;
            }

}

void    draw_direction(t_data *info)
{
    double  x;
    double  y;
    double  init_x;
    double  init_y;
    int     size;
    int     hit_wall;

    init_x = info->position_player.x + (player_size / 2);
    init_y = info->position_player.y + (player_size / 2);
    size = player_size / 2;

    hit_wall = 0;
    
    while (hit_wall == 0)
    {
        x =  cos(info->angle_player) * size;
        y = sin(info->angle_player) * size;
        mlx_pixel_put(info->mlx_cnx, info->mlx_win,  init_x  + x, init_y + y , 16711680);
        size++;


        // check wall 
        if ( (int)(x + init_x) % SIZE == 0 || (int)(y + init_y) % SIZE == 0)
            check_hit_wall(info, &hit_wall, (int)(init_x + x), (int)(init_y + y));

    }
}

void    redraw_player(t_data *info)
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
            mlx_pixel_put(info->mlx_cnx, info->mlx_win, x + info->position_player.x, y + info->position_player.y , 16776960);
            y++;
        }
        x++;
    }
}

void    init_angle_player(t_data *info, char Direction)
{
    if (Direction == 'N')
        info->angle_player = 90 * radian;
    else if (Direction == 'S')
        info->angle_player = 270 * radian;
    else if (Direction == 'E')
        info->angle_player = 0;
    else if (Direction == 'W')
        info->angle_player = 180 * radian;

}

void    draw_player(t_data *info, char Direction)
{
    int x;
    int y;

    x = 0;
    y = 0;

    // position of player . 
    info->position_player.x = info->place_x;
    info->position_player.y = info->place_y;
    // --- //

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
    init_angle_player(info, Direction);
    draw_direction(info);

}

void    draw_line_in_empty(t_data *info)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < SIZE + 1)
    {
        y = 0;
        while (y < SIZE + 1)
        {
            if ((x + info->place_x) % SIZE == 0 || (y + info->place_y) % SIZE == 0)
                mlx_pixel_put(info->mlx_cnx, info->mlx_win, x +info->place_x, y + info->place_y, 255);
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
            else if (info->map[i][j] == 'N' || info->map[i][j] == 'W' 
            || info->map[i][j] == 'E' || info->map[i][j] == 'S')
                draw_player(info, info->map[i][j]);
            else if (info->map[i][j] == '0')
                draw_line_in_empty(info);
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

void    calculte_new_position(t_data *info, char Direction)
{
    int x;
    int y;

    x = cos(info->angle_player) * speed_move;
    y = sin(info->angle_player) * speed_move;

    if (Direction == 'N')
    {
        info->position_player.x += x; 
        info->position_player.y += y; 
    }
    else if (Direction == 'S')
    {
        info->position_player.x -= x; 
        info->position_player.y -= y; 
    }
    else if (Direction == 'E')
    {
        x = cos(info->angle_player  + (PI / 2)) * speed_move;
        y = sin(info->angle_player  + (PI / 2)) * speed_move;
        info->position_player.x += x; 
        info->position_player.y += y; 
    }
    else if (Direction == 'W')
    {
        x = cos(info->angle_player  - (PI / 2)) * speed_move;
        y = sin(info->angle_player  - (PI / 2)) * speed_move;
        info->position_player.x += x; 
        info->position_player.y += y; 
    }
}

void    redraw_map(t_data *info, int flag_player_is_move)
{
    int     i;
    int     j;

    info->place_x = 0;
    info->place_y = 0;
    i = 0;
    j = 0;
    while (info->map[i])
    {
        j = 0;
        while (info->map[i][j])
        {
            if (flag_player_is_move == 1)
            {
                if (info->map[i][j] == '0')
                    draw_line_in_empty(info);
            }
            else
            {
                if (info->map[i][j] == '1')
                    draw_wall(info);
                else if (info->map[i][j] == '0')
                    draw_line_in_empty(info);
            }
            j++;
            info->place_x += SIZE;
        }
        i++;
        info->place_x = 0;
        info->place_y += SIZE;
    }

}

void    do_move(t_data *info, char Direction)
{
    int     x;
    int     y;

    x = 0;
    y = 0;

    // task 1 : replace player by a empty . 

    while (x < player_size)
    {
        y = 0;
        while (y < player_size)
        {
            mlx_pixel_put(info->mlx_cnx, info->mlx_win, x + info->position_player.x, y + info->position_player.y, 0);
            y++;
        }
        x++;
    }
    redraw_map(info, 1);
    // --//
    // task 2 : add speed movement of the player to his place .
    calculte_new_position(info, Direction);

    // -- //
    // task 3 : draw player in his new place .
    // --- //
    x = 0;
    y = 0;
    while (x < player_size)
    {
        y = 0;
        while (y < player_size)
        {
            mlx_pixel_put(info->mlx_cnx, info->mlx_win, x + info->position_player.x, y + info->position_player.y, 16776960);
            y++;
        }
        x++;
    }
    // --- //
}




void    delete_direction(t_data *info)
{
    double  x;
    double  y;
    double  init_x;
    double  init_y;
    int     size;
    int     hit_wall;

    init_x = info->position_player.x + (player_size / 2);
    init_y = info->position_player.y + (player_size / 2);
    size = player_size / 2;
    hit_wall = 0;
    while (hit_wall == 0)
    {
        x =  cos(info->angle_player) * size;
        y = sin(info->angle_player) * size;
        mlx_pixel_put(info->mlx_cnx, info->mlx_win,  init_x  + x, init_y + y , 0);
        size++;
        
         // check wall 
        if ( (int)(x + init_x) % SIZE == 0 || (int)(y + init_y) % SIZE == 0)
            check_hit_wall(info, &hit_wall, (int)(init_x + x), (int)(init_y + y));


    }
    redraw_player(info);


}

void    left_rotate(t_data *info)
{  

    double  x;
    double  y;
    double  init_x;
    double  init_y;
    int     size;
    int     hit_wall;

    delete_direction(info);
    redraw_map(info, 0);
                                                                                                                                                                                     
    info->angle_player -= speed_rotate;
    if (info->angle_player < 0)
        info->angle_player += 2 * PI;
    init_x = info->position_player.x + (player_size / 2);
    init_y = info->position_player.y + (player_size / 2);
    size = player_size / 2;

    hit_wall = 0;
    while (hit_wall == 0)
    {
        x =  cos(info->angle_player) * size;
        y = sin(info->angle_player) * size;
        mlx_pixel_put(info->mlx_cnx, info->mlx_win,  init_x  + x, init_y + y , 16711680);
        size++;
         // check wall 
        if ( (int)(x + init_x) % SIZE == 0 || (int)(y + init_y) % SIZE == 0)
            check_hit_wall(info, &hit_wall, (int)(init_x + x), (int)(init_y + y));

    }


}

void    right_rotate(t_data *info)
{  

    double  x;
    double  y;
    double  init_x;
    double  init_y;
    int     size;
    int     hit_wall;

    delete_direction(info);
    redraw_map(info, 0);

    info->angle_player += speed_rotate;
    if (info->angle_player > (2 * PI))
        info->angle_player -= 2 * PI;
    init_x = info->position_player.x + (player_size / 2);
    init_y = info->position_player.y + (player_size / 2);
    size = player_size / 2;

    hit_wall = 0;
    while (hit_wall == 0)
    {
        x =  cos(info->angle_player) * size;
        y = sin(info->angle_player) * size;
        mlx_pixel_put(info->mlx_cnx, info->mlx_win,  init_x  + x, init_y + y , 16711680);
        size++;
        // check wall 
        if ( (int)(x + init_x) % SIZE == 0 || (int)(y + init_y) % SIZE == 0)
            check_hit_wall(info, &hit_wall, (int)(init_x + x), (int)(init_y + y));

    }


}


int     move(int key_pressed, t_data *info)
{
    if (key_pressed == KEY_W)
    {
        delete_direction(info);
        redraw_map(info, 0);
        do_move(info, 'N');
        draw_direction(info);
    }
    else if (key_pressed == KEY_S)
    {
        delete_direction(info);
        redraw_map(info, 0);
        do_move(info, 'S');
        draw_direction(info);
    }
    else if (key_pressed == KEY_D)
    {
        delete_direction(info);
        redraw_map(info, 0);
        do_move(info, 'E');
        draw_direction(info);
    }
    else if (key_pressed == KEY_A)
    {
        delete_direction(info);
        redraw_map(info, 0);
        do_move(info, 'W');
        draw_direction(info);
    }
    else if (key_pressed == KEY_LEFT)
    {
        left_rotate(info);
    }
    else if (key_pressed == KEY_RIGHT)
    {
        right_rotate(info);
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

// 2 : ray-casting (rendering map 2D) .