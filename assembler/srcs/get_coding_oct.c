/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_coding_oct.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jheeresm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/10 17:07:18 by jheeresm      #+#    #+#                 */
/*   Updated: 2019/10/10 17:07:19 by jheeresm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

static char	get_arg_code(t_type type)
{
	if (type == regist)
		return (REG_CODE);
	else if (type == direct || type == dir_label)
		return (DIR_CODE);
	else if (type == indirect || type == ind_label)
		return (IND_CODE);
	else
	{
		ft_error("coding oct bad type");
		return (4);
	}
}

char		get_coding_oct(t_tokens *t, t_instruction inst)
{
	char		args[3];
	int			i;
	static int	arg_number[16] =
	{1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1};

	args[0] = 0;
	args[1] = 0;
	args[2] = 0;
	i = 0;
	t = t->next;
	if (!t)
		ft_error("coding oct token error");
	while (i < arg_number[inst - 1])
	{
		args[i] = get_arg_code(t->type);
		i++;
		if (i < arg_number[inst - 1])
		{
			if (!t->next || !t->next->next)
				ft_error("coding oct token error");
			t = t->next->next;
		}
	}
	return ((args[0] << 6) | (args[1] << 4) | (args[2] << 2));
}

int			oct_check(t_instruction inst)
{
	static int	coding_oct[16] =
	{0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1};

	return (coding_oct[inst - 1]);
}
