/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sti.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 19:57:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/17 16:20:42 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		sti_op(t_vm *vm, t_cursor *cursor)
{
	int			position;

	get_registry_argument(cursor);
	get_indirect_arg_idx_mod(vm, cursor);
	position = cursor->position + ((SECOND_ARG + THIRD_ARG) % IDX_MOD);
	position = ft_modulo(position, MEM_SIZE);
	write_value_in_memory(vm, FIRST_ARG, position, CURRENT_COLOR);
	if (vm->visualizer)
		change_color(vm, CURRENT_COLOR, position, 4);
	return ;
}
