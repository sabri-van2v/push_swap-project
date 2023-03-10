/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:57:41 by svan-de-          #+#    #+#             */
/*   Updated: 2023/01/08 21:15:21 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	next_number_index(t_stack *begin_a, t_stack *begin_b)
{
	int	lower;
	int	index;

	lower = INT32_MAX;
	index = begin_a->link;
	while (begin_a)
	{
		if (begin_a->number < lower && begin_a->number > begin_b->number)
		{
			lower = begin_a->number;
			index = begin_a->link;
		}
		begin_a = begin_a->next;
	}
	return (index);
}

int	len_same(int index_a, int index_b, int len_a, int len_b)
{
	int	len_tot;

	len_tot = 0;
	if (index_b <= len_b / 2 && index_a <= len_a / 2)
	{
		if (index_a > index_b)
			len_tot = index_a - 1;
		else
			len_tot = index_b - 1;
	}
	else if (index_b > len_b / 2 && index_a > len_a / 2)
	{
		if (len_a - index_a > len_b - index_b)
			len_tot = len_a - index_a + 1;
		else
			len_tot = len_b - index_b + 1;
	}
	return (len_tot);
}

int	len_opposite(int index_a, int index_b, int len_a, int len_b)
{
	int	len_tot;

	len_tot = 0;
	if (index_a <= len_a / 2)
		len_tot = len_b - index_b + index_a;
	else
		len_tot = len_a - index_a + index_b;
	return (len_tot);
}

t_short	calcul_path(t_stack *begin_a, t_stack *begin_b, int len_a, int len_b)
{
	t_short	path;

	path.index_a = next_number_index(begin_a, begin_b);
	path.index_b = begin_b->link;
	if ((path.index_b <= len_b / 2 && path.index_a <= len_a / 2)
		|| (path.index_b > len_b / 2 && path.index_a > len_a / 2))
		path.len_tot = len_same(path.index_a, begin_b->link, len_a, len_b);
	else
		path.len_tot = len_opposite(path.index_a, begin_b->link, len_a, len_b);
	if (path.index_b <= len_b / 2)
		path.sens_b = 'a';
	else if (path.index_b > len_b / 2)
		path.sens_b = 'd';
	if (path.index_a <= len_a / 2)
		path.sens_a = 'a';
	else if (path.index_a > len_a / 2)
		path.sens_a = 'd';
	return (path);
}

t_short	short_path(t_stack *begin_a, t_stack *begin_b)
{
	t_short	good;
	t_short	check;
	int		len_a;
	int		len_b;

	good.len_tot = INT32_MAX;
	len_a = stack_len(begin_a);
	len_b = stack_len(begin_b);
	while (begin_b)
	{
		check = calcul_path(begin_a, begin_b, len_a, len_b);
		if (check.len_tot < good.len_tot)
			good = check;
		begin_b = begin_b->next;
	}
	return (good);
}
