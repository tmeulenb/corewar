/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jheeresm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/24 13:05:13 by jheeresm       #+#    #+#                */
/*   Updated: 2019/11/07 18:49:38 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** DECREASE_CYCLES_TO_DIE
** If the amount of lives exected is >= 21. We decrease cycles to die by 50.
** Everytime the amount of lives is < 21, we increment check by 1.
** If check = 10, we decrease cycles to die by 50 and set check back to 0.
** If after decreasing cycles to die, it becomes less than 0, we set it to 1.
** This means there will be just 1 cycle before death.
*/

void		decrease_cycles_to_die(t_game *game, int *cycles)
{
	if (game->nbr_live >= NBR_LIVE)
		game->cycles_to_die -= CYCLE_DELTA;
	else
	{
		if (game->check == 10)
		{
			game->cycles_to_die -= CYCLE_DELTA;
			game->check = 0;
			return ;
		}
		game->check += 1;
	}
	if (game->cycles_to_die < 0)
		game->cycles_to_die = 1;
	*cycles = game->cycles_to_die;
	return ;
}

void		check_dead_cursor_or_players(t_vm *vm)
{
	t_cursor	*cursor;
	int			i;

	cursor = vm->cursors;
	i = 0;
	while (i < vm->champion_count)
	{
		vm->champions[i].amount_of_lives = 0;
		i++;
	}
	while (cursor)
	{
		if (cursor->last_live <= vm->game.cycles - vm->game.cycles_to_die &&
													cursor->last_live != -1)
		{
			if (vm->verbose)
				verbose_cursor_died(vm, cursor);
			cursor->last_live = -1;
			vm->game.total_cursors--;
		}
		cursor = cursor->next;
	}
	return ;
}

void		increase_cycles(int *cycles_to_die, t_vm *vm)
{
	*cycles_to_die -= 1;
	vm->game.cycles += 1;
	return ;
}

int			alive_champ_and_cursor(t_vm *vm)
{
	t_cursor	*cursor;

	cursor = vm->cursors;
	while (cursor)
	{
		if (cursor->last_live > (vm->game.cycles - vm->game.cycles_to_die))
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

void		game(t_vm *vm, t_game *game)
{
	int			cycles_to_die;

	cycles_to_die = game->cycles_to_die;
	if (dump_check(*vm))
		return ;
	while (cycles_to_die && alive_champ_and_cursor(vm))
	{
		exec_cursor_list(vm, vm->cursors);
		increase_cycles(&cycles_to_die, vm);
		if (cycles_to_die == 0)
		{
			check_dead_cursor_or_players(vm);
			decrease_cycles_to_die(game, &cycles_to_die);
		}
		if (vm->visualizer)
			update_game_variables(vm->v.game_variables, vm);
		if (dump_check(*vm))
			return ;
	}
	if (vm->visualizer)
		endwin();
	return ;
}
