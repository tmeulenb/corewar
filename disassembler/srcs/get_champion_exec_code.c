/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_champion_exec_code.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ayundina <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:26:07 by ayundina      #+#    #+#                 */
/*   Updated: 2019/10/29 12:26:10 by ayundina      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disassembler.h"

static void	check_for_end_of_file(int fd)
{
	int				ret;
	unsigned char	buff[1];

	ret = (int)read(fd, buff, 1);
	check_if_return_of_read_is_valid(ret, 0);
	return ;
}

void		get_champion_exec_code(int fd, t_exec *exec)
{
	int				ret;

	exec->code = (unsigned char *)ft_memalloc(exec->header.prog_size + 1);
	ret = (int)read(fd, exec->code, exec->header.prog_size);
	check_if_return_of_read_is_valid(ret, exec->header.prog_size);
	exec->code[exec->header.prog_size] = '\0';
	check_for_end_of_file(fd);
	return ;
}
