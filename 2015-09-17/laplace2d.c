#include <stdio.h>
#include <math.h>


double u(double x, double y)
{
    return cos(x) * sin(y);
}


double laplacian_u(double (*u)(double x, double y),
                   double h, double x, double y)
{
  return ((4*u(x,y) - (u(x+h,y) + u(x-h,y) + u(x,y+h) + u(x,y-h))) * pow(h, -2)); 
}


int main()
{
    printf("Numerical Laplacian at (0.8,0.5) = %g\n",
           laplacian_u(u, 1e-3, 0.8, 0.5));
    printf("True Laplacian at (0.8,0.5) = %g\n",
           2 * cos(0.8) * sin(0.5));
    return 0;
}
