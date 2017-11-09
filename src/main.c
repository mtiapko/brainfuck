/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 15:38:10 by exam              #+#    #+#             */
/*   Updated: 2017/09/08 16:09:22 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

typedef unsigned char	t_byte;

void	bf_memzero(int size, t_byte *mem)
{
	while (size--)
		mem[size] = 0;
}

void	bf_while_start(char *code, int *ip, t_byte current)
{
	int b_counter;

	if (current == 0)
	{
		b_counter = 1;
		while (b_counter)
		{
			(*ip)++;
			if (code[*ip] == '[')
				b_counter++;
			else if (code[*ip] == ']')
				b_counter--;
		}
	}
}

void	bf_while_end(char *code, int *ip, t_byte current)
{
	int b_counter;

	if (current != 0)
	{
		b_counter = 1;
		while (b_counter)
		{
			(*ip)--;
			if (code[*ip] == ']')
				b_counter++;
			else if (code[*ip] == '[')
				b_counter--;
		}
	}
}

void	bf_run(char *code, t_byte mem[2048])
{
	int ip;
	int mem_ptr;

	ip = 0;
	mem_ptr = 0;
	while (code[ip] != '\0')
	{
		if (code[ip] == '>')
			mem_ptr++;
		else if (code[ip] == '<')
			mem_ptr--;
		else if (code[ip] == '+')
			mem[mem_ptr]++;
		else if (code[ip] == '-')
			mem[mem_ptr]--;
		else if (code[ip] == '.')
			write(1, &mem[mem_ptr], 1);
		else if (code[ip] == '[')
			bf_while_start(code, &ip, mem[mem_ptr]);
		else if (code[ip] == ']')
			bf_while_end(code, &ip, mem[mem_ptr]);
		ip++;
	}
}

int		main(int argc, char **argv)
{
	t_byte	mem[2048];

	if (argc == 2)
	{
		bf_memzero(sizeof(mem), mem);
		bf_run(argv[1], mem);
	}
	else
		write(1, "\n", 1);
	return (0);
}
