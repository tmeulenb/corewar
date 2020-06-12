/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmeulenb <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 16:04:45 by tmeulenb      #+#    #+#                 */
/*   Updated: 2019/11/04 16:04:46 by tmeulenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disassembler.h"

void		init_octet(t_exec *exec)
{
	exec->octet[0] = 0;
	exec->octet[1] = 1;
	exec->octet[2] = 1;
	exec->octet[3] = 1;
	exec->octet[4] = 1;
	exec->octet[5] = 1;
	exec->octet[6] = 1;
	exec->octet[7] = 1;
	exec->octet[8] = 0;
	exec->octet[9] = 1;
	exec->octet[10] = 1;
	exec->octet[11] = 0;
	exec->octet[12] = 1;
	exec->octet[13] = 1;
	exec->octet[14] = 0;
	exec->octet[15] = 1;
	return ;
}

void		init_t_dir(t_exec *exec)
{
	exec->t_dir[0] = 4;
	exec->t_dir[1] = 4;
	exec->t_dir[2] = 4;
	exec->t_dir[3] = 4;
	exec->t_dir[4] = 4;
	exec->t_dir[5] = 4;
	exec->t_dir[6] = 4;
	exec->t_dir[7] = 4;
	exec->t_dir[8] = 2;
	exec->t_dir[9] = 2;
	exec->t_dir[10] = 2;
	exec->t_dir[11] = 2;
	exec->t_dir[12] = 4;
	exec->t_dir[13] = 2;
	exec->t_dir[14] = 2;
	exec->t_dir[15] = 4;
	return ;
}

void		init_exec(t_exec *exec)
{
	init_t_dir(exec);
	init_octet(exec);
	return ;
}
