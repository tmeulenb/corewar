/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_if_return_of_read_is_valid.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: ayundina <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:25:06 by ayundina      #+#    #+#                 */
/*   Updated: 2019/10/29 12:25:12 by ayundina      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disassembler.h"

void	check_if_return_of_read_is_valid(int ret, int bytes_to_read)
{
	if (ret == -1)
		error_messaging(3);
	if (ret != bytes_to_read)
		error_messaging(4);
	return ;
}
