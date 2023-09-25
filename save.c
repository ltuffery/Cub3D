#include <stdio.h>
#include <math.h>

int main() {
    double x1, y1, x2, y2;
    // Assigner les valeurs de x1, y1, x2, y2 ici

	x1 = 5.5;
	x2 = 7.8;
	y1 = 6.4;
	y2 = 8;
    double longueur, dx, dy, x, y;
    if (fabs(x2 - x1) >= fabs(y2 - y1)) {
        longueur = fabs(x2 - x1);
    } else {
        longueur = fabs(y2 - y1);
    }

    dx = (x2 - x1) / longueur;
    dy = (y2 - y1) / longueur;
    x = x1 + 0.5;
    y = y1 + 0.5;
    int i = 1;

    while (i <= longueur) {
        // Utilisez la fonction setPixel(E(x), E(y)) pour dessiner le pixel
        // Remarque : La fonction E(x) et E(y) n'est pas définie dans l'algorithme initial.
        // Vous devez la remplacer par la fonction appropriée ou la logique de dessin de pixel.
        // setPixel(E(x), E(y));
        
        x += dx;
        y += dy;
        i++;
    }
	printf("dx : %f | dy %f\n", dx, dy);
	printf("x : %f | y : %f\n", x, y);

    return 0;
}
