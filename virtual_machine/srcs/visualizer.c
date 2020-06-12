/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   visualizer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 20:11:11 by tide-jon       #+#    #+#                */
/*   Updated: 2019/11/13 17:17:35 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	end_of_game(t_vm *vm)
{
	int	key;

	while (1)
	{
		nodelay(vm->v.memory_display, 0);
		key = wgetch(vm->v.memory_display);
		if (key == 113)
		{
			endwin();
			return ;
		}
	}
}

void	pauze_visualizer(WINDOW *game_variables)
{
	mvwprintw(game_variables, 2, 17, "*** PAUSED *** ");
	wrefresh(game_variables);
	while (wgetch(game_variables) != 32)
		;
	mvwprintw(game_variables, 2, 17, "*** RUNNING ***");
}

void	update_game_variables(WINDOW *game_variables, t_vm *vm)
{
	int	i;

	iwait();
	nodelay(game_variables, 1);
	if (wgetch(game_variables) == 32)
		pauze_visualizer(game_variables);
	mvwprintw(game_variables, 5, 33, "%6s", ft_itoa(vm->game.cycles));
	mvwprintw(game_variables, 7, 33, "%6s", ft_itoa(vm->game.cycles_to_die));
	wprintw(game_variables, "    ");
	mvwprintw(game_variables, 9, 33, "%6s", ft_itoa(vm->game.total_cursors));
	wprintw(game_variables, "    ");
	i = 0;
	while (i < vm->champion_count)
	{
		mvwprintw(game_variables, 20 + i * 11, 30, "%6s",
					ft_itoa(vm->champions[i].last_live));
		wprintw(game_variables, "    ");
		mvwprintw(game_variables, 21 + i * 11, 30, "%6s",
					ft_itoa(vm->champions[i].amount_of_lives));
		wprintw(game_variables, "    ");
		i++;
	}
	wrefresh(game_variables);
}

void	update_cursor(t_vm *vm, t_cursor *cursor, int jump)
{
	int			x;
	int			y;
	int			color;

	if (!vm->visualizer)
		return ;
	color = vm->color_mask[cursor->position + 1];
	change_color(vm, color, cursor->position, 1);
	y = ((ft_modulo(cursor->position + jump, MEM_SIZE)) / 64) + 1;
	x = (((ft_modulo(cursor->position + jump, MEM_SIZE)) * 3) % 192) + 2;
	mvwchgat(vm->v.memory_display, y, x, 2, A_STANDOUT, color, NULL);
	return ;
}

void	init_visuals(t_vm *vm)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	start_color();
	use_default_colors();
	vm->v.memory_display = newwin(66, 195, 0, 0);
	vm->v.corewar_header = newwin(10, 50, 0, 196);
	vm->v.game_variables = newwin(56, 50, 10, 196);
	fill_corewar_header(vm->v.corewar_header);
	fill_game_variables(vm->v.game_variables, vm);
	update_memory(vm->v.memory_display, vm);
	init_memory_colors(vm);
	wrefresh(vm->v.memory_display);
	box(vm->v.memory_display, 0, 0);
	wrefresh(vm->v.corewar_header);
	box(vm->v.game_variables, 0, 0);
	wrefresh(vm->v.game_variables);
	return ;
}
