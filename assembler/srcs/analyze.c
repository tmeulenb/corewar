/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   analyze.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/05 16:35:44 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/30 21:41:40 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

static void	check_label(t_tokens *current)
{
	int		i;
	char	*content;

	content = current->content;
	i = 0;
	while (ft_strchr(LABEL_CHARS, content[i]))
		i++;
	if (i == 0 || content[i] != LABEL_CHAR || content[i + 1] != '\0')
	{
		ft_printf("incorrect label: '%s'\n", current->content);
		exit(0);
	}
	else
		current->type = label;
}

static void	check_register(t_tokens *token)
{
	int len;
	int	value;

	len = ft_strlen(token->content);
	if (len > 1)
	{
		if (ft_isdigit(token->content[1]) && (len == 2 ||
		(len == 3 && ft_isdigit(token->content[2]))))
		{
			token->type = regist;
			value = ft_atoi(token->content + 1);
			if (value == 0 || value > REG_NUMBER)
				check_label(token);
			else
				token->value = value;
		}
		else
			check_label(token);
	}
	else
		ft_error("token 'r' is invalid");
}

static void	check_indirect(t_tokens *token)
{
	char	*content;
	int		i;

	content = token->content;
	if (content[0] == LABEL_CHAR)
		token->type = ind_label;
	else
	{
		i = 0;
		if (content[0] == '-')
			i++;
		while (content[i] != '\0')
		{
			if (content[i] < '0' || content[i] > '9')
				bad_token(content);
			i++;
		}
		token->type = indirect;
		token->value = ft_atoi(content);
	}
}

static void	check_direct(t_tokens *token)
{
	char	*content;
	int		i;

	content = token->content + 1;
	if (content[0] == LABEL_CHAR)
		token->type = dir_label;
	else
	{
		i = 0;
		if (content[0] == '-')
			i++;
		while (content[i] != '\0')
		{
			if (content[i] < '0' || content[i] > '9')
				bad_token(content);
			i++;
		}
		token->type = direct;
		token->value = ft_atoi(content);
	}
}

void		analyze_tokens(t_corewar *data)
{
	t_tokens	*current;
	int			len;

	data->total_bytes = 0;
	current = data->tokens;
	while (current != NULL)
	{
		len = ft_strlen(current->content);
		if (current->content[0] == SEPARATOR_CHAR &&
		ft_strlen(current->content) == 1)
			current->type = seperator;
		else if (current->content[len - 1] == LABEL_CHAR)
			check_label(current);
		else if (current->content[0] == 'r')
			check_register(current);
		else if (current->content[0] == DIRECT_CHAR)
			check_direct(current);
		else if (current->content[0] == LABEL_CHAR ||
		ft_isdigit(current->content[0]) || current->content[0] == '-')
			check_indirect(current);
		else
			check_instruction(current, data);
		byte_tracker(data, current);
		current = current->next;
	}
}
