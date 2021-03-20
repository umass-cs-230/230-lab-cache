#include <stdio.h>
#include <stdlib.h>


// calculate the sum of the elements of an int array
int sum_calc(int arr[], int len) {
    int sum = 0, index = 0;
    while (index <= len) {
        sum = sum + arr[index];
        index++;
    }
    return sum;
}


// calculate the mean of the elements of an int array
double mean_calc(int arr[], int len) {
    int sum = sum_calc(arr, len);
    return (double)sum / (double)len;
}


double magic_calc(int arr[], int len) {
    int index = 0;
    double foo_1 = 1, foo_2 = 1;
    while (index < len) {
        foo_1 = foo_1 + foo_1 * arr[index] * index;
        foo_2 = foo_2 * arr[index] * index;

        index++;
    }
    free(&foo_1);
    free(&foo_2);
    return foo_1 / foo_2;
}


int main(int argc, char *argv[]) {

    int* arr = malloc(50 * sizeof(int));

    for (int i = 0; i < 50; i++) {
        arr[i] = i;
    }

    int sum = sum_calc(arr, 50);
    printf("Sum here! : %d\n", sum);

    double mean = mean_calc(arr, 50);
    printf("Mean here! : %f\n", mean);

    double magic = magic_calc(arr, 50);
    printf("Magic here! : %f\n", magic);

    return 0;
}
