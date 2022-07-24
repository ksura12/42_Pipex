/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:53:36 by ksura             #+#    #+#             */
/*   Updated: 2022/07/24 15:41:35 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	pid_t	pid2;
	int		ends[2];
	char	*cmd_path;
	int		fd_file[2];
	char	**options;

	if (argc != 5)
	{
		ft_printf("Wrong amount of input arguments\n");
		return (0);
	}
	else
	{
		if(pipe(ends) == -1)
			return (1);
		
		
		
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			options = ft_split(argv[2], ' ');
			cmd_path = get_cmd_path(options[0], envp);
			fd_file[0] = open_file(argv[1], 0, envp);
			dup2(fd_file[0], STDIN_FILENO);
			dup2(ends[1], STDOUT_FILENO);
			close(ends[0]);
			close(ends[1]);
			execve(cmd_path, options, envp);
			exit(-1); // if execve fails
		}
		pid2 = fork();
		if (pid2 == -1)
			return (1);
		if (pid2 == 0)
		{
			options = ft_split(argv[3], ' ');
			cmd_path = get_cmd_path(options[0], envp);
			fd_file[1] = open_file(argv[4], 1, envp);
			dup2(ends[0], STDIN_FILENO);
			dup2(fd_file[1], STDOUT_FILENO);
			close(ends[0]);
			close(ends[1]);
			execve(cmd_path, options, envp);
		}
		close(fd_file[0]);
		close(fd_file[1]);
		close(ends[0]);
		close(ends[1]);
		waitpid(pid, NULL, WUNTRACED);// WUNTRACED
		waitpid(pid2, NULL, WUNTRACED);
		return (0);
	}
		
}

// char **get_options(char *arg)
// {
// 	char	**options;
// 	options = ft_split(arg, " ");
// }

