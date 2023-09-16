#include "../../includes/minishell.h"

void    here_run(char *eof, int fd)
{
    char    *input;

    while (1)
    {
        input = readline("> ");
        if (ft_strlen(input) == ft_strlen(eof))
        {
            if (!ft_strncmp(eof, input, ft_strlen(eof)))
            {
                close(fd);
                free(input);
                exit(EXIT_SUCCESS);
            }
        }
        ft_putendl_fd(input, fd);
        free(input);
    }
    ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
    ft_putstr_fd(eof, STDERR_FILENO);
    ft_putstr_fd("')\n", STDERR_FILENO);
    close(fd);
    free(input);
    exit(EXIT_SUCCESS);
}

int hd_input(char *eof, int fd)
{
    pid_t   pid;
    int     wstatus;

    pid = fork();
    if (pid == -1)
       // TODO: // exit status
    if (pid == 0)
    {
        heredoc_signals();
        here_run(eof, fd);
    }
    else
    {
        ignore_signals();
        waitpid(pid, &wstatus, 0);
        if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) + 128 == 130)
        {
            ft_putchar_fd('\n', STDOUT_FILENO);
            return (0);
        }
        parent_signals();
    }
    return (1);
}

int handle_hd(t_ast *redir)
{
    int fd;

    fd = open(".heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
    if (fd == -1)
        TODO: // handle error
    if (!hd_input(redir->content, fd))
    {
        close(fd);
        return (0);
    }
    free(redir->content);
    redir->content = ft_strdup(".heredoc");
    close(fd);
    return 1;
}