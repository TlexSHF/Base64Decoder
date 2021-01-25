#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64decoder.h"

int main(int argc, char **argv) {
    int i = 0;
    int j;
    int c = 0;
    FILE *fpBase64, *fpDecoded;
    int iSize = 512; //Length of text
    char *szText = malloc(sizeof(char) * iSize);

    if(szText == NULL) {
        printf("error in malloc: szText");
    } else {
        memset(szText, 0, sizeof(char) * iSize);

        fpBase64 = fopen("base64.txt", "r");
        if(fpBase64 == NULL) {
            printf("error opening base64 file \r\n");
        } else {
            printf("success opening base64 file \r\n");

            c = fgetc(fpBase64);
            while(c != EOF) {
                szText[i] = c;
                i++;

                c = fgetc(fpBase64);
            }

            //Here all the decoding happens
            decode64(szText, i);

            fpDecoded = fopen("decoded.txt", "w");
            if(fpDecoded == NULL) {
                printf("error opening decoded file\r\n");
            } else {
                printf("success opening decoded file\r\n");

                for(j = 0; j < i; j++) {
                    if(szText[j] == 0) {
                        //End of translated characters
                        break;
                    } else {
                        fputc(szText[j], fpDecoded);
                    }
                }

                fclose(fpDecoded);
                printf("closing decoded file\r\n");
            }
            fclose(fpBase64);
            printf("closing base64 file\r\n");
        }
        free(szText);
    }
    printf("check the 'decoded.txt' to view results\r\n");

   return 0;
}