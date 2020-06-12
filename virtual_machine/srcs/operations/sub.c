/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sub.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 19:57:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/17 16:20:42 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** SUB_OP
** At first the value at cursor->operation.arg[x] will be the registry number.
** After we call get_registry_argument this
** 							value will be what is inside reg[registry_number].
** That's why we save the registry number of the 3rd argument.
** We need to know the actual registry
** to put the outcome of (argument1 - argument2) in.
*/

void			sub_op(t_cursor *cursor)
{
	int			registry;

	registry = THIRD_ARG - 1;
	get_registry_argument(cursor);
	cursor->reg[registry] = FIRST_ARG - SECOND_ARG;
	if (cursor->reg[registry] == 0)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	return ;
}
