/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:09:45 by mgavorni          #+#    #+#             */
/*   Updated: 2025/03/23 00:47:22 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

sig_action_t	m_sigint_handler(sigset_t sig_mask)
{
	return ((sig_action_t){
		.descript = "Ctrl-C Handler",
		.type = REAL_SIGNAL,
		.sig_handler = sig_handler,
		.sig_alt_handler = NULL,
		.virtual = NULL,
		.sig_mask = sig_mask,
		.virtual_id = 0,
		.sig_flag = SA_RESTART,
		.signum = SIGINT});
}

sig_action_t	m_sigquit_handler(sigset_t sig_mask)
{
	return ((sig_action_t){
		.descript = "Ctrl-\\ Handler",
		.type = REAL_SIGNAL,
		.sig_handler = NULL,
		.sig_alt_handler = SIG_IGN,
		.virtual = NULL,
		.sig_mask = sig_mask,
		.virtual_id = 0,
		.sig_flag = 0,
		.signum = SIGQUIT});
}

sig_action_t	m_sigchild_handler(sigset_t sig_mask)
{
	return ((sig_action_t){
		.descript = "Child exit Handler",
		.type = REAL_SIGNAL,
		.sig_handler = NULL,
		.sig_alt_handler = sig_alt_handler,
		.virtual = NULL,
		.sig_mask = sig_mask,
		.virtual_id = 0,
		.sig_flag = SA_SIGINFO | SA_RESTART,
		.signum = SIGCHLD});
}


void	setup_sig_handler(void)
{
	sigset_t		sig_mask;
	size_t			i;
	sig_action_t	signals[SIGNAL_COUNT];

	rl_catch_signals = 0;
	sigemptyset(&sig_mask);
	signals[0] = m_sigint_handler(sig_mask);
	signals[1] = m_sigquit_handler(sig_mask);
	signals[2] = m_sigchild_handler(sig_mask);
	signals[3] = m_virtual_handler(sig_mask);
	i = 0;
	while (i < SIGNAL_COUNT)
	{
		if (signals[i].type == REAL_SIGNAL && register_sig(&signals[i]) == -1)
		{
			printf("Registration of : %s FAILED\n", signals[i].descript);
		}
		i++;
	}
}
