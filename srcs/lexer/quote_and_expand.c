#include "minishell.h"

char	*replace_env_var(char *var)
{
	int	pos;
	int	max;
	int	len;

	pos = 0;
	while (get()->env[pos] != NULL)
		pos++;
	max = pos;
	pos = search_env(var);
	len = ft_strlen(var);
	free (var);
	if (pos < max)
		return (ft_strdup(get()->env[pos] + len + 1));
	return (NULL);
}

// TODO verificar caso: export ls="ls -la", $ls, "$ls"
// handle $? e $$

char	*expand(char *content, char *new_str, int *i, int *j)
{
	char	*new_str2;
	char	*exp;
	int		start;
	int		var_len;

	start = i[0] + 1;
	var_len = 0;
	while (content[i[0]++] && ft_isalnum(content[i[0]]))
		var_len++;
	exp = replace_env_var(ft_strndup(content + start, var_len));
	new_str2 = ft_strjoin(new_str, exp);
	if (new_str2)
	{
		free (new_str);
		free (exp);
		new_str = calloc(ft_strlen(new_str2) + \
			ft_strlen(content + i[0]) + 1, sizeof(char));
		ft_memcpy(new_str, new_str2, ft_strlen(new_str2));
		free (new_str2);
		j[0] = ft_strlen(new_str);
	}
	return (new_str);
}

char	*handle_quotes(char *content)
{
	char	q;
	int		i;
	int		j;
	char	*new_str;

	q = 0;
	i = 0;
	j = 0;
	new_str = calloc(ft_strlen(content) + 1, sizeof(char));
	while (content[i])
	{
		if ((content[i] == '\"' || content[i] == '\'') && q == 0)
			q = content[i++];
		else if (content[i] == q)
		{
			q = 0;
			i++;
		}
		else if (content[i] != '$' || (content[i] == '$' && q == '\''))
			new_str[j++] = content[i++];
		if (content[i] == '$' && q != '\'')
			new_str = expand(content, new_str, &i, &j);
	}
	return (new_str);
}

void	quote_and_expand(t_list *tokens)
{
	t_list	*tmp;
	char	*old_str;

	tmp = tokens;
	while (tokens)
	{
		old_str = tokens->content;
		tokens->content = handle_quotes(tokens->content);
		free (old_str);
		tokens = tokens->next;
	}
	tokens = tmp;
}
