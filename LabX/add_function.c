#include <stdio.h>

// Function to add three numbers
void add(int *a, int *b, int *c, int *result) {
    *result = *a + *b + *c;
}

int main() {
    int a, b, c, result;

    printf("Enter three integers: ");
    scanf("%d %d %d", &a, &b, &c);

    add(&a, &b, &c, &result);

    printf("The sum is: %d\n", result);

    return 0;
}
