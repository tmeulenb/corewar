/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   disassemble_exec_code.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ayundina <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:25:06 by ayundina      #+#    #+#                 */
/*   Updated: 2019/10/29 12:25:12 by ayundina      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disassembler.h"

static void	get_operation(int fd, t_exec *exec, int *pos)
{
	const char *names[16];

	names[0] = "live";
	names[1] = "ld";
	names[2] = "st";
	names[3] = "add";
	names[4] = "sub";
	names[5] = "and";
	names[6] = "or";
	names[7] = "xor";
	names[8] = "zjmp";
	names[9] = "ldi";
	names[10] = "sti";
	names[11] = "fork";
	names[12] = "lld";
	names[13] = "lldi";
	names[14] = "lfork";
	names[15] = "aff";
	exec->op_code = exec->code[*pos];
	if (exec->op_code < 1 || exec->op_code > 16)
		error_messaging(5);
	ft_dprintf(fd, "%s", names[exec->op_code - 1]);
	(*pos)++;
	return ;
}

static void	set_octal_code_to_null(int *args)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		args[i] = 0;
		i++;
	}
	return ;
}

static void	get_octal_code(t_exec *exec, int *pos)
{
	int	args_code;

	if (exec->octet[exec->op_code - 1] == true)
	{
		args_code = exec->code[*pos];
		exec->arg[0] = args_code >> 6;
		exec->arg[1] = args_code >> 4;
		exec->arg[1] = exec->arg[1] ^ exec->arg[0] << 2;
		exec->arg[2] = args_code >> 2;
		exec->arg[2] = exec->arg[2] ^ exec->arg[1] << 2 ^ exec->arg[0] << 4;
		(*pos)++;
	}
	return ;
}

void		disassemble_exec_code(int fd, t_exec *exec)
{
	int	pos;

	pos = 0;
	ft_dprintf(fd, ".name\t\t\"%s\"\n.comment\t\"%s\"\n\n", \
				exec->header.prog_name, exec->header.comment);
	while ((unsigned)pos < exec->header.prog_size)
	{
		get_operation(fd, exec, &pos);
		set_octal_code_to_null(exec->arg);
		get_octal_code(exec, &pos);
		get_arguments(fd, exec, &pos);
	}
	return ;
}
