#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define the structure for t_tokens
typedef struct s_tokens {
    char **tokens;
} t_tokens;

// Mocked function for ft_isquote
bool ft_isquote(int c) {
    return (c == '\'' || c == '\"');
}

// Mocked function for lenquote
int lenquote(char *line) {
    int i;
    char c;

    c = line[0];
    i = 1;
    while (line[i] != '\0') {
        if (line[i] == c)
            return (i + 1);
        i++;
    }
    return (0);
}
int	count_quote(char *token)
{
	int	i;
	int qc;

	i = 0;
	qc = 0;
	
	while (token[i])
	{
		if (ft_isquote(token[i]))
		{
			printf("quote length = %d \n", lenquote(&(token[i])));
			i += lenquote(&(token[i]));
			qc += 2;
		}
		else
			i++;
	}
	return (qc);
}
/*easy version*/
char	*qt_fixed_string(char *token, int *cq, int *j)
{
	int open_qt;
	char *new_str;
    int limiter;
    int i;

    limiter = *cq;
    i = *j;
    // start_len = 0;
	new_str = (char *)calloc(sizeof(char), (strlen(token) - 2));
    
	
	printf("new_str length = %lu \n token_len = %lu \n", strlen(token) - 2, strlen(token));
    while (!(ft_isquote(token[i])) && token[i])
        i++;
	if (ft_isquote(token[i]))
	{
		printf("lenquote = %d \n", lenquote(&(token[i])));
        memcpy(new_str, token, i);
        printf("new_string (memcpy) = %s\n", new_str);
		memcpy(new_str + strlen(new_str), &(token[i]) + 1, lenquote(&(token[i])) - 2);
        printf("new_string (strlcat) = %s\n", new_str);
        *j = strlen(new_str);
        printf("(before lenquote addition)length of i = %d, token_length = %lu\n", i, strlen(token));
	    i += lenquote(&(token[i]));
        printf("length of i = %d, token_length = %lu\n", i, strlen(token));
        memcpy(new_str + *j, &(token[i]), strlen(token) - i);
        printf("new_string (strlcat2) = %s\n", new_str);
        printf("token(end of function) = %s\n", token);
        limiter -= 2;      
	}
    // memcpy(new_str + strlen(new_str), "\0", 1);
    // *j = i;
    *cq = limiter;
	return (new_str);
}

// char	*qt_fixed_string(char *token, int cq)
// {
// 	int open_qt;
// 	int i;
// 	char *new_str;
//     int limiter;

// 	i = 0;
//     limiter = cq;
// 	new_str = (char *)malloc(sizeof(char) * (strlen(token) - cq));
	
// 	printf("new_str length = %lu \n token_len = %lu \n", strlen(token) - cq, strlen(token));
// 	while (limiter > 0)
// 	{
// 		if (ft_isquote(token[i]))
// 		{
// 			printf("lenquote = %d \n", lenquote(&(token[i])));
//             if (limiter == cq)
//                 memcpy(new_str, token, i);
//             printf("new_string (memcpy) = %s\n", new_str);
// 			memcpy(new_str + strlen(new_str), &(token[i]) + 1, lenquote(&(token[i])) - 2);
//             printf("new_string (strlcat) = %s\n", new_str);
// 		    i += lenquote(&(token[i]));
//             // if (limiter == cq)
//             printf("length of i = %d, token_length = %lu\n", i, strlen(token));
//                 memcpy(new_str + strlen(new_str), &(token[i]), strlen(token) - i);
//             // else
//                 // memcpy(new_str + strlen(new_str), &(token[i]), ); 
//             printf("new_string (strlcat2) = %s\n", new_str);
//             /*Using this method doesn't work bc quotes in quotes*/
//             // token = new_str;
//             printf("token = %s\n", token);
//             limiter -= 2;
//             // if (limiter > 0)
//             //     new_str = (char *)calloc(sizeof(char), (strlen(token) - cq));
        
// 		}
// 		else
//             i++;
// 	}
//     // memcpy(new_str + strlen(new_str), &(token[i]), strlen(token) - i);
// 	// free(token);
// 	return (new_str);
// }

// Mocked function for quote_trim
bool quote_trim(t_tokens *tokens) {
    int quote_count;
    char *tmp_token;
    int i;
    int j;

    i = 0;
    
    while (tokens->tokens[i]) {
        quote_count = count_quote(tokens->tokens[i]);
		printf("bitch1\n");
		printf("quote count = %d\n", quote_count);
        j = 0;
        while (quote_count > 0) {
			printf("bitch2\n");
            tmp_token = qt_fixed_string(tokens->tokens[i], &quote_count, &j);
            printf("token_result = %s || its length = %lu\n", tmp_token, strlen(tmp_token));
			printf("bitch3\n");
            if (!(tokens->tokens[i])) {
                // Handle error and free resources
                return false; // Indicate failure
            }
            free(tokens->tokens[i]);
            tokens->tokens[i] = tmp_token;
            printf("token_result(tok) = %s || its length = %lu\n", tokens->tokens[i], strlen(tokens->tokens[i]));
            // tmp_token = NULL;
            // free(tmp_token);
        }
        i++;
    }
    return true; // Indicate success
}

// int main() {
//     // Sample tokens with quotes
//     char *sample_tokens[] = {
//         "This is' a \"bitch\" as's'hole str'ing",
//         "Another 'quoted' one",
//         "Wacka cwafej ''fe ''fexexs",
//         NULL
//     };
// 	printf("bitch\n");
//     // Create a t_tokens structure
//     t_tokens tokens;
//     tokens.tokens = sample_tokens;

//     // Call the quote_trim function to remove quotes
//     if (quote_trim(&tokens)) {
//         // Print the modified token strings
//         printf("%s \n", tokens.tokens[0]);
//         int i = 0;
//         while (tokens.tokens[i]) {
//             printf("Modified Token %d: %s\n", i, tokens.tokens[i]);
//             i++;
//         }
//     } else {
//         printf("quote_trim failed.\n");
//     }

//     // Clean up: Free memory if necessary
//     // ...

//     return 0;
// }

/*Better Main*/
int main() {
    // Sample tokens with quotes
    char *sample_tokens[] = {
        "This is' a \"bitch\" as's'hole str'ing",
        "Another 'quoted' one",
        "Wacka cwafej ''fe ''fexexs",
        NULL
    };

    // Create a t_tokens structure
    t_tokens tokens;

    // Count the number of tokens
    int num_tokens = 0;
    while (sample_tokens[num_tokens] != NULL) {
        num_tokens++;
    }

    // Allocate memory for token strings in tokens.tokens
    tokens.tokens = (char **)malloc(sizeof(char *) * (num_tokens + 1));

    if (tokens.tokens != NULL) {
        for (int i = 0; i < num_tokens; i++) {
            // Allocate memory for the current token string and copy it
            tokens.tokens[i] = (char *)malloc(strlen(sample_tokens[i]) + 1);
            if (tokens.tokens[i] != NULL) {
                strcpy(tokens.tokens[i], sample_tokens[i]);
            } else {
                // Handle memory allocation error
                // Free previously allocated memory and exit
                for (int j = 0; j < i; j++) {
                    free(tokens.tokens[j]);
                }
                free(tokens.tokens);
                printf("Memory allocation error.\n");
                return 1;
            }
        }
        // Null-terminate the tokens.tokens array
        tokens.tokens[num_tokens] = NULL;

        // Call the quote_trim function to remove quotes
        if (quote_trim(&tokens)) {
            // Print the modified token strings
            int i = 0;
            while (tokens.tokens[i] != NULL) {
                printf("Modified Token %d: %s\n", i, tokens.tokens[i]);
                i++;
            }
        } else {
            printf("quote_trim failed.\n");
        }

        // Free memory for token strings
        for (int i = 0; i < num_tokens; i++) {
            free(tokens.tokens[i]);
        }
        // Free memory for the tokens.tokens array itself
        free(tokens.tokens);
    } else {
        // Handle memory allocation error
        printf("Memory allocation error.\n");
        return 1;
    }

    return 0;
}
