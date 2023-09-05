/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fililafrappe <fililafrappe@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:25:55 by fd-arco           #+#    #+#             */
/*   Updated: 2023/08/29 12:54:59 by fililafrapp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <fcntl.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include <stdlib.h>

char		**ft_split(char const *s, char c);
char		*ft_strjoin2(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s1, char *s2, int fd);
int			strlen2(char *s);
int			ft_strchr(char *str, char c);
int			ft_len_nb(long n);
char		*ft_is_neg(char *res, long n, int i);
char		*ft_itoa(int n);
long long	ft_atoll(const char *str);

#endif
