/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   live.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 19:57:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/17 16:20:42 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** Operation was read from memory.
** Encoding bytes are stored in cursor->operation->check[0 to 2]
** Argument bytes are stored in cursor->operation->arg[0 to 2]
**
** 1. Updates when cursor last reported alive.
** 2. If cursor's r1 == Argument1, set player, cursor as last reported alive.
*/

/*
**	wasn't tested!
**
** vm->game.last_alive_champ = vm->champions[i].id;//champ_reported alive
**
**	//cursor reported alive in current cycle
**	cursor->last_live = vm->game.cycles;
**
**	//number of lives reported increased
**	vm->game.nbr_live++;
**	//at the end of each cycle nmbr_live will be reset to zero
*/

void	live_op(t_vm *vm, t_cursor *cursor)
{
	int i;

	i = 0;
	while (i < vm->champion_count)
	{
		if (FIRST_ARG == vm->champions[i].id)
		{
			vm->game.last_alive_champ = vm->champions[i].id;
			vm->champions[i].last_live = vm->game.cycles;
			vm->champions[i].amount_of_lives += 1;
		}
		i++;
	}
	cursor->last_live = vm->game.cycles;
	vm->game.nbr_live++;
}
