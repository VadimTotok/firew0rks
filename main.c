#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

int count_lines(const char *str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            count++;
        }
    }

    return count;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("\n");
        printf("Play text art animations in the terminal\n\n");
        printf("Usage: %s <folder> <loops>\n", argv[0]);
        printf("\t<folder>\tFolder containing text art frames\n");
        printf("\t<loops>\t\tNumber of times to loop the animation or use -1 to loop until the user terminates the program\n");
        printf("\n");

        return 0;
    }

    char *folder_name = argv[1];
    int loops = atoi(argv[2]);

    DIR *dir = opendir(folder_name);
    if (dir == NULL)
    {
        printf("%s could not be found\n", folder_name);

        return 0;
    }

    closedir(dir);

    bool files_exist = true;
    int num_found = 0;
    char **text_files = NULL;
    int text_files_count = 0;

    while (files_exist)
    {
        char file_name[256];
        snprintf(file_name, sizeof(file_name), "%s/%d.txt", folder_name, num_found);

        FILE *fp = fopen(file_name, "r");
        if (fp != NULL)
        {
            fseek(fp, 0, SEEK_END);
            long file_size = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            char *file_content = (char *)malloc(file_size + 1);
            if (file_content == NULL)
            {
                perror("Memory allocation failed");
                fclose(fp);

                return 1;
            }

            size_t bytes_read = fread(file_content, 1, file_size, fp);
            if (bytes_read < file_size)
            {
                free(file_content);
                fclose(fp);
                printf("Error reading file: %s\n", file_name);

                return 1;
            }

            file_content[bytes_read] = '\0';

            text_files = (char **)realloc(text_files, sizeof(char *) * (text_files_count + 1));
            if (text_files == NULL)
            {
                perror("Failed to allocate more memory for text_files");
                fclose(fp);

                return 1;
            }

            text_files[text_files_count] = file_content;
            text_files_count++;

            num_found++;
            fclose(fp);
        }
        else
        {
            files_exist = false;
        }
    }

    if (text_files_count == 0)
    {
        printf("%s did not have text art files\n", folder_name);

        return 0;
    }

    int num_lines = count_lines(text_files[0]) + 1;
    char backspace_adjust[100];

    strcpy(backspace_adjust, "");
    for (int j = 0; j < num_lines; j++)
    {
        strcat(backspace_adjust, "\033[A");
    }

    int i = 0;
    bool first = true;
    while (i < loops || loops == -1)
    {
        for (int j = 0; j < text_files_count; j++)
        {
            if (!first)
            {
                printf("%s", backspace_adjust);
            }

            printf("%s", text_files[j]);
            first = false;

            struct timespec sleep_time;
            sleep_time.tv_sec = 0;
            sleep_time.tv_nsec = 50000000;
            nanosleep(&sleep_time, NULL);
        }

        i++;
    }

    for (int j = 0; j < text_files_count; j++)
    {
        free(text_files[j]);
    }

    free(text_files);

    return 0;
}