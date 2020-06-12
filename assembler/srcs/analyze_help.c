/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   analyze_help.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jheeresm <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/10 12:14:46 by jheeresm       #+#    #+#                */
/*   Updated: 2019/10/30 21:43:07 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

/*
** byte tracker always gives a token it's byte coordinate.
** to do this it remembers the last instruction.
** because the first instruction (live) has the value 1 all instructions must
** be adjusted with - 1 to fit the arrays.
*/

void		byte_tracker(t_corewar *data, t_tokens *current)
{
	static t_instruction	instr = -1;
	static int				direct_size[16] =
	{4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 4};
	static int				instr_size[16] =
	{1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2};

	current->position = data->total_bytes;
	if (current->type == seperator || current->type == label)
		return ;
	else if (current->type == instruction)
	{
		instr = current->instruction;
		data->total_bytes += instr_size[instr - 1];
	}
	else if (current->type == regist)
		data->total_bytes++;
	else if (current->type == direct || current->type == dir_label)
		data->total_bytes += direct_size[instr - 1];
	else if (current->type == indirect || current->type == ind_label)
		data->total_bytes += 2;
}

void		check_instruction(t_tokens *token, t_corewar *data)
{
	t_instruction	instr;
	static char		names[16][6] =
	{"live", "ld", "st", "add", "sub", "and", "or", "xor",
	"zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff"};

	token->type = instruction;
	instr = live;
	while (instr <= aff && ft_strcmp(token->content, names[instr - 1]))
		instr++;
	if (instr > aff)
		bad_token(token->content);
	else
		token->instruction = instr;
	data->found_first_op = 1;
}

static void	find_label(t_corewar *data, t_tokens *token,
						t_tokens *last_instruc, int dir)
{
	t_tokens	*current;
	char		*trimmed;

	current = data->tokens;
	while (current != NULL)
	{
		trimmed = ft_strdup(current->content);
		trimmed[ft_strlen(trimmed) - 1] = '\0';
		if (current->type == 1 && ft_strcmp(token->content + 1 + dir,
												trimmed) == 0)
		{
			token->value = current->position - last_instruc->position;
			return ;
		}
		free(trimmed);
		current = current->next;
	}
	ft_printf("Error: label %s not found\n", token->content + 1 + dir);
	exit(0);
}

void		replace_labels(t_corewar *data)
{
	t_tokens	*current;
	t_tokens	*last_instruc;

	current = data->tokens;
	while (current != NULL)
	{
		if (current->type == 2)
			last_instruc = current;
		if (current->type == 6)
			find_label(data, current, last_instruc, 1);
		if (current->type == 7)
			find_label(data, current, last_instruc, 0);
		current = current->next;
	}
}
