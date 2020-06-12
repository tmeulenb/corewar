/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_arguments.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmeulenb <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 12:25:51 by jheeresm       #+#    #+#                */
/*   Updated: 2019/11/12 21:36:27 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			check_for_champion(char *arg)
{
	size_t		len;

	len = ft_strlen(arg);
	if (len > 4 && ft_strcmp(arg + len - 4, ".cor") == 0)
		return (1);
	else
		return (0);
}

void		count_champions(t_vm *vm)
{
	int			i;

	i = 1;
	while (i < vm->argc)
	{
		if (check_for_champion(vm->argv[i]))
			vm->champion_count += 1;
		i++;
	}
	if (vm->champion_count < 1 || vm->champion_count > 4)
		input_error(NULL, champ_nmbr);
	return ;
}

void		check_arguments(t_vm *vm)
{
	int			i;

	i = 1;
	if (vm->argc == 1)
		display_help();
	count_champions(vm);
	while (i < vm->argc)
	{
		if (check_for_flags(vm, vm->argv[i]))
			;
		else if (check_for_champion(vm->argv[i]))
			;
		else if (!ft_strcmp("-dump", vm->argv[i]))
			save_dump_flag(vm, &i);
		else if (!ft_strcmp("-n", vm->argv[i]))
			save_n_flag(vm, &i);
		else
			input_error(vm->argv[i], bad_arg);
		i++;
	}
	if ((vm->verbose && vm->visualizer) ||
	(vm->visualizer && vm->dump_flag != -1))
		ft_error("Verbose/dump and visualizer can't be used together.");
}
