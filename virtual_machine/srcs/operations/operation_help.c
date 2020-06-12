/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operation_help.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmeulenb <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 12:25:51 by jheeresm       #+#    #+#                */
/*   Updated: 2019/10/24 21:38:27 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
** GET_VALUE_AT_ADDRESS
** Reads 4 bytes from a certain position in memory.
** Stores these 4 bytes into an integer.
** The bytes are read as big endian and stored in little endian.
*/

int				get_value_at_address(unsigned char *memory, int pos)
{
	int			value;

	value = (int)(memory[MOD(pos)] << 24 | memory[MOD(pos + 1)] << 16 |
				memory[MOD(pos + 2)] << 8 | memory[MOD(pos + 3)]);
	return (value);
}

/*
** WRITE_VALUE_IN_MEMORY
** Used in st and sti.
** Take value and writes it byte per byte (BIG endian) into memory.
** Starts at position (pos) and will write 4 bytes total.
*/

void			write_value_in_memory(t_vm *vm, int value, int pos,
														unsigned char color)
{
	int			i;

	i = 3;
	while (i >= 0)
	{
		vm->memory[MOD(pos + i)] = (char)value;
		vm->color_mask[MOD(pos + i)] = color;
		value = value >> 8;
		i--;
	}
	return ;
}

void			get_indirect_arg_idx_mod(t_vm *vm, t_cursor *cursor)
{
	int			i;
	int			position;

	i = 0;
	while (i < 3)
	{
		if (ARGUMENT_TYPE == IND_CODE)
		{
			position = cursor->position + (ARGUMENT % IDX_MOD);
			position = ft_modulo(position, MEM_SIZE);
			ARGUMENT = get_value_at_address(vm->memory, position);
		}
		i++;
	}
	return ;
}

void			get_indirect_arg_mem_size(t_vm *vm, t_cursor *cursor)
{
	int			i;
	int			position;

	i = 0;
	while (i < 3)
	{
		if (ARGUMENT_TYPE == IND_CODE)
		{
			position = cursor->position + ARGUMENT;
			position = ft_modulo(position, MEM_SIZE);
			ARGUMENT = get_value_at_address(vm->memory, position);
		}
		i++;
	}
	return ;
}

void			get_registry_argument(t_cursor *cursor)
{
	int			i;

	i = 0;
	while (i < 3)
	{
		if (ARGUMENT_TYPE == REG_CODE)
			ARGUMENT = cursor->reg[ARGUMENT - 1];
		i++;
	}
	return ;
}
