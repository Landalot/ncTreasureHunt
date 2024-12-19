# include <stdio.h>
# include <stdlib.h>

void newline(int);

int main() {

    void (*funptr)(int) = &newline;

    char *chars = malloc(20*sizeof(char));

    chars[0] = 'c';
    chars[1] = 'a';
    chars[2] = 't';
    chars[3] = 's';
    chars[4] = 0x23;
    chars[19] = 0;

    scanf("%13c", chars + 5);

//     srand(1);
//
//     for (int i = 0; i < 9; i++) {
//         chars[i] = rand() % 100;
//     }

    //free(chars);

    printf(chars);
    (*funptr)(1);
    return 0;

}

void newline(int NumOfLines) {

    for (int i = 0; i < NumOfLines; i++) {
        printf("%c", 10);
    }

}
