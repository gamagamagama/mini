/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_hand.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavorni <mgavorni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:09:02 by mgavorni          #+#    #+#             */
/*   Updated: 2025/03/23 02:30:56 by mgavorni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_HAND_H
# define SIG_HAND_H

# define _POSIX_C_SOURCE 200809L

# include <sys/signal.h>
# include <sys/wait.h>
// # include <asm-generic/siginfo.h>
// # include <asm-generic/signal.h>

# define SIGNAL_COUNT 4
# define SIG_VIRTUAL_CTRL_D 1
# define SIG_REAL 0

// --- Handler function typedefs ---
typedef void				(*real_af)(int);
typedef void				(*real_af_plus)(int, siginfo_t *, void *);
typedef void				(*fake_af)(void);

// --- Signal type: real vs virtual ---
typedef enum e_signal_type_e
{
	REAL_SIGNAL,
	FAKE_SIGNAL
}							t_signal_type;

// --- Global signal state ---
typedef struct sig_data_s
{
	volatile sig_atomic_t	sig;
}							t_sig_data;

// --- Signal action configuration ---
typedef struct sig_action_s
{
	const char				*descript;       // Optional: short description
	t_signal_type			type;            // REAL_SIGNAL or FAKE_SIGNAL
	real_af					sig_handler;     // Handler for classic signal
	real_af_plus			sig_alt_handler; // Handler for SA_SIGINFO
	fake_af					virtual;         // Virtual (fake) handler function
	sigset_t				sig_mask;        // Signal mask
	int						id;      // ID for virtual handler
	int						sig_flag;        // SA_* flags
	int						signum;          // Signal number (e.g., SIGINT)
}							t_sig_action;

// --- Globals ---
extern t_sig_data			g_glob_sig;
extern t_sig_action			signals[SIGNAL_COUNT];

// --- Core signal system API ---
int							register_sig(const t_sig_action *config);
void						setup_sig_handler(int id);
void						setup_virt_handler(int id);

// --- General-purpose handlers ---
void						sig_handler(int sig);
void						sig_alt_handler(int sig, siginfo_t *info, void *context);
void						virtual(void);
pid_t						child_ret(siginfo_t *info, int *status);

// --- Signal configuration builders ---
t_sig_action				m_virtual_handler(sigset_t sig_mask);
t_sig_action				m_sigchild_handler(sigset_t sig_mask);
t_sig_action				m_sigquit_handler(sigset_t sig_mask);
t_sig_action				m_sigint_handler(sigset_t sig_mask);

#endif // SIG_HAND_H

// 	// # include <signal.h>
// 	// # include <sys/signal.h>
// 	// # include <sys/wait.h>
// 	// # include <asm-generic/signal.h>
// 	// # include <asm-generic/siginfo.h>
// 	// # include <asm-generic/signal-defs.h>
// #endif