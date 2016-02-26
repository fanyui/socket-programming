//a client program developed by harisu with interface written in gtk to send data to the server for computation
#include <gtk/gtk.h>
#include <ctype.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
GtkWidget *textview;//the text view made global so it can be access from but the send data and clear data
typedef struct{//to store the entries so we can send but this structure to the server
GtkWidget *entry,*entry1,*entry2 ;
} Widgets;
static void send_data(GtkButton*, Widgets*);//sends data to the server ie callback for send button
static void clear_data(GtkButton*, Widgets*);//clear data in the entries

void itoa(int n, char s[]);//to convert integer to a string see definition below
void reverse(char s[]);//to reverse a string in the reverse order
int main (int argc,char *argv[])
{
GtkWidget *label1,*label2,*label3,*labelhbox;
GtkWidget *window, *scrolled_win, *hbox, *vbox, *send, *clear,*buttons;
Widgets *w = g_slice_new (Widgets);
gtk_init (&argc, &argv);
window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
gtk_window_set_title (GTK_WINDOW (window), "client program by Bunyuy Justin");
gtk_container_set_border_width (GTK_CONTAINER (window), 10);
gtk_widget_set_size_request (window, -1, 200);
//creating the text view
textview = gtk_text_view_new ();
gtk_text_view_set_editable (GTK_TEXT_VIEW (textview), FALSE);
gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (textview), FALSE);

label1=gtk_label_new("digit 1");
label2=gtk_label_new("operator");
label3=gtk_label_new("digit 2");

w->entry = gtk_entry_new ();
w->entry1 = gtk_entry_new ();
gtk_entry_set_max_length (GTK_ENTRY(w->entry1),1);
w->entry2 = gtk_entry_new ();

send = gtk_button_new_with_label ("send");
clear = gtk_button_new_with_label ("clear");

g_signal_connect (G_OBJECT (send), "clicked",G_CALLBACK (send_data),(gpointer) w);
g_signal_connect (G_OBJECT (clear), "clicked",G_CALLBACK (clear_data),(gpointer) w);
scrolled_win = gtk_scrolled_window_new (NULL, NULL);
gtk_container_add (GTK_CONTAINER (scrolled_win), textview);
labelhbox=gtk_hbox_new (FALSE,5);//hbox to pack the labels
gtk_box_pack_start_defaults(GTK_BOX (labelhbox), label1);
gtk_box_pack_start_defaults(GTK_BOX (labelhbox), label2);
gtk_box_pack_start_defaults(GTK_BOX (labelhbox), label3);

hbox = gtk_hbox_new (FALSE,5);//box to pack the entrys
gtk_box_pack_start_defaults(GTK_BOX (hbox), w->entry);
gtk_box_pack_start_defaults(GTK_BOX (hbox), w->entry1);
gtk_box_pack_start_defaults(GTK_BOX (hbox), w->entry2);

buttons = gtk_hbox_new (FALSE,5);
gtk_box_pack_start_defaults(GTK_BOX (buttons), send);
gtk_box_pack_start_defaults(GTK_BOX (buttons), clear);

vbox = gtk_vbox_new (FALSE, 5);
gtk_box_pack_start (GTK_BOX (vbox), scrolled_win, TRUE, TRUE, 0);
gtk_box_pack_start (GTK_BOX (vbox), labelhbox, FALSE, TRUE, 0);
gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 0);
gtk_box_pack_start (GTK_BOX (vbox), buttons, FALSE, TRUE, 0);
gtk_container_add (GTK_CONTAINER (window), vbox);
gtk_widget_show_all (window);
gtk_main();
return 0;
}
//this function is used when the send button is pressed  to create  the client sucket and pass the data from the entry to the server for  computation
static void send_data(GtkButton *button,Widgets *w)
{

GtkTextBuffer *buffer;
GtkTextMark *mark;
GtkTextIter iter;
GtkTextBuffer *buffer1 = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));//gives access to the textview for printing of answer
const gchar *text;



const gchar  *digit1,*operator,*digit2,*digit3;
int sockfd;
	int len;
	struct sockaddr_in address;
	int ans;
	char servrespond[15];
int result;
	int num1;
	int num2;
	char opt;//the operator given by the user to be sent to the server
int optlen;
//retrieving the values of the entry given by the user 
digit1=gtk_entry_get_text(GTK_ENTRY(w->entry));
operator=gtk_entry_get_text(GTK_ENTRY(w->entry1));
digit2=gtk_entry_get_text(GTK_ENTRY(w->entry2));
optlen=strlen(operator);
opt=operator[optlen-1];
num1=atoi(digit1);
num2=atoi(digit2);
//opt=(char)operator;
sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(8080);
	len=sizeof(address);
result = connect(sockfd, (struct sockaddr *)&address, len);//connecting to the server
if(result == -1) {
perror("oops: client1");
exit(1);
}
write(sockfd, &num1, 4);//write first number
write(sockfd, &num2, 4);//write second number
write(sockfd, &opt,sizeof(opt));//write operator
read(sockfd, &ans, sizeof(ans));//read answer from server

close(sockfd);
if(ans==100000)
gtk_text_buffer_insert_at_cursor (buffer1, "error", -1);
else{
itoa(ans,servrespond);
g_printf("result of %d %c %d from server = %d\n",num1,opt,num2, ans);
gtk_text_buffer_insert_at_cursor (buffer1, servrespond, -1);
}
gtk_text_buffer_insert_at_cursor (buffer1, "\n", -1);
//gtk_text_view_scroll_mark_onscreen (textview,mark);

}

static void clear_data(GtkButton *button,Widgets *w){

gtk_entry_set_text(GTK_ENTRY(w->entry)," ");
gtk_entry_set_text(GTK_ENTRY(w->entry1)," ");
gtk_entry_set_text(GTK_ENTRY(w->entry2)," ");
}



//convert an interger to a string
void itoa(int n, char s[])
{
int i, sign;

if ((sign = n) < 0) /* record sign */
n = -n;
/* make n positive */
i = 0;
do {
/* generate digits in reverse order */
s[i++] = n % 10 + '0'; /* get next digit */
} while ((n /= 10) > 0);
/* delete it */
if (sign < 0)
s[i++] = '-';
s[i] = '\0';
reverse(s);
}
//the reverse function used in itoa
void reverse(char s[])
{
int c, i, j;

for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
c = s[i];
s[i] = s[j];
s[j] = c;
}
}
