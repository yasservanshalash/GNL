#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

char *get_next_line(int fd)
{
    char *line;
    char *chunk;
    static char *leftover = NULL;
    int i;
    int j;
    int k;
    int read_chars;

    line = calloc(BUFFER_SIZE, sizeof(char));
    chunk = calloc(BUFFER_SIZE + 1, sizeof(char)); // +1 for null-termination
    i = 0;
    j = 0;
    k = 0;
    if (line == NULL || chunk == NULL)
        return NULL;
    if (leftover != NULL && (strlen(leftover) > 0))
    {
        if (!strchr(leftover, '\n'))
        {
            line = ft_strjoin(line, leftover);
            i += strlen(leftover);
        }
        else
        {
            while (leftover[k] != '\n')
            {
                line[i] = leftover[k];
                i++;
                k++;
            }
            line[i] = '\n';
            i++;
            leftover = strdup(leftover + k + 1);
            return line;
        }
    } 
    while ((read_chars = read(fd, chunk, BUFFER_SIZE)) > 0)
    {
        chunk[read_chars] = '\0'; // null-terminate the chunk
        if (!strchr(chunk, '\n'))
        {
            line = ft_strjoin(line, chunk);
            i += strlen(chunk);
        }
        else
        {
            while (j < read_chars && chunk[j] != '\n')
            {
                line[i] = chunk[j];
                i++;
                j++;
            }
            if (j < read_chars)
            {
                line[i] = '\n';
                i++;
                j++;
            }
            free(leftover);
            leftover = strdup(chunk + j);
            break;
        }
    }
    free(chunk);
    if (i > 0)
        return (line);
    else
        return (NULL);
}

// int main(void)
// {
//     int fd;

//     fd = open("text.txt", O_RDONLY);
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));

//     close(fd);
//     return 0;
// }
// int main(void)
// {
//     int fd;

//     fd = open("text.txt", O_RDONLY);
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     close(fd);
//     return 0;
// }


// #include "get_next_line.h"
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 7
// #endif

// char *get_next_line(int fd)
// {
//     char *line;
//     char *chunk;
//     static char *leftover = NULL;
//     int i;
//     int j;
//     int k;

//     line = calloc(1024, sizeof(char));
//     chunk = calloc(BUFFER_SIZE + 1, sizeof(char));
//     i = 0;
//     j = 0;
//     k = 0;
//     if (line == NULL || chunk == NULL)
//         return NULL;
//     if (leftover != NULL && (strlen(leftover) > 0))
//     {
//         if (!strchr(leftover, '\n'))
//         {
//             strcat(line, leftover);
//             i += strlen(leftover);
//         }
//         else
//         {
//             while (leftover[k] != '\n')
//             {
//                 line[i] = leftover[k];
//                 i++;
//                 k++;
//             }
//             line[i] = '\n';
//             i++;
//             leftover = strdup(leftover + k + 1);
//             return line;
//         }
//     } 
//     while ((read(fd, chunk, BUFFER_SIZE)) > 0)
//     {
//         chunk[(int)strlen(chunk)] = '\0';
//         if (!strchr(chunk, '\n'))
//         {
//             strcat(line, chunk);
//             i += strlen(chunk);
//         }
//         else
//         {
//             while (j < (int)strlen(chunk) && chunk[j] != '\n')
//             {
//                 line[i] = chunk[j];
//                 i++;
//                 j++;
//             }
//             if (j < (int)strlen(chunk))
//             {
//                 line[i] = '\n';
//                 i++;
//                 j++;
//             }
//             free(leftover);
//             leftover = strdup(chunk + j);
//             break;
//         }
//     }
//     free(chunk);
//     if (i > 0)
//         return (line);
//     else
//         return (NULL);
// }