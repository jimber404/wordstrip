#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_SENTENCE_LENGTH 9999

int main(int argc, char *argv[]) {
    FILE *inputFile, *outputFile;
    char *inputFileName, *outputFileName;
    char sentence[MAX_SENTENCE_LENGTH];
    char *token;
    // Potential probelms here, notably full stops at the end of speaking.
    const char *delimiter = ".!?";
    int sentenceCount = 0, selectedCount = 0, percentileSelectionChance = 75, writtenSentences = 0;
    int i;

    // Check if input and output filenames are provided
    if (argc < 3) {
        printf("Usage: %s inputFileName outputFileName\n", argv[0]);
        return 1;
    }

    // Useful to know for later, how to do it with hyphon prefix?
    inputFileName = argv[1];
    outputFileName = argv[2];
    // percentileSelectionChance = 100-arg[n];

    // Open input and output files
    // This needs to work for .odt files as well.
    inputFile = fopen(inputFileName, "r+");
    if (!inputFile) {
        printf("Error opening input file: %s\n", inputFileName);
        return 1;
    }

    outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        printf("Error opening output file: %s\n", outputFileName);
        fclose(inputFile);
        return 1;
    }

    // Seeding RNG
    srand(time(NULL));
    // Still randomly writes empty lines, why?
    // Empty lines can still be included with current delims, 
    while (fgets(sentence, MAX_SENTENCE_LENGTH, inputFile)) {
        token = strtok(sentence, delimiter);
        while (token != NULL) {
            // RNG, probably a cleaner way to do this. Wich condition is read first?
            if (rand() % 101 >= percentileSelectionChance && strchr(token, '\n') == NULL){ //I think the para filter actually works?! Probably really slow.
                // Whitespace filter, probably a quicker way to do this
                while(isspace((unsigned char)*token)) token++;
                fprintf(outputFile, "%s\n", token);
                writtenSentences++;
            }
            token = strtok(NULL, delimiter);
        }
    }

    
    fclose(inputFile);
    fclose(outputFile);

    printf("Wrote %d sentences \n", writtenSentences);

    return 0;
}
