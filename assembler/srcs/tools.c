/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/04 14:47:52 by tide-jon       #+#    #+#                */
/*   Updated: 2019/10/30 00:42:43 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/assembler.h"

void	bad_token(char *str)
{
	ft_printf("token '%s' is not recognized\n", str);
	exit(0);
}

/*
**	takes a string and returns the same string up until a comment character
**	is found: '#' or ';'
*/

char	*trim_comment(char *line)
{
	char	**arr;
	char	*temp;
	int		i;

	arr = ft_strsplit(line, COMMENT_CHAR);
	i = 1;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	temp = arr[0];
	arr = ft_strsplit(arr[0], ALT_COMMENT_CHAR);
	free(temp);
	i = 1;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	return (arr[0]);
}

/*
**	error message for wrong syntax
*/

void	wrong_syntax(char *line)
{
	ft_printf("incorrect syntax on line %s\n", line);
	exit(0);
}

/*
**	returns next index at which there is no whitespace or end of line
*/

int		skip_whitespace(char *line, int i)
{
	while (line[i] != '\0' && ft_iswhitespace(line[i]) == 1)
		i++;
	return (i);
}

/*
**	returns next index at which there is a whitespace or end of line
**	or the separator character ','
*/

int		skip_chars_delim(char *line, int i)
{
	while (line[i] != '\0' && ft_iswhitespace(line[i]) == 0 &&
									line[i] != SEPARATOR_CHAR)
	{
		if (i > 0 && (line[i] == LABEL_CHAR || line[i] == DIRECT_CHAR))
		{
			if (line[i - 1] != LABEL_CHAR && line[i - 1] != DIRECT_CHAR &&
			line[i - 1] != SEPARATOR_CHAR && ft_iswhitespace(line[i - 1]) == 0)
				break ;
		}
		i++;
	}
	return (i);
}
