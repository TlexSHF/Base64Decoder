#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "base64decoder.h"

void decode64(char *szText, int iTextSize) {
    int i;
    int i64Size = 6;
    int *iBinArr;
    int iBase64;
    int *iDecArr;

    resetBinFile();

    iBinArr = malloc(sizeof(int) * i64Size);
    if(iBinArr == NULL) {
        printf("error in malloc iBinArr\r\n");
    } else {
        memset(iBinArr, 0, sizeof(int) * i64Size);

        for(i = 0; i < iTextSize; i++) {
            iBase64 = base64AsciiToInt(szText[i]);

            if(iBase64 == ERROR) {
                //-1/ERROR indicates the number was not base64
                printf("number %i on %i cant be converted\r\n", szText[i], i);
            } else {
                    decToBin(iBase64, iBinArr, i64Size);
                    appendBinToFile(iBinArr, i64Size);
            }
        }
        free(iBinArr);

        //iDecArr is same length as szText
        iDecArr = malloc(sizeof(int) * iTextSize);
        if(iDecArr == NULL) {
            printf("malloc failed iDecArr\r\n");
        } else {
            memset(iDecArr, 0, sizeof(int) * iTextSize);
            binFileToDec(iDecArr, iTextSize);

            for(i = 0; i < iTextSize; i++) {
                szText[i] = (char) iDecArr[i];
            }

            free(iDecArr);
        }
    }
}
void resetBinFile() {
    FILE *fpBin = fopen("binaryFile.dat", "wb");
    fclose(fpBin);
}
/* CONVERTS A BASE64 ASCII TO ITS CORRESPONDING INT VALUE */
int base64AsciiToInt(char cAscii) {
    int i;
    int iValue = -1; //-1 as default "fail check" value
    const char cBase64Table[] = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G',
            'H', 'I', 'J', 'K', 'L', 'M', 'N',
            'O', 'P', 'Q', 'R', 'S', 'T', 'U',
            'V', 'W',  'X', 'Y', 'Z',
            'a', 'b', 'c', 'd', 'e', 'f', 'g',
            'h', 'i', 'j', 'k', 'l', 'm', 'n',
            'o', 'p', 'q', 'r', 's', 't', 'u',
            'v', 'w', 'x', 'y', 'z',
            '0', '1', '2', '3', '4', '5', '6',
            '7', '8', '9', '+', '/', '='
    };

    //Including the '=' padding
    for(i = 0; i < 65; i++) {
        if(cAscii == cBase64Table[i]) {
            iValue = i;
            break;
        }
    }
    return iValue;
}
/* CONVERTS A DECIMAL TO BINARY AND STORES IN OPPOSITE WAY A ARRAY */
void *decToBin(int iDec, int *iBinArr, int iSize) {
    int i = iSize - 1;

    while(iDec >= 0 && i >= 0) {
        iBinArr[i] = iDec % 2;
        iDec = iDec / 2;
        i--;
    }
}
/* CONVERTS 6bit INT TO CORRESPONDING BINARY */
/* & Appends the bin result to file */
void appendBinToFile(int *iSextet, int iSize) {
    int i;
    FILE *fpBin;
    fpBin = fopen("binaryFile.dat", "ab");
    if(fpBin == NULL) {
        printf("error opening binary file\r\n");
    } else {
        //Successfully opened binary file

        for(i = 0; i < iSize; i++) {
            fprintf(fpBin, "%i", iSextet[i]);
        }
    }
    fclose(fpBin);
}
void binFileToDec(int *iDecArr, int iSize) {
    int i = 0;
    int i8 = 0; //counts only to 8
    int iInput[8];
    int iConverted;
    FILE *fpBin = fopen("binaryFile.dat", "rb");
    if(fpBin == NULL) {
        printf("error opening bin file\r\n");
    } else {

        while(!feof(fpBin)) {

            //Gets the ascii value and subtracts with the ascii value for '0' (48)
            //This results in getting the numbers directly into the iInput
            iInput[i8] = fgetc(fpBin) - '0';

            //Every 8th digits will be converted
            if(i8+1 == 8) {
                iConverted = binToDec( iInput, 8);
                if(iConverted == ERROR) {
                    printf("decimal conversion went wrong\r\n");
                    break;
                } else {
                    iDecArr[i] = iConverted;
                    i8 = 0;
                    i++;
                }
            } else {
                i8++;
                if(i == iSize) {
                    printf("binary file larger than decimal array\r\n");
                    break;
                }
            }
        }
    }
}
int binToDec(int *iBinArr, int iSize) {
    int i;
    int iExponent = 0;
    double dDec = 0;
    for(i = iSize-1; i >= 0; i--) {
        if(iBinArr[i] != 0 && iBinArr[i] != 1) {
            printf("invalid binary number: %i\r\n", iBinArr[i]);
            dDec = ERROR;
            break;
        } else {
            dDec += iBinArr[i] * pow(2, iExponent);
            iExponent++;
        }
    }
    return (int) dDec;
}

