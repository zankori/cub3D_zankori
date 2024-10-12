/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alassiqu <alassiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:34:39 by alassiqu          #+#    #+#             */
/*   Updated: 2024/10/08 15:39:17 by alassiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	is_it_player(char c)
{
	return (c == 'W' || c == 'N' || c == 'S' || c == 'E');
}

void	alloc_and_set(t_cub3d *cub)
{
	cub->player = calloc(1, sizeof(t_player));
	if (cub->player == NULL)
		ft_error(cub, "Error: allocation failed.");
	cub->player->fov = DEG_TO_RAD(60);
	cub->player->movespeed = 0.2;
	cub->player->rotationspeed = 3 * (PI / 180);
}

int	get_angle(char c)
{
	if (c == 'E')
		return (DEG_TO_RAD(0));
	if (c == 'N')
		return (DEG_TO_RAD(90));
	if (c == 'S')
		return (DEG_TO_RAD(180));
	if (c == 'W')
		return (DEG_TO_RAD(270));
	return (-1); 
}

void	get_player(t_cub3d *cub)
{
	char	**map;
	int		i;
	int		j;

	alloc_and_set(cub);
	map = cub->map->map;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_it_player(map[i][j]))
			{
				cub->player->angle = get_angle(map[i][j]);
				cub->player->x = j;
				cub->player->y = i;
				cub->player->count++;
			}
		}
	}
	if (cub->player->count != 1)
		ft_error(cub, "Error: expecting 1 player.");
}
