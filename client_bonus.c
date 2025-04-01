/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:19:24 by nmeintje          #+#    #+#             */
/*   Updated: 2024/10/14 12:21:26 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_reply;

static void	msg_done(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_reply = signal;
}

static void	msg_confirm(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGUSR2)
		ft_putstr_fd("Message received by the server successfully!", 1);
}

static void	send_signal(unsigned char byte, int pid)
{
	unsigned char	bit;
	int				i;

	i = 8;
	while (i > 0)
	{
		bit = ((byte >> (i - 1)) & 1);
		if (bit == 1)
			kill(pid, SIGUSR1);
		else if (bit == 0)
			kill(pid, SIGUSR2);
		i--;
		while (g_reply == 0)
		{
			usleep(DELAY);
			if (g_reply == 0)
			{
				ft_putstr_fd("Server error\n", 1);
				exit(1);
			}
		}
		g_reply = 0;
	}
}

void	setup_sigaction(int signum, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handler;
	sigemptyset(&action.sa_mask);
	sigaction(signum, &action, NULL);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc != 3)
	{
		ft_putstr_fd("Please enter <server PID> <your message>\n", 1);
		ft_putstr_fd("Your message should be a single string\n", 1);
		return (0);
	}
	setup_sigaction(SIGUSR1, &msg_done);
	setup_sigaction(SIGUSR2, &msg_confirm);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("Invalid PID\n", 1);
		exit (1);
	}
	str = argv[2];
	while (*str)
	{
		send_signal((unsigned char)*str, pid);
		str++;
	}
	send_signal(0, pid);
	return (0);
}
