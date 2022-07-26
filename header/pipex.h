/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:07:45 by ksura             #+#    #+#             */
/*   Updated: 2022/07/26 09:07:31 by ksura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef struct s_pipex
{
	int		fd_file[2];
	int		ends[2];
	int		pid[2];
	char	**envp;
}	t_pipex;

/**
*@brief get the right path for execution of shell
*commants out of the envp
*
*@param *cmd: char * to which command to look for
*@param **envp; environmentpointer of the mainfct to get 
*systeminformation about path
*@return char * of the path to the given shell command
*/
char	*get_cmd_path(char *cmd, char **envp);

/**
*@brief opens/creates given files, checks for access rights
*
*@param *filename: char pointer to the file to open/create
*@param rw: int to declare if its input file (rw = 0) or 
*output file (rw = 1)
*@param **envp; environmentpointer of the mainfct for 
*execution of "touch" and "chmod"
*@return filedescritor fd of the opened file
*/
int		open_file(char *filename, int rw, char **envp);

/**
*@brief handles the function execution and pipe input for child1 
*
*@param **argv: argv pointer of main
*@param **envp: environmentpointer of the mainfct
*@param *ends: ends of the opened pipe (0-read, 1-write)
*@return f-
*/
void	child1(char **argv, t_pipex *pipex);

/**
*@brief handles the function execution and pipe input for child1 
*
*@param **argv: argv pointer of main
*@param **envp: environmentpointer of the mainfct
*@param *ends: ends of the opened pipe (0-read, 1-write)
*@return f-
*/
void	child2(char **argv, t_pipex *pipex);

#endif