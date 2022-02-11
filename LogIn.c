#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include "Backend.h"
#include "SQLite_Comm.h"
#include <gdk/gdk.h>




GtkWidget	*window;
GtkWidget	*window2;
GtkWidget	*welcomeScreen;
GtkWidget	*fixed1;
GtkWidget	*signUpButt;
GtkWidget	*logInButt;
GtkWidget	*label;

// text box for username and password for Login page
GtkWidget	*userName;
GtkWidget	*password;

// text box username, first name, login, password for sign up page
GtkWidget	*userName2;
GtkWidget	*password2;
GtkWidget	*lastName2;
GtkWidget	*firstName2;

//TextBuffer for username and password for Login page
GtkTextBuffer	*TextBuffer; 
GtkTextBuffer	*TextBuffer2; 

// TextBuffer username, first name, login, password for sign up page
GtkTextBuffer	*TextBuffer3; 
GtkTextBuffer	*TextBuffer4; 
GtkTextBuffer	*TextBuffer5; 
GtkTextBuffer	*TextBuffer6; 

GtkBuilder	*builder; 

void	on_changed_text(GtkTextBuffer *t);

int main(int argc, char *argv[]) {
	
	Startup(); // startup the database
	gtk_init(&argc, &argv); // init Gtk
	builder = gtk_builder_new_from_file ("Design 1.glade");
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	window2 = GTK_WIDGET(gtk_builder_get_object(builder, "window2"));
	welcomeScreen = GTK_WIDGET(gtk_builder_get_object(builder, "WelcomeScreen"));
	
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(welcomeScreen, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_builder_connect_signals(builder, NULL);
	
	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));

	
	signUpButt = GTK_WIDGET(gtk_builder_get_object(builder, "signUp"));
	logInButt = GTK_WIDGET(gtk_builder_get_object(builder, "logIn"));
	label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
	
	userName = GTK_WIDGET(gtk_builder_get_object(builder, "userName"));
	password = GTK_WIDGET(gtk_builder_get_object(builder, "password"));
	
	userName2 = GTK_WIDGET(gtk_builder_get_object(builder, "userName2"));
	password2 = GTK_WIDGET(gtk_builder_get_object(builder, "password2"));
	lastName2 = GTK_WIDGET(gtk_builder_get_object(builder, "lastName2"));
	firstName2 = GTK_WIDGET(gtk_builder_get_object(builder, "firstName2"));
	

	TextBuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(userName));
	TextBuffer2 = gtk_text_view_get_buffer (GTK_TEXT_VIEW(password));
	
	TextBuffer3 = gtk_text_view_get_buffer (GTK_TEXT_VIEW(userName2));
	TextBuffer4 = gtk_text_view_get_buffer (GTK_TEXT_VIEW(password2));
	TextBuffer5 = gtk_text_view_get_buffer (GTK_TEXT_VIEW(lastName2));
	TextBuffer6 = gtk_text_view_get_buffer (GTK_TEXT_VIEW(firstName2));
	//g_signal_connect(TextBuffer, "changed", G_CALLBACK(on_changed_text), NULL);
	//gtk_text_buffer_set_text (TextBuffer, (const gchar *) tmp, (gint) -1);
	
	gtk_widget_show(window);
	gtk_widget_hide(label);
	
	gtk_main();
	
	return EXIT_SUCCESS;
}

void on_signUpButt_clicked (GtkButton *b) {
	//gtk_label_set_text (GTK_LABEL(label1), (const gchar* ) "Hello World");

	gtk_widget_hide(window);
	gtk_widget_show(window2);
	gtk_widget_hide(label);
	gtk_text_buffer_set_text (TextBuffer, (const gchar *) "", (gint) -1);
	gtk_text_buffer_set_text (TextBuffer2, (const gchar *) "", (gint) -1);
	
	
}
void on_SignUp2_clicked(GtkButton *b){
	char tempUser[100];
	char tempPass[100];
	char tempfirst[100];
	char tempLast[100];
	
	GtkTextIter begin, end;
	gchar * text;
	

	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer3), &begin, (gint) 0);
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer3), &end, (gint) -1);

	text = gtk_text_buffer_get_text (GTK_TEXT_BUFFER(TextBuffer3), &begin, &end, TRUE);
	printf("-------\n%s\n--------\n",text);
	strcpy(tempUser, text);
	
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer4), &begin, (gint) 0);
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer4), &end, (gint) -1);

	text = gtk_text_buffer_get_text (GTK_TEXT_BUFFER(TextBuffer4), &begin, &end, TRUE);
	printf("-------\n%s\n--------\n",text);
	strcpy(tempPass, text);
	
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer5), &begin, (gint) 0);
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer5), &end, (gint) -1);

	text = gtk_text_buffer_get_text (GTK_TEXT_BUFFER(TextBuffer5), &begin, &end, TRUE);
	printf("-------\n%s\n--------\n",text);
	strcpy(tempLast, text);
	
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer6), &begin, (gint) 0);
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer6), &end, (gint) -1);

	text = gtk_text_buffer_get_text (GTK_TEXT_BUFFER(TextBuffer6), &begin, &end, TRUE);
	printf("-------\n%s\n--------\n",text);
	strcpy(tempfirst, text);
	
	ValidInput(tempUser,tempfirst, tempLast, tempPass);
	//AddtoDb(tempUser,tempfirst,"skjew",tempLast,tempPass);
}

void on_Return_clicked(GtkButton *b) {
	gtk_widget_hide(window2);
	gtk_widget_show(window);
	gtk_text_buffer_set_text (TextBuffer3, (const gchar *) "", (gint) -1);
	gtk_text_buffer_set_text (TextBuffer4, (const gchar *) "", (gint) -1);
	gtk_text_buffer_set_text (TextBuffer5, (const gchar *) "", (gint) -1);
	gtk_text_buffer_set_text (TextBuffer6, (const gchar *) "", (gint) -1);
	
}

void on_logInButt_clicked (GtkButton *b) {
	char tempUser[100];
	char tempPass[100];
	char returnSig[100];
	
	//char *returnSig= malloc((50) * sizeof(char));;
	//char *tempPass = malloc((100) * sizeof(char));
	GtkTextIter begin, end;
	gchar * text;
	

	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer), &begin, (gint) 0);
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer), &end, (gint) -1);

	text = gtk_text_buffer_get_text (GTK_TEXT_BUFFER(TextBuffer), &begin, &end, TRUE);
	printf("-------\n%s\n--------\n",text);
	strcpy(tempUser, text);
	
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer2), &begin, (gint) 0);
	gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER(TextBuffer2), &end, (gint) -1);

	text = gtk_text_buffer_get_text (GTK_TEXT_BUFFER(TextBuffer2), &begin, &end, TRUE);
	printf("-------\n%s\n--------\n",text);
	strcpy(tempPass, text);
	//getFromDB(tempUser, tempPass);
	//returnSig = retrieve(tempUser, tempPass);
	retrieve(tempUser, tempPass, returnSig);
	//strcpy(returnSig, retrieve(tempUser, tempPass));
	if (!strcmp(returnSig,"TRUE")){
		printf("\n GOOD \n");
		gtk_widget_hide(window);
		gtk_widget_show(welcomeScreen);
	}else if (!strcmp(returnSig,"FALSE")){
		gtk_widget_show(label);
	}
	//getSaltDB(tempUser);
	//gtk_widget_hide(saveText);
}


/*
void	on_changed_text(GtkTextBuffer *t) {
	printf("*** text changed\n");
	gtk_widget_show(saveText);
	
}
*/
		

