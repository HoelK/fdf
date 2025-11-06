/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:32:05 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/01 18:51:49 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# ifndef FD_MAX
#  define FD_MAX 1024
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

char	*ft_strjoin(char *s1, char *s2);
char	*fill_rest(char *buffer, char *rest);
char	*extract_line(char *rest);
char	*get_next_line(int fd);
char	*join_and_free(char *s1_tofree, char *buffer);
char	*kill_func(char *buffer, char **rest, int error);
int		ft_lento(char *s, char c);
char	*ft_strdup(char	*s);
char	*ft_calloc(size_t n, size_t size);

#endif
