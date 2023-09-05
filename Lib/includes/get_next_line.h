/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fd-arco <fd-arco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 00:09:16 by fililafrapp       #+#    #+#             */
/*   Updated: 2023/03/28 11:19:10 by fd-arco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE	
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
int		ft_strrchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);

#endif