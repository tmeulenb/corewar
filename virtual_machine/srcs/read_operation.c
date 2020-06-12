/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_operation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmeulenb <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 12:25:51 by jheeresm      #+#    #+#                 */
/*   Updated: 2019/07/21 12:25:52 by jheeresm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** IS_SINGLE_ARG_OP
** determines if the operation has a single argument or not.
** Unfortuntly this did not fit in a #define.
*/

int			is_single_arg_op(t_cursor *cursor)
{
	if (cursor->opcode == live_code || cursor->opcode == zjmp_code ||
		cursor->opcode == fork_code || cursor->opcode == lfork_code)
		return (1);
	return (0);
}

/*
** READ_ENCODINGBYTE
** The byte has 8 bits, we read per 2 bits.
** 01 = register, 10 is direct, 11 is indirect.
** We check which on of the above it is and put it in check[x].
** Later on check will be used for:
** - Checking if the argument types are correct for an opcode.
** - Check how much bytes to read for the arguments.
*/

void		read_encodingbyte(t_cursor *cursor, unsigned char byte)
{
	int				i;
	int				x;

	i = 1;
	x = 0;
	while (i < 8 && x < cursor->operation.n_args)
	{
		if (BYTE(byte, (i - 1)) == 0 && BYTE(byte, i) == 0)
			cursor->operation.check[x] = 0;
		else if (BYTE(byte, (i - 1)) == 0 && BYTE(byte, i) == 1)
			cursor->operation.check[x] = 1;
		else if (BYTE(byte, (i - 1)) == 1 && BYTE(byte, i) == 0)
			cursor->operation.check[x] = 2;
		else if (BYTE(byte, (i - 1)) == 1 && BYTE(byte, i) == 1)
			cursor->operation.check[x] = 3;
		x++;
		i += 2;
	}
	return ;
}

/*
** RIGHT_ENCODING_FOR_OP
** This function will compare the arguments we got in read_encodingbyte
** with the actual possible arguments for every opcode defined in the header.
** Return (1) means it is correct. Return (0) means incorrect,
*/

int			right_encoding_for_op(t_opcode op_code, int *check)
{
	if ((op_code == live_code && CHECK_LIVE(check)) ||
	(op_code == ld_code && CHECK_LD(check)) ||
	(op_code == st_code && CHECK_ST(check)) ||
	(op_code == add_code && CHECK_ADD(check)) ||
	(op_code == sub_code && CHECK_SUB(check)) ||
	(op_code == and_code && CHECK_AND(check)) ||
	(op_code == or_code && CHECK_OR(check)) ||
	(op_code == xor_code && CHECK_XOR(check)) ||
	(op_code == zjmp_code && CHECK_ZJMP(check)) ||
	(op_code == ldi_code && CHECK_LDI(check)) ||
	(op_code == sti_code && CHECK_STI(check)) ||
	(op_code == fork_code && CHECK_FORK(check)) ||
	(op_code == lld_code && CHECK_LLD(check)) ||
	(op_code == lldi_code && CHECK_LLDI(check)) ||
	(op_code == lfork_code && CHECK_LFORK(check)) ||
	(op_code == aff_code && CHECK_AFF(check)))
		return (1);
	return (0);
}

/*
** READ_AND_CHECK_ENCODINGBYTE
** If the operation has a single argument, we return (1).
** This means the read was 'succesfull'.
** We read the encoding byte and put the type of arguments in a int[4].
** int[i] == 1 > register, int[i] == 2 > direct, int[i] == 3 > indirect.
** We match the type of arguments against the
** possible arguments types for the opcode.
** These argument types are defined in the header for all 16 operations.
** If the arguments are not correct, we return (0).
*/

int			read_and_check_encoding(t_cursor *cursor, unsigned char byte)
{
	if (is_single_arg_op(cursor))
		return (1);
	read_encodingbyte(cursor, byte);
	if (cursor->operation.check[3] != 0)
		return (0);
	if (!right_encoding_for_op(cursor->opcode, cursor->operation.check))
		return (0);
	return (1);
}

/*
** READ_OPERATION
** Read_and_check_encoding will check if encodingbyte matches opcode.
** If it is not, the return is (0) and
** the operation is not going to be executed and we skip to next operations.
**
** Check_and_save_arguments will read the arguments from memory and
** store them in struct operation.
** If an argument is incorrect,
** the return is (0) and the operation will also not be executed.
** If the arguments are CORRECT,
** it will return (1) with the proper arguments set into struct operation.
*/

int			read_operation(t_vm *vm, t_cursor *cursor)
{
	unsigned char	encoding;

	encoding = vm->memory[ft_modulo(cursor->position + 1, MEM_SIZE)];
	cursor->operation.n_args = vm->n_arg[cursor->opcode - 1];
	if (!read_and_check_encoding(cursor, encoding))
		return (0);
	if (!save_arguments(vm, cursor))
		return (0);
	return (1);
}
