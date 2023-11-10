/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:05:59 by acronert          #+#    #+#             */
/*   Updated: 2023/11/10 13:52:34 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 42

typedef struct	s_list
{
		char			*content;
		struct s_list	*next;
}						t_list;

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

char	*get_next_line(int fd);
void	clean_stash(t_list **stash);
char	*extract_line(t_list *stash, char **line);
void	malloc_line(t_list *stash, char **line);
void	read_and_stash(t_list **stash, int *nread_ptr, int fd);
int	check_eof(t_list *stash);
t_list	*lst_getlast(t_list	*stash);
void	add_to_stash(t_list **stash, char *buffer, int nread);
void	free_stash(t_list *stash);
int	ft_strlen(char	*str);

#endif
