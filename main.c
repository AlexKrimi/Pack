#include "PackReader.h"

static char child_stack[STACK_SIZE];

static int child_fn(void) {
    printf("Clone internal PID: %ld\n", (long) getpid());
    pid_t child_pid = fork();
    if (child_pid) {
        printf("Clone fork child PID: %ld\n", (long) child_pid);

        FILE *fp;

        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        fp = fopen("Packfile", "r");
        if (fp == NULL)
            exit(EXIT_FAILURE);

        while ((read = getline(&line, &len, fp)) != -1) {
            if (strncmp(line, "#bash", strlen("#bash")) == 0){
                printf("@@@@@@@@@@@@@@@@@@@@@@@@@  %s\n", line);
            }
            system(line);
        }
        fclose(fp);



    } else {
        printf("PARENT PROCESS");
    }
    _exit(EXIT_SUCCESS);
}


int main(void) {
    pid_t child_pid = clone(child_fn, child_stack + STACK_SIZE, CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWNET | SIGCHLD,
                            NULL);
    printf("clone() = %ld\n", (long) child_pid);
//    system("mount --make-private -o remount /");
//    system("mount -t proc proc /proc --make-private");
    waitpid(child_pid, NULL, 0);
//    system("mount --make-private -o remount /");
//    system("umount /proc");
    _exit(EXIT_SUCCESS);
}

char **fileReader(char *filepath) {
    int lines_allocated = 1024;
    int max_line_len = 1024;

    /* Allocate lines of text */
    char **words = (char **) malloc(sizeof(char *) * lines_allocated);
    if (words == NULL) {
        fprintf(stderr, "Out of memory (1).\n");
        exit(1);
    }

    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        fprintf(stderr, "ErrorR opening file.\n");
        exit(2);
    }
    int i;
    for (i = 0; 1; i++) {
        int j;

        /* Have we gone over our line allocation? */
        if (i >= lines_allocated) {
            int new_size;

            /* Double our allocation and re-allocate */
            new_size = lines_allocated * 2;
            words = (char **) realloc(words, sizeof(char *) * new_size);
            if (words == NULL) {
                fprintf(stderr, "Out of memory.\n");
                exit(3);
            }
            lines_allocated = new_size;
        }
        /* Allocate space for the next line */
        words[i] = malloc(max_line_len);
        if (words[i] == NULL) {
            fprintf(stderr, "Out of memory (3).\n");
            exit(4);
        }
        if (fgets(words[i], max_line_len - 1, fp) == NULL)
            break;

        /* Get rid of CR or LF at end of line */
        for (j = strlen(words[i]) - 1; j >= 0 && (words[i][j] == '\n' || words[i][j] == '\r'); j--);
        words[i][j + 1] = '\0';
    }
    /* Close file */
    fclose(fp);

    int j;
    for (j = 0; j < i; j++)
        printf("%s\n", words[j]);

    /* Good practice to free memory */
//    for (;i>=0;i--)
//        free(words[i]);
//    free(words);
    return words;
}

