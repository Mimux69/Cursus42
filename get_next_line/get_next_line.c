/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:00:58 by acronert          #+#    #+#             */
/*   Updated: 2023/11/10 13:52:32 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



char	*get_next_line(int fd)
{
	t_list	*stash;
	char	*line;
	int		nread;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	stash = NULL;
	line = NULL;
	nread = 1;
	//read file and add to t_list
	read_and_stash(&stash, &nread, fd);
	if (stash == NULL)
		return (NULL);
	//extract from stash to line
	line = extract_line(stash, &line);
	//clean stash
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);

}

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int	i;
	int	j;

	clean_node = malloc(sizeof(t_list));
	if (stash == NULL || clean_node == NULL)
		return;
	clean_node->next = NULL;
	last = lst_getlast(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(((ft_strlen(last->content) - i) + 1) * sizeof(char));
	if (clean_node == NULL)
		return;
	j = 0;
	while (last->content[i])
	{
		clean_node->content[j] = last->content[i];
		j++;
		i++;
	}
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}

char	*extract_line(t_list *stash, char **line)
{
	int		i;
	int		j;

	if (!stash)
		return (NULL);
	malloc_line(stash, line);
	if (!*line)
		return (NULL);
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				*line[j] = '\n';
				j++;
				break ;
			}
			*line[j] =  stash->content[i];
			i++;
			j++; 
		}
		stash = stash->next;
	}
	*line[j] = '\0';
	return (*line);
}

void	malloc_line(t_list *stash, char **line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (stash)
	{
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc((len + 1) * sizeof(char));
}

void	read_and_stash(t_list **stash, int *nread_ptr, int fd)
{
	char	*buffer;

	while (check_eof(*stash) != 0 && *nread_ptr != 0)
	{
		buffer = malloc(BUFFER_SIZE * sizeof(char));
		if (!buffer)
			return ;
		*nread_ptr = read(fd, buffer, BUFFER_SIZE);
		if (*stash == NULL && *nread_ptr <= 0)
			{
				free(buffer);
				return ;
			}
		buffer[*nread_ptr] = '\0';
		add_to_stash(stash, buffer, *nread_ptr);
		free(buffer);
	}
}
int	check_eof(t_list *stash)
{
	int	i;
	t_list	*current;

	if (stash == NULL)
		return (0);
	current = lst_getlast(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*lst_getlast(t_list	*stash)
{
	t_list	*current;

	current = stash;
	while (current->next)
		current = current->next;
	return (current);
}

void	add_to_stash(t_list **stash, char *buffer, int nread)
{
	int	i;
	t_list	*last;
	t_list	*newnode;

	newnode = malloc(sizeof(size_t));
	if (!newnode)
		return ;
	newnode->next = NULL;
	newnode->content = malloc((nread + 1) * sizeof(char));
	if (newnode->content == NULL)
		return ;
	i = 0;
	while (buffer[i] && i < nread)
	{
		newnode->content[i] = buffer[i];
		i++;
	}
	newnode->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = newnode;
		return ;
	}
	last = lst_getlast(*stash);
	last->next = newnode;
}
void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free (current);
		current = next;
	}
}
int	ft_strlen(char	*str)
{
	int	len;

	len = 0;
	while (*str)
	{
		str++;
		len++;
	}
	return (len);
}

int	main()
{
	int		fd;
	char	*line;

	printf("\n");
	fd = open("./test_files/file1", O_RDONLY);
	if (fd == -1)
		printf("no file or incorrect filename\n");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf ("%s", line);
		printf("\n");
		free (line);
	}
	return (0);

}