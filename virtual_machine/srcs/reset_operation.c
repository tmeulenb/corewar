/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reset_operation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jheeresm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/24 14:00:35 by jheeresm      #+#    #+#                 */
/*   Updated: 2019/10/24 14:00:35 by jheeresm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		reset_operation(t_cursor *cursor)
{
	FIRST_ARG = 0;
	SECOND_ARG = 0;
	THIRD_ARG = 0;
	cursor->operation.check[0] = 0;
	cursor->operation.check[1] = 0;
	cursor->operation.check[2] = 0;
	cursor->operation.check[3] = 0;
	cursor->operation.n_args = 0;
	cursor->opcode = 0;
	return ;
}
