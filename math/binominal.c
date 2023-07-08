#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

double k, n, p;

static inline double fac(double n) {
    if (n <= 1)
        return 1;
    else
        return fac(n - 1) * n;

}
int main(int argc, char *argv[]) {
    char doK = 0;
    char smaller = 0;
    for (int i = 0; i < argc; i++) {
        if (!strcmp(argv[i], "-n"))
            n = atof(argv[i + 1]);
        if (!strcmp(argv[i], "-p"))
            p = atof(argv[i + 1]);
        if (!strcmp(argv[i], "--smaller")) {
            smaller = atof(argv[i + 1]);

        }
        if (!strcmp(argv[i], "-k")) {
            k = atof(argv[i + 1]);
            doK = 1;
        }

    }
    printf("k %f, n %f, p %f\n", k, n, p);
    if (doK) {
        printf("k %f, n %f, p %f\n", k, n, p);

        printf("\\begin{equation}\n\\begin{split}\n\tP(X = k) &= \n\t\\begin{pmatrix}\n\t\tn\\\\\n\t\tk\n\t\\end{pmatrix}\n\t\\cdot p^{k} \\cdot (1 - p)^{n - k}\n");
        printf("\t= \\frac{n!}{k! \\cdot (n - k)!}\\cdot p^{k} \\cdot (1 - p)^{n - k}\\\\\n");
        printf("\tP(X = %f) &= \\frac{%f}{%f \\cdot %f!} \\cdot %f \\cdot %f^{%f}\\\\\n", k, fac(n), fac(k), n - k, pow(p, k), 1 - p, n - k);
        printf("\t&=\\frac{%f}{%f} \\cdot %f\\\\\n", fac(n) * pow(p, k), fac(k) * fac(n - k), pow((1 - p), (n - k)));
        printf("\t&=%f\n", fac(n) * pow(p, k) * pow((1 - p), n - k) / (fac(k) * fac(n - k)));
        printf("\\end{split}\n\\end{equation}\n");
    }
    else {
        if (smaller) {
            double ret;
            for (k = 0; k <= smaller; k++) {
                ret += fac(n) * pow(p, k) * pow((1 - p), n - k) / (fac(k) * fac(n - k));
            }
            printf("%f\n", ret);
        }
        else {
            printf("\n\\begin{tikzpicture}\n\\begin{axis}[\n\txlabel = {$r$},\n\tylabel = {$P(X = t)$}]\n\\addplot+[ybar] coordinates {\n");
            for (k = 0; k <= n; k++) {
                printf("\t(%d,%f)\n", (int) k, fac(n) * pow(p, k) * pow((1 - p), n - k) / (fac(k) * fac(n - k)));
            }
            printf("};\n\\end{axis}\n\\end{tikzpicture}\n");
        }
    }
}
