/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acronert <acronert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:00:58 by acronert          #+#    #+#             */
/*   Updated: 2023/11/09 12:29:01 by acronert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_eof (char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	char	*buf;
	char	*nextline;
	size_t	nbytes;

	buf = malloc(BUFFER_SIZE * sizeof(char));
	if (!buf)
		return (0);
	nbytes = 5;
	printf ("buf = %s\n", buf);
	while (!check_eof(buf) || check_eof(buf) != (int)nbytes)
		read(fd, buf, nbytes);
	
	nextline = buf;

	return (nextline);
}




int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (0);
	fd = open(argv[1], 0);
	printf ("fd = %d\n", fd);
	printf ("%s", get_next_line(fd));
	return (0);

}