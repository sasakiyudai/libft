/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 17:48:31 by syudai            #+#    #+#             */
/*   Updated: 2021/02/05 23:21:20 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void one_command(char ***cmd, char ***raw_cmd, t_arg_main *arg_main)
{
	pid_t pid;
	int tmp;
	int semi[2];
	char **envs;
	char *path;
	int status;

	if ((tmp = is_builtin((*cmd)[0])))
	{
		set_right(raw_cmd, 0, semi, 0);
		set_left(raw_cmd, 0, semi, 0);
		set_hatena(g_arg_main, call_builtin(tmp, *cmd, arg_main));
	}
	else 
	{
		tmp = get_path(arg_main, &path, (*cmd)[0]);
		if (tmp == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				set_right(raw_cmd, 0, semi, 0);
				set_left(raw_cmd, 0, semi, 0);
				envs = arg_list_get(arg_main);
				execve(path, *cmd, envs);
				exit(error((*cmd)[0]));
			}
			free(path);
			waitpid(pid, &status, 0);
			set_hatena(arg_main, WEXITSTATUS(status));
		}
		else
		{
			set_hatena(arg_main, 127);
			error((*cmd)[0]);
		}
	}
}

/*
int main(void)
{
	t_arg_main arg_main;
	t_arg		arg;

	arg.name = "PATH";
	arg.data = "/bin";
	arg.type = ARG_TYPE_STR;

	arg_main_ini(&arg_main);
	arg_add(&arg_main, &arg);
	
	char *ls[] = {"ls", "<", "hoe", NULL};
	char *ls1[] = {"ls", NULL};
	char *cat[] = {"cat", NULL};
	char *cat1[] = {"cat", NULL};

	char **raw_cmd[] = {ls, cat, NULL};
	char **cmd[] = {ls1, cat1, NULL};

	
	if (count(cmd) == 1)
		one_command(cmd, raw_cmd, &arg_main);
	else if (count(cmd) >= 1)
		pipeline(cmd, raw_cmd, &arg_main);
	return (0);
}

*/
/*

ほんとのmainのしょっぱなの方で
g_in = dup(0);
g_out = dup(1);

要素ごとに
resetする

dup2(g_in, 1);
dup2(g_out, 0);

set_right, set_leftのopenでエラー起きたら
no execのが正しいかも

*/