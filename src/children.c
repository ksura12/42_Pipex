/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:09:35 by ksura             #+#    #+#             */
/*   Updated: 2022/07/24 17:32:21 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	child1(char **argv, t_pipex *pipex)
{
	char	*cmd_path;
	char	**options;

	options = ft_split(argv[2], ' ');
	cmd_path = get_cmd_path(options[0], pipex->envp);
	pipex->fd_file[0] = open_file(argv[1], 0, pipex->envp);
	dup2(pipex->fd_file[0], STDIN_FILENO);
	dup2(pipex->ends[1], STDOUT_FILENO);
	close(pipex->ends[0]);
	close(pipex->ends[1]);
	execve(cmd_path, options, pipex->envp);
	exit(-1);
}

void	child2(char **argv,t_pipex 	*pipex)
{
	char	*cmd_path;
	char	**options;

	options = ft_split(argv[3], ' ');
	cmd_path = get_cmd_path(options[0], pipex->envp);
	pipex->fd_file[1] = open_file(argv[4], 1, pipex->envp);
	dup2(pipex->ends[0], STDIN_FILENO);
	dup2(pipex->fd_file[1], STDOUT_FILENO);
	close(pipex->ends[0]);
	close(pipex->ends[1]);
	execve(cmd_path, options, pipex->envp);
}
