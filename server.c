/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimarque <mimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 11:23:41 by mimarque          #+#    #+#             */
/*   Updated: 2022/05/16 00:58:09 by mimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* equal to base ^ e but recursive */
int	ft_rpower(int base, int e)
{
	if (e != 0)
		return (base * ft_rpower(base, e - 1));
	else
		return (1);
}

//example with less bits
//1 << 7 == mask == 10000000
//~(1<<7) == 01111111
//char_value == aaaaaaaa
//char_value >> 1 == 0aaaaaaa
//Therefore ((char_value >> 1) & ~(1 << 7)) shifts 
//all bits 1 to the right and adds a zero at the end
//val == 0 is checking if last char (NUL)
//1ull is so it takes 64bits instead of the default 32
/**
 * @brief receives first the pid so it can acknoledge later
 * Then it receives lenght and allocates it with calloc
 * 
 * @param num pid by reference
 * @param str string 
 * @param s signal
 * @return int 
 */
static int	receive_size_t(size_t *num, char **str, int s)
{
	static int		curr_bit = 0;
	static int		received = 0;
	static size_t	value = 0;

	if (s == SIGUSR2)
		value = (value >> 1) | (1ull << 63);
	if (s == SIGUSR1)
		value = ((value >> 1) & ~(1ull << 63));
	if (curr_bit == 63 && received == 0)
	{
		received = 1;
		*num = value;
		return (curr_bit = 0);
	}
	else if (curr_bit == 63 && received == 1)
	{
		received = 0;
		*str = ft_calloc(value + 1, sizeof(char));
		if (!*str)
			exit(1 + kill(*num, SIGUSR2));
		value = 0;
		return (curr_bit = 0);
	}
	curr_bit++;
	return (0);
}

/**
 * @brief frees the string, resets variables
 * and sends an acknoledge to client
 * 
 * @param pid pid
 * @param str string
 * @param i counter
 */
void	ack_clear_vars(size_t *pid, char **str, int *i)
{
	kill(*pid, SIGUSR1);
	*pid = 0;
	*i = 0;
	if (str)
	{
		ft_putendl_fd(*str, 1);
		free(*str);
		*str = 0;
	}
}

/**
 * @brief Receives the info from client,
 * note that NUL is the ending char
 * 
 * @param signal signal
 */
void	receive_info(int signal)
{
	static size_t	pid = 0;
	static char		*str = 0;
	static int		current_bit = 0;
	static int		val = 0;
	static int		i = 0;

	if (!pid)
		receive_size_t(&pid, &str, signal);
	else if (!str)
		receive_size_t(&pid, &str, signal);
	else
	{
		if (signal == SIGUSR2)
			val += ft_rpower(2, current_bit);
		if (current_bit == 7)
		{
			str[i++] = val;
			current_bit = 0;
			if (val == 0)
				return (ack_clear_vars(&pid, &str, &i));
			val = 0;
			return ;
		}
		current_bit++;
	}
}

int	main(void)
{
	int	id;

	id = (int)(getpid());
	ft_putnbr_fd(id, 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, receive_info);
	signal(SIGUSR2, receive_info);
	while (1)
		usleep(WAIT_TIME);
}
