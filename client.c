/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arbaboom <arbaboom@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 15:00:57 by arbaboom          #+#    #+#             */
/*   Updated: 2022/08/12 15:58:31 by arbaboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	ft_send(int pid, char *str)
{
	int	b;
	int	i;
	int	a;
	int	c;

	i = -1;
	a = 0;
	c = 0;
	while (str[++i])
	{
		b = 128;
		while (b != 0)
		{
			if (str[i] & b)
				a += kill(pid, SIGUSR1);
			else
				c += kill(pid, SIGUSR2);
			usleep(100);
			b = b >> 1;
		}
	}
	if (a == 0 && c == 0)
		write(1, "message sent", 12);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	size_t				i;
	int					n;
	unsigned long int	res;

	i = 0;
	n = 1;
	res = 0;
	while ((str[i] == ' ' || str[i] == '\t') || (str[i] == '\n'
			|| str[i] == '\f') || (str[i] == '\v' || str[i] == '\r'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			n *= -1;
	while (ft_isdigit(str[i]))
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * n);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		write(1, "bad command: ./a.out [pid] [message] \n", 38);
		return (0);
	}
	pid = ft_atoi(argv[1]);
	ft_send(pid, argv[2]);
	return (0);
}
