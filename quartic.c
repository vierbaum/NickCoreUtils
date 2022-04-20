#include <stdio.h>
#include <math.h>
#include <complex.h>

double complex* cubicEq(double a, double b, double c, double d) {
  static double complex roots[3];
  double complex C, XI = (-1 + csqrt(-3))/2;
  double d0, d1;


  // b² - 3ac
  d0 = b * b - 3 * a * c;
  // 2b3 - 9abc + 27a²d
  d1 = 2 * b * b * b - 9 * a * b * c + 27 * a * a * d;

  C = cpowf((d1 + csqrt(d1 * d1 - 4 * d0 * d0 * d0))/2, 1.0/3.0);
  if(C == 0)
    C = cpowf((d1 - csqrt(d1 * d1 - 4 * d0 * d0 * d0))/2, 1.0/3.0);
  for(int k = 0; k <= 2; k++) {
    roots[k] = -1/(3*a) * (b + cpow(XI, k) * C + d0/(cpow(XI, k) * C));
  }
  return roots;
}

int main() {
  double a, b, c, d, e, f, g, h;
  double complex p, q, s, r;
  double complex roots[4];
  /*
  a = 3;
  b = 6;
  c = -123;
  d = -126;
  e = 1080;
  */
  printf("a: ");
  scanf("%lf", &a);
  printf("b: ");
  scanf("%lf", &b);
  printf("c: ");
  scanf("%lf", &c);
  printf("d: ");
  scanf("%lf", &d);
  printf("e: ");
  scanf("%lf", &e);

  // simplify to x⁴+bx³+cx²+dx+e
  b = b/a;
  c = c/a;
  d = d/a;
  e = e/a;

  f = c - (3 * b * b / 8);
  g = d + (b * b * b / 8) - (b * c / 2);
  h = e - (3 * b * b * b * b / 256) + (b * b * c / 16) - (b * d / 4);


  double complex* qroots = cubicEq(1, f/2, (f * f -4*h)/16, -g * g/64);
  double complex root;
  double complex validRoots[2];
  int j = 0;
  for(int i = 0; i < 3; i++) {
    root = *(qroots + i);
    if(creal(root) + cimag(root) < -0.99 || creal(root) + cimag(root) > 0.1 && j < 2) {
      validRoots[j] = root;
      j++;
    }
  }
  p = csqrt(validRoots[0]);
  q = csqrt(validRoots[1]);
  r = -g/(8 * p * q);
  s = b * a / (4 * a);

  roots[0] = p + q + r - s;
  roots[1]= p - q - r - s;
  roots[2]= -p + q - r - s;
  roots[3]= -p - q + r - s;
  for(int i = 0; i <= 3; i++)
    printf("x%d: %f + %fi\n", i, creal(roots[i]), cimag(roots[i]));
  return 0;
}

