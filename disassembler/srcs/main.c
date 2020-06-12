/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                              :+:    :+:           */
/*                                                     +:+                    */
/*   By: tmeulenb <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/24 11:55:05 by tmeulenb       #+#    #+#                */
/*   Updated: 2019/10/24 21:18:25 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disassembler.h"

static void		display_help(void)
{
	ft_printf("------------------------------------------------------------");
	ft_printf("------------------\n");
	ft_printf("* Usage: ./dis_asm file.cor \n");
	ft_printf("* This program will translate a .cor file ");
	ft_printf("into a assembly file.\n");
	ft_printf("* It will only work with .cor files and will output errors");
	ft_printf(" if there are any. \n");
	ft_printf("------------------------------------------------------------");
	ft_printf("------------------\n");
	return ;
}

static int		check_for_valid_file(char *filename)
{
	int			i;
	int			len;

	i = 0;
	len = (int)ft_strlen(filename);
	while (i < len - 4)
		i++;
	if (i == len - 4)
	{
		if (!ft_strcmp(".cor", filename + i) && len != 4)
			return (1);
	}
	ft_printf("Invalid file as input: %s\n", filename);
	return (0);
}

int				main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (!ft_strcmp("-help", argv[1]))
			display_help();
		if (check_for_valid_file(argv[1]))
			disassemble_file(argv[1]);
	}
	else
		display_help();
	return (1);
}
