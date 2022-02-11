# Login-Signup

This project is coded in C utilizing Linux - Ubuntu. 
Database was created and modified using Sqlite3 code. 
Front end was done using the Glade RAD Tool to enable GUI development for the GTK toolkid 
and GNOME desktop environment

------------Log In page---------------
When a user wants to login they must put in user name and password. if Username and password is match 
then user will be redirected to welcome page. 


------------Sign Up page---------------
When a user wants to signup they must proceed to the signup page and follow the signup instructions;
If the password does not meet the requirements the account will not be added. If the account passes the
check a randomly generated salt will be added to the password then the password will by encrypted using an
XOR algorithm. User id, First name, Last name, salt and Encrypted password will be added to the Database.

