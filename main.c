#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 1024

typedef struct {
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int num_lines;
} Editor;

void init_editor(Editor *editor) {
    editor->num_lines = 0;
}

void list_lines(Editor *editor) {
    for (int i = 0; i < editor->num_lines; ++i) {
        printf("%d: %s\n", i + 1, editor->lines[i]);
    }
}

void save_to_file(Editor *editor, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("ERROR: Error opening file for writing!");
        return;
    }

    for (int i = 0; i < editor->num_lines; ++i) {
        fprintf(file, "%s\n", editor->lines[i]);
    }
    
    fclose(file);
    printf("Saved as '%s'! Yey!\n", filename);
}

int main(int argc, char *argv[]) {
    Editor editor;
    init_editor(&editor);
    
    if (argc > 1) {
        FILE *edit_file = fopen(argv[1], "r");
        if (edit_file) {
            char line[MAX_LINE_LENGTH];
            while (fgets(line, sizeof(line), edit_file)) {
                line[strlen(line) - 1] = '\0';
                strcpy(editor.lines[editor.num_lines++], line);
                if (editor.num_lines >= MAX_LINES) {
                    printf("Max number of lines reached...\n");
                    break;
                }
            }
            fclose(edit_file);
        } else {
            printf("ERROR: File not found or error opening file.\n");
        }
    }
    
    while (1) {
        printf(": ");
        char command[10];
        if (scanf("%s", command) == EOF) {
            break;
        }   
        if (strcmp(command, "q") == 0) {
            break;
        } else if (strcmp(command, "a") == 0) {
            char line[MAX_LINE_LENGTH];
            getchar();
            while (1) {
                if (fgets(line, sizeof(line), stdin) == NULL) {
                    break;
                }
                if (strcmp(line, ".\n") == 0) {
                    break;
                }
                line[strlen(line) - 1] = '\0';
                strcpy(editor.lines[editor.num_lines++], line);
                if (editor.num_lines >= MAX_LINES) {
                    printf("Max number of lines reached man...\n");
                    break;
                }
            }
        } else if (strcmp(command, "n") == 0) {
            list_lines(&editor);
        } else if (strcmp(command, "w") == 0) {
            char filename[MAX_LINE_LENGTH];
            scanf("%s", filename);
            save_to_file(&editor, filename);
        } else if (strcmp(command, "c") == 0) {
            int line_number;
            scanf("%d", &line_number);
            getchar();
            if (line_number >= 1 && line_number <= editor.num_lines) {
                printf("Editing line %d you messed up. Enter new stuff:\n", line_number);
                if (fgets(editor.lines[line_number - 1], sizeof(editor.lines[line_number - 1]), stdin)) {
                    editor.lines[line_number - 1][strlen(editor.lines[line_number - 1]) - 1] = '\0';
                }
            } else {
                printf("Nope... Wrong invalid line number. Sorry man...\n");
            }
        } else {
            printf("What?\n");
        }
    }
    return 0;
}
