#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Número de bytes no cabeçalho de um arquivo WAV
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Verifica o uso correto
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Abre os arquivos
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file %s.\n", argv[1]);
        return 2;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        fclose(input);
        printf("Could not open file %s.\n", argv[2]);
        return 3;
    }

    // Converte o fator de escala de string para float
    float factor = atof(argv[3]);

    // Lê o cabeçalho do arquivo WAV
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // Lê as amostras de áudio do arquivo WAV, altera o volume e escreve no arquivo de saída
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        sample = (int16_t)(sample * factor);
        fwrite(&sample, sizeof(int16_t), 1, output);
    }

    // Fecha os arquivos
    fclose(input);
    fclose(output);

    return 0;
}
