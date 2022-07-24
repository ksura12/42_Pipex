/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:53:36 by ksura             #+#    #+#             */
/*   Updated: 2022/07/24 17:44:32 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int child2_parent(char **argv, t_pipex *pipex)
{
	if (pipex->pid[1] == -1)
		return (1);
	if (pipex->pid[1] == 0)
		child2(argv, pipex);
	close(pipex->fd_file[0]);
	close(pipex->fd_file[1]);
	close(pipex->ends[0]);
	close(pipex->ends[1]);
	waitpid(pipex->pid[0], NULL, WUNTRACED);
	waitpid(pipex->pid[1], NULL, WUNTRACED);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc != 5)
	{
		ft_printf("Wrong amount of input arguments\n");
		return (0);
	}
	else
	{
		pipex = (t_pipex *)calloc(1, sizeof(t_pipex));
		pipex->envp = envp;
		if (pipe(pipex->ends) == -1)
			return (1);
		pipex->pid[0] = fork();
		if (pipex->pid[0] == -1)
			return (1);
		if (pipex->pid[0] == 0)
			child1(argv, pipex);
		pipex->pid[1] = fork();
		if (child2_parent(argv, pipex) == 1)
			return (1);
		free (pipex);
		return (0);
	}
}
