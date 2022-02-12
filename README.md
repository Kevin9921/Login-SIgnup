# Login-Signup


------------Design---------------
•This project is a Log-In/Sign-Up system utilizing the C programming language, assembled in the linux-Ubuntu OS 

•	Designed Log-In and Sign-Up windows harnessing the Glade RAD Tool enabling GUI development for the GTK toolkit and GNOME desktop environment 

•	Constructed Backend for storing/retrieving user data (user id, first name, last name, password, salt) into a database, built using the SQLite3 rational database management library 


------------Security---------------
•	Ensures all passwords in the sign-up page meet privacy standards before account can be created and stored in database

•	Generates a random salt (String) upon account creation to append to user password, preventing against dictionary attacks

•	Encrypts the user password with the appended salt using XOR encryption then stores the salt and encrypted password into the database to prevent against breach of user information in case the database was hacked.


------------Log In page---------------

When a user wants to login they must put in user name and password. if Username and password is match 
then user will be redirected to welcome page. 


------------Sign Up page---------------

When a user wants to signup they must proceed to the signup page and follow the signup instructions.
If the password does not meet the requirements the account will not be added. 

