#include "../includes/minishell.h"

static int numeric_exit(char *str)
{
    int i = 0;
    int over = ft_atoi(str);
    if(str[0] == '\0')
        return (1);
    if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
        i++;
    while(str[i])
    {
        if (!ft_isdigit(str[i]))
            return (1);
        i++;
    }
    if((over == 0 || over == -1) && ft_strlen(str) > 2)
        return (1);
    return (0);
}

static int	exit_atoi(const char *str)
{
	unsigned char	result;
	int						i;
	int						sign;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
	}
	return (result * sign);
}

void exitshell_command(t_command *cmd, t_envs *envs)
{
    char **lexed = NULL;

    if(cmd->args[2])
           ft_printf(2, "exit: too Many arguments");
    else if (cmd->args[1])
        {
            lexed = lexer(cmd->args[1], envs);
            if (!lexed || (lexed[0] && numeric_exit(lexed[0])))
            {
                ft_printf(2, "bash: line 1: exit: %s: numeric argument required\n", lexed[0]);
                g_exit_codes = 255;
            }
            else if (lexed[1])
            {
                 ft_printf(2, "exit: too many arguments\n");
                 free_tab(lexed);
            }
            else
                g_exit_codes = exit_atoi(lexed[0]);
            free_tab(lexed);
            kb_quit(envs);
        }
}
