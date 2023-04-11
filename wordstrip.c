// NEED SOME CAMEL CASE UP IN THIS BITCH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_SENTENCE_LENGTH 9999

int main(int argc, char *argv[]) {
    FILE *input_file, *output_file;
    char *input_filename, *output_filename;
    char sentence[MAX_SENTENCE_LENGTH];
    char *token;
    // Potential probelms here, notably full stops at the end of speaking.
    const char *delimiter = ".!?";
    int sentence_count = 0, selected_count = 0, percentileSelectionChance = 75, writtenSentences = 0;
    int i;

    // Check if input and output filenames are provided
    if (argc < 3) {
        printf("Usage: %s input_filename output_filename\n", argv[0]);
        return 1;
    }

    // Useful to know for later, how to do it with hyphon prefix?
    input_filename = argv[1];
    output_filename = argv[2];
    // percentile_selection_change = 100-arg[n];

    // Open input and output files
    // This needs to work for .odt files as well.
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

    // Seeding RNG
    srand(time(NULL));
    // Still randomly writes empty lines, why?
    // Empty lines can still be included with current delims, 
    while (fgets(sentence, MAX_SENTENCE_LENGTH, input_file)) {
        token = strtok(sentence, delimiter);
        while (token != NULL) {
            // RNG, probably a cleaner way to do this. Wich condition is read first?
            if (rand() % 101 >= percentileSelectionChance && strchr(token, '\n') == NULL){ //I think the para filter actually works?! Probably really slow.
                // Whitespace filter, probably a quicker way to do this
                while(isspace((unsigned char)*token)) token++;
                fprintf(output_file, "%s\n", token);
                writtenSentences++;
            }
            token = strtok(NULL, delimiter);
        }
    }

    
    fclose(input_file);
    fclose(output_file);

    printf("Wrote %d sentences \n", writtenSentences);

    return 0;
}
