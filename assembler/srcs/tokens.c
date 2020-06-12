/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/04 19:27:27 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/04 19:37:19 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

/*
**	adds tokens to the linked list
*/

void		add_token(t_corewar *data, char *line, int start, int end)
{
	t_tokens	*current;

	if (data->tokens == NULL)
	{
		data->tokens = (t_tokens*)ft_memalloc(sizeof(t_tokens));
		current = data->tokens;
	}
	else
	{
		current = data->tokens;
		while (current->next != NULL)
			current = current->next;
		current->next = (t_tokens*)ft_memalloc(sizeof(t_tokens));
		current = current->next;
	}
	current->next = NULL;
	current->content = ft_strsub(line, start, end - start);
	current->linenum = data->linenum;
}

/*
**	deals with a specific case of syntax where '%' (instead of
**	whitespace or ',') marks the beginning of a new token
*/

static int	token_helper(t_corewar *data, char *str, int i)
{
	int		start;

	start = i;
	i = skip_chars_delim(str, i + 1);
	add_token(data, str, start, i);
	return (i - 1);
}

/*
**	parses the executable bit into tokens and passes them to add_token,
**	which adds them to a linked list
*/

void		get_tokens(t_corewar *data, char *line)
{
	char	*str;
	int		i;
	int		start;

	str = trim_comment(line);
	i = 0;
	while (str[i] != '\0')
	{
		i = skip_whitespace(str, i);
		start = i;
		i = skip_chars_delim(str, i);
		if (str[i] == LABEL_CHAR)
			add_token(data, str, start, i + 1);
		else if (i > start)
			add_token(data, str, start, i);
		if (str[i] == DIRECT_CHAR)
			i = token_helper(data, str, i);
		if (str[i] == SEPARATOR_CHAR)
			add_token(data, str, i, i + 1);
		if (str[i] == '\0')
			break ;
		i++;
	}
}
