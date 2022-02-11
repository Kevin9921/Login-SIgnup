#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Backend.h"
#include "SQLite_Comm.h"

const char alphabet[] = "abcdefghijklmnopqrstuvwxyz0123456789";

//method to retrieve from Database.txt
char* retrieve(char *userid, char* passcode, char* output){
	printf("\nIn retrive\n");
		
	char* salt = malloc((12) * sizeof(char));
	getSaltDB(userid, salt);
	
	printf("\nSalty %s\n",salt);

	strcat(passcode, salt);
	free(salt);
	
	printf("\nUser provided Passcode %s\n",passcode);
	char *temp = malloc((strlen(passcode)) * sizeof(char));

	strcpy(temp, passcode);
	
	printf("\nPasscode given by user: %s\n", temp);

	char* encrypted = malloc((22) * sizeof(char));
	encrypted = encryptDecrypt(temp);
	printf("\n Encrypted Passcode froim user: %s\n", encrypted);
		
	char* DBPasscode = malloc((22) * sizeof(char));
	getPassDB(userid,DBPasscode);

	char *UserPasscode= malloc((22) * sizeof(char));
	strncpy(UserPasscode,encrypted,22);
	
	printf("\nPasscode %s\n",UserPasscode);
	printf("\n encrypted size %d \n", strlen(UserPasscode));
	printf("\n DBPasscode size %d \n", strlen(DBPasscode));
	printf("\n str val = %d \n", strcmp(UserPasscode, DBPasscode));
	if (!strcmp(UserPasscode, DBPasscode)){
		printf("\n TRUE \n");
		strcpy(output, "TRUE");
	}else{
		strcpy(output, "FALSE");
	}
	free(DBPasscode);
	free(UserPasscode);
	 
	

}

char* encryptDecrypt(char *input) {
	int len = strlen(input);
	char *temp = malloc((len) * sizeof(char));
	char key[] = {'G'}; //Can be any chars, and any size array
	
	int i;
	for(i = 0; i < strlen(input); i++) {
		temp[i] = input[i] ^ key[i % (sizeof(key)/sizeof(char))];
	}
	return temp;
}

//checks if input is valid
void ValidInput(char *userid,char *first, char *last,char *passcode){
	printf("\nin valid\n");
	if(check(passcode)){
		//printf("%s %s %s %s %s \n",userid, first, last, passcode);
		srand(time(NULL));
		
		int passLen = strlen(passcode);
		int maxPasslen = 22;
		
		char* salt = randomString(maxPasslen-passLen);
		char *temp = malloc((maxPasslen) * sizeof(char));
		strcpy(temp, passcode);
		strcat(temp,salt);
		
		printf("\nPasscode: %s\n", temp);
		//char encrypted[strlen(temp)];
		char* encrypted = encryptDecrypt(temp);
		
		char* decrypted = encryptDecrypt(encrypted);
		printf("\nPasscode encrypted: %s\n", encrypted);
		printf("\nPasscode encrypted: %s\n", decrypted);
		AddtoDb(userid,first,last, salt,encrypted);
		
		}
}

char* randomString(int len) {
  char *rstr = malloc((len + 1) * sizeof(char));
  int i;
  for (i = 0; i < len; i++) {
    rstr[i] = alphabet[rand() % (strlen(alphabet))];
  }
  rstr[len] = '\0';
  return rstr;
}

//checks is password is valid
int check(char *Password){

	int UpperCase = 0;
	int LowerCase = 0;
	int NumDigit = 0;
	int SpecialChar = 0;

	int Match = 0;	

	//checks if there is an uppercase, lowercase, number of special character
	int pass = strlen(Password);
	
	if (pass>12 ||pass<8){
		return 0;
	}
	
	for (int i = 0; i< pass; i++){
		if (isupper(Password[i])){
        		UpperCase = 1;
		}else if (islower(Password[i])){
			LowerCase = 1;
		}else if (isdigit(Password[i])){
			NumDigit = 1;
		}else if(!isalnum(Password[i])){
			SpecialChar = 1;
		}
	}
	if (UpperCase && LowerCase && NumDigit && SpecialChar){
		//Match = passwordMatch(Password);
		//passwordFormat(Password);
		//passwordID(Password);
		//if (Match){
		//	return 1;		
		//}
		printf("Passed the check");
		return 1;
	}
	return 0;
}

