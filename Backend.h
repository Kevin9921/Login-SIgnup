#define MAXCHAR 1000

char id[MAXCHAR]; 
char buff[MAXCHAR];

int check(char *Password);
int passwordMatch(char *Password);
void add(char *userid,char *first, char *last, char* salt, char *passcode);
char* retrieve(char *userid, char* passcode, char* output);
void ValidInput(char *userid,char *first, char *last, char *passcode);
char *randomString(int len);
char* encryptDecrypt(char *input);

