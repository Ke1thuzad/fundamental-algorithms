#include "main.h"

int compute_norms(VectorArray ***vectors, int vector_amount, int norm_amount, ...) {
    VectorArray **pVectorArray = (VectorArray **)malloc(sizeof(VectorArray *) * norm_amount);
    if (!pVectorArray)
        return throw_err(MEMORY_NOT_ALLOCATED);

    for (int i = 0; i < norm_amount; ++i) {
        pVectorArray[i] = (VectorArray*) malloc(sizeof(VectorArray));
        if (!pVectorArray[i]) {
            free(pVectorArray);
            return throw_err(MEMORY_NOT_ALLOCATED);
        }

        int err = create_vector_arr(5, pVectorArray[i]);
        if (err) {
            free(pVectorArray[i]);
            free(pVectorArray);
            return err;
        }

    }

    VectorArray temp;
    int err = create_vector_arr(vector_amount, &temp);
    if (err) {
        free(pVectorArray);
        return err;
    }

    va_list args;
    va_start(args, norm_amount);

    for (int i = 0; i < vector_amount; ++i) {
        Vector arg = va_arg(args, Vector);
        err = append_vector(&temp, arg);
        if (err) {
            free(pVectorArray);
            va_end(args);
            destroy_vector(&temp);
            return err;
        }
    }

    va_list copy_factor;
    for (int i = 0; i < norm_amount; ++i) {
        norm_func norm = va_arg(args, norm_func);

        double max_norm = -1;

        for (int j = 0; j < vector_amount; ++j) {
            double vector_len;
            if (j != vector_amount - 1) {
                va_copy(copy_factor, args);
                vector_len = norm(temp.val[j], copy_factor);
                va_end(copy_factor);
            } else {
                vector_len = norm(temp.val[j], args);
            }

            if (j == 0) {
                max_norm = vector_len;
            } else if (vector_len > max_norm) {
                max_norm = vector_len;

                destroy_vector(pVectorArray[i]);
                err = create_vector_arr(vector_amount, pVectorArray[i]);
                if (err) {
                    free(pVectorArray);
                    destroy_vector(&temp);
                    va_end(args);
                    return err;
                }
            }

            if (vector_len == max_norm) {
                err = append_vector(pVectorArray[i], temp.val[j]);
                if (err) {
                    free(pVectorArray);
                    destroy_vector(&temp);
                    va_end(args);
                    return err;
                }
            }
        }
    }

    va_end(args);
    destroy_vector(&temp);
    *vectors = pVectorArray;

    return 0;
}

double norm1(Vector vector, va_list factors) {
    double max = vector.coords[0];

    for (int i = 1; i < vector.n; ++i) {
        if (fabs(vector.coords[i]) > max) {
            max = fabs(vector.coords[i]);
        }
    }

    return max;
}

double norm2(Vector vector, va_list factors) {
    double res = 0;
    int p = va_arg(factors, int);
    if (p < 1) {
        p = 1;
    }

    for (int i = 1; i < vector.n; ++i) {
        res += pow(fabs(vector.coords[i]), (double) p);
    }

    res = pow(res, 1.0 / (double) p);

    return res;
}

double norm3(Vector vector, va_list factors) {
    double res = 0;
    double** A = va_arg(factors, double**);

    for (int i = 0; i < vector.n; ++i) {
        for (int j = 0; j < vector.n; ++j) {
            res += A[i][j] * vector.coords[i] * vector.coords[j];
        }
    }

    res = sqrt(res);

    return res;
}

int main() {
    // Test Case 1: 3 vectors and 3 norms
    {
        int n = 3;
        Vector v1 = {3, (double[]){1.0, 7.0, 3.0}};
        Vector v2 = {3, (double[]){-4.0, 5.0, -7.0}};
        Vector v3 = {3, (double[]){-6.0, -2.0, -5.0}};
        double **A = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++) {
            A[i] = (double *)malloc(sizeof(double) * n);
            for (int j = 0; j < n; j++) {
                A[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
        int count_vectors = 3;
        int count_norms = 3;
        int p = 2;
        VectorArray **vectors = NULL;
        int errorMsg = compute_norms(&vectors, count_vectors, count_norms, v1, v2, v3, norm1, norm2, p, norm3, A);
        if (errorMsg) {
            for (int i = 0; i < count_norms; ++i) {
                destroy_vector(vectors[i]);
                free(vectors[i]);
            }
            free(vectors);
            return throw_err(errorMsg);
        }
        for (int i = 0; i < count_norms; ++i) {
            printf("Norm %d:\n", i + 1);
            for (int j = 0; j < vectors[i]->length; ++j) {
                printf("  [");
                for (int k = 0; k < 3; ++k) {
                    printf("%f", vectors[i]->val[j].coords[k]);
                    if (k < 2) printf(", ");
                }
                printf("]\n");
            }
            destroy_vector(vectors[i]);
            free(vectors[i]);
        }
        free(vectors);
        for (int i = 0; i < n; ++i) {
            free(A[i]);
        }
        free(A);
        printf("\n\n");
    }

    // Test Case 2: 2 vectors and 2 norms
    {
        int n = 2;
        Vector v1 = {2, (double[]){1.0, 2.0}};
        Vector v2 = {2, (double[]){3.0, 4.0}};
        double **A = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++) {
            A[i] = (double *)malloc(sizeof(double) * n);
            for (int j = 0; j < n; j++) {
                A[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
        int count_vectors = 2;
        int count_norms = 2;
        int p = 2;
        VectorArray **vectors = NULL;
        int errorMsg = compute_norms(&vectors, count_vectors, count_norms, v1, v2, norm1, norm2, p, norm3, A);
        if (errorMsg) {
            for (int i = 0; i < count_norms; ++i) {
                destroy_vector(vectors[i]);
                free(vectors[i]);
            }
            free(vectors);
            return throw_err(errorMsg);
        }
        for (int i = 0; i < count_norms; ++i) {
            printf("Norm %d:\n", i + 1);
            for (int j = 0; j < vectors[i]->length; ++j) {
                printf("  [");
                for (int k = 0; k < 2; ++k) {
                    printf("%f", vectors[i]->val[j].coords[k]);
                    if (k < 1) printf(", ");
                }
                printf("]\n");
            }
            destroy_vector(vectors[i]);
            free(vectors[i]);
        }
        free(vectors);
        for (int i = 0; i < n; ++i) {
            free(A[i]);
        }
        free(A);
        printf("\n\n");
    }

    // Test Case 3: 4 vectors and 1 norm
    {
        int n = 4;
        Vector v1 = {4, (double[]){1.0, 2.0, 3.0, 4.0}};
        Vector v2 = {4, (double[]){5.0, 6.0, 7.0, 8.0}};
        Vector v3 = {4, (double[]){9.0, 10.0, 11.0, 12.0}};
        Vector v4 = {4, (double[]){13.0, 14.0, 15.0, 16.0}};
        double **A = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++) {
            A[i] = (double *)malloc(sizeof(double) * n);
            for (int j = 0; j < n; j++) {
                A[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
        int count_vectors = 4;
        int count_norms = 1;
        int p = 2;
        VectorArray **vectors = NULL;
        int errorMsg = compute_norms(&vectors, count_vectors, count_norms, v1, v2, v3, v4, norm1, norm2, p, norm3, A);
        if (errorMsg) {
            for (int i = 0; i < count_norms; ++i) {
                destroy_vector(vectors[i]);
                free(vectors[i]);
            }
            free(vectors);
            return throw_err(errorMsg);
        }
        for (int i = 0; i < count_norms; ++i) {
            printf("Norm %d:\n", i + 1);
            for (int j = 0; j < vectors[i]->length; ++j) {
                printf("  [");
                for (int k = 0; k < 4; ++k) {
                    printf("%f", vectors[i]->val[j].coords[k]);
                    if (k < 3) printf(", ");
                }
                printf("]\n");
            }
            destroy_vector(vectors[i]);
            free(vectors[i]);
        }
        free(vectors);
        for (int i = 0; i < n; ++i) {
            free(A[i]);
        }
        free(A);
        printf("\n\n");
    }

    // Test Case 4: 1 vector and 4 norms
    {
        int n = 1;
        Vector v1 = {1, (double[]){1.0}};
        double **A = (double **)malloc(sizeof(double *) * n);
        for (int i = 0; i < n; i++) {
            A[i] = (double *)malloc(sizeof(double) * n);
            for (int j = 0; j < n; j++) {
                A[i][j] = (i == j) ? 1.0 : 0.0;
            }
        }
        int count_vectors = 1;
        int count_norms = 3;
        int p = 2;
        VectorArray **vectors = NULL;
        int errorMsg = compute_norms(&vectors, count_vectors, count_norms, v1, norm1, norm2, p, norm3, A);
        if (errorMsg) {
            for (int i = 0; i < count_norms; ++i) {
                destroy_vector(vectors[i]);
                free(vectors[i]);
            }
            free(vectors);
            return throw_err(errorMsg);
        }
        for (int i = 0; i < count_norms; ++i) {
            printf("Norm %d:\n", i + 1);
            for (int j = 0; j < vectors[i]->length; ++j) {
                printf("  [");
                for (int k = 0; k < 1; ++k) {
                    printf("%f", vectors[i]->val[j].coords[k]);
                }
                printf("]\n");
            }
            destroy_vector(vectors[i]);
            free(vectors[i]);
        }
        free(vectors);
        for (int i = 0; i < n; ++i) {
            free(A[i]);
        }
        free(A);
        printf("\n\n");
    }

    return 0;
}