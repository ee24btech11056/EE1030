#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITER 1000//here we are defining global variables for further uses
#define EPS 1e-10

void hessenbergReduction(int n, double A[n][n]);
void QR_Decomposition(int n, double A[n][n], double Q[n][n], double R[n][n]);//these are the function prototypes
void matrixMultiply(int n, double A[n][n], double B[n][n], double C[n][n]);
double Norm(int n, double A[n][n]);
void finding_eigenvalues(int n, double A[n][n], double eigenvalues[n]);

int main() {
    int n;
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);

    double A[n][n];
    printf("Enter the matrix elements row by row:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Performing Hessenberg reduction...\n");//we are calling all functions required for finding eigenvalues
    hessenbergReduction(n, A);

    double eigenvalues[n];
    finding_eigenvalues(n, A, eigenvalues);
    printf("Eigenvalues:\n");
    for (int i = 0; i < n; i++) {
        printf("%lf\n", eigenvalues[i]);
    }

    return 0;
}

void hessenbergReduction(int n, double A[n][n]) {
    for (int p = 0; p < n - 2; p++) {
        double norm = 0.0;

        for (int i = p + 1; i < n; i++) {
            norm += A[i][p] * A[i][p];
        }
        norm = sqrt(norm);

        double alpha = (A[p + 1][p] > 0) ? -norm : norm;

        double v[n];
        for (int i = 0; i < n; i++) v[i] = 0.0;//we are defining a householder vector v

        v[p + 1] = A[p + 1][p] - alpha;
        for (int i = p + 2; i < n; i++) {
            v[i] = A[i][p];
        }

        double v_norm = 0.0;
        for (int i = p + 1; i < n; i++) {//here we are finding norm of v to normalise the vector v 
            v_norm += v[i] * v[i];
        }
        v_norm = sqrt(v_norm);

        if (fabs(v_norm) > EPS) {
            for (int i = p + 1; i < n; i++) {//here we are comparing with very small value EPS to avoid division by a very small number, which could cause numerical instability 
                v[i] /= v_norm;
            }
        }

        for (int j = p; j < n; j++) {
            double dot = 0.0;
            for (int i = p + 1; i < n; i++) {
                dot += v[i] * A[i][j];
            }
            for (int i = p + 1; i < n; i++) {//by using householder reflections we are turning the matrix into hessenberg form
                A[i][j] -= 2 * v[i] * dot;
            }
        }

        for (int i = 0; i < n; i++) {
            double dot = 0.0;
            for (int j = p + 1; j < n; j++) {
                dot += v[j] * A[i][j];
            }
            for (int j = p + 1; j < n; j++) {
                A[i][j] -= 2 * v[j] * dot;
            }
        }
    }
}

void QR_Decomposition(int n, double A[n][n], double Q[n][n], double R[n][n]) {
    double V[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            V[i][j] = A[i][j];
            Q[i][j] = 0.0;
            R[i][j] = 0.0;
        }
    }

    for (int k = 0; k < n; k++) {
        double norm = 0.0;
        for (int i = 0; i < n; i++) {
            norm += V[i][k] * V[i][k];
        }
        norm = sqrt(norm);
        R[k][k] = norm;

        for (int i = 0; i < n; i++) {//here we are using Gram-Schmidt process to perform QR decomposition
            Q[i][k] = V[i][k] / norm;
        }

        for (int j = k + 1; j < n; j++) {
            double dot = 0.0;
            for (int i = 0; i < n; i++) {
                dot += Q[i][k] * V[i][j];
            }
            R[k][j] = dot;
            for (int i = 0; i < n; i++) {
                V[i][j] -= dot * Q[i][k];
            }
        }
    }
}

void matrixMultiply(int n, double A[n][n], double B[n][n], double C[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];//here we are finding multiplication of two matrices
            }
        }
    }
}

double Norm(int n, double A[n][n]) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * A[i][j];//we are finding norm of a matrix
        }
    }
    return sqrt(sum);
}

void finding_eigenvalues(int n, double A[n][n], double eigenvalues[n]) {
    double Q[n][n], R[n][n], temp[n][n];
    int iter = 0;

    while (iter < MAX_ITER) {

        QR_Decomposition(n, A, Q, R);//MAX_ITER is a predefined maximum number of iterations to avoid infinite loops if convergence fails
        matrixMultiply(n, R, Q, temp);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = temp[i][j];
            }
        }

        int converged = 1;
        for (int i = 1; i < n; i++) {
            if (fabs(A[i][i - 1]) > EPS) {
                converged = 0;
                break;
            }
        }
        if (converged) break;  //check if the subdiagonal elements are close to zero.if they are the algorithm has converged.

        iter++;
    }

    for (int i = 0; i < n; i++) {
        eigenvalues[i] = A[i][i];
    }
}

