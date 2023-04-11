#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SENTENCE_LENGTH 1000

int main(int argc, char *argv[]) {
    FILE *input_file, *output_file;
    char *input_filename, *output_filename;
    char sentence[MAX_SENTENCE_LENGTH];
    char *token;
    const char *delimiter = ".!?";
    int sentence_count = 0, selected_count = 0;
    int i;

    // Check if input and output filenames are provided
    if (argc < 3) {
        printf("Usage: %s input_filename output_filename\n", argv[0]);
        return 1;
    }

    input_filename = argv[1];
    output_filename = argv[2];

    // Open input and output files
    input_file = fopen(input_filename, "r+");
    if (!input_file) {
        printf("Error opening input file: %s\n", input_filename);
        return 1;
    }

    output_file = fopen(output_filename, "w");
    if (!output_file) {
        printf("Error opening output file: %s\n", output_filename);
        fclose(input_file);
        return 1;
    }

    srand(time(NULL));
    while (fgets(sentence, MAX_SENTENCE_LENGTH, input_file)) {
        token = strtok(sentence, delimiter);
        while (token != NULL) {
            if (rand() % 101 >= 75){
                fprintf(output_file, "%s\n", token);
            }
            token = strtok(NULL, delimiter);
        }
    }

    
    fclose(input_file);
    fclose(output_file);

    return 0;
}
