#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DELTA_X 1e-4

double func1(double x);
double func2(double x);
double func3(double *px);
double func4(double *px);
double numerical_derivative_scalar(double (*f)(double), double x);
double *numerical_derivative_vector(double (*f)(double[]), double x[], int n);
double **numerical_derivative_matrix(double (*f)(double *), double *x, int n, int m);

int main(void)
{
  double x;
  double y;
  double z;
  double w;
  double result;
  double *result2;
  double **result3;
  double xy[2] = {0};
  double wxyz[2][2] = {0};

  printf("Input X : ");
  scanf("%lf", &x);
  printf("Input Y : ");
  scanf("%lf", &y);
  printf("Input Z : ");
  scanf("%lf", &z);
  printf("Input W : ");
  scanf("%lf", &w);

  xy[0] = x; // 1
  xy[1] = y; // 2

  wxyz[0][0] = x; // 1
  wxyz[0][1] = y; // 2
  wxyz[1][0] = z; // 3
  wxyz[1][1] = w; // 4

  result = numerical_derivative_scalar(&func1, x);
  printf("Numerial Derivative Func 1 => %f\n", result); // 2
  result = numerical_derivative_scalar(&func2, y);
  printf("Numerial Derivative Func 2 => %f\n", result); // 66.501505
  result2 = numerical_derivative_vector(&func3, xy, sizeof xy / sizeof(double));
  printf("Numerial Derivative Func 3 => %f / %f\n", result2[0], result2[1]); // 8, 15
  result3 = numerical_derivative_matrix(&func4, wxyz, sizeof wxyz / sizeof wxyz[0], sizeof wxyz[0] / sizeof(double));
  printf("Numerial Derivative Func 4 => %f / %f\n", result3[0][0], result3[0][1]); // 5, 13
  printf("Numerial Derivative Func 4 => %f / %f\n", result3[1][0], result3[1][1]); // 32, 15

  free(result2);

  for (int i; i < 2; i++)
  {
    free(result3[i]);
  }

  free(result3);

  return 0;
}

double func1(double x)
{
  return x * x;
}

double func2(double x)
{
  return 3 * x * exp(x);
}

double func3(double *px)
{
  double x = px[0];
  double y = px[1];

  return 2 * x + 3 * x * y + pow(y, 3);
}

double func4(double *px)
{
  double **ppx = &px;
  double w = ppx[0][0];
  double x = ppx[0][1];
  double y = ppx[0][2];
  double z = ppx[0][3];

  return w * x + x * y * z + 3 * w + z * y * y;
}

double numerical_derivative_scalar(double (*f)(double), double x)
{
  return (f(x + DELTA_X) - f(x - DELTA_X)) / (2 * DELTA_X);
}

double *numerical_derivative_vector(double (*f)(double[]), double x[], int n)
{
  double *result = (double *)malloc(sizeof(double) * n);
  for (int i = 0; i < n; i++)
  {
    double temp = x[i];
    x[i] = temp + DELTA_X;
    double fx1 = f(x); //f(x + DELTA_X)
    x[i] = temp - DELTA_X;
    double fx2 = f(x); //f(x - DELTA_X)
    result[i] = (fx1 - fx2) / (2 * DELTA_X);
    x[i] = temp;
  }
  return result;
}

double **numerical_derivative_matrix(double (*f)(double *), double *x, int row, int col)
{
  double **result = (double **)malloc(sizeof(double *) * row);
  double **ppx = &x;
  int cnt = 0;
  for (int i = 0; i < row; i++)
  {
    result[i] = (double *)malloc(sizeof(double *) * col);
  }

  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      double temp = ppx[0][cnt];
      ppx[0][cnt] = temp + DELTA_X;
      double fx1 = f(x); //f(x + DELTA_X)
      ppx[0][cnt] = temp - DELTA_X;
      double fx2 = f(x); //f(x - DELTA_X)
      result[i][j] = (fx1 - fx2) / (2 * DELTA_X);
      ppx[0][cnt] = temp;
      cnt++;
    }
  }
  return result;
}