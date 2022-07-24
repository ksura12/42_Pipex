/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:09:05 by ksura             #+#    #+#             */
/*   Updated: 2022/07/24 18:17:45 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <unistd.h>
#include <stdio.h>

static char	*get_paths(int i, char **envp)
{
	char	*envp_path;

	while (envp[i])
	{
		envp_path = ft_strnstr(envp[i], "PATH=", 5);
		if (envp_path)
		{
			envp_path = ft_substr(envp[i], 5, 100);
			if (!envp_path)
				return (0);
			break ;
		}
		i++;
	}
	return (envp_path);
}

char	**slash_path(int i, char **paths)
{
	char	*tmp;

	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
	return (paths);
}

char	*wright_path(int i, char **paths, char *cmd)
{
	char	*cmd_path;

	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free (cmd_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*envp_path;
	char	*cmd_path;
	char	**paths;

	i = 0;
	if (get_paths(i, envp) == 0)
		return (0);
	envp_path = get_paths(i, envp);
	paths = ft_split(envp_path, ':');
	if (!paths)
		return (0);
	i = 0;
	paths = slash_path(i, paths);
	i = 0;
	cmd_path = wright_path(i, paths, cmd);
	if (cmd_path != NULL)
		return(cmd_path);
	perror(envp_path);
	free (envp_path);
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char	*cmd_path;
// 	char	*options[3] = {"ls", "-la", NULL};
// 	char	*cmd = "ls";

// 	(void)argc;
// 	(void)argv;
// 	cmd_path = get_cmd_path(cmd, envp);

// 	if(!cmd_path)
// 	{
// 		perror(cmd_path);
// 		return(-1);
// 	}
// 	execve(cmd_path, options, envp);
// 	//free(cmd_path);
// 	return (0);

// }