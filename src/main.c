/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:53:36 by ksura             #+#    #+#             */
/*   Updated: 2022/07/24 17:10:17 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	pid_t	pid2;
	int		ends[2];
	int		fd_file[2];

	if (argc != 5)
	{
		ft_printf("Wrong amount of input arguments\n");
		return (0);
	}
	else
	{
		if (pipe(ends) == -1)
			return (1);
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			child1(argv, envp, ends);
		pid2 = fork();
		if (pid2 == -1)
			return (1);
		if (pid2 == 0)
			child2(argv, envp, ends);
		close(fd_file[0]);
		close(fd_file[1]);
		close(ends[0]);
		close(ends[1]);
		waitpid(pid, NULL, WUNTRACED);
		waitpid(pid2, NULL, WUNTRACED);
		return (0);
	}
}
