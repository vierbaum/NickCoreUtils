#include <stdio.h>
#include <math.h>
#include<complex.h>

int main() {
  double complex XI = (-1 + csqrt(-3))/2;
  double a, b, c, d;
  double complex d0, d1, C, x;
  printf("a: ");
  scanf("%lf", &a);
  printf("b: ");
  scanf("%lf", &b);
  printf("c: ");
  scanf("%lf", &c);
  printf("d: ");
  scanf("%lf", &d);


  // b² - 3ac
  d0 = b * b - 3 * a * c;
  // 2b3 - 9abc + 27a²d
  d1 = 2 * b * b * b - 9 * a * b * c + 27 * a * a * d;

  C = cbrt((d1 + sqrt(d1 * d1 - 4 * d0 * d0 * d0))/2);
  if(C == 0)
    C = cbrt((d1 - sqrt(d1 * d1 - 4 * d0 * d0 * d0))/2);

  for(int k = 0; k <= 2; k++) {
    x = -1/(3*a) * (b + cpow(XI, k) * C + d0/(cpow(XI, k) * C));
    if (cimag(x) > 0)
        printf("%d: , %f + %fi\n", k, creal(x), cimag(x));
    else
        printf("%d: , %f %fi\n", k, creal(x), cimag(x));
    }
  }
