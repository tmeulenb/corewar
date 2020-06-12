/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   change_colors.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 20:11:11 by tide-jon       #+#    #+#                */
/*   Updated: 2019/11/08 22:22:38 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		calculate_position(int *x, int *y, int pos, int i)
{
	*y = ((ft_modulo(pos + i, MEM_SIZE)) / 64) + 1;
	*x = (((ft_modulo(pos + i, MEM_SIZE)) * 3) % 192) + 2;
	return ;
}

void		write_in_color(WINDOW *window, t_color var, unsigned char *memory)
{
	int			i;
	int			x;
	int			y;

	i = 0;
	init_pair(var.color, var.color, -1);
	wattron(window, COLOR_PAIR(var.color));
	while (i < var.size)
	{
		calculate_position(&x, &y, var.pos, i);
		mvwprintw(window, y, x, "%02x ",
									memory[ft_modulo(var.pos + i, MEM_SIZE)]);
		i++;
	}
	wattroff(window, COLOR_PAIR(var.color));
	wrefresh(window);
	return ;
}

void		change_color(t_vm *vm, int color, int position, int size)
{
	t_color	var;
	WINDOW	*window;

	var.pos = position;
	var.size = size;
	var.color = color;
	window = vm->v.memory_display;
	write_in_color(window, var, vm->memory);
	return ;
}

void		init_memory_colors(t_vm *vm)
{
	int	i;
	int	start_pos;
	int	len;
	int	color;

	i = 0;
	while (i < vm->champion_count)
	{
		start_pos = calc_starting_position(vm, vm->champions[i].id);
		len = vm->champions[i].size;
		color = vm->color_mask[start_pos];
		change_color(vm, color, start_pos, len);
		i++;
	}
	return ;
}
