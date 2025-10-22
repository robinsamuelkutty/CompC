#include <stdio.h>
#include <string.h>

#define MAX 100

char input[MAX], stack[MAX];
int i = 0, j = 0;  // i = stack top index, j = input index
int len;

void check();
void print_status(const char* action);

int main() {
    printf("GRAMMAR:\n E -> E + E\n E -> E * E\n E -> (E)\n E -> id\n");
    printf("Enter input string: ");
    scanf("%s", input);
    len = strlen(input);

    printf("\nStack\t\tInput\t\tAction\n");

    i = 0;  // stack pointer
    j = 0;  // input pointer

    while (j < len) {
        // Shift step
        if (input[j] == 'i' && input[j + 1] == 'd') {
            // Shift 'id' as one token
            stack[i++] = 'i';
            stack[i++] = 'd';
            stack[i] = '\0';

            // Mark input chars as processed (optional)
            input[j] = input[j + 1] = ' ';
            j += 2;

            print_status("Shift id");
        } else if (input[j] != ' ') {
            // Shift single character (operator or parentheses)
            stack[i++] = input[j];
            stack[i] = '\0';
            input[j] = ' ';
            j++;

            print_status("Shift symbol");
        } else {
            j++;  // skip spaces if any
            continue;
        }

        // Try to reduce after every shift
        check();
    }

    // Final stack status
    if (strcmp(stack, "E") == 0) {
        printf("\nInput string is Accepted.\n");
    } else {
        printf("\nInput string is Rejected.\n");
    }

    return 0;
}

void print_status(const char* action) {
    printf("%-16s %-16s %-s\n", stack, input, action);
}

// Try reductions repeatedly until no more possible
void check() {
    int changed;
    do {
        changed = 0;

        // Reduce id -> E
        for (int k = 0; k < i - 1; k++) {
            if (stack[k] == 'i' && stack[k + 1] == 'd') {
                stack[k] = 'E';
                // Shift rest left by 1
                for (int m = k + 1; m < i - 1; m++) {
                    stack[m] = stack[m + 1];
                }
                i--;
                stack[i] = '\0';

                print_status("Reduce id -> E");
                changed = 1;
                break;
            }
        }
        if (changed) continue;

        // Reduce E+E -> E
        for (int k = 0; k < i - 2; k++) {
            if (stack[k] == 'E' && stack[k + 1] == '+' && stack[k + 2] == 'E') {
                stack[k] = 'E';
                // Shift left by 2
                for (int m = k + 1; m < i - 2; m++) {
                    stack[m] = stack[m + 2];
                }
                i -= 2;
                stack[i] = '\0';

                print_status("Reduce E+E -> E");
                changed = 1;
                break;
            }
        }id+id*id
        if (changed) continue;

        // Reduce E*E -> E
        for (int k = 0; k < i - 2; k++) {
            if (stack[k] == 'E' && stack[k + 1] == '*' && stack[k + 2] == 'E') {
                stack[k] = 'E';
                // Shift left by 2
                for (int m = k + 1; m < i - 2; m++) {
                    stack[m] = stack[m + 2];
                }
                i -= 2;
                stack[i] = '\0';

                print_status("Reduce E*E -> E");
                changed = 1;
                break;
            }
        }
        if (changed) continue;

        // Reduce (E) -> E
        for (int k = 0; k < i - 2; k++) {
            if (stack[k] == '(' && stack[k + 1] == 'E' && stack[k + 2] == ')') {
                stack[k] = 'E';
                // Shift left by 2
                for (int m = k + 1; m < i - 2; m++) {
                    stack[m] = stack[m + 2];
                }
                i -= 2;
                stack[i] = '\0';
                

                print_status("Reduce (E) -> E");
                changed = 1;
                break;
            }
        }

    } while (changed);
}

