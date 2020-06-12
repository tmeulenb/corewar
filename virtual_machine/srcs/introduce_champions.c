/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   introduce_champions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmeulenb <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 12:25:51 by jheeresm       #+#    #+#                */
/*   Updated: 2019/10/24 21:18:19 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void			introduce_champions(t_vm *vm, t_champion *champ)
{
	int			i;

	i = 0;
	ft_printf(" --------------------------------------------------\n");
	ft_printf("| Let me introduce our champion(s) for this game!  |\n");
	ft_printf(" --------------------------------------------------\n");
	while (i < vm->champion_count)
	{
		ft_printf("| * Player %d, ", abs(champ[i].id));
		ft_printf("starting at position: ");
		ft_printf("%d\n", calc_starting_position(vm, champ[i].id));
		ft_printf("| ->   \"%s\" (\"%s\")\n", champ[i].name,
														champ[i].comment);
		ft_printf("|\n");
		i++;
	}
	ft_printf(" --------------------------------------------------\n");
	return ;
}
