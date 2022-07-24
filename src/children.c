/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:09:35 by ksura             #+#    #+#             */
/*   Updated: 2022/07/24 17:15:03 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	child1(char **argv, char **envp, int *ends)
{
	char	*cmd_path;
	int		fd_file[2];
	char	**options;

	options = ft_split(argv[2], ' ');
	cmd_path = get_cmd_path(options[0], envp);
	fd_file[0] = open_file(argv[1], 0, envp);
	dup2(fd_file[0], STDIN_FILENO);
	dup2(ends[1], STDOUT_FILENO);
	close(ends[0]);
	close(ends[1]);
	execve(cmd_path, options, envp);
	exit(-1);
}

void	child2(char **argv, char **envp, int *ends)
{
	char	*cmd_path;
	int		fd_file[2];
	char	**options;

	options = ft_split(argv[3], ' ');
	cmd_path = get_cmd_path(options[0], envp);
	fd_file[1] = open_file(argv[4], 1, envp);
	dup2(ends[0], STDIN_FILENO);
	dup2(fd_file[1], STDOUT_FILENO);
	close(ends[0]);
	close(ends[1]);
	execve(cmd_path, options, envp);
}
