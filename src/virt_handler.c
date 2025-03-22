/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virt_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:19:38 by mgavorni          #+#    #+#             */
/*   Updated: 2025/03/23 00:47:26 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	virtual(void)
{
	printf("exit\n");
	exit(0);
}

sig_action_t	m_virtual_handler(sigset_t sig_mask)
{
	return ((sig_action_t){
		.descript = "Ctrl-D Handler",
		.type = FAKE_SIGNAL,
		.sig_handler = NULL,
		.sig_alt_handler = NULL,
		.virtual = virtual,
		.sig_mask = sig_mask,
		.virtual_id = SIG_VIRTUAL_CTRL_D,
		.sig_flag = 0,
		.signum = 0
	});
}

void	setup_virt_handler(int id)
{
	size_t			i;
	sig_action_t	signals_vr[SIGNAL_COUNT];

	i = 0;
	while (i < SIGNAL_COUNT)
	{
		if (signals_vr[i].type == FAKE_SIGNAL && signals_vr[i].virtual_id == id)
		{
			signals_vr->virtual();
			break ;
		}
		i++;
	}
}
