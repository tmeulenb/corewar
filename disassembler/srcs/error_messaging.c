/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messaging.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ayundina <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:25:37 by ayundina      #+#    #+#                 */
/*   Updated: 2019/10/29 12:25:41 by ayundina      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disassembler.h"

void	error_messaging(int choice)
{
	if (choice == 1)
		ft_printf("Magic-header of .cor file is not correct!\n");
	if (choice == 2)
		ft_printf("File we are trying to read is empty!\n");
	if (choice == 3)
		ft_printf("Error while reading file. It might not exist!\n");
	if (choice == 4)
		ft_printf(".cor file is not complete!\n");
	if (choice == 5)
		ft_printf("Operation code is incorrect\n");
	exit(1);
	return ;
}
