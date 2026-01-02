#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

void encrypt() {

    char usrMessage[1000];
    char usrMessageLower[1000];
    usrMessageLower[0] = '\0';
    char buffer[200];
    char bufferLower[1000];
    bufferLower[0] = '\0';
    char characters[200];
    char alphabet[200];
    char alphabetType[15];
    char procced[3];
    char InversionChar[3];
    char inversionMessage[10];
    

    int alphabetChoice;
    int module;
    int i;
    int j;
    bool correct = false;
    bool change = false;
    bool found = false;
    bool hasDuplicates = false;
    bool allLetters = true;
    bool inversion;

    printf("\nEncrypting...\n");

    printf("\nMessage: ");
    printf("\nEnter the Message you want to encrypt: ");
    fgets(usrMessage, sizeof(usrMessage), stdin);

    usrMessage[strcspn(usrMessage, "\n")] = '\0';  

    int usrLen = strlen(usrMessage);

    for (i = 0; i < usrLen; i++) {
        usrMessageLower[i] = tolower((unsigned char)usrMessage[i]);  
    }

    usrMessageLower[usrLen] = '\0';  
    

    printf("\nAlphabet:\n");
    printf("1. Standard (abc...)\n");
    printf("2. Standard++ (abc...123¿?!¡.,)\n");
    printf("3. Custom\n");
    printf("Enter the alphabet you want to use: ");
    fgets(buffer, sizeof(buffer), stdin);
    alphabetChoice = atoi(buffer);

    switch (alphabetChoice) {

        case 1:
        strcpy(alphabet, "abcdefghijklmnopqrstuvwxyz");
        strcpy(alphabetType, "Standard");
        break;

        case 2:
        strcpy(alphabet, "abcdefghijklmnopqrstuvwxyz0123456789.,!?@#$%%^&*()-_+=;:'\"<>/\\ ");
        strcpy(alphabetType, "Standard++");
        break;

        case 3:

        while (!correct)  {

            //Geting Buffer
            printf("\nEnter your custom alphabet: ");
            fgets(buffer, sizeof(buffer), stdin);

            buffer[strcspn(buffer, "\n")] = '\0';  
            int bufLen = strlen(buffer);
            for (i = 0; i < bufLen; i++) {
                bufferLower[i] = tolower((unsigned char)buffer[i]);  
            }
            bufferLower[bufLen] = '\0';  
            
            //Restting flag
            hasDuplicates = false;

            //Checking if duplicate letters
            for (i = 0; i < strlen(bufferLower); i++) { 
                for (j = 0; bufferLower[j] != '\0'; j++) { 
                    if (bufferLower[i] == bufferLower[j] && i != j) { 
                        hasDuplicates = true;
                    } 
                } 
            }

            // If duplicates skip iteration
            if (hasDuplicates) {
                printf("Invalid alphabet!, Duplicates Found.\n");
                continue;

            }

            //Checking If it contains all the letters
            allLetters = true;
            for (i = 0; i < strlen(usrMessageLower); i++) {
                found = false;
                for (j = 0; j < strlen(bufferLower); j++) {
                    if (usrMessageLower[i] == bufferLower[j]) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    allLetters = false;
                    break;
                }
            }

            if (!allLetters) {
                printf("Invalid alphabet!, Not all letters in your Message are present.\n");
                continue;
            }

            printf("Valid alphabet.\n");
            correct = 1;

        }

        strcpy(alphabet, bufferLower);
        strcpy(alphabetType, "Custom");
        break;
        
    }

    printf("\nModule: ");
    printf("\nEnter the module you want to use: ");
    fgets(buffer, sizeof(buffer), stdin);
    module = atoi(buffer);

    printf("\nInversion: ");
    printf("\nApply inversion on encryption (Y/N)? ");
    fgets(buffer, sizeof(buffer), stdin);
    strcpy(InversionChar, buffer);

    InversionChar[strcspn(InversionChar, "\n")] = '\0';
    
    if (!strcmp(InversionChar, "Y") || !strcmp(InversionChar, "y")) {
        inversion = true;
        strcpy(inversionMessage, "Yes");

    } else {
        inversion = false;
        strcpy(inversionMessage, "No");
    }


    printf("\nOverview: \n");
    printf("Message: %s\n", usrMessage);
    printf("Alphabet: %s, '%s'\n", alphabetType, alphabet);
    printf("Module: %d\n", module);
    printf("Apply Inversion: %s\n\n", inversionMessage);

    printf("Procced with encryption (Y/N)? ");
    fgets(procced, sizeof(procced), stdin);

    procced[strcspn(procced, "\n")] = '\0';
    
    if (!strcmp(procced, "N") || !strcmp(procced, "n")) {
        encrypt();
    }

    //encryption

    int len = strlen(usrMessageLower);
    int offset = module%strlen(alphabet);
    int pos;
    char encrypted[1000];
    encrypted[0] = '\0';
    char invertedSentence[1000];
    invertedSentence[0] = '\0';
    


    found = false;

    for (i = 0; i < len; i++) {
        found = false;
        for (j = 0; alphabet[j] != '\0'; j++) {
            if (alphabet[j] == usrMessageLower[i]) {
                pos = j;
                found = true;
                break;
            }
        }

        if (!found) {
            size_t encryptLen = strlen(encrypted);
            encrypted[encryptLen] = usrMessageLower[i];
            encrypted[encryptLen + 1] = '\0';

        } else {

            size_t encryptLen = strlen(encrypted);

            if (isalpha(usrMessage[i]) && isupper(usrMessage[i])) {
                encrypted[encryptLen] = toupper(alphabet[(pos + offset) % strlen(alphabet)]);
            } else {
                encrypted[encryptLen] = alphabet[(pos + offset) % strlen(alphabet)];
            }

            encrypted[encryptLen + 1] = '\0';
        }
        
    }

    size_t encryptLen = strlen(encrypted);

    if (inversion) {
        for (int i = encryptLen - 1; i >= 0; i--) {
            size_t invertedLen = strlen(invertedSentence);
            invertedSentence[invertedLen] = encrypted[i];
            invertedSentence[invertedLen + 1] = '\0';
        }
        
        strcpy(encrypted, invertedSentence);
    }


    printf("\n-------------------------------------------\n");
    printf("Encrypted Message: \n %s\n", encrypted);
    printf("-------------------------------------------\n\n");

}

void decrypt() {

    char usrMessage[1000];
    char alphabet[200];
    char buffer[200];
    char alphabetType[15];
    char bufferLower[1000];
    bufferLower[0] = '\0';
    char usrMessageLower[1000];
    usrMessageLower[0] = '\0';
    char inversionChar[3];
    char procced[3];
    char inversionStr[20];
    char target;
    char decryptedMessage[1000];
    decryptedMessage[0] = '\0';
    char inverted[1000];
    
    int alphabetChoice;
    int letter;
    int differentLetter;
    int j;
    int i;
    int module;
    int pos;

    bool correct = false;
    bool hasDuplicates = false;
    bool allLetters = true;
    bool found = false;
    bool inversion;



    printf("\nDecrypting...\n");

    printf("\nMessage: ");
    printf("\nEnter the Message you want to decrypt: ");
    fgets(usrMessage, sizeof(usrMessage), stdin);

    usrMessage[strcspn(usrMessage, "\n")] = '\0';  

    int usrLen = strlen(usrMessage);

    for (i = 0; i < usrLen; i++) {
        usrMessageLower[i] = tolower((unsigned char)usrMessage[i]);  
    }

    usrMessageLower[usrLen] = '\0';  
    

    printf("\nAlphabet:\n");
    printf("1. Standard (abc...)\n");
    printf("2. Standard++ (abc...123¿?!¡.,)\n");
    printf("3. Custom\n");
    printf("Enter the alphabet the mesagge is encrypted with: ");
    fgets(buffer, sizeof(buffer), stdin);
    alphabetChoice = atoi(buffer);

    switch (alphabetChoice) {

        case 1:
        strcpy(alphabet, "abcdefghijklmnopqrstuvwxyz");
        strcpy(alphabetType, "Standard");
        break;

        case 2:
        strcpy(alphabet, "abcdefghijklmnopqrstuvwxyz0123456789.,!?@#$%%^&*()-_+=;:'\"<>/\\ ");
        strcpy(alphabetType, "Standard++");
        break;

        case 3:

        while (!correct)  {

            //Geting Buffer
            printf("\nEnter your custom alphabet: ");
            fgets(buffer, sizeof(buffer), stdin);

            buffer[strcspn(buffer, "\n")] = '\0';  
            int bufLen = strlen(buffer);
            for (i = 0; i < bufLen; i++) {
                bufferLower[i] = tolower((unsigned char)buffer[i]);  
            }
            bufferLower[bufLen] = '\0';  
            
            //Restting flag
            hasDuplicates = false;

            //Checking if duplicate letters
            for (i = 0; i < strlen(bufferLower); i++) { 
                for (j = 0; bufferLower[j] != '\0'; j++) { 
                    if (bufferLower[i] == bufferLower[j] && i != j) { 
                        hasDuplicates = true;
                    } 
                } 
            }

            // If duplicates skip iteration
            if (hasDuplicates) {
                printf("Invalid alphabet!, Duplicates Found.\n");
                continue;

            }

            //Checking If it contains all the letters
            allLetters = true;
            for (i = 0; i < strlen(usrMessageLower); i++) {
                found = false;
                for (j = 0; j < strlen(bufferLower); j++) {
                    if (usrMessageLower[i] == bufferLower[j]) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    allLetters = false;
                    break;
                }
            }

            if (!allLetters) {
                printf("Invalid alphabet!, Not all letters in your Message are present.\n");
                continue;
            }

            printf("Valid alphabet.\n");
            correct = 1;

        }

        strcpy(alphabet, bufferLower);
        strcpy(alphabetType, "Custom");
        break;
        
    }

    printf("\nInversion:\n");
    printf("(if you don't know, leave it empty)\n");
    printf("Is your message inverted (Y/N)? ");

    fgets(inversionChar, sizeof(inversionChar), stdin);

    inversionChar[strcspn(inversionChar, "\n")] = '\0';

    if (!strcmp(inversionChar, "Y") || !strcmp(inversionStr, "y")) {
        inversion = 1;
        strcpy(inversionStr, "Yes");
    } else if (!strcmp(inversionChar, "N") || !strcmp(inversionChar, "n")) {
        inversion = 0;
        strcpy(inversionStr, "No");
    } else {
        inversion = 2;
        strcpy(inversionStr, "Don't Know");
    }

    printf("\n\nOverview:\n");
    printf("Message: %s\n", usrMessage);
    printf("Alphabet: %s, '%s'\n", alphabetType, alphabet);
    printf("Inversion: %s\n", inversionStr);

    printf("\nProcced with decryption (Y/N)? ");
    fgets(procced, sizeof(procced), stdin);

    procced[strcspn(procced, "\n")] = '\0';
    
    if (!strcmp(procced, "N") || !strcmp(procced, "n")) {
        decrypt();
    }


    //decryption

    int lenAlphabet = strlen(alphabet);
    int usrlen = strlen(usrMessage);
    found = false;

    for (module = 1; module <= lenAlphabet; module++) {

        decryptedMessage[0] = '\0';
        
        for (letter = 0; letter < usrLen; letter++) {
            found = false;
            for (differentLetter = 0; alphabet[differentLetter] != '\0'; differentLetter++) {

                if (usrMessageLower[letter] == alphabet[differentLetter]) {
                    pos = differentLetter;
                    found = true;
                    break;
                }
            }

            if (!found) {
                size_t decryptedLen = strlen(decryptedMessage);
                decryptedMessage[decryptedLen] = usrMessageLower[letter];
                decryptedMessage[decryptedLen + 1] = '\0';

            } else {

                size_t decryptLen = strlen(decryptedMessage);

                int shiftedPos = (pos - module + lenAlphabet) % lenAlphabet;

                if (isalpha(usrMessage[letter]) && isupper(usrMessage[letter])) {
                    decryptedMessage[decryptLen] = toupper(alphabet[shiftedPos]);
                } else {
                    decryptedMessage[decryptLen] = alphabet[shiftedPos];
                }

                decryptedMessage[decryptLen + 1] = '\0';
            }
        
        }

        size_t decryptedLen = strlen(decryptedMessage);

        for (int i = 0; i < decryptedLen; i++) {
            inverted[i] = decryptedMessage[decryptedLen - 1 - i];
        }
        
        inverted[decryptedLen] = '\0';
        
        if (inversion == 0) {
            printf("Module: %d (Normal)\n%s\n\n", module, decryptedMessage);
        } else if (inversion == 1) {
            printf("Module: %d (Inverted)\n%s\n\n", module, inverted);
        } else {
            printf("Module: %d (Normal)\n%s\n\n", module, decryptedMessage);
            printf("Module: %d (Inverted)\n%s\n\n", module, inverted);
        }
    
    }
}

int main() {

    bool run = true;

    while (run) {

        printf("\nCeaser Cipher.\n");
        printf("1. Encrypt.\n"),
        printf("2. Decrypt.\n");
        printf("3. Quit..\n");

        char buffer[3];

        printf("\nEnter your desire selection (1/2/3): ");
        fgets(buffer, 3, stdin);

        printf("\n-------------------------------------------\n");

        int selection = atoi(buffer);

        switch (selection) {

            case 1:
            encrypt();
            break;

            case 2:
            decrypt();
            break;

            case 3:
            printf("\nQuitting...\n\n");
            run = false;
            
        }
    }




    return 0;
}