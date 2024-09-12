#include <stdio.h>

int main() {
    // Coordinates of one end of the diameter and the center
    int x1 = 2, y1 = 3;
    int h = -2, k = 5;
    
    // Calculate the coordinates of the other end of the diameter
    int x2 = 2 * h - x1;
    int y2 = 2 * k - y1;
    
    // Open a file to write the results
    FILE *file = fopen("coordinates.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    
    // Print the coordinates to the file
    fprintf(file, "End of Diameter 1: (%d, %d)\n", x1, y1);
    fprintf(file, "Center of Circle: (%d, %d)\n", h, k);
    fprintf(file, "End of Diameter 2: (%d, %d)\n", x2, y2);
    
    // Close the file
    fclose(file);
    
    return 0;
}
