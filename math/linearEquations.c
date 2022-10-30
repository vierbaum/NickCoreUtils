#include <stdio.h>
#include <stdlib.h>

double factors[255][255];
double solutions[2][255];

void printFactors(int f, int e) {
    printf("\\[\n\\left[\n\\begin{array}{");
    for (int z = 0; z < f - 1; z++)
        printf("c");
    printf("|c}\n");
    for(int y = 0; y < e; y++) {
        printf("\t");
        for(int x = 0; x < f; x++) {
            if(x != 0)
                printf("&");
            printf("%f", factors[y][x]);
        }
        printf("\\\\\n");
    }
    printf("\\end{array}\n\\right]\n\\]\n\\\\\n");
}

void solve(int pos, int f, int e) {
    char first = 1;
    for (int eq = 0; eq < pos; eq++) {
        factors[eq][f - 1] = factors[eq][f - 1] - factors[pos][f - 1] * factors[eq][pos];
        factors[eq][pos] = 0;

        first = 1;
        for(int i = 0; i < pos -1; i++)
            if (factors[eq][i])
                first = 0;
        if (first) {
            factors[eq][f - 1] = factors[eq][f - 1] / factors[eq][pos - 1];
            factors[eq][pos - 1] = 1;
        }
    }
}

void calc(int pos, int f, int e) {
    for (int eq = pos + 1; eq < e; eq++) {
        if (factors[eq][pos] != 0) {
            double quo = factors[eq][pos] / factors[pos][pos];
            for (int i = pos; i < f; i++)
                factors[eq][i] = factors[eq][i] - factors[pos][i] * quo;

        }
    }
}

void sort (int f, int e) {
    for (int eq = 0; eq < e; eq++)
        if (factors[eq][eq])
    return;
}

int main() {
    printf("\\documentclass{article}\n\\begin{document}\n");
    char numChar[255];
    char c, out = 0, f = 0, e = 0, ic = 0, gF = 0;

    read:
        for(int a = 0; a < 255; a++) numChar[a] = 0;
        while ((c = getchar()) != '\n') {
            numChar[ic] = c;
            ic++;
        }

        if (ic == 0) {
            e++;
            if (out == 1)
                goto out;
            f = 0;
            out = 1;
            goto read;
        }
        out = 0;

        ic = 0;
        factors[e][f] = atof(numChar);
        f++;
        gF = f;
        goto read;
    out:
    e--;
    f = gF;

    printFactors(f, e);


    for (int i = 0; i < e - 1; i++) {
        calc(i, f, e);
        printFactors(f, e);
    }

    if (factors[e - 1][f - 2] != 0) {
        factors[e - 1][f - 1] = factors[e - 1][f - 1] / factors[e - 1][f - 2];
        factors[e - 1][f - 2] = 1;

        for (int i = e - 1; i >= 1; i--) {
            solve(i, f, e);
            printFactors(f, e);
        }

        for(int i = 0; i < e; i++)
            printf("$x_{%d} \\approx %f$\\\\\n", i + 1, factors[i][f - 1]);
    }
    printf("\\end{document}\n");
    return 0;
}