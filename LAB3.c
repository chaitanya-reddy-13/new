#include <stdio.h>
#include <ctype.h>
#include <string.h>
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register",
    "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary"
};
int isKeyword(char *str) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
int isVowel(char ch) {
    ch = tolower(ch);
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
}
int isConsonant(char ch) {
    ch = tolower(ch);
    return (isalpha(ch) && !isVowel(ch));
}

int main() {
    FILE *file;
    char filename[100], token[100];
    char ch;
    int characters = 0, words = 0, lines = 0, vowels = 0, consonants = 0, digits = 0;
    int keywordsCount = 0, operators = 0, identifiers = 0;

    char *operatorsList = "+-*/%=&|^!<>?:~";

    printf("Enter the filename: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }
    int inWord = 0, index = 0;
    printf("Tokens Found:\n");

    while ((ch = fgetc(file)) != EOF) {
        characters++;

        if (ch == '\n') {
            lines++;
        }

        if (isdigit(ch)) {
            digits++;
            printf("Digit: %c\n", ch);
        }

        if (isalpha(ch)) {
            if (isVowel(ch)) {
                vowels++;
            } else if (isConsonant(ch)) {
                consonants++;
            }
        }

        if (strchr(operatorsList, ch)) {
            operators++;
            printf("Operator: %c\n", ch);
        }

        if (isalnum(ch) || ch == '_') {
            token[index++] = ch;
            inWord = 1;
        } else {
            if (inWord) {
                token[index] = '\0';
                if (isKeyword(token)){
                    printf("Keyword: %s\n", token);
                    keywordsCount++;
                } else {
                    printf("Identifier: %s\n", token);
                    identifiers++;
                }
                index = 0;
                words++;
            }
            inWord = 0;
        }
    }

    if (inWord) {
        token[index] = '\0';
        if (isKeyword(token)) {
            printf("Keyword: %s\n", token);
            keywordsCount++;
        } else {
            printf("Identifier: %s\n", token);
            identifiers++;
        }
        words++;
    }
    fclose(file);
    if (lines == 0) {
        lines = 1;
    }
    printf("\nSummary:\n");
    printf("Number of characters: %d\n", characters);
    printf("Number of words: %d\n", words);
    printf("Number of lines: %d\n", lines);
    printf("Number of vowels: %d\n", vowels);
    printf("Number of consonants: %d\n", consonants);
    printf("Number of digits: %d\n", digits);
    printf("Number of keywords: %d\n", keywordsCount);
    printf("Number of identifiers: %d\n", identifiers);
    printf("Number of operators: %d\n", operators);
    return 0;
}
