#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h> 

int Encrypt(char * FILENAME, char * OUTPUT) {
    
    char key1 = "";
    char key2 = "";
    
    int inputcheck1 = 0;
    printf("Enter the First Key: (A Character or A Single Digit)\n");
    while(inputcheck1 == 0) {
        
        scanf(" %c", &key1);
        
        if(isdigit(key1) || isspace(key1) || isalpha(key1)) {
            inputcheck1 = 1; //exit loop when one of the conditions are met
        }
        
        else { printf("Error:Re-Enter, A Character or Single Digit For Key1: \n"); }
    } //Input with error checking for first key.
    
    int inputcheck2 = 0;
    printf("Enter the Second Key: (A Character or A Single Digit)\n");
    while(inputcheck2 == 0) {
        
        scanf(" %c", &key2);
        
        if(isdigit(key2) || isspace(key2) || isalpha(key2)) {
            inputcheck2 = 1; //exit loop when one of the condition are met.
        }
        else { printf("Error:Re-Enter, A Character or Single Digit For Key2: \n"); }
    } //Input with error checking for second key.
    
    
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
                left = left ^ key1;
                Byte = (right << 8) | left;
                if (fputc(Byte, outF) == EOF) {
                    printf("Error");
                    exit(3);
                }
            }
                while ((Byte = fgetc(inF)) != EOF) { //Second Iteration of Encryption Algorithm

                left = Byte & ( (1<<8) -1);
                right = Byte & ( (9<<16) -1);
                left = left ^ key2;
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
    
    char key1 = "";
    char key2 = "";
    
    int inputcheck1 = 0;
    printf("Enter the First Key: (A Character or A Single Digit)\n");
    while(inputcheck1 == 0) {
        
        scanf(" %c", &key1);
        
        if(isdigit(key1) || isspace(key1) || isalpha(key1)) {
            inputcheck1 = 1; //exit loop when one of the condition are met
        }
        
        else { printf("Error:Re-Enter, A Character or Single Digit For Key1: \n"); }
    }
    
    int inputcheck2 = 0;
    printf("Enter the Second Key: (A Character or A Single Digit)\n");
    while(inputcheck2 == 0) {
        
        scanf(" %c", &key2);
        
        if(isdigit(key2) || isspace(key2) || isalpha(key2)) {
            inputcheck2 = 1; //exit loop when one of the conditions are met.
        }
        else { printf("Error:Re-Enter, A Character or Single Digit For Key2: \n"); }
    }
    
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
        Decryption algorithm moves the bits to the original position of the shifted bits, thus revealing
        the original message within the .txt file/
        */

                Byte = (Byte ^ key1) & 0xFF; //First Iteration of Decryption Algorithm
                if (fputc(Byte, outF) == EOF) {
                    printf("Error");
                    exit(3);
                }
            }
            while ((Byte = fgetc(inF)) != EOF) { //Second Iteration od Decryption Algorithm

                Byte = (Byte ^ key2) & 0xFF;
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

    char data[500], choice, encFile[550] = "encryptedOutput.txt"; //data file and output file
    char decFile[550] = "decryptedOutput.txt";  //allocated more space for output, will not be same size as data file.

    printf("Enter E to Encrypt a File or D to Decrypt an Existing File: \n"); //prompt user

    while(choice != 'E' && choice != 'D') {

        scanf(" %100s", &choice);           
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
