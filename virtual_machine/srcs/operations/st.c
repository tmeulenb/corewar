/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   st.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/23 19:31:43 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/24 22:23:37 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void		st_op(t_vm *vm, t_cursor *cursor)
{
	int			position;

	if (cursor->operation.check[1] == REG_CODE)
		cursor->reg[SECOND_ARG - 1] = cursor->reg[FIRST_ARG - 1];
	else if (cursor->operation.check[1] == IND_CODE)
	{
		get_registry_argument(cursor);
		position = cursor->position + (SECOND_ARG % IDX_MOD);
		position = ft_modulo(position, MEM_SIZE);
		write_value_in_memory(vm, FIRST_ARG, position, CURRENT_COLOR);
		if (vm->visualizer)
			change_color(vm, CURRENT_COLOR, position, 4);
	}
	return ;
}
