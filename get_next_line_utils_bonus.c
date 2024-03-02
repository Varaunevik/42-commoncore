/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaunevik <vaunevik@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:23:54 by vaunevik          #+#    #+#             */
/*   Updated: 2024/03/02 10:50:59 by vaunevik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

void	free_list(t_list *list)
{
	t_list	*tmp;

	if (!list)
		return ;
	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
	list = NULL;
}

int	find_newline(t_list *node)
{
	int	i;

	i = 0;
	if (!node)
		return (0);
	while (node->content[i])
	{
		if (node->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	create_line(t_list **list, char **line, int i)
{
	int		j;
	t_list	*tmp;

	tmp = *list;
	if (!tmp)
		return ;
	while (tmp)
	{
		j = 0;
		while (tmp->content[j])
		{
			if (tmp->content[j] == '\n')
			{
				i++;
				break ;
			}
			i++;
			j++;
		}
		tmp = tmp->next;
	}
	*line = malloc((i + 1) * sizeof(char));
	if (*line == NULL)
		return ;
	(*line)[i] = '\0';
}

void	pass_over_node(t_list *list, t_list **pass_over)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (list->content[i] && list->content[i] != '\n')
		i++;
	if (list->content[i] == '\n')
		i++;
	while (list->content[i]) 
	{
		(*pass_over)->content[j] = list->content[i];
		i++;
		j++;
	}
	(*pass_over)->content[j] = '\0';
}

int	check_line(char **line, t_list *list)
{
	if ((*line)[0] == '\0' || !line)
	{
		free_list(list);
		free(*line);
		return (1);
	}
	return (0);
}

