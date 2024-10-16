#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "/home/anvitha/gvv/matgeo/codes/msoft/libs/matfun.h"
int main() {
    // Coordinates of one end of the diameter and the center
// create three matrices B=2*O-A
// end points of the diameters
    double **A=createMat(2,1);
    double **B=createMat(2,1); 
    double **O=createMat(2,1); //centre
    A[0][0]=2;
    A[1][0]=3;
    O[0][0]=-2;
    O[1][0]=5;

    //create temporary matrix 
    double **temp = createMat(2, 1);
    temp[0][0] = 2 * O[0][0];
    temp[1][0] = 2 * O[1][0];
    B=Matsub(temp,A,2,1);
// // Open a file to write the results
    FILE *file = fopen("coordinates.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // Print the coordinates to the file
    fprintf(file, "End of Diameter 1: (%.2lf, %.2lf)\n", A[0][0], A[1][0]);
    fprintf(file, "Center of Circle: (%.2lf, %.2lf)\n", O[0][0], O[1][0]);
    fprintf(file, "End of Diameter 2: (%.2lf, %.2lf)\n", B[0][0], B[1][0]);
    
    // Close the file
    fclose(file);
    
    return 0;
}
