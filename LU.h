#include <iostream>

using namespace std;



class LU{
    ComplexMatrix<float> mat, inverse, lower, upper, Z, I;
    int N;

public:
    LU(const ComplexMatrix<float> &mat, const ComplexMatrix<float> &inverse, const ComplexMatrix<float> &lower,
       const ComplexMatrix<float> &upper, const ComplexMatrix<float> &z, const ComplexMatrix<float> &i, int n) : mat(
            mat), inverse(inverse), lower(lower), upper(upper), Z(z), I(i), N(n) {}


    void lu()
    {
        int i = 0, j = 0, k = 0;
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (j < i)
                    lower[j][i] = Complex<float>(0);
                else
                {
                    lower[j][i] = mat[j][i];
                    for (k = 0; k < i; k++)
                    {
                        lower[j][i] = lower[j][i] - lower[j][k] * upper[k][i];
                    }
                }
            }
            for (j = 0; j < N; j++)
            {
                if (j < i)
                    upper[i][j] = Complex<float>(0);
                else if (j == i)
                    upper[i][j] = Complex<float>(1);
                else
                {
                    upper[i][j] = mat[i][j] / lower[i][i];
                    for (k = 0; k < i; k++)
                    {
                        upper[i][j] = upper[i][j] - ((lower[i][k] * upper[k][j]) / lower[i][i]);
                    }
                }
            }
        }
    }

    Complex<float> compute_z(int col, int row) {
        Complex<float> sum = Complex<float>(0);
        for(int i = 0; i < N; i++) {
            if(i != row) {
                sum += lower[row][i] * Z[i][col];
            }
        }

        Complex<float> result = I[row][col] - sum;
        result = result / lower[row][row];

        return result;
    }

    Complex<float> compute_inverse(int col, int row) {
        Complex<float> sum = Complex<float>(0);
        for(int i = 0; i < N; i++) {
            if(i != row) {
                sum += upper[row][i] * inverse[i][col];
            }
        }

        Complex<float> result = Z[row][col] - sum;
        result = result / upper[row][row];


        return result;
    }


    void inverse_matrix() {

        // compute z
        for(int col = 0; col < N; col++) {
            for(int row = 0; row < N; row++) {
                Z[row][col] = compute_z(col, row);
            }
        }
        ;
        // compute inverse
        for(int col = 0; col < N; col++) {
            for(int row = N - 1; row >= 0; row--) {
                inverse[row][col] = compute_inverse(col, row);
            }
        }
    }

// Driver code
    int run() {

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                Z[i][j] = Complex<float>(0);
                if(i == j)
                    I[i][j] = Complex<float>(1);
            }
        }

        lu();
        inverse_matrix();

        cout << "Matrix" << endl;
        mat.print();

        cout << "Inverse" << endl;
        inverse.print();

        return 0;
    }
};

