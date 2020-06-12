/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ldi.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 19:57:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/17 16:20:42 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		ldi_op(t_vm *vm, t_cursor *cursor)
{
	int			registry;
	int			position;

	registry = THIRD_ARG - 1;
	get_indirect_arg_idx_mod(vm, cursor);
	get_registry_argument(cursor);
	position = cursor->position + ((FIRST_ARG + SECOND_ARG) % IDX_MOD);
	position = ft_modulo(position, MEM_SIZE);
	cursor->reg[registry] = get_value_at_address(vm->memory, position);
	return ;
}
