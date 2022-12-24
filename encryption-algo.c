#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int Encrypt(char * FILENAME, char * OUTPUT) {

    char key1[] = "", key2[] = "";  //Empty keys to take in input

    printf("Enter the First Key: (A Character or A Single Digit)\n");
    while(key1 == NULL || key1[0] == '\0' || strlen(key1) != 1) {
        scanf(" %s", key1);

        if(strlen(key1) != 1) {printf("Error:Re-Enter, A Character or Single Digit For Key1: \n");}
        else if(key1 == NULL || key1[0] == '\0') {printf("Empty, A Character or A Single Digit: \n");}
    } //Take in input with error checking

    printf("Enter the Second Key: (A Character or A Single Digit)\n");
    while(key2 == NULL || key2[0] == '\0' || strlen(key2) != 1) {
        scanf(" %s", key2);

        if(strlen(key2) != 1) {printf("Error:Re-Enter, A Character or Single Digit For Key2: \n");}
        else if(key2 == NULL || key2[0] == '\0') {printf("Empty, A Character or A Single Digit: \n");}
    } //Take in input with error checking

    FILE *inF; //input file pointer
    FILE *outF; //output file pointer
    unsigned int Byte;
    unsigned char left;
    unsigned char right;

    inF = fopen(FILENAME,"r"); //file to be read from
    outF = fopen(OUTPUT, "w");  //file that will be written to

    if (0 != access(OUTPUT, W_OK)) { //check if output file can be written to, if not exit
        printf("Output File Cannot be Written To: \n");
        exit(1);
    } //error checking

    if(inF == NULL) {
        printf("Error in Opening File or File Does Not Exist. \n");
        exit(2);
    } else {
        printf("File Opened, Encrypting Destination: encryptedOuput.txt \n");
        
        /*
        Encryption Algorithm utilizes bit shifting and shifts the binary representation of each character
        to the left or right by a pre-defined number of positions.
        */
            while ((Byte = fgetc(inF)) != EOF) { //Implement Encryption algorithm

                left = Byte & ( (1<<8) -1);
                right = Byte & ( (9<<16) -1);
                left = left ^ key1[0];
                Byte = (right << 8) | left;
                if (fputc(Byte, outF) == EOF) {
                    printf("Error");
                    exit(3);
                }
            }
                while ((Byte = fgetc(inF)) != EOF) { //Second Iteration of Encryption Algorithm

                left = Byte & ( (1<<8) -1);
                right = Byte & ( (9<<16) -1);
                left = left ^ key2[0];
                Byte = (right << 8) | left;
                if (fputc(Byte, outF) == EOF) {
                    printf("Error");
                    exit(4);
                }
            }
    printf("\nEnd of File, Successfully Encrypted. \n");
    }
    fclose(inF); //close to prevent memory leak
    fclose(outF);
}

int Decrypt(char * FILENAME, char * OUTPUT) {

    char key1[] = "", key2[] = "";  //Empty keys to take in input

    printf("Enter the First Key: (A Character or A Single Digit)\n");
    while(key1 == NULL || key1[0] == '\0' || strlen(key1) != 1) {
        scanf(" %s", key1);

        if(strlen(key1) != 1) {printf("Error:Re-Enter, A Character or Single Digit For Key1: \n");}
        else if(key1 == NULL || key1[0] == '\0') {printf("Empty, A Character or A Single Digit: \n");}
    } //Take in input with error checking

    printf("Enter the Second Key: (A Character or A Single Digit)\n");
    while(key2 == NULL || key2[0] == '\0' || strlen(key2) != 1) {
        scanf(" %s", key2);

        if(strlen(key2) != 1) {printf("Error:Re-Enter, A Character or Single Digit For Key2: \n");}
        else if(key2 == NULL || key2[0] == '\0') {printf("Empty, A Character or A Single Digit: \n");}
    } //Take in input with error checking

    FILE *inF;
    FILE *outF;
    unsigned int Byte;
    unsigned char left;
    unsigned char right;

    inF = fopen(FILENAME,"r");  //file to be read from
    outF = fopen(OUTPUT, "w");  //file that will be written to

    if (0 != access(OUTPUT, W_OK)) {//check if output file can be written to, if not exit
        printf("Output File Cannot be Written To: \n");
        exit(1);
    }

    if(inF == NULL) {
        printf("Error in Opening File or File Does Not Exist. \n");
        exit(2);
    } else {
        printf("File Opened, Decrypting Destination: decryptedOuput.txt \n");
        while ((Byte = fgetc(inF)) != EOF) {
            
        /*
        Encryption Algorithm utilizes bit shifting and shifts the binary representation of each character
        to the left or right by a pre-defined number of positions.
        Decryption algorithm moves the bits to before original position of the shifted bits, thus revealing
        the original message within the .txt file/
        */

                Byte = (Byte ^ key1[0]) & 0xFF; //First Iteration of Decryption Algorithm
                if (fputc(Byte, outF) == EOF) {
                    printf("Error");
                    exit(3);
                }
            }
            while ((Byte = fgetc(inF)) != EOF) { //Second Iteration od Decryption Algorithm

                Byte = (Byte ^ key2[0]) & 0xFF;
                if (fputc(Byte, outF) == EOF) {
                    printf("Error");
                    exit(4);
                }
            }
    printf("\nEnd of File, Successfully Decrypted. \n");
    }
    fclose(inF); //close to prevent memory leak
    fclose(outF);
}

int main() {

    char data[500], choice[51], encFile[550] = "encryptedOutput.txt"; //data file and output file
    char decFile[550] = "decryptedOutput.txt";  //allocated more space for output, will not be same size as data file.

    printf("Enter E to Encrypt a File or D to Decrypt an Existing File: \n"); //prompt user

    while(choice != 'E' && choice != 'D') {

        scanf(" %50c", &choice);
        if(choice != 'E' && choice != 'D') {printf("Error: Re-Enter E or D: \n");}
                //error checking, re enter if incorrect.
    }
    //choice of decryption or encryption for based on user input.
    if(choice == 'E') {
        printf("Enter the Source Filename: \n");//file to encrypt
        scanf(" %s",data);
        Encrypt(data, encFile); //do Encryption
    }
    else if(choice == 'D') {
        printf("Enter Filename to be Decrypted: \n");//file to be decrypted(must be encrypted)
        scanf(" %s",data);
        Decrypt(data, decFile); //do Decryption
    }
    return 0;
}
