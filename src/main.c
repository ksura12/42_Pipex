/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:53:36 by ksura             #+#    #+#             */
/*   Updated: 2022/07/23 14:11:09 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 5)
	{
		perror ("Wrong amount of input arguments");
		return (-1);
	}
	else
		return (0);
}