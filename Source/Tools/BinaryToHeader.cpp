#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

// TODO: Use stb_include.

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        return EXIT_FAILURE;
    }

    FILE* input = fopen(argv[1], "rb");
    if (!input) {
        return EXIT_FAILURE;
    }

    FILE* output = fopen(argv[2], "w");
    if (!output) {
        fclose(input);
        return EXIT_FAILURE;
    }

    fseek(input, 0, SEEK_END);
    const long fileSize = ftell(input);
    fseek(input, 0, SEEK_SET);

    const char* variableName = argv[3];
    int column = 0;

    fprintf(output, "const char %s[] = {\n", variableName);

    int byte;
    while ((byte = fgetc(input)) != EOF) {
        if (column == 0) {
            fprintf(output, "    ");
        }

        fprintf(output, (column == 15) ? "0x%02X,\n" : "0x%02X, ", unsigned char(byte));

        column = (column + 1) % 16;
    }

    if (column == 0) {
        fprintf(output, "    ");
    }

    fprintf(output, (column == 15) ? "0x00,\n" : "0x00, ");

    fprintf(output, (column == 0) ? "};" : "\n};");

    fclose(output);
    fclose(input);
    return EXIT_SUCCESS;
}
