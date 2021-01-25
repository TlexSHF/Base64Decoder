#ifndef OPPGAVE_5_BASE64CONVERTER_H
#define OPPGAVE_5_BASE64CONVERTER_H
#define ERROR -1

void decode64(char *szText, int iTextSize);
void resetBinFile();
int base64AsciiToInt(char cAscii);
void *decToBin(int iDec, int *iBinArr, int iSize);
void appendBinToFile(int *iSextet, int iSize);
void binFileToDec(int *iDecArr, int iSize);
int binToDec(int *iBinArr, int iSize);

#endif //OPPGAVE_5_BASE64CONVERTER_H
