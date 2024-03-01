// Daylan Pereira Arroyo C05858
// Juan Carlos Gomez Montero C13201 
// Jefri Barrios Pernudez C21078
// Este código lo que hace es recibir dos funciones cuadraticas 
// las mismas pasan a ser graficadas segun la expresion que de el usuario
// el usuario a demas da un procentaje de error, el mismo
// se debe cumplir al momento de generar un subdominio que debe ser 
// menor al procentade de error, ademas, el cuando se genera el subdominio
// en esos puntos se grafica dos rectas verticales (asintotas)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Función cuadrática 1
double funcionCuadratica1(double x, double a, double b, double c) {
    return a * x * x + b * x + c;
}

// Función cuadrática 2
double funcionCuadratica2(double x, double d, double e, double f) {
    return d * x * x + e * x + f;
}

int main() {
    double a, b, c, d, e, f;

    // Ingreso de coeficientes para la primera función cuadrática
    printf("Ingrese los coeficientes para la primera función cuadrática (a b c): ");
    int tipo = 0;
    do {
        printf("\nCoeficiente a: ");
        while (scanf("%lf", &a) != 1) {
            printf("\nERROR: El valor ingresado es inválido.\nCoeficiente a: ");
            scanf("%*s");
        }
        tipo = 1;
        } while (tipo == 0);
    tipo = 0;
    do {
        printf("Coeficiente b: ");
        while (scanf("%lf", &b) != 1) {
            printf("\nERROR: El valor ingresado es inválido.\nCoeficiente b: ");
            scanf("%*s");
        }
        tipo = 1;
        } while (tipo == 0);
    tipo = 0;
    do {
        printf("Coeficiente c: ");
        while (scanf("%lf", &c) != 1) {
            printf("\nERROR: El valor ingresado es inválido.\nCoeficiente c: ");
            scanf("%*s");
        }
        tipo = 1;
        } while (tipo == 0);
    printf("La Función 1 es: %.2lfx² + %.2lfx + %.2lf\n\n.", a, b, c);
    // Ingreso de coeficientes para la segunda función cuadrática
    printf("Ingrese los coeficientes para la segunda función cuadrática (d e f): ");
    tipo = 0;
    do {
        printf("\nCoeficiente d: ");
        while (scanf("%lf", &d) != 1) {
            printf("\nERROR: El valor ingresado es inválido.\nCoeficiente d: ");
            scanf("%*s");
        }
        tipo = 1;
        } while (tipo == 0);
    tipo = 0;
    do {
        printf("Coeficiente e: ");
        while (scanf("%lf", &e) != 1) {
            printf("\nERROR: El valor ingresado es inválido.\nCoeficiente e: ");
            scanf("%*s");
        }
        tipo = 1;
        } while (tipo == 0);
    tipo = 0;
    do {
        printf("Coeficiente f: ");
        while (scanf("%lf", &f) != 1) {
            printf("\nERROR: El valor ingresado es inválido.\nCoeficiente f: ");
            scanf("%*s");
        }
        tipo = 1;
        } while (tipo == 0);
    printf("La Función 2 es: %.2lfx² + %.2lfx + %.2lf.\n\n", d, e, f);
    
    // Ingreso del porcentaje de error
    double porcentajeError;
    tipo = 0;
    do {
        printf("\nIngrese el porcentaje de error: ");
        while (scanf("%lf", &porcentajeError) != 1 || porcentajeError < 0 || porcentajeError > 100) {
            printf("\nERROR: Por favor digite un valor numérico entre 0 y 100 (POSITIVO).\nIngrese el porcentaje de error: ");
            scanf("%*s");
        }
        tipo = 1;
        } while (tipo == 0);
    printf("El porcentaje de error es: %.2lf.\n\n", porcentajeError);
    double x, diferencia;
    double subdominioInicio = INFINITY, subdominioFin = -INFINITY;

    // Iteración en el rango de valores
    for (x = -100000.0; x <= 100000.0; x += 0.1) {
        double resultado1 = funcionCuadratica1(x, a, b, c);
        double resultado2 = funcionCuadratica2(x, d, e, f);

        // Verificar si resultado1 está cerca de cero
        if (fabs(resultado1) < 1e-3) {
            fprintf(stderr, "Aviso: La función cuadrática 1 tiene un resultado cercano a 0 en x=%.2lf.\n", x);
        }

        // Calcular la diferencia porcentual
        diferencia = (fabs(resultado1 - resultado2) / fabs(resultado1)) * 100;

        // Verificar si la diferencia es menor al porcentaje de error y resultado1 no es cercano a cero
        if (diferencia <= porcentajeError && fabs(resultado1) > 1e-3) {
            if (x < subdominioInicio) subdominioInicio = x;
            if (x > subdominioFin) subdominioFin = x;
        }
    }

    // Imprimir el subdominio calculado
    if (subdominioInicio == INFINITY || subdominioFin == -INFINITY) {
        printf("No se encontró ningún subdominio que cumpla con el criterio de error.\n");
        FILE *fp = popen ("gnuplot -persist", "w");
        fprintf(fp, "plot %.2lf*x*x + %.2lf*x + %.2f lc rgb 'red' lt 2 lw 2 title 'Función 1'\n",a, b, c);
        fprintf(fp, "replot %.2lf*x*x + %.2lf*x + %.2f lc rgb 'green' lt 2 lw 2 title 'Función 2'\n",d, e, f);
        fprintf(fp, "set terminal wxt title 'Gráfica de las Funciones\n'");
        //fprintf(fp, "replot\n");
        fclose(fp);
    } else {
        printf("Subdominio donde la diferencia es menor al %.2lf%% de error: [%.2lf, %.2lf]\n",
               porcentajeError, subdominioInicio, subdominioFin);
        FILE *fp = popen ("gnuplot -persist", "w");
        fprintf(fp, "plot %.2lf*x*x + %.2lf*x + %.2f lc rgb 'red' lt 2 lw 2 title 'Función 1'\n",a, b, c);
        fprintf(fp, "replot %.2lf*x*x + %.2lf*x + %.2f lc rgb 'green' lt 2 lw 2 title 'Función 2'\n",d, e, f);
        fprintf(fp, "set arrow from %.2lf, graph(0,0) to %.2lf, graph(1,1) nohead lc rgb 'blue' lw 2\n", subdominioInicio, subdominioInicio);
        fprintf(fp, "set arrow from %.2lf, graph(0,0) to %.2lf, graph(1,1) nohead lc rgb 'blue' lw 2\n", subdominioFin, subdominioFin);
        fprintf(fp, "set xrange [%lf-10:%lf+10]\n", subdominioInicio, subdominioFin);
        fprintf(fp, "replot\n");
        fprintf(fp, "set terminal wxt title 'Gráfica de las Funciones y el subdominio\n'");
        //fprintf(fp, "replot\n");
        fclose(fp);

    }
    
    /* Grafica ambas Funciones y el dominio calculado.
    FILE *fp = popen ("gnuplot -persist", "w");
    fprintf(fp, "plot %.2lf*x*x + %.2lf*x + %.2f lc rgb 'red' lt 2 lw 2 title 'Función 1'\n",a, b, c);
    fprintf(fp, "replot %.2lf*x*x + %.2lf*x + %.2f lc rgb 'green' lt 2 lw 2 title 'Función 2'\n",d, e, f);
    fprintf(fp, "set arrow from %.2lf, graph(0,0) to %.2lf, graph(1,1) nohead lc rgb 'blue' lw 2\n", subdominioInicio, subdominioInicio);
    fprintf(fp, "set arrow from %.2lf, graph(0,0) to %.2lf, graph(1,1) nohead lc rgb 'blue' lw 2\n", subdominioFin, subdominioFin);
    fprintf(fp, "set xrange [%lf-10:%lf+10]\n", subdominioInicio, subdominioFin);
    fprintf(fp, "replot\n");
    fclose(fp); */

    return 0;
}
