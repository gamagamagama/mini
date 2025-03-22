/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_hand.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:09:02 by mgavorni          #+#    #+#             */
/*   Updated: 2025/03/22 21:26:07 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HAND_H
# define SIG_HAND_H

# define _POSIX_C_SOURCE 200809L
# include <signal.h>
# include <sys/signal.h>
# include <sys/wait.h>

# define SIG_VIRTUAL_CTRL_D 1
# define SIGNAL_COUNT 4

typedef enum e_signal_type_e
{
	REAL_SIGNAL,
	FAKE_SIGNAL
}							signal_type_t;

typedef void				(*real_af)(int);
typedef void				(*real_af_plus)(int, siginfo_t *, void *);
typedef void				(*fake_af)(void);

typedef struct sig_data_s
{
	volatile sig_atomic_t	sig;
}							sig_data_t;

typedef struct sig_action_s
{
	const char				*descript;
	signal_type_t			type;
	real_af					sig_handler;
	real_af_plus			sig_alt_handler;
	fake_af					virtual;
	sigset_t				sig_mask;
	int						virtual_id;
	int						sig_flag;
	int						signum;
}							sig_action_t;

extern sig_data_t			g_glob_sig;
extern sig_action_t			signals[SIGNAL_COUNT];

int							register_sig(const sig_action_t *config);
void						setup_sig_handler(void);
void						setup_virt_handler(int id);
void						sig_alt_handler(int sig, siginfo_t *info,
								void *context);
void						virtual(void);
void						sig_handler(int sig);
pid_t						child_ret(siginfo_t *info, int *status);

sig_action_t				m_virtual_handler(sigset_t sig_mask);
sig_action_t				m_sigchild_handler(sigset_t sig_mask);
sig_action_t				m_sigquit_handler(sigset_t sig_mask);
sig_action_t				m_sigint_handler(sigset_t sig_mask);
#endif