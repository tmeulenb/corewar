/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_file_dot.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ayundina <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 12:25:06 by ayundina      #+#    #+#                 */
/*   Updated: 2019/10/29 12:25:12 by ayundina      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/disassembler.h"

int		create_file_dot_s(char *filename)
{
	int	fd;
	int	len;

	len = (int)ft_strlen(filename);
	filename[len - 3] = 's';
	filename[len - 2] = '\0';
	filename[len - 1] = '\0';
	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		error_messaging(3);
	return (fd);
}
