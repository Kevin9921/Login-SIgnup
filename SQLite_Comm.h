int AddtoDb(char *userid, char *first, char* salt, char *last, char *passcode);
int Startup();
void getFromDB(char *userid, char *passcode);
void getSaltDB(char *userid, char* output);
void getPassDB(char *userid, char* output);
