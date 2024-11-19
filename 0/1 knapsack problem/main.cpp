#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack(int wr[], int val[], int W, int n) {
    if (n == 0 || W == 0) 
        return 0;

    // If weight of the nth item is less than or equal to W,
    // we can either include it or exclude it from the knapsack
    if (wr[n-1] <= W) {
        return max(
            val[n-1] + knapsack(wr, val, W - wr[n-1], n - 1), // Include the item
            knapsack(wr, val, W, n - 1) // Exclude the item
        );
    } else {
        return knapsack(wr, val, W, n - 1); // Exclude the item
    }
}

int main() {
    int n, W;
    
    printf("Enter number of items: ");
    scanf("%d", &n);
    
    int wr[n], val[n];
    
    printf("Enter the weights of the items: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &wr[i]);
    }
    
    printf("Enter the values of the items: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }
    
    printf("Enter the maximum weight capacity: ");
    scanf("%d", &W);
    
    int maxProfit = knapsack(wr, val, W, n);
    
    printf("Maximum profit: %d\n", maxProfit);
    
    return 0;
}

/*
Sample Input:
Enter number of items: 4
Enter the weights of the items: 1 3 4 5
Enter the values of the items: 1 4 5 7
Enter the maximum weight capacity: 7
Output:
Maximum profit: 9
*/
