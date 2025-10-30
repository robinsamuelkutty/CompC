#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 50
#define MAX_ALPHA  26

struct node {
    int st;
    struct node *link;
};

struct node *transition[MAX_STATES+1][MAX_ALPHA]; // transitions[state][alpha_index]
int e_closure[MAX_STATES+1][MAX_STATES+1];        // closure rows with count at index 0: e_closure[i][0] = size
char alphabet[MAX_ALPHA];
int noalpha, nostate, notransition;

int findalpha(char c) {
    for (int i = 0; i < noalpha; ++i)
        if (alphabet[i] == c) return i;
    return -1;
}

void insert_trantbl(int r, char ch, int s) {
    int j = findalpha(ch);
    if (j == -1) {
        printf("Error: alphabet '%c' not found\n", ch);
        exit(1);
    }
    struct node *temp = malloc(sizeof(struct node));
    if (!temp) { perror("malloc"); exit(1); }
    temp->st = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}

void findclosure_recursive(int x, int sta, int *visited, int eps_index) {
    if (visited[x]) return;
    visited[x] = 1;
    // append x to closure list
    int sz = e_closure[sta][0];
    e_closure[sta][ ++e_closure[sta][0] ] = x;

    // follow epsilon transitions if epsilon exists
    if (eps_index >= 0) {
        struct node *p = transition[x][eps_index];
        while (p) {
            findclosure_recursive(p->st, sta, visited, eps_index);
            p = p->link;
        }
    }
}

void compute_and_print_closures() {
    int eps_index = findalpha('e'); // -1 if epsilon not present
    for (int i = 1; i <= nostate; ++i) {
        // clear closure
        for (int k = 0; k <= nostate; ++k) e_closure[i][k] = 0;
        int visited[MAX_STATES+1] = {0};
        findclosure_recursive(i, i, visited, eps_index);

        // print
        printf("e-closure(q%d) = {", i);
        for (int k = 1; k <= e_closure[i][0]; ++k) {
            printf("q%d", e_closure[i][k]);
            if (k < e_closure[i][0]) printf(", ");
        }
        printf("}\n");
    }
}

int main() {
    // init
    for (int i = 0; i <= MAX_STATES; ++i)
        for (int j = 0; j < MAX_ALPHA; ++j)
            transition[i][j] = NULL;

    printf("Enter number of alphabets (including 'e' for epsilon if present): ");
    if (scanf("%d", &noalpha) != 1) return 1;
    getchar();

    if (noalpha <= 0 || noalpha > MAX_ALPHA) {
        printf("Bad alphabet count (1..%d)\n", MAX_ALPHA); return 1;
    }

    printf("Enter alphabets (one per line or separated by spaces). Example: a b e\n");
    for (int i = 0; i < noalpha; ++i) {
        // read non-space char
        int ch;
        do { ch = getchar(); } while (ch == ' ' || ch == '\n' || ch == '\t');
        alphabet[i] = (char)ch;
        // consume until whitespace or next token (optional)
        while ((ch = getchar()) != EOF && ch != '\n' && ch != ' ' && ch != '\t') ;
    }

    printf("Enter number of states: ");
    if (scanf("%d", &nostate) != 1) return 1;
    if (nostate <= 0 || nostate > MAX_STATES) {
        printf("Bad state count (1..%d)\n", MAX_STATES); return 1;
    }

    printf("Enter number of transitions: ");
    if (scanf("%d", &notransition) != 1) return 1;

    printf("Enter transitions one per line in format: from_state symbol to_state\n");
    printf("Example: 1 a 2    2 e 3\n");
    for (int i = 0; i < notransition; ++i) {
        int r, s; char ch;
        if (scanf(" %d %c %d", &r, &ch, &s) != 3) {
            printf("Bad transition input\n"); return 1;
        }
        if (r < 1 || r > nostate || s < 1 || s > nostate) {
            printf("State numbers must be between 1 and %d\n", nostate); return 1;
        }
        insert_trantbl(r, ch, s);
    }

    printf("\nComputing e-closures...\n");
    compute_and_print_closures();
    return 0;
}
