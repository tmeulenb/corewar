/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_arguments.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ayundina <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:25:06 by ayundina      #+#    #+#                 */
/*   Updated: 2019/10/29 12:25:12 by ayundina      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disassembler.h"

static void	get_registry_number(int fd, t_exec *exec, int i, int *pos)
{
	if (exec->arg[i] == REG_CODE && exec->octet[exec->op_code - 1] == true)
	{
		if (i > 0)
			ft_dprintf(fd, ",");
		ft_dprintf(fd, " r%d", exec->code[*pos]);
		(*pos)++;
	}
	return ;
}

static int	read_bytes(int size, unsigned char *code, int *pos)
{
	int value;

	if (size == 1)
		value = code[*pos];
	if (size == 2)
	{
		value = (short)(code[*pos] << 8 | code[*pos + 1]);
		*pos += 2;
	}
	if (size == 4)
	{
		value = code[*pos] << 24 | code[*pos + 1] << 16 | code[*pos + 2] << 8
		| code[*pos + 3];
		*pos += 4;
	}
	return (value);
}

static void	get_direct_argument(int fd, t_exec *exec, int i, int *pos)
{
	int	value;

	if ((exec->arg[i] == 0 && exec->octet[exec->op_code - 1] == false) \
	|| (exec->arg[i] == DIR_CODE && exec->octet[exec->op_code - 1] == true))
	{
		value = read_bytes(exec->t_dir[exec->op_code - 1], exec->code, pos);
		if (i > 0)
			ft_dprintf(fd, ",");
		ft_dprintf(fd, " %%%d", value);
	}
	return ;
}

static void	get_indirect_argument(int fd, t_exec *exec, int i, int *pos)
{
	int	value;

	if (exec->arg[i] == IND_CODE && exec->octet[exec->op_code - 1] == true)
	{
		value = read_bytes(IND_SIZE, exec->code, pos);
		if (i > 0)
			ft_dprintf(fd, ",");
		ft_dprintf(fd, " %d", value);
	}
	return ;
}

void		get_arguments(int fd, t_exec *exec, int *pos)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		get_registry_number(fd, exec, i, pos);
		get_direct_argument(fd, exec, i, pos);
		get_indirect_argument(fd, exec, i, pos);
		i++;
		if (i == 3 || (i < 3 && exec->arg[i] == 0))
		{
			ft_dprintf(fd, "\n");
			return ;
		}
	}
}
