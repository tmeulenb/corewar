/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   audio.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 21:01:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/11/18 19:00:41 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int	ft_strrchr_index(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (s[i] == c)
			break ;
		i--;
	}
	return (i);
}

static char	*trim_path(char *exec_path)
{
	char	*filepath;
	char	*temp;
	int		index;

	index = ft_strrchr_index(exec_path, '/');
	if (index < 0)
		ft_error("something went wrong with the audio");
	temp = ft_strsub(exec_path, 0, index);
	filepath = ft_strjoin(temp, "/includes/Chiptronical.ogg");
	free(temp);
	return (filepath);
}

int			play_audio(char *exec_path)
{
	DWORD	chan;
	char	*filepath;

	filepath = trim_path(exec_path);
	BASS_Init(1, 44100, 0, 0, NULL);
	chan = BASS_StreamCreateFile(
	FALSE, filepath, 0, 0, BASS_SAMPLE_LOOP);
	BASS_ChannelPlay(chan, FALSE);
	return (0);
}
