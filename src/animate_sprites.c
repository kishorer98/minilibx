/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 05:23:36 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/04 03:44:11 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_put_back_exit_on_map(t_env *env)
{
	char	**map;
	int		x;
	int		y;

	map = env->map;
	x = env->tex.exit_pipe.pos.x;
	y = env->tex.exit_pipe.pos.y;
	map[y][x] = MAP_EXIT;
}

int	sl_is_collectible(char elem_to_check)
{
	int	i;

	i = 0;
	while (MAP_COLLECTIBLES[i])
	{
		if (elem_to_check == MAP_COLLECTIBLES[i])
			return (i + 1);
		++i;
	}
	return (0);
}

bool	sl_check_if_bomb_is_there(t_env *env, t_items *bombs, int x, int y)
{
	t_coord	bomb_pos;
	int		i;	

	i = 0;
	while (i < env->tex.bomb.set_bombs_nbr)
	{
		bomb_pos = sl_assign_pos(bombs[i].pos.x, bombs[i].pos.y);
		if (bombs[i].draw == true && x == bomb_pos.x && y == bomb_pos.y)
			return (true);
		++i;
	}
	return (false);
}

bool	sl_found_obstacle(t_env *env, t_coord pos)
{
	char	**map;
	bool	found_wall;
	bool	found_bomb;

	map = env->map;
	if (map[pos.y][pos.x] == MAP_WALL)
		found_wall = true;
	else
		found_wall = false;
	if (sl_check_if_bomb_is_there(env, env->tex.bomb.set_bombs, pos.x, pos.y))
		found_bomb = true;
	else
		found_bomb = false;
	return (found_wall || found_bomb);
}

void	sl_animate_sprite(\
	t_env *env, t_sprite_info *info, t_states *img, t_coord coord)
{
	char	**map;
	t_coord	pos;

	map = env->map;
	pos = sl_assign_pos(\
		info->sprite->pos.x + coord.x, info->sprite->pos.y + coord.y);
	if (sl_found_obstacle(env, pos))
		coord = sl_assign_pos(0, 0);
	sl_handle_textures_while_moving(env, info->apply_to, coord);
	if (info->sprite->time <= info->sprite->speed)
		sl_update_sub_pos_state_0(info->sprite, img, coord);
	if (info->sprite->time > info->sprite->speed)
		sl_update_sub_pos_state_1(info->sprite, img, coord);
	if (info->sprite->time == info->sprite->speed * 2)
	{
		if (info->apply_to == PLAYER && (coord.x != 0 || coord.y != 0))
			++env->p1.steps;
		sl_update_sub_pos_state_2(env, info, img, coord);
		if (info->apply_to != ENNEMY)
			info->sprite->curr_dir = 0;
		info->sprite->time = 0;
	}
	else
		++info->sprite->time;
}
