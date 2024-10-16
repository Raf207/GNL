/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:18:38 by rafnasci          #+#    #+#             */
/*   Updated: 2024/03/21 17:02:11 by rafnasci         ###   ########.fr       */
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

int	ft_createlist(t_list **list, int fd)
{
	char	*buffer;
	int		counter;

	while (!ft_find_nl(*list))
	{
		buffer = malloc (sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return (ft_cleanlist(list, NULL), 1);
		counter = read(fd, buffer, BUFFER_SIZE);
		if (counter == 0)
			return (free(buffer), 0);
		buffer[counter] = '\0';
		ft_addlist(list, buffer);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*list[OPEN_MAX];
	char			*str;
	char			*last;

	if (fd < 0 || fd > OPEN_MAX || read(fd, 0, 0) < 0 || BUFFER_SIZE < 0
		|| BUFFER_SIZE > INT32_MAX - 1)
		return (ft_cleanlist(&list[fd], NULL), NULL);
	if (ft_createlist(&list[fd], fd) == 1)
		return (NULL);
	if (!list[fd])
		return (NULL);
	str = ft_getline(list[fd]);
	if (!str)
		return (ft_cleanlist(&list[fd], NULL), NULL);
	last = ft_lastpart(list[fd]);
	ft_cleanlist(&list[fd], last);
	if (!last)
		return (free(str), NULL);
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