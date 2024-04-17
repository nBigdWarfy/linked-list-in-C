#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 0;
    char strg[n];
    int *pointer = (int)malloc(sizeof(int));

    printf("Enter a number: ");
    scanf("%d", &n);

    for (int i = 0; i <= n; i++) {
        printf("%c\n%p\n%d\n%p\n", strg[i], (void *)&strg[i], pointer, (void *)&pointer[i]);
    }
    free(pointer);
    return 0;
}