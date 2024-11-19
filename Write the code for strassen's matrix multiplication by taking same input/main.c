#include<stdio.h>
#include<stdlib.h>
#define n 4
void add(int a[n][n], int b[n][n], int c[n][n], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}
void subtract(int a[n][n], int b[n][n], int c[n][n], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
}
void strassen(int a[n][n], int b[n][n], int c[n][n], int size) {
    if (size == 2) {// Base case: 2x2 matrix multiplication
        int p1 = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
        int p2 = (a[1][0] + a[1][1]) * b[0][0];
        int p3 = a[0][0] * (b[0][1] - b[1][1]);
        int p4 = a[1][1] * (b[1][0] - b[0][0]);
        int p5 = (a[0][0] + a[0][1]) * b[1][1];
        int p6 = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1]);
        int p7 = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);

        c[0][0] = p1 + p4 - p5 + p7;
        c[0][1] = p3 + p5;
        c[1][0] = p2 + p4;
        c[1][1] = p1 + p3 - p2 + p6;
    } else {
        int new_size = size / 2;
        int a11[n][n], a12[n][n], a21[n][n], a22[n][n];
        int b11[n][n], b12[n][n], b21[n][n], b22[n][n];
        int c11[n][n], c12[n][n], c21[n][n], c22[n][n];
        int p1[n][n], p2[n][n], p3[n][n], p4[n][n], p5[n][n], p6[n][n], p7[n][n];
        int temp1[n][n], temp2[n][n];

        // Dividing matrices into sub-matrices
        for (int i = 0; i < new_size; i++) {
            for (int j = 0; j < new_size; j++) {
                a11[i][j] = a[i][j];
                a12[i][j] = a[i][j + new_size];
                a21[i][j] = a[i + new_size][j];
                a22[i][j] = a[i + new_size][j + new_size];

                b11[i][j] = b[i][j];
                b12[i][j] = b[i][j + new_size];
                b21[i][j] = b[i + new_size][j];
                b22[i][j] = b[i + new_size][j + new_size];
            }
        }

        // P1 = (A11 + A22) * (B11 + B22)
        add(a11, a22, temp1, new_size);
        add(b11, b22, temp2, new_size);
        strassen(temp1, temp2, p1, new_size);

        // P2 = (A21 + A22) * B11
        add(a21, a22, temp1, new_size);
        strassen(temp1, b11, p2, new_size);

        // P3 = A11 * (B12 - B22)
        subtract(b12, b22, temp1, new_size);
        strassen(a11, temp1, p3, new_size);

        // P4 = A22 * (B21 - B11)
        subtract(b21, b11, temp1, new_size);
        strassen(a22, temp1, p4, new_size);

        // P5 = (A11 + A12) * B22
        add(a11, a12, temp1, new_size);
        strassen(temp1, b22, p5, new_size);

        // P6 = (A21 - A11) * (B11 + B12)
        subtract(a21, a11, temp1, new_size);
        add(b11, b12, temp2, new_size);
        strassen(temp1, temp2, p6, new_size);

        // P7 = (A12 - A22) * (B21 + B22)
        subtract(a12, a22, temp1, new_size);
        add(b21, b22, temp2, new_size);
        strassen(temp1, temp2, p7, new_size);

        // Calculating C11, C12, C21, C22
        add(p1, p4, temp1, new_size);
        subtract(temp1, p5, temp2, new_size);
        add(temp2, p7, c11, new_size);

        add(p3, p5, c12, new_size);
        add(p2, p4, c21, new_size);

        add(p1, p3, temp1, new_size);
        subtract(temp1, p2, temp2, new_size);
        add(temp2, p6, c22, new_size);
        
        // Combine the results into matrix C
        for (int i = 0; i < new_size; i++) {
            for (int j = 0; j < new_size; j++) {
                c[i][j] = c11[i][j];
                c[i][j + new_size] = c12[i][j];
                c[i + new_size][j] = c21[i][j];
                c[i + new_size][j + new_size] = c22[i][j];
            }
        }
    }
}
int main() {
    int a[n][n] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int b[n][n] = {
        {16, 15, 14, 13},
        {12, 11, 10, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };
    int c[n][n];
    strassen(a, b, c, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", c[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}


/*
Strassen's algorithm splits each matrix into four submatrices and recursively computes seven matrix products (P1 through P7).
Base case is a 2x2 matrix multiplication, which is handled directly.
The add and subtract functions are used to perform matrix addition and subtraction, which are essential steps in the Strassen algorithm.
For a 4x4 matrix, Strassen's algorithm reduces the multiplication complexity compared to the standard O(n³) approach.

In the above method, we do 8 multiplications for matrices of size N/2 x N/2 and 4 additions. Addition of two matrices takes O(n^2) time. So the time complexity can be written as 
T(N) = 8T(N/2) + O(N2)  

From Master's Theorem, time complexity of above method is O(N3)

Time Complexity of Strassen’s Method
Addition and Subtraction of two matrices takes O(N^2) time. So time complexity can be written as 
T(N) = 7T(N/2) +  O(N2)
From Master's Theorem, time complexity of above method is 
O(N^Log7) which is approximately O(N^2.8074)


int a[n][n] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};

int b[n][n] = {
    {16, 15, 14, 13},
    {12, 11, 10, 9},
    {8, 7, 6, 5},
    {4, 3, 2, 1}
};
first divides the matrices a and b into four submatrices each.
a11= 1 2
     5 7
a12= 3 4
     7 8
a21= 9 10
     13 14
a22= 11 12 
     15 16
b11= 16 15
     12 11
b12= 14 13
     10 9
b21= 8 7
     4 3
b22= 6 5
     2 1


*/