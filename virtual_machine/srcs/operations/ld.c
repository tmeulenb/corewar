/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ld.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 19:44:14 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/17 16:18:47 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		ld_op(t_vm *vm, t_cursor *cursor)
{
	int			registry;

	registry = SECOND_ARG - 1;
	get_indirect_arg_idx_mod(vm, cursor);
	cursor->reg[registry] = FIRST_ARG;
	if (FIRST_ARG == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	return ;
}
