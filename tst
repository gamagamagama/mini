int main(int argc, char **argv, char **envp) {
    char        *input;
    char        *prompt;
    t_ast_node  *root;
    int         status;
    t_env       *env;

    (void)argc;
    (void)argv;
    env = init_env(envp);
    setup_sig_handler(SIG_REAL);

    while (1) {
        prompt = get_prompt(env);
        input = readline(prompt);
        free(prompt);

        if (!input) {
            setup_sig_handler(SIG_VIRTUAL_CTRL_D);
            continue;
        }
        if (ft_strcmp(input, "exit") == 0) {
            free(input);
            break;
        }
        if (*input)
            add_history(input);
        else {
            free(input);
            continue;  // Skip processing if input is empty
        }

        print_transient_prompt(input);

        env->tokenizer->tokens = tokenize(env->tokenizer, input);
        if (!env->tokenizer->tokens) {  // Handle invalid tokenization
            fprintf(stderr, "Error: Invalid input detected.\n");
            free(input);
            continue;
        }

        root = parse(env->tokenizer);
        if (!root) {  // Handle parsing failure
            fprintf(stderr, "Error: Syntax error.\n");
            free_tokens(env->tokenizer);
            free(input);
            continue;
        }

        debug_ast(root);
        status = execute_ast(env, root);

        free_tokens(env->tokenizer);
        free_ast(root);
        env->last_exit_code = status;

        printf("Command return value: %d\n", status);
        free(input);
    }

    free_env(env);
    rl_clear_history();
    rl_cleanup_after_signal();
    return 0;
}