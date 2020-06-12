/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   verbose.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jheeresm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 13:38:26 by jheeresm      #+#    #+#                 */
/*   Updated: 2019/10/28 13:38:27 by jheeresm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int		calc_read_size(t_vm *vm, t_cursor *cursor)
{
	int			read_size;
	int			i;

	i = 0;
	read_size = 2;
	while (i < 3)
	{
		if (cursor->operation.check[i] == REG_CODE)
			read_size += 1;
		if (cursor->operation.check[i] == DIR_CODE)
			read_size += vm->t_dir[cursor->opcode - 1];
		if (cursor->operation.check[i] == IND_CODE)
			read_size += 2;
		i++;
	}
	if (is_single_arg_op(cursor))
		read_size -= 1;
	return (read_size);
}

void			verbose_operation(t_vm *vm, t_cursor *cursor)
{
	int			read_size;
	int			i;
	int			pos;

	if (cursor->opcode == zjmp_code && cursor->carry == 0)
	{
		ft_printf("Cursor[%d] couldn't execute zjmp\n", cursor->id);
		return ;
	}
	ft_printf("Cursor[%d] is executing.\n", cursor->id);
	ft_printf("   Opcode: %d\n", cursor->opcode);
	ft_printf("   Memory: [");
	read_size = calc_read_size(vm, cursor);
	i = 0;
	while (i < read_size)
	{
		pos = ft_modulo((cursor->position + i), MEM_SIZE);
		ft_printf("%x ", vm->memory[pos]);
		i++;
	}
	ft_printf("]\n");
	ft_printf("   Carry: %d\n", cursor->carry);
	return ;
}

void			verbose_new_cursor(t_cursor *cursor)
{
	ft_printf("NEW CURSOR ------> ");
	ft_printf("Cursor[%d] at position %d\n", cursor->id, cursor->position);
	return ;
}

void			verbose_cursor_died(t_vm *vm, t_cursor *cursor)
{
	int			last_alive;

	last_alive = vm->game.cycles - cursor->last_live;
	ft_printf("DEAD CURSOR ------> ");
	ft_printf("Cursor[%d] died! ", cursor->id);
	ft_printf("[Last_alive: %d cycles ago. ", last_alive);
	ft_printf("Cycles to die: %d]\n", vm->game.cycles_to_die);
	return ;
}
