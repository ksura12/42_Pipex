/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opening.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:53:36 by ksura             #+#    #+#             */
/*   Updated: 2022/07/24 20:07:23 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static void	file_outputting(char *filename, char **envp, char *cmd_p, char **t)
{
	pid_t	pid;

	if (access (filename, F_OK) == 0)
	{
		if (access (filename, W_OK) != 0)
		{
			ft_putstr_fd("zsh: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(filename, 2);
			ft_putstr_fd("\n", 2);
			// ft_printf("zsh: %s: %s\n", strerror(errno), filename);
			exit (0);
		}
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("zsh: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(filename, 2);
			ft_putstr_fd("\n", 2);
			// ft_printf("zsh: %s: %s\n", strerror(errno), filename);
			exit(0);
		}
		if (pid == 0)
			execve(cmd_p, t, envp);
		waitpid(pid, NULL, WUNTRACED);
	}
}

int	open_file(char *filename, int rw, char **envp)
{
	int		fd;
	char	*touching[3];
	char	*cmd_path;

	touching[0] = "touch";
	touching[1] = filename;
	touching[2] = NULL;
	cmd_path = get_cmd_path("touch", envp);
	if (rw == 0)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("zsh: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(filename, 2);
			ft_putstr_fd("\n", 2);
			// ft_printf("zsh: %s: %s\n", strerror(errno), filename);
			exit (0);
		}
	}
	else
	{
		file_outputting(filename, envp, cmd_path, touching);
		fd = open(filename, O_WRONLY);
	}
	return (fd);
}
