#include <sqlite3.h> 
#include <stdio.h>
#include <string.h>
#include "SQLite_Comm.h"
#include "Backend.h"
#include <stdlib.h>

int Startup(){
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("test.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
   
   char *sql = "DROP TABLE IF EXISTS test.db;" 
                "CREATE TABLE UsersData(UserId TEXT, First Name TEXT, last Name TEXT, Salt TEXT, Passcode TEXT);";
              
   rc = sqlite3_exec(db, sql, 0, 0, 0);
   sqlite3_close(db);
}

void getFromDB(char *userid, char *passcode){
	sqlite3* db;
	sqlite3_open("test.db", &db);
	char** temp;
	// rc = sqlite3_open_v2(argc[1], &db, SQLITE_OPEN_READONLY, NULL);
	sqlite3_stmt *stmt;
	
	if ( sqlite3_prepare_v2(
		db, 
		"SELECT * FROM UsersData WHERE UserId= ? AND Passcode= ?",  // stmt
		-1, // If than zero, then stmt is read up to the first nul terminator
		&stmt,
		 0  // Pointer to unused portion of stmt
	       )
	       != SQLITE_OK) {
	    printf("\nCould not prepare statement.");
  	}
  	
  	// used to bind the userid to the statement
  	if (sqlite3_bind_text (
		stmt,
		1,  // Index of wildcard
		userid,  //sends user id 
		strlen(userid),  // length of text
		SQLITE_STATIC
		)
	      != SQLITE_OK) {
	    printf("\nCould not bind int.\n");
	}
	
	//used to bind the salt to the statment 
	if (sqlite3_bind_text (
		stmt,
		2,  // Index of wildcard
		passcode, //sends passcode
		strlen(passcode),  // length of text
		SQLITE_STATIC
		)
	      != SQLITE_OK) {
	    printf("\nCould not bind int.\n");
	}
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		printf("Userid %s: ", sqlite3_column_text(stmt, 0));
        	printf("First %s\n", sqlite3_column_text(stmt, 1));
        	printf("last %s\n", sqlite3_column_text(stmt, 2));
        	printf("salt %s\n", sqlite3_column_text(stmt, 3));
        	printf("passcode %s\n", sqlite3_column_text(stmt, 4));
 	}else{
		printf("\nCould not step (execute) stmt.\n");
 	}
 	sqlite3_finalize(stmt);
 	sqlite3_close(db);
 	//return temp;
} 

void getPassDB(char *userid, char* output){
	sqlite3* db;
	sqlite3_open("test.db", &db);
	const unsigned char *name,*state;
	char *temp; 
	printf("\nGetting Passcode\n");
	// rc = sqlite3_open_v2(argc[1], &db, SQLITE_OPEN_READONLY, NULL);
	sqlite3_stmt *stmt;
	
	if ( sqlite3_prepare_v2(
		db, 
		"SELECT Passcode FROM UsersData WHERE UserId= ?",  // stmt
		-1, // If than zero, then stmt is read up to the first nul terminator
		&stmt,
		 0  // Pointer to unused portion of stmt
	       )
	       != SQLITE_OK) {
	    printf("\nCould not prepare statement.");
  	}
  	printf("\nPrepare\n");
  	// used to bind the userid to the statement
  	if (sqlite3_bind_text (
		stmt,
		1,  // Index of wildcard
		userid,  //sends user id 
		strlen(userid),  // length of text
		SQLITE_STATIC
		)
	      != SQLITE_OK) {
	    printf("\nCould not bind int.\n");
	}
	
	printf("\nBinding\n");
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		name = sqlite3_column_text(stmt, 0);
		strcpy(output,name);
		printf("\n Passcode: %s \n", output);
 	}else{
		printf("\nCould not step (execute) stmt.\n");
 	}
 	printf("\nDone\n");
 	sqlite3_finalize(stmt);
 	sqlite3_close(db);
 	printf("\n Passcode2: %s \n", output);
 	return;
} 

void getSaltDB(char *userid, char* output){
	sqlite3* db;
	sqlite3_open("test.db", &db);
	const unsigned char *name,*state;
	char *temp; 
	printf("\nGetting Salt\n");
	// rc = sqlite3_open_v2(argc[1], &db, SQLITE_OPEN_READONLY, NULL);
	sqlite3_stmt *stmt;
	
	if ( sqlite3_prepare_v2(
		db, 
		"SELECT Salt FROM UsersData WHERE UserId= ?",  // stmt
		-1, // If than zero, then stmt is read up to the first nul terminator
		&stmt,
		 0  // Pointer to unused portion of stmt
	       )
	       != SQLITE_OK) {
	    printf("\nCould not prepare statement.");
  	}
  	printf("\nPrepare\n");
  	// used to bind the userid to the statement
  	if (sqlite3_bind_text (
		stmt,
		1,  // Index of wildcard
		userid,  //sends user id 
		strlen(userid),  // length of text
		SQLITE_STATIC
		)
	      != SQLITE_OK) {
	    printf("\nCould not bind int.\n");
	}
	
	printf("\nBinding\n");
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		name = sqlite3_column_text(stmt, 0);
		strcpy(output,name);
		printf("\nSalt: %s \n", output);
 	}else{
		printf("\nCould not step (execute) stmt.\n");
 	}
 	printf("\nDone\n");
 	sqlite3_finalize(stmt);
 	sqlite3_close(db);
 	printf("\nSalt2: %s \n", output);
 	return;
} 

int AddtoDb(char *userid, char *first, char *last,char* salt, char *passcode){
	sqlite3* db;
	sqlite3_open("test.db", &db);
	sqlite3_stmt *stmt;
	
	//creates a SQLite statement
	if ( sqlite3_prepare_v2(
		db, 
		"insert into UsersData values (?,?,?,?,?)",  // stmt
		-1, // If than zero, then stmt is read up to the first nul terminator
		&stmt,
		 0  // Pointer to unused portion of stmt
	       )
	       != SQLITE_OK) {
	    printf("\nCould not prepare statement.");
	    return 1;
  	}
  	if (sqlite3_bind_text (
		stmt,
		1,  // Index of wildcard
		userid,  //sends user id 
		strlen(userid),  // length of text
		SQLITE_STATIC
		)
	      != SQLITE_OK) {
	    printf("\nCould not bind int.\n");
	    return 1;
	}
	
	if (sqlite3_bind_text (
		stmt,
		2,  // Index of wildcard
		first,  //sends first name
		strlen(first),  // length of text
		SQLITE_STATIC
		)
	      != SQLITE_OK) {
	    printf("\nCould not bind int.\n");
	    return 1;
	}
	
	if (sqlite3_bind_text (
		stmt,
		3,  // Index of wildcard
		last, //sends last name
		strlen(last),  // length of text
		SQLITE_STATIC
		)
	      != SQLITE_OK) {
	    printf("\nCould not bind int.\n");
	    return 1;
	}
	
	if (sqlite3_bind_text (
		stmt,
		4,  // Index of wildcard
		salt, //sends salt
		strlen(salt),  // length of text
		SQLITE_STATIC
		)
	      != SQLITE_OK) {
	    printf("\nCould not bind int.\n");
	    return 1;
	}
	
	if (sqlite3_bind_text (
		stmt,
		5,  // Index of wildcard
		passcode, //sends Passcode
		strlen(passcode),  // length of text
		SQLITE_STATIC
		)
	      != SQLITE_OK) {
	    printf("\nCould not bind int.\n");
	    return 1;
	}   
	if (sqlite3_step(stmt) != SQLITE_DONE) {
	    printf("\nCould not step (execute) stmt.\n");
	    return 1;
 	}
 	sqlite3_finalize(stmt);
 	sqlite3_close(db);
 }











