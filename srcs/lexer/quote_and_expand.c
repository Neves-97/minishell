#include "minishell.h"

char	*replace_env_var(char *var)
{
	int	pos;
	int	max;
	int	len;

	if (var[0] == '?')
		return (ft_itoa(get()->exit_status));
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

char	*expand(char *cont, char *ns, int *i, int *j)
{
	char	*n2;
	char	*exp;
	int		start;
	int		var_len;

	start = i[0] + 1;
	var_len = 0;
	while (cont[i[0]++] && (ft_isalnum(cont[i[0]]) || cont[i[0]] == '?'))
	{
		var_len++;
		if (cont[i[0] + 1] == '?')
			break ;
	}
	exp = replace_env_var(ft_strndup(cont + start, var_len));
	n2 = ft_strjoin(ns, exp);
	if (n2)
	{
		free (ns);
		free (exp);
		ns = calloc(ft_strlen(n2) + ft_strlen(cont + i[0]) + 1, sizeof(char));
		ft_memcpy(ns, n2, ft_strlen(n2));
		free (n2);
		j[0] = ft_strlen(ns);
	}
	return (ns);
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
		else if (content[i] != '$' || (content[i] == '$' && q == '\'') || \
		(!ft_isalnum(content[i + 1]) && content[i + 1] != '?'))
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
