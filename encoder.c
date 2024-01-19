#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int debug = 1;
    int encode = 0;
    const char *encKey = 0;
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
            encKey = argv[i] + 2;
        }
         if (argv[i][1] == 'D') {
             if (argv[i][0] == '-'){
                 debug = 0;
             }
             else if (argv[i][0] == '+'){
                 debug = 1;
             }
        }
         if (argv[i][0] == '-' && argv[i][1] == 'I'){
             infile = fopen(argv[i] + 2, "r");
             if (infile == NULL) {
                 fprintf(stderr, "Error: Cannot open input file %s\n", argv[i] + 2);
                 exit(1);
             }
         }
        if (argv[i][0] == '-' && argv[i][1] == 'O'){
            outfile = fopen(argv[i] + 2, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Error: Cannot open output file %s\n", argv[i] + 2);
                exit(1);
            }
        }
    }
    const char *encTmp = encKey;
    do{
       char ch= fgetc(infile);
       int keyDig = *encTmp - '0';
       if (feof(infile)) {
           break;
       }
        if (encode) {
            if (ch >= 'A' && ch <= 'Z') {
                if (encode == 1) {
                    ch += keyDig;
                } else {
                    ch -= keyDig;
                }

                // Wrap around for uppercase letters
                if (ch > 'Z') {
                    ch -= 26;
                } else if (ch < 'A') {
                    ch += 26;
                }
            }
            else if (ch >= '0' && ch <= '9') {
                if (encode==1){
                    ch = '0' + (ch + keyDig - '0');
                }
                else {
                    ch = '0' + (ch - keyDig - '0');
                }
            }
        }

        encTmp++;

        // If we reached the end of the encoding key, reset to the beginning
        if (*encTmp == '\0') {
            encTmp = encKey;
        }
        fputc(ch, outfile);
    } while(1);

    if (outfile != stdout) {
        fclose(outfile);
    }

    if (infile != stdin) {
        fclose(infile);
    }
    return 0;
}
