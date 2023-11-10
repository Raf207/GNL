/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:18:38 by rafnasci          #+#    #+#             */
/*   Updated: 2023/11/10 14:51:29 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_copyline(char *str, t_list *list)
{
	int	i;
	int	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = -1;
		while (list->buffer_str[++i])
		{
			str[j++] = list->buffer_str[i];
			if (list->buffer_str[i] == '\n')
			{
				str[j] = '\0';
				return ;
			}
		}
		list = list->next;
	}
	str[j] = '\0';
}

char	*ft_getline(t_list	*list)
{
	int		len_line;
	char	*new_line;

	len_line = ft_countlen(list);
	new_line = malloc (sizeof(char) * (len_line + 1));
	if (!new_line)
		return (NULL);
	ft_copyline(new_line, list);
	return (new_line);
}

int	ft_find_nl(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = -1;
		while (list->buffer_str[++i] && i < BUFFER_SIZE)
			if (list->buffer_str[i] == '\n')
				return (1);
		list = list->next;
	}
	return (0);
}

void	ft_createlist(t_list **list, int fd)
{
	char	*buffer;
	int		counter;

	while (!ft_find_nl(*list))
	{
		buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		counter = read(fd, buffer, BUFFER_SIZE);
		if (counter == 0)
			return (free(buffer));
		buffer[counter] = '\0';
		ft_addlist(list, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[100];
	char			*str;
	char			*last;

	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE < 0)
		return (NULL);
	ft_createlist(&list[fd], fd);
	if (!list[fd])
		return (NULL);
	str = ft_getline(list[fd]);
	last = ft_lastpart(list[fd]);
	ft_cleanlist(&list[fd], last);
	return (str);
}

// #include <fcntl.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*str;
// 	int		i;
// 	int		fd2;

// 	fd = open("text.txt", O_RDONLY);
// 	fd2 = open("test.txt", O_RDONLY);
// 	i = -1;
// 	while (++i < 5)
// 	{
// 		str = get_next_line(fd);
// 		printf("fd : %s\n", str);
// 		free(str);
// 		str = get_next_line(fd2);
// 		printf("fd2 : %s\n", str);
// 		free(str);
// 	}
// }
