/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dump_flag.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jheeresm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 15:12:13 by jheeresm       #+#    #+#                */
/*   Updated: 2019/10/24 18:25:55 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			dump_check(t_vm vm)
{
	static int cycles = -1;

	cycles++;
	if (vm.dump_flag == -1)
		return (0);
	if (cycles >= vm.dump_flag)
	{
		dump_flag(vm.memory);
		return (1);
	}
	else
		return (0);
}

void		dump_flag(unsigned char *mem)
{
	int i;

	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", mem[i]);
		if ((i + 1) % 64 == 0 && i + 1 != MEM_SIZE)
		{
			ft_putstr("\n");
			ft_printf("%#.4x : ", i + 1);
		}
		i++;
	}
	ft_putchar('\n');
}
