/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_arguments.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jheeresm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/09 16:50:49 by jheeresm       #+#    #+#                */
/*   Updated: 2019/10/10 18:12:59 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

/*
** op_tab holds the information about which args are allowed.
** it's a lot clearer if you let each {} have it's own line.
**
** The calculations on arg_type is so that:
** 3 register		-> 0
** 4 direct			-> 1
** 5 indirect		-> 2
** 6 direct_label	-> 1
** 7 indirect_label	-> 2
**
** This way the arg_type matches the value of it's corresponding T_ flag.
*/

static int		arg_check(t_instruction inst, t_type arg_type, int i)
{
	static int op_tab[16][3] = {
	{T_DIR, 0, 0},
	{T_DIR | T_IND, T_REG, 0},
	{T_REG, T_IND | T_REG, 0},
	{T_REG, T_REG, T_REG}, {T_REG, T_REG, T_REG},
	{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
	{T_DIR, 0, 0},
	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
	{T_DIR, 0, 0},
	{T_DIR | T_IND, T_REG, 0},
	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
	{T_DIR, 0, 0},
	{T_REG, 0, 0}};

	if (arg_type == 6 || arg_type == 7)
		arg_type -= 5;
	else
		arg_type -= 3;
	if ((op_tab[inst - 1][i] & (1 << arg_type)) > 0)
		return (1);
	else
		return (0);
}

static t_tokens	*args_cycle(t_tokens *t, t_instruction inst,
							int n_arg, int line_n)
{
	int i;

	i = 0;
	while (i < n_arg)
	{
		if (t && t->linenum != line_n)
			ft_error("argument not found on same line as instruction");
		if (t && i > 0)
		{
			if (t->type != seperator)
				ft_error("missing separator");
			t = t->next;
		}
		if (t && 3 <= t->type && t->type <= 7)
		{
			if (!arg_check(inst, t->type, i))
				ft_error("argument does not match instruction");
		}
		else
			ft_error("not enough arguments");
		t = t->next;
		i++;
	}
	return (t);
}

void			check_arguments(t_tokens *tokens)
{
	t_tokens		*t;
	int				line_n;
	static int		arg_number[16] =
	{1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1};

	t = tokens;
	line_n = -1;
	while (t)
	{
		if (t->type == seperator)
			ft_error("lonely seperator char");
		else if (t->type == regist || t->type == direct ||
		t->type == indirect || t->type == dir_label || t->type == ind_label)
			ft_error("argument before instruction");
		else if (t->type == instruction)
		{
			if (t->linenum == line_n)
				ft_error("multiple instructions on the same line");
			line_n = t->linenum;
			t = args_cycle(t->next, t->instruction,
			arg_number[t->instruction - 1], line_n);
		}
		else
			t = t->next;
	}
}
