/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:37:59 by tdonato           #+#    #+#             */
/*   Updated: 2024/10/07 19:38:00 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_err(char *str, int nl)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		write(2, &str[i++], 1);
	if (nl)
		write(2, &nl, 1);
}

void	t(char *str1, char *str2, char *path, char **cmd)
{
	put_err(str1, 0);
	put_err(str2, '\n');
	if (path)
		free(path);
	if (cmd)
		destroy_matrix(cmd);
	exit(1);
}

void	child_process(int *pipe_fd, char **argv, char **envp)
{
	int		fd;
	char	*path;
	char	**cmd;

	close(pipe_fd[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1 && errno == ENOENT)
		t("pipex: no such file or directory: ", argv[1], NULL, NULL);
	if (fd == -1 && errno == EACCES)
		t("pipex: permission denied: ", argv[1], NULL, NULL);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	cmd = ft_split(argv[2], ' ');
	path = find_path(cmd[0], envp, cmd);
	if (execve(path, cmd, envp) == -1)
		t("pipex: command not found: ", cmd[0], path, cmd);
}

void	parent_process(int *pipe_fd, char **argv, char **envp)
{
	int		fd;
	char	*path;
	char	**cmd;

	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1 && errno == EACCES)
		t("pipex: permission denied: ", argv[4], NULL, NULL);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cmd = ft_split(argv[3], ' ');
	path = find_path(cmd[0], envp, cmd);
	if (execve(path, cmd, envp) == -1)
		t("pipex: command not found: ", cmd[0], path, cmd);
}

int	main(int argc, char **argv, char **envp)
{
	int		wstatus;
	__pid_t	pid;
	int		pipe_fd[2];

	if (argc != 5)
		t(NULL, "pipex: only five arguments accepted", NULL, NULL);
	if (pipe(pipe_fd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		child_process(pipe_fd, argv, envp);
	else
		parent_process(pipe_fd, argv, envp);
	if (waitpid(pid, &wstatus, 0) == -1 || WIFEXITED(wstatus) == 0)
		exit(1);
}
