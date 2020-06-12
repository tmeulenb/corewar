/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_visualizer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 20:11:11 by tide-jon       #+#    #+#                */
/*   Updated: 2019/11/08 22:22:38 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	fill_corewar_header(WINDOW *corewar_header)
{
	mvwprintw(corewar_header, 1, 5,
	"   ___                                  ");
	mvwprintw(corewar_header, 2, 5,
	"  / __\\___  _ __ _____      ____ _ _ __ ");
	mvwprintw(corewar_header, 3, 5,
	" / /  / _ \\| '__/ _ \\ \\ /\\ / / _` | '__|");
	mvwprintw(corewar_header, 4, 5,
	"/ /__| (_) | | |  __/\\ V  V / (_| | |   ");
	mvwprintw(corewar_header, 5, 5,
	"\\____/\\___/|_|  \\___| \\_/\\_/ \\__,_|_|   ");
	mvwprintw(corewar_header, 7, 0,
	"\tAnna Yundina\tJim heeresma\n\tTim de Jong\tThijs Meulenbelt");
	wrefresh(corewar_header);
	return ;
}

void	fill_game_variables_help(WINDOW *game_variables)
{
	mvwprintw(game_variables, 2, 17, "*** PLAYING ***");
	mvwchgat(game_variables, 3, 12, 25, A_UNDERLINE, 0, NULL);
	mvwprintw(game_variables, 5, 10, "total cycles:");
	mvwprintw(game_variables, 7, 10, "cycles to die:");
	mvwprintw(game_variables, 9, 10, "number of cursors:");
	mvwchgat(game_variables, 10, 12, 25, A_UNDERLINE, 0, NULL);
	return ;
}

void	fill_game_variables(WINDOW *game_variables, t_vm *vm)
{
	int	i;

	i = 0;
	fill_game_variables_help(game_variables);
	while (i < vm->champion_count)
	{
		init_pair(i + 1, i + 1, -1);
		wattron(game_variables, COLOR_PAIR(i + 1));
		mvwprintw(game_variables, 12 + i * 11, 4, "PLAYER");
		mvwprintw(game_variables, 12 + i * 11, 11,
												ft_itoa(vm->champions[i].id));
		mvwprintw(game_variables, 12 + i * 11, 17, "%.82s",
														vm->champions[i].name);
		wattroff(game_variables, COLOR_PAIR(i + 1));
		wattron(game_variables, A_DIM);
		mvwprintw(game_variables, 14 + i * 11, 4, "\"");
		wprintw(game_variables, "%.293s", vm->champions[i].comment);
		wprintw(game_variables, "\"");
		wattroff(game_variables, A_DIM);
		mvwprintw(game_variables, 20 + i * 11, 4, "last live:");
		mvwprintw(game_variables, 21 + i * 11, 4, "lives in current period:");
		mvwprintw(game_variables, 22 + i * 11, 4,
							"-------------------------------------------");
		i++;
	}
}

void	update_memory(WINDOW *memory_display, t_vm *vm)
{
	int			i;
	int			y;
	int			x;

	i = 0;
	y = 1;
	while (y < 65)
	{
		x = 2;
		while (x < 194)
		{
			mvwprintw(memory_display, y, x, "%.2x ", vm->memory[i]);
			x += 3;
			i++;
		}
		y++;
	}
	wrefresh(memory_display);
}
