/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:53:36 by ksura             #+#    #+#             */
/*   Updated: 2022/07/24 11:02:47 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	open_file(char *filename);

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	// pid_t	pid2;
	int		ends[2];
	char	*cmd_path;
	int		fd_infile;
	char	**options;

	if (argc != 5)
	{
		write (0, "Wrong amount of input arguments\n", 40);
		return (0);
	}
	else
	{
		if(pipe(ends) == -1)
			return (1);
		options = ft_split(argv[2], ' ');
		cmd_path = get_cmd_path(options[0], envp);
		fd_infile = open_file(argv[1]);
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			dup2(fd_infile, STDIN_FILENO);
			dup2(ends[1], STDOUT_FILENO);
			close(ends[0]);
			close(ends[1]);
			execve(cmd_path, options, envp);
			exit(-1); // if execve fails
		}
		// pid2 = fork();
		// if (pid2 == -1)
		// 	return (1);
		// if (pid2 == 0)
		// {
		// 	dup2(ends[0], STDIN_FILENO);
		// 	close(ends[0]);
		// 	close(ends[1]);
		// 	execve(cmd_path, options, envp);
		// }
		close(ends[0]);
		close(ends[1]);
		waitpid(pid, NULL, 0);// WUNTRACED
		// waitpid(pid2, NULL, 0);
		return (0);
	}
		
}

// char **get_options(char *arg)
// {
// 	char	**options;
// 	options = ft_split(arg, " ");
// }

int	open_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open_file failed");
		exit (0);
	}
	return (fd);
}
