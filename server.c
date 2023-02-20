/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:12:41 by arbaboom          #+#    #+#             */
/*   Updated: 2022/08/12 16:00:30 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	ft_putnbr(pid_t pid)
{
	char	l;

	if (pid < 0)
	{
		write(1, "-", 1);
		pid *= -1;
	}
	if (pid >= 10)
		ft_putnbr(pid / 10);
	l = '0' + (pid % 10);
	write(1, &l, 1);
}

void	signal_hanlder(int sig)
{
	static unsigned char	c = 0;
	static int				flag = 0;

	++flag;
	c = c << 1;
	if (sig == SIGUSR1)
		c = c | 1;
	if (flag == 8)
	{
		write (1, &c, 1);
		flag = 0;
	}
}

int	main(void)
{
	write (1, "server pid is: ", 15);
	ft_putnbr(getpid());
	while (1)
	{
		signal(SIGUSR1, signal_hanlder);
		signal(SIGUSR2, signal_hanlder);
		pause();
	}
	return (0);
}
