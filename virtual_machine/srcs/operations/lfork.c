/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lfork.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 19:57:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/17 16:20:42 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		lfork_op(t_vm *vm, t_cursor *cursor)
{
	t_cursor		*fork;
	int				position;

	position = FIRST_ARG + cursor->position;
	position = ft_modulo(position, MEM_SIZE);
	fork = duplicate_cursor(vm, cursor, position);
	add_to_cursor_list(vm, fork);
	if (vm->verbose)
		verbose_new_cursor(fork);
	return ;
}
