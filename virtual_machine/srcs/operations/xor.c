/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   xor.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 19:57:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/17 16:20:42 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** XOR_OP
** The value at operation.arg[2] will be the registry we save the value in
** after the and, or or xor operation.
** We save this variables in the variable [registry].
** We do this because if we call get_registry_argument,
** all the arguments that are of type
** registry will be initialized with the actual value in the registry.
** This would mean we lose the registry number we have to save the output in.
** We call get_indirect_arg_idx_mod which will check if
** the arguments are of type indirect.
** If so, it will % IDX_MOD and read 4 bytes from the address.
** The value read will be stored in the operation.arg[x].
** The previous value at operation.arg[x] was the amount of bytes
** we need to look back or forward.
*/

void			xor_op(t_vm *vm, t_cursor *cursor)
{
	int			registry;

	registry = THIRD_ARG - 1;
	get_registry_argument(cursor);
	get_indirect_arg_idx_mod(vm, cursor);
	cursor->reg[registry] = FIRST_ARG ^ SECOND_ARG;
	if (cursor->reg[registry] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	return ;
}
