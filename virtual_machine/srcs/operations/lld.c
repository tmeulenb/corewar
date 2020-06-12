/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lld.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 19:50:59 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/17 16:19:55 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		lld_op(t_vm *vm, t_cursor *cursor)
{
	int			registry;

	registry = SECOND_ARG - 1;
	cursor->reg[registry] = 6;
	get_indirect_arg_mem_size(vm, cursor);
	cursor->reg[registry] = FIRST_ARG;
	if (FIRST_ARG == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	return ;
}
