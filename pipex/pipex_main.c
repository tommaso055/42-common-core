#include "pipex.h"

void	put_err(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
}

void	terminate(char *str)
{
	put_err(str);
	exit(1);
}

void	child_process(int *pipe_fd, char **argv, char **envp)
{
	int		fd;
	char	*path;
	char	**cmd;
	
	close(pipe_fd[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		exit(-1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	cmd = ft_split(argv[2], ' ');
	path = find_path(cmd[0], envp);

	if (execve(path, cmd, envp) == -1)
	{
		write(2, "qui", 3);
		free(path);
		destroy_matrix(cmd);
		put_err("pipex: command not found: ");
		terminate(cmd[0]);
	}
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
	if (!fd)
		exit(-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cmd = ft_split(argv[3], ' ');
	path = find_path(cmd[0], envp);

	if (execve(path, cmd, envp) == -1)
	{
		write(2, "quo", 3);
		free(path);
		destroy_matrix(cmd);
		put_err("pipex: command not found: ");
		terminate(cmd[0]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		wstatus;
	__pid_t	pid;
	int		pipe_fd[2];

	if (argc != 5)
		terminate("Error: only 5 arguments");
	if(pipe(pipe_fd) == -1)
		terminate("Error: failed pipe");
	pid = fork();
	if (pid == -1)
		terminate("Error: failed fork");
	if (pid == 0)
		child_process(pipe_fd, argv, envp);
	else
	{
		if (waitpid(pid, &wstatus, 0) == -1 || WIFEXITED(wstatus) == 0)
			terminate("Error: failed child");
		parent_process(pipe_fd, argv, envp);
	}
	
}