/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_arguments.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmeulenb <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 12:25:51 by jheeresm      #+#    #+#                 */
/*   Updated: 2019/07/21 12:25:52 by jheeresm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** GET_VALUE_OF_ARG
** This function will read the bytes into a short or integer using
** the order of BIG-endian
** If read_size is 2 bytes, we will convert it into a short and return
** it typecasted as an int.
** Otherwise, we just return (int)value.
** The return of this function will be put in operation.arg[x].
** This int array is used as the arguments for operations later on.
*/

int			get_value_of_arg(t_vm *vm, int pos, int read_size)
{
	int				value;

	value = 0;
	if (read_size == 1)
		value = vm->memory[MOD(pos)];
	if (read_size == 2)
		value = (short)(vm->memory[MOD(pos)] << 8 | vm->memory[MOD(pos + 1)]);
	if (read_size == 4)
		value = vm->memory[MOD(pos)] << 24 | vm->memory[MOD(pos + 1)] << 16 |
				vm->memory[MOD(pos + 2)] << 8 | vm->memory[MOD(pos + 3)];
	return (value);
}

/*
** GET_READSIZE
** Find the proper readsize in the operation.check.
** Returns (1) for register, returns (size of t_dir) for direct,
** returns (2) for indirect.
*/

int			get_readsize(t_vm *vm, t_cursor *cursor, int n_arg)
{
	if (cursor->operation.check[n_arg] == 1)
		return (1);
	if (cursor->operation.check[n_arg] == 2)
		return (vm->t_dir[cursor->opcode - 1]);
	if (cursor->operation.check[n_arg] == 3)
		return (2);
	return (0);
}

/*
** GET_ARGUMENT
** First we get the readsize, so we know how many bytes to read from memory
** for this argument.
** Then we get the value for this argument with get_value_of_arg.
** If the argument is a register and the value is not valid (x < 1 || x > 16),
** we return (0).
** With the variables jump we keep track of which bytes are already read.
**
** For example: If we read a indirect argument, we read 2 bytes.
** After succesfully reading, we increase jump by 2.
** The next time we get to get_argument, it will start
** reading from the right position in memory.
*/

int			get_argument(t_vm *vm, t_cursor *cursor, int *jump, int n)
{
	int			read_size;
	int			pos;

	read_size = get_readsize(vm, cursor, n);
	pos = cursor->position;
	cursor->operation.arg[n] = get_value_of_arg(vm, pos + *jump, read_size);
	if (cursor->operation.check[n] == REG_CODE &&
										!VALID_REG(cursor->operation.arg[n]))
		return (0);
	*jump += read_size;
	return (1);
}

/*
** SAVE_SINGLE_ARGUMENT
** If the operation has only 1 argument, we save the correct code in check[0].
** This will register (1) for opcode 16 and the rest is direct (2).
*/

void		save_single_arg(t_cursor *cursor)
{
	if (cursor->opcode == live_code || cursor->opcode == zjmp_code ||
	cursor->opcode == fork_code || cursor->opcode == lfork_code)
		cursor->operation.check[0] = 2;
	else if (cursor->opcode == aff_code)
		cursor->operation.check[0] = 1;
	else
		ft_error("single arg check error");
	return ;
}

/*
** SAVE_ARGUMENTS
** Jump is the variables used to keep track of what position in memory we are
** reading from.
** More information on this in the comments of function: get_argument.
** Jump is initialize at 2 (opcode + encoding byte). If the argument has no
** encoding byte, jump will be 1 (just opcode).
**
** If the opcode is is_single_arg_op(cursor) (only one argument) we save it's
** argument code (1: reg, 2: dir, 3:ind) to check[0].
** This is needed for the get_argument function.
**
** If check[i] != 0,
** we check and save the value of the argument in get_argument.
** If get_argument returns (0) this means the argument type was register but
** the value was incorrect (not VALID_REG (1 - 16))
** This will stop the saving of arguments: return (0).
**
** The last if (is_single_arg_op(cursor)) just breaks the loop because we only
** have to get 1 argument.
**
** Return (1) means we succesfully got a argument.
*/

int			save_arguments(t_vm *vm, t_cursor *cursor)
{
	int			jump;
	int			i;

	jump = 2;
	if (is_single_arg_op(cursor))
	{
		save_single_arg(cursor);
		jump = 1;
	}
	i = 0;
	while (i < 3)
	{
		if (ARGUMENT_TYPE != 0)
		{
			if (!get_argument(vm, cursor, &jump, i))
				return (0);
		}
		if (is_single_arg_op(cursor))
			return (1);
		i++;
	}
	return (1);
}
