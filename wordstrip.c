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
    int *selected_indices, i;

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

    // Count the number of sentences in the input file
    // Can this an sentence slection not be done at the same time? I guess rng is intesive.
    while (fgets(sentence, MAX_SENTENCE_LENGTH, input_file)) {
        token = strtok(sentence, delimiter);
        while (token != NULL) {
            sentence_count++;
            token = strtok(NULL, delimiter);
        }
    }

    // Select 25% of the sentences
    selected_count = sentence_count / 4;
    selected_indices = (int*) malloc(selected_count * sizeof(int));

    //Fails to preserve sentence order.
    int start = 0;
    srand(time(NULL)); // Seed random number generator
    for (i = 0; i < selected_count; i++) {
        selected_indices[i] = rand() % sentence_count + start; //added +start to try and order
        start++;
    }

    //Viewing contents. All seems okay?
    for (int i = 0; i < selected_count; i++) {
        printf("Selected index %d: %d\n", i, selected_indices[i]);
    }

    // Read the input file again and write selected sentences to the output file
    // Some of the text comes out wonnky with hyphons and breaks, consider alternative?
    rewind(input_file);
    i = 0;
    while (fgets(sentence, MAX_SENTENCE_LENGTH, input_file)) {
        token = strtok(sentence, delimiter);
        while (token != NULL) {
            // It seems like this if condition is failing to be met most of the time, why?
            // I think the below function assumes that selected_indicies are stored in order. Might overhaul this bit.
            if (i < selected_count && selected_indices[i] == i) {
                fprintf(output_file, "%s\n", token);
                printf( " %s was written \n", token );
                i++;
                printf("Hit \n");
            // This condition is often met, is this intended?
            } else if (i >= selected_count) {
                printf("Break \n");
                break;
            } else {
                printf("Miss \n");
                i++;
            }
            token = strtok(NULL, delimiter);
        }
    }

    // Close files and free memory
    fclose(input_file);
    fclose(output_file);
    free(selected_indices);

    printf("Selected %d out of %d sentences from %s and saved to %s.\n",
           selected_count, sentence_count, input_filename, output_filename);

    return 0;
}
