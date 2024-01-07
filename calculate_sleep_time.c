

#include <philo.h>

#define POINT1_X_EVEN 4
#define POINT1_Y_EVEN 3000
#define POINT2_X_EVEN 6000
#define POINT2_Y_EVEN 160000
#define POINT3_X_EVEN 256
#define POINT3_Y_EVEN 6200

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*restrict d;
	const char	*restrict s;

	if (!dst && !src && n)
		return (dst);
	d = (char *restrict)dst;
	s = (const char *restrict)src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

double determinant(double matrix[3][3])
{
	double	det;

	det = matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
		- matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
		+ matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
	return (det);
}

void solve_quadratic(double points[3][2], double *a, double *b, double *c)
{
	double	matrix[3][3];
	double	matrix_a[3][3];
	double	matrix_b[3][3];
	double	matrix_c[3][3];
	double	det;
	// Populate the matrix with x^2, x, and 1
	for (int i = 0; i < 3; i++)
	{
		matrix[i][0] = points[i][0] * points[i][0];
		matrix[i][1] = points[i][0];
		matrix[i][2] = 1;
	}
	ft_memcpy(matrix_a, matrix, sizeof(matrix));
	ft_memcpy(matrix_b, matrix, sizeof(matrix));
	ft_memcpy(matrix_c, matrix, sizeof(matrix));
	// Replace the appropriate columns with y values
	for (int i = 0; i < 3; i++)
	{
		matrix_a[i][0] = points[i][1];
		matrix_b[i][1] = points[i][1];
		matrix_c[i][2] = points[i][1];
	}
	// Calculate determinants
	det = determinant(matrix);
	// Calculate coefficients
	*a = determinant(matrix_a) / det;
	*b = determinant(matrix_b) / det;
	*c = determinant(matrix_c) / det;
}

int64_t quadratic_function_even(int64_t x)
{
	double	a;
	double	b;
	double	c;
	double	points[3][2];

	points[0][0] = POINT1_X_EVEN;
	points[0][1] = POINT1_Y_EVEN;
	points[1][0] = POINT2_X_EVEN;
	points[1][1] = POINT2_Y_EVEN;
	points[2][0] = POINT3_X_EVEN;
	points[2][1] = POINT3_Y_EVEN;
	// Solve for coefficients
	solve_quadratic(points, &a, &b, &c);
	// Calculate y using the quadratic function y = ax^2 + bx + c
	return ((int64_t)(a * x * x + b * x + c));
}
