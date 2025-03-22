/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnicoles <vnicoles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:11:46 by vnicoles          #+#    #+#             */
/*   Updated: 2024/02/14 13:11:46 by vnicoles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isdigit(int a)
{
	if (a >= '0' && a <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
