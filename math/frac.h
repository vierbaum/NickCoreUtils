#ifndef FRAC_H_
#define FRAC_H_

#include <stdlib.h>
#include <stdio.h>
#include <printf.h>


typedef struct {
    double den;
    double num;
} Frac;

static Frac genFrac(double, double);

static void reduce(Frac* f) {
    int red = 1;
    for (int i = 1; i <= abs(f->num); i++) {
        if ((int) (f->num / i) == f->num / i && (int) (f->den / i) == f->den / i) {
            red = i;
        }
    }
    f->num = f->num / red;
    f->den = f->den / red;
}

static char* printFrac(Frac* f, char* s) {
    sprintf(s, "\\Frac{%d}{%d}", (int) f->num, (int) f->den);
    return s;
}

static inline Frac operator+ (Frac lhs, Frac rhs) {
    Frac fres;
    fres.num = lhs.num * rhs.den + rhs.num * lhs.den;
    fres.den = lhs.den * rhs.den;
    reduce(&fres);
    return fres;
}

static inline Frac operator- (Frac lhs, Frac rhs) {
    Frac fres;
    fres.num = lhs.num * rhs.den - rhs.num * lhs.den;
    fres.den = lhs.den * rhs.den;
    reduce(&fres);
    return fres;
}

static inline Frac operator* (Frac lhs, Frac rhs) {
    Frac fres;
    fres.num = lhs.num * rhs.num;
    fres.den = lhs.den * rhs.den;
    reduce(&fres);
    return fres;
}

static inline Frac operator/ (Frac lhs, Frac rhs) {
    Frac fres;
    Frac ftmp = genFrac(rhs.den, rhs.num);
    fres = lhs * ftmp;
    reduce(&fres);
    return fres;
}

static Frac genFrac(double num, double den) {
    Frac ret;
    ret.num = num;
    ret.den = den;
    reduce(&ret);
    return ret;
}

int print_frac (FILE *stream,
              const struct printf_info *info,
              const void *const *args)
{
  const Frac* f;
  char *buffer;
  int len;

  /* Format the output into a string. */
  f = *((const Frac **) (args[0]));
  if (f->num == (int) f->num && f->den == (int) f->den)
    len = asprintf (&buffer, "\\frac{%d}{%d}", (int) f->num, (int) f->den);
  else if (f->num == (int) f->num)
    len = asprintf (&buffer, "\\frac{%d}{%f}", (int) f->num, f->den);
  else if (f->den == (int) f->den)
    len = asprintf (&buffer, "\\frac{%f}{%d}", f->num, (int) f->den);
  else
    len = asprintf (&buffer, "\\frac{%f}{%f}", f->num, f->den);

  if (len == -1)
    return -1;

  /* Pad to the minimum field width and print to the stream. */
  len = fprintf (stream, "%*s",
                 (info->left ? -info->width : info->width),
                 buffer);

  /* Clean up and return. */
  free (buffer);
  return len;
}


int print_frac_arginfo (const struct printf_info *info, size_t n,
                      int *argtypes)
{
  /* We always take exactly one argument and this is a pointer to the
     structure.. */
  if (n > 0)
    argtypes[0] = PA_POINTER;
  return 1;
}


//  register_printf_function ('W', print_widget, print_widget_arginfo);
//void __attribute__((constructor)) register_printf_specifier('F', print_frac, print_frac_arginfo);
#endif