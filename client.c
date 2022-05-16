/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimarque <mimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:23:23 by mimarque          #+#    #+#             */
/*   Updated: 2022/05/16 00:58:04 by mimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/**
 * @brief Check for input formating errors
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int	check_arg(int argc, char **argv)
{
	int	i;

	if (argc != 3)
	{
		printf("Usage: ./client <PID> \"message\"\n");
		return (1);
	}
	i = 0;
	while (argv[1][i])
	{
		if (!ft_strchr("0123456789", argv[1][i]))
			return (ft_printf("Usage: ./client <PID> \"message\"\n"));
		i++;
	}
	return (0);
}

void	send_char(unsigned char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(WAIT_TIME);
		i++;
	}
}

void	send_size_t(size_t num, int pid)
{
	int	i;

	i = 0;
	while (i < 64)
	{
		if (num & 0x01)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		num = num >> 1;
		usleep(WAIT_TIME);
		i++;
	}
}

void	ack(int num)
{
	if (num == SIGUSR1)
		ft_putendl_fd("Acknowledged", 1);
	else
		ft_putendl_fd("Error", 1);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;
	int		len;
	int		i;

	signal(SIGUSR1, ack);
	signal(SIGUSR2, ack);
	if (check_arg(argc, argv))
		return (-1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (-1);
	str = argv[2];
	len = ft_strlen(str);
	send_size_t((size_t)getpid(), pid);
	send_size_t(len, pid);
	i = -1;
	while (str[++i])
		send_char(str[i], pid);
	send_char(str[i], pid);
}
