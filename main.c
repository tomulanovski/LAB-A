#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int debug = 1;
    int encode = 0;
    int encKey = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;

    for (int i = 1; i < argc; i++) {
        if (debug == 1) {
            fprintf(stderr, " %s\n", argv[i]);
        }

        if (argv[i][1] == 'E') {
            if (argv[i][0] == '-'){
                encode = -1;
            }
            else if (argv[i][0] == '+'){
                encode = 1;
            }
            encKey = atoi(argv[i] + 2);
        }
         if (argv[i][1] == 'D') {
             if (argv[i][0] == '-'){
                 debug = 0;
             }
             else if (argv[i][0] == '+'){
                 debug = 1;
             }
        }
    }
    int ch;
    while ((ch = fgetc(infile)) != EOF) {
        if (encode) {
            if ((ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
                if (encode == 1) {
                    ch += encKey;
                } else {
                    ch -= encKey;
                }

                // Wrap around for uppercase letters
                if (ch > 'Z') {
                    ch -= 26;
                } else if (ch < 'A') {
                    ch += 26;
                }
            }
        }

        if (debug) {
            fprintf(stderr, "Character: %c\n", (char)ch);
        }

        fputc(ch, outfile);
    }

    // Close the output stream
    fclose(outfile);
    return 0;
}
