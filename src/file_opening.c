/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opening.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:53:36 by ksura             #+#    #+#             */
/*   Updated: 2022/07/24 16:28:22 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static void	file_outputting(char *filename, char **envp)
{
	char	*touching[3];
	char	*cmd_path;
	pid_t	pid;

	touching[0] = "touch";
	touching[1] = filename;
	touching[2] = NULL;
	cmd_path = get_cmd_path("touch", envp);
	if (access (filename, F_OK) == 0)
	{
		if (access (filename, W_OK) != 0)
		{
			ft_printf("zsh: %s: %s\n", strerror(errno), filename);
			exit (0);
		}
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			ft_printf("zsh: %s: %s\n", strerror(errno), filename);
			exit(0);
		}
		if (pid == 0)
			execve(cmd_path, touching, envp);
		waitpid(pid, NULL, WUNTRACED);
	}
}

int	open_file(char *filename, int rw, char **envp)
{
	int		fd;

	if (rw == 0)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("zsh: %s: %s\n", strerror(errno), filename);
			exit (0);
		}
	}
	else
	{
		file_outputting(filename, envp);
		fd = open(filename, O_WRONLY);
	}
	return (fd);
}
