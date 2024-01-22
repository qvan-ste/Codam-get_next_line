/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: qvan-ste <qvan-ste@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 11:49:20 by qvan-ste      #+#    #+#                 */
/*   Updated: 2024/01/22 15:15:09 by qvan-ste      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(const char *s)
{
	char	*s_dupe;
	int		i;

	i = 0;
	s_dupe = malloc(ft_strlen(s) * sizeof(const char) + 1);
	if (!s_dupe)
		return (0);
	while (s[i])
	{
		s_dupe[i] = s[i];
		i++;
	}
	s_dupe[i] = '\0';
	return (s_dupe);
}

char	*clean_ret(char *full_ret, char **buf, int *error)
{
	int		len;
	char	*ret;

	len = 0;
	if (full_ret[0] == '\0' || *error == -1)
		return (free(full_ret), NULL);
	while (full_ret[len])
	{
		if (full_ret[len] == '\n')
		{
			len++;
			break ;
		}
		len++;
	}
	ret = ft_substr(full_ret, 0, len);
	if (!ret)
	{
		free(*buf);
		free(full_ret);
		*buf = NULL;
		return (NULL);
	}
	free(full_ret);
	return (ret);
}

char	*save_buf(char *full_buf, int *error)
{
	int		i;
	char	*save;

	i = 0;
	*error = 0;
	if (full_buf[0] == '\0')
		return (free(full_buf), NULL);
	while (full_buf[i])
	{
		if (full_buf[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	save = ft_substr(full_buf, i, ft_strlen(full_buf) - i);
	if (!save)
	{
		*error = -1;
		return (free(full_buf), NULL);
	}
	free(full_buf);
	return (save);
}

char	*read_and_append(int fd, char *buf, char **ret)
{
	char	*tmp;
	int		char_read;

	char_read = 0;
	while (!ft_strchr(buf, '\n'))
	{
		tmp = *ret;
		free(buf);
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			return (free(tmp), NULL);
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
			break ;
		if (char_read < 0)
			return (free(buf), free(tmp), NULL);
		*ret = ft_strjoin(tmp, buf);
		if (!*ret)
			return (free(buf), free(tmp), NULL);
		free(tmp);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf[4096];
	char		*ret;
	int			error;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buf[fd]);
		buf[fd] = NULL;
		return (NULL);
	}
	if (buf[fd])
		ret = ft_strdup(buf[fd]);
	else
		ret = ft_strdup("");
	if (!ret)
	{
		free(buf[fd]);
		buf[fd] = NULL;
		return (NULL);
	}
	buf[fd] = read_and_append(fd, buf[fd], &ret);
	if (!buf[fd])
		return (NULL);
	buf[fd] = save_buf(buf[fd], &error);
	return (clean_ret(ret, &buf[fd], &error));
}
