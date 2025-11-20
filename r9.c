

int main() {
    int *arr;
    int i, n = 5;


    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
    printf("Memory allocation failed\n");
    return 1;
    }

    printf("Enter 5 elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Address and value of each element:\n");
    for (i = 0; i < n; i++) {
        printf("Element %d: Address = %p, Value = %d\n", i, (void *)&arr[i], arr[i]);
    }
    return 0;
}
