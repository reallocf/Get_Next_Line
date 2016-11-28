/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csummers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 16:31:36 by csummers          #+#    #+#             */
/*   Updated: 2016/11/17 16:31:37 by csummers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** mallocate ft_strlen(s) + n memory in a new string
**
** copy s into the new string then copy n chars from buff into the new string
**
** free s
**
** return
**       the resulting "fresh" string
**       error if malloc throws an error
*/

char	*copy_until_n(char **s, char *buff, size_t n)
{
	size_t	s_len;
	char	*res;

	if (!*s)
		s_len = 0;
	else
		s_len = ft_strlen(*s);
	if (!(res = ft_strnew(s_len + n)))
		return (NULL);
	if (*s)
		ft_strcpy(res, *s);
	ft_strncat(res, buff, n);
	free(*s);
	return (res);
}

/*
** initialize buffer at fd should fd be new and buff[fd]'s string to NULL
**
** read BUFF_SIZE characters into read_s and copy read_s into buff[fd]'s string
** continue reading and copying into buff[fd]'s string until a new line is found
** or reading completes
**
** if anything has been read into buff[fd]'s string, set buff[fd]'s is_s to 1
** otherwise set to false
**
** if read_size is greater than 0 and the last read_size is equal to the most
** recent read_size, set buff[fd]'s is_f to 1, otherwise set it to 0
**
** set buff[fd]'s old_r_s to read_size for future comparison
**
** set buff[fd]'s pointer to buff[fd]'s string's head (so buff[fd]->s)
**
** return
**       buff[fd]
**       error if malloc throws an error
**       error if read throws an error
**       error if copy_until_n throws an error
*/

t_buff	*read_into(t_buff **buff, int fd)
{
	long long	read_size;
	char		read_s[BUFF_SIZE + 1];

	if (!buff[fd])
	{
		if (!(buff[fd] = (t_buff*)malloc(sizeof(t_buff))))
			return (NULL);
		buff[fd]->old_r_s = 0;
	}
	buff[fd]->s = NULL;
	while ((read_size = read(fd, read_s, BUFF_SIZE)))
	{
		if (read_size == -1)
			return (NULL);
		if (!(buff[fd]->s = copy_until_n(&buff[fd]->s, read_s, read_size)))
			return (NULL);
		buff[fd]->old_r_s = read_size;
		if (ft_strchr(buff[fd]->s, 10))
			break ;
	}
	buff[fd]->is_s = (buff[fd]->s) ? 1 : 0;
	buff[fd]->is_f = (read_size && read_size == buff[fd]->old_r_s) ? 1 : 0;
	buff[fd]->old_r_s = read_size;
	buff[fd]->p = buff[fd]->s;
	return (buff[fd]);
}

/*
** free buff[fd]'s string, note that this is pointing to the same string that
** was originally mallocated
**
** set buff[fd]'s string and buff[fd]'s pointer to NULL for safety's sake
**
** return
**       1
*/

int		buff_clear(t_buff **buff, int fd)
{
	free(buff[fd]->s);
	buff[fd]->s = NULL;
	buff[fd]->p = buff[fd]->s;
	return (1);
}

/*
** initialize line so it's first char is a \0
**
** if buff[fd] doesn't exist or buff[fd]'s string is empty, call read_into
**
** if buff[fd]'s string is empty and the file that fd points to has nothing
** in it, call buff_clear
**
** if there is a new line in buff[fd]'s string anywhere after buff[fd]'s pointer
** then copy into *line up through that new line then set buff[fd]'s pointer
** to the character after the new line. Should this character be \0, set
** buff[fd]'s is_s to 0
**
** if there is not a new line, copy the rest of buff[fd]'s contents after
** buff[fd]'s pointer into *line and set buff[fd]'s is_s to 0
**
** loop through infinitely until one of the (many) return conditions is met
**
** return
**      -1 if line is NULL
**      -1 if fd indicates an error in opening
**      -1 if malloc throws an error
**      -1 if read_into throws an error
**      -1 if copy_until_n throws an error
**       0 if buff[fd] has no string remaining and the file has no more
**         chars in it and *line has no content in it
**       1 if buff[fd] has no string remaining and the file has no more
**         chars in it and *line has content in it
**       1 if buff[fd]'s string had a new line in it
**       1 if buff[fd] copied the remaining amount of buff[fd]'s string
**         into *line and the file has more chars in it
*/

int		get_next_line(const int fd, char **line)
{
	static t_buff	*buff[MAX_FD];
	char			*nl;

	if (!line || fd < 0 || fd >= MAX_FD || !(*line = ft_strnew(0)))
		return (-1);
	while (1)
	{
		if ((!buff[fd] || !buff[fd]->is_s) && !read_into(buff, fd))
			return (-1);
		if (!buff[fd]->is_s && !buff[fd]->is_f && buff_clear(buff, fd))
			return ((**line) ? 1 : 0);
		if ((nl = ft_strchr(buff[fd]->p, 10)))
		{
			if (!(*line = copy_until_n(line, buff[fd]->p, nl - buff[fd]->p)))
				return (-1);
			if (!*(buff[fd]->p = nl + 1))
				buff[fd]->is_s = 0;
			return (1);
		}
		if (!(*line = copy_until_n(line, buff[fd]->p, ft_strlen(buff[fd]->p))))
			return (-1);
		if (!(buff[fd]->is_s = 0) && !buff[fd]->is_f)
			return (1);
	}
}
