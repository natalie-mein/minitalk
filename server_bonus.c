/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeintje <nmeintje@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:21:36 by nmeintje          #+#    #+#             */
/*   Updated: 2024/10/10 11:49:03 by nmeintje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char	*process_char(char c, char *str)
{
	char	*msg;
	int		i;

	msg = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!msg)
		return (NULL);
	i = 0;
	while (str[i])
	{
		msg[i] = str[i];
		i++;
	}
	msg[i] = c;
	msg[i + 1] = 0;
	free(str);
	return (msg);
}

static void	ft_printstr(char **str, int pid)
{
	ft_putstr_fd(*str, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\n[---------------End of message-----------------]\n", 1);
	free(*str);
	*str = NULL;
	kill(pid, SIGUSR2);
}

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	bits = 0;
	static char	c = 0;
	static char	*str;

	(void)context;
	if (!str)
		str = ft_strdup("");
	bits++;
	if (signal == SIGUSR1)
		c |= 1;
	if (signal == SIGUSR2)
		c |= 0;
	if (bits != 8)
		c <<= 1;
	if (bits == 8)
	{
		if (c != 0)
			str = process_char(c, str);
		else
			ft_printstr(&str, info->si_pid);
		bits = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	action;

	pid = getpid();
	ft_putstr_fd("The Server PID is: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putstr_fd("\n", 1);
	sigemptyset(&action.sa_mask);
	action.sa_sigaction = &signal_handler;
	action.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &action, NULL) == -1)
	{
		ft_putstr_fd("Failed to set up SIGUSR1.\n", 1);
		return (0);
	}
	if (sigaction(SIGUSR2, &action, NULL) == -1)
	{
		ft_putstr_fd("Failed to set up SIGUSR2.\n", 1);
		return (0);
	}
	while (1)
		pause();
	return (0);
}
