#include <stdio.h>

double tafel[3][3];
char A, B;


void fillTafel() {
    tafel[0][2] = tafel[0][0] + tafel[0][1];
    tafel[1][2] = tafel[1][0] + tafel[1][1];

    tafel[2][0] = tafel[0][0] + tafel[1][0];
    tafel[2][1] = tafel[0][1] + tafel[1][1];
    tafel[2][2] = tafel[0][2] + tafel[1][2];
    //tafel[1][2] = tafel[1][0] + tafel[1][1];
    //tafel[2][2] = tafel[2][0] + tafel[2][1];
}
/*
    \begin{tabular}{c|c|c|c}
        &\textbf{A}&\textbf{\bar{A}}\\
        \textbf{B}&_&_&_\\
        \textbf{\bar{B}}&_&_&_\\
        &_&_&_
    \end{tabular}

*/
void printTafel() {
    printf("\\begin{tabular}{c|c|c|c}\n\t&\\textbf{%c}&\\textbf{$\\bar{%c}$}\\\\\n", A, A);
    printf("\t\\hline\n\t\\textbf{%c}&%f&%f&%f\\\\\n", B, tafel[0][0], tafel[0][1], tafel[0][2]);
    printf("\t\\hline\n\t\\textbf{$\\bar{%c}$}&%f&%f&%f\\\\\n", B, tafel[1][0], tafel[1][1], tafel[1][2]);
    printf("\t\\hline\n\t&%f&%f&%f\n", tafel[2][0], tafel[2][1], tafel[2][2]);
    printf("\\end{tabular}\n\n");
}
int main() {
    printf("\\documentclass{article}\n\\begin{document}\n");
    scanf("%c\n", &A);
    scanf("%c\n", &B);
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            scanf("%lf", tafel[x] + y);
        }
    }
    fillTafel();
    printf("\\subsection{Tafel}\n");
    printTafel();
    printf("\\subsection{bedingte Wahrscheinlichkeit}\n");
    printf("$P_{%c}(%c) \\approx %f$\\\\\n", A, B, (tafel[0][0] / tafel[2][2]) / (tafel[2][0] / tafel[2][2]));
    printf("$P_{\\bar{%c}}(%c) \\approx %f$\\\\\n", A, B, (tafel[0][1] / tafel[2][2]) / (tafel[2][1] / tafel[2][2]));
    printf("$P_{%c}(%c) \\approx %f$\\\\\n", B, A, (tafel[0][0] / tafel[2][2]) / (tafel[0][2] / tafel[2][2]));
    printf("$P_{\\bar{%c}}(%c) \\approx %f$\\\\\n", B, A, (tafel[1][0] / tafel[2][2]) / (tafel[1][2] / tafel[2][2]));
    printf("\\subsection{Stochastische Abhängikeit}\n");
    if (tafel[0][0] == tafel[2][0] * tafel[0][2] / tafel[2][2])
        printf("$P(%c\\cap %c) = P(%c) \\cdot P(%c) \\Leftrightarrow %f = %f$\\\\\n", A, B, A, B, tafel[0][0] / tafel[2][2], tafel[2][0] * tafel[0][2] / (tafel[2][2] * tafel[2][2]));
    else
        printf("$P(%c\\cap %c) \\neq P(%c) \\cdot P(%c) \\Leftrightarrow %f = %f$\\\\\n", A, B, A, B, tafel[0][0] / tafel[2][2], tafel[2][0] * tafel[0][2] / (tafel[2][2] * tafel[2][2]));
    printf("\\end{document}\n");
    return 0;
}