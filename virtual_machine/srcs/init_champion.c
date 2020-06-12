/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_champion.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 19:57:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/24 21:43:27 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int	check_n_flag_for_id(t_vm *vm, int id)
{
	int			i;

	i = 0;
	while (i < 4)
	{
		if (vm->n_flag[i] == id)
			return (1);
		i++;
	}
	return (0);
}

static void	give_champion_n_flag_id(t_vm *vm, int id)
{
	int			i;

	i = 1;
	while (i < vm->argc)
	{
		if (vm->argv[i] && vm->argv[i][0] - '0' == id)
		{
			vm->champions[id - 1].filename = ft_strdup(vm->argv[i + 1]);
			vm->champions[id - 1].id = -id;
			vm->argv[i + 1] = ".";
			return ;
		}
		i++;
	}
	return ;
}

void		give_champion_id(t_vm *vm, int id)
{
	int			i;

	i = 1;
	while (i < vm->argc)
	{
		if (vm->argv[i] && ft_strstr(vm->argv[i], ".cor"))
		{
			vm->champions[id - 1].filename = ft_strdup(vm->argv[i]);
			vm->champions[id - 1].id = -id;
			vm->argv[i] = ".";
			return ;
		}
		i++;
	}
	return ;
}

static void	give_champion_id_and_set_filename(t_vm *vm)
{
	int			i;

	i = 0;
	while (i < vm->champion_count)
	{
		if (check_n_flag_for_id(vm, i + 1))
			give_champion_n_flag_id(vm, i + 1);
		else
			give_champion_id(vm, i + 1);
		i++;
	}
	return ;
}

void		init_champions(t_vm *vm)
{
	int			i;

	i = 0;
	give_champion_id_and_set_filename(vm);
	while (i < vm->champion_count)
	{
		vm->champions[i].last_live = 0;
		vm->champions[i].amount_of_lives = 0;
		i++;
	}
	return ;
}
