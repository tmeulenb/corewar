/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 19:57:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/17 16:20:42 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		display_help(void)
{
	ft_putstr("Usage:	./corewar [-v | -ncurses | -d N | -help] [-n N] ");
	ft_putstr("champion1.cor [-n N] champion2.cor [-n N] ");
	ft_putstr("champion3.cor [-n N] champion4.cor\n");
	ft_putstr("	-v	: verbose mode. Shows cursor's execution details\n");
	ft_putstr("	-ncurses: visual mode. Visualizes the game ");
	ft_putstr("| can't be used with -v or -dump together\n");
	ft_putstr("	-d N	: dump flag. Dumps memory after N cycles and exits\n");
	ft_putstr("	-help	: help flag. Shows usage details\n");
	ft_putstr("	-n N	: player's order.");
	ft_putstr(" Sets N's ID number of the next player");
	ft_putstr(". N is min. 1 and max. 4 \n");
	exit(1);
}

void		input_error(char *arg, t_input_error choice)
{
	if (arg)
		ft_printf("Error at argument: \"%s\"\n", arg);
	if (choice == no_dot_cor)
		ft_printf("Champion can only be .cor file.\n");
	else if (choice == bad_flag)
		ft_printf("Incorrect flag. Need help? ./corewar -help.\n");
	else if (choice == champ_nmbr)
		ft_printf("Wrong amount of champions (min. 1 | max. 4).\n");
	else if (choice == bad_arg)
		ft_printf("Invalid argument. Need help? ./corewar -help\n");
	else if (choice == flag_nmbr)
		ft_printf("No valid number for the flag.\n");
	else if (choice == id_no_champ)
		ft_printf("No champion argument to give id to.\n");
	else if (choice == n_too_big)
		ft_printf("N is higher than the amount of champions.\n");
	else if (choice == same_id)
		ft_printf("Same id used twice.\n");
	else if (choice == double_dump)
		ft_printf("Dump flag used twice\n");
	exit(1);
}
