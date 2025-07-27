#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for sleep

int main() {
    const char* command = "curl -s \"https://data-asg.goldprice.org/dbXRates/USD\" > temp.json";

    while (1) {
        system(command);

        FILE* file = fopen("temp.json", "r");
        if (file == NULL) {
            printf("Error al abrir el archivo.\n");
            return 1;
        }

        char buffer[1024];
        fread(buffer, sizeof(buffer), 1, file);
        fclose(file);

        char* price_str = strstr(buffer, "\"xauPrice\":");
        if (price_str) {
            price_str += 11; // Saltar "\"xauPrice\":"
            double price = atof(price_str);
            system("cls"); // Limpia la pantalla en Windows (usa "clear" en Unix/Linux)
            printf("Precio del oro en directo (USD/oz): %.2f\n", price);
        } else {
            printf("Error al parsear el precio.\n");
        }

        sleep(60); // Actualiza cada 60 segundos
    }

    return 0;
}
