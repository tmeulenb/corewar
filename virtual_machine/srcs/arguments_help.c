/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arguments_help.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: tmeulenb <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/21 12:25:51 by jheeresm       #+#    #+#                */
/*   Updated: 2019/11/12 21:36:27 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			check_for_flags(t_vm *vm, char *arg)
{
	if (!ft_strcmp("-v", arg))
	{
		vm->verbose = 1;
		return (1);
	}
	if (!ft_strcmp("-ncurses", arg))
	{
		vm->visualizer = 1;
		return (1);
	}
	if (!ft_strcmp("-help", arg))
		display_help();
	return (0);
}

void		save_dump_flag(t_vm *vm, int *i)
{
	if (*i + 1 == vm->argc)
		input_error("-dump", flag_nmbr);
	if (ft_isint(vm->argv[*i + 1], ft_strlen(vm->argv[*i + 1])))
	{
		if (vm->dump_flag >= 0)
			input_error("-dump", double_dump);
		vm->dump_flag = ft_atoi(vm->argv[*i + 1]);
		if (vm->dump_flag < 0)
			input_error("-dump", flag_nmbr);
	}
	else
		input_error(vm->argv[*i + 1], flag_nmbr);
	*i += 1;
	return ;
}

void		check_duplicate_n_flag(int *n_flag, int n)
{
	int			i;
	int			newest_n_flag;

	i = 0;
	newest_n_flag = n_flag[n];
	while (i < n)
	{
		if (n_flag[i] == newest_n_flag)
			input_error(NULL, same_id);
		i++;
	}
	return ;
}

void		save_n_flag(t_vm *vm, int *i)
{
	static int			n;

	if (*i + 1 == vm->argc)
		input_error("-n", flag_nmbr);
	if (ft_isint(vm->argv[*i + 1], ft_strlen(vm->argv[*i + 1])))
		vm->n_flag[n] = ft_atoi(vm->argv[*i + 1]);
	else
		input_error(vm->argv[*i + 1], flag_nmbr);
	check_duplicate_n_flag(vm->n_flag, n);
	if (vm->n_flag[n] > vm->champion_count)
		input_error("-n", n_too_big);
	if (vm->n_flag[n] <= 0)
		input_error("-n", bad_flag);
	*i += 1;
	n += 1;
	if (*i + 1 == vm->argc)
		input_error("-n", flag_nmbr);
	if (!check_for_champion(vm->argv[*i + 1]))
		input_error(NULL, id_no_champ);
	return ;
}
