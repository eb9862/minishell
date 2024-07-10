#include "minishell.h"

t_env_node *create_env_node(char *content)
{
    t_env_node *node;

    node = (t_env_node *)malloc(sizeof(t_env_node));
    if (!node)
        return (0);
    node -> content = content;
    node -> next = NULL;
    return (node);
}

void clear_env_list(t_env_list *env_list)
{
    t_env_node *now;
    t_env_node *tmp;

    now = env_list -> head;
    if (now)
    {
        while (now)
        {
            tmp = now -> next;
            free(now);
            now = tmp;
        }
    }
    free(env_list);
}

void add_node_last(t_env_list *env_list, t_env_node *node)
{
    t_env_node *tmp;

    if (!env_list || !node)
        return ;
    if (!env_list -> head)
    {
        env_list -> head = node;
        env_list -> tail = node;
    }
    else
    {
        tmp = env_list -> head;
        while(tmp -> next)
            tmp = tmp -> next;
        tmp -> next = node;
        env_list -> tail = node;
    }
}

t_env_list *init_env(char **envp)
{
    int i;
    t_env_list *env_list;
    t_env_node *env_node;
    
    i = 0;
    env_list = (t_env_list *)malloc(sizeof(t_env_list));
    if (!env_list)
        return (0);
    while (envp[i])
    {
        env_node = create_env_node(envp[i]);
        if (!env_node)
        {
            clear_env_list(env_list);
            return (0);
        }
        add_node_last(env_list, env_node);
        i++;
    }
    return (env_list);
}
