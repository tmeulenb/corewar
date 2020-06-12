/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_cursors.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmeulenb <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 12:25:51 by jheeresm       #+#    #+#                */
/*   Updated: 2019/11/07 18:18:28 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** INITIALIZE_REG_AND_OPERATION
** Register and operation (t_operation) have some int array that need to
** be initialized. reg[0] (actually r1) is initialized with player id.
*/

void		initialize_reg_and_operation(t_cursor *cursor)
{
	int			i;

	i = 1;
	reset_operation(cursor);
	cursor->reg[0] = (cursor->id * -1) - 1;
	while (i < REG_NUMBER)
	{
		cursor->reg[i] = 0;
		i++;
	}
	return ;
}

/*
** MALLOC_CURSOR
** Just a function that mallocs the cursor and sets all the variables.
*/

t_cursor	*malloc_cursor(void)
{
	t_cursor		*cursor;
	static int		id;

	cursor = malloc(sizeof(t_cursor));
	cursor->id = id;
	cursor->carry = 0;
	cursor->opcode = 0;
	cursor->last_live = 0;
	cursor->wait_cycles = 0;
	cursor->next = NULL;
	initialize_reg_and_operation(cursor);
	id += 1;
	return (cursor);
}

/*
** SET_STARTING_POSITION
** Starting position is calculated depending on the amount of champions.
** This functions calculates the starting position.
** The calculation is from the cookbook.
*/

int			calc_starting_position(t_vm *vm, int player_id)
{
	int			divided_memory;

	divided_memory = MEM_SIZE / vm->champion_count;
	return (divided_memory * (abs(player_id) - 1));
}

/*
** ADD_TO_CURSOR_LIST
** Simple function to add the cursor to the beginning of the list.
*/

void		add_to_cursor_list(t_vm *vm, t_cursor *new)
{
	t_cursor		*temp;

	temp = vm->cursors;
	if (!temp)
		vm->cursors = new;
	else
	{
		new->next = temp;
		vm->cursors = new;
	}
	vm->game.total_cursors++;
	return ;
}

/*
** INIT_CURSORS
** We initialize 1 cursor per champion.
** We malloc cursor, set all the variables and set the starting position.
** We add the cursor the the beginning of the list.
*/

void		init_cursors(t_vm *vm)
{
	int			i;
	t_cursor	*new_cursor;

	i = 0;
	while (i < vm->champion_count)
	{
		new_cursor = malloc_cursor();
		new_cursor->position = calc_starting_position(vm, vm->champions[i].id);
		add_to_cursor_list(vm, new_cursor);
		i++;
	}
	return ;
}
