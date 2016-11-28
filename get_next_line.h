/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csummers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 08:08:25 by csummers          #+#    #+#             */
/*   Updated: 2016/11/07 08:08:26 by csummers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# define BUFF_SIZE 1
# define MAX_FD 2048

typedef struct	s_buff
{
	char		*s;
	char		*p;
	int			is_s;
	int			is_f;
	long long	old_r_s;
}				t_buff;

int				get_next_line(const int fd, char **line);

#endif
