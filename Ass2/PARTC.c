


// **************************************************************************** //
//                                                                              //
//                                                         :::      ::::::::    //
//    My_own_shell                                          :+:      :+:    :+: //
//                                                     +:+ +:+         +:+      //
//    By: Sudhir_Sharma <12041500>        +//+  +:+            +//+             //
//                                                 +//+//+//+//+//+   +//+      //
//    					                //+//    //+//          //
//                                                     //#   ########.fr        //
//                                                                              //
// **************************************************************************** //


#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

/*
Use these colors to print colored text on the console
*/

#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>
   
   
#define vt vector
#define pb push_back
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()
     
#define F_OR(i, a, b, s) for (int i=(a); (s)>0?i<(b):i>(b); i+=(s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)
#define FOR(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)
    

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_reset_colour   "\x1b[0m"
#define ANSI_COLOR_YELLOW   "\033[1;33m"
#define KNRM  "\x1B[0m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define reset_colour "\x1B[0m"

/*
use with redirection(< > >>) to indicate to the function in which mode to open the file
and to know that redirection of the input OR output has to be done
*/
#define INPUT 0
#define OUTPUT 1
#define APPEND 2

/*
removes the newline and space character from the end and start of a char*
*/
void removeWhiteSpace(char* buf){
	if(buf[strlen(buf)-1]==' ' || buf[strlen(buf)-1]=='\n')
	buf[strlen(buf)-1]='\0';
	if(buf[0]==' ' || buf[0]=='\n') memmove(buf, buf+1, strlen(buf));
}

/*
shows the internal help
*/

void showHelp(){
	printf(CYN"\n \t \t \t    WELCOME TO MY SHELL \t \t \t \nThis is an implementation of the Linux/Unix Shell in C Language. Similiar to the Linux Shell, it allows the users to enter various commands, and then it works accordingly. It supports a list of internal and external commands which are described briefly below. The implementation doesn't use the inbuilt external command implementations, instead it uses exec and fork to call the programs written for the external commands. This has been made as a part of the Operating Systems - CSE231 Course at IIIT Delhi.\n\n" reset_colour);
	printf( KCYN "\t \t\t    Features \t \t \t \n" reset_colour);
	printf(KCYN "The commands supported are: \n1) cd \nThis is used to change the current directory of the program. The flags supported are:\n\ta) cd .. : takes you to the parent directory\n\tb) cd ~ : takes you to the root directory\n\tc) cd [dirname] : takes you to the directory name specified\n" reset_colour);
	printf(KCYN "\n2) echo\nThis displays a line of text. The flags supported are:\n\ta) echo -n : do not output the trailing newline\n\tb) echo -e : enable interpretation of backslash escapes\n" reset_colour);
	
	printf(KCYN "\n3) pwd\nThis prints the name of current/working directory. The flags supported are:\n\ta) pwd --help : display this help and exit\n\tb) pwd --version : output version information and exit\n" reset_colour);
	printf(KCYN "\n4) exit\nThis causes normal process termination.\n" reset_colour);
	printf(KCYN "\n5) mkdir\nThis make directories. The flags supported are:\n\ta) mkdir -v : print a message for each created directory\n\tb) mkdir -p : creates the parent directories as well\n\tc) mkdir --help : display this help and exit\n" reset_colour);
	printf(KCYN "\n5) rm\nThis remove files or directories. The flags suuported are:\n\ta) rm -d : remove empty directories\n\tb) rm -f : ignore nonexistent files and arguments, never prompt\n\tc) rm -v : explain what is being done\n" reset_colour);
	printf(KCYN "\n7) ls\nThis list directory contents. The flags supported are:\n\ta) ls -U : do not sort; list entries in directory order\n\tb) ls -a : do not ignore entries starting with .\n" reset_colour);
	printf(KCYN "\n8) cat\nThis concatenates files and print on the standard output. The flags supported are:\n\ta) cat -E : display $ at end of each line\n\tb) cat -n : number all output lines\n" reset_colour);
	printf(KCYN "\n9) date\nThis prints or set the system date and time. The flags supported are:\n\ta) date -u : print or set Coordinated Universal Time (UTC)\n\tb) date -r : display the last modification time of FILE\n" reset_colour);
}
/*
tokenizes char* buf using the delimiter c, and returns the array of strings in param
and the size of the array in pointer nr
*/
void Token(char** param,int *nr,char *buf,const char *c){
	char *token;
	token=strtok(buf,c);
	int pc=-1;
	while(token){
		param[++pc]=malloc(sizeof(token)+1);
		strcpy(param[pc],token);
		removeWhiteSpace(param[pc]);
		token=strtok(NULL,c);
	}
	param[++pc]=NULL;
	*nr=pc;
}

/*
used for debugging purposes to print all the strings in a string array
*/
void print_params(char ** param){
	while(*param){
		printf("param=%s..\n",*param++);
	}
}

/*
loads and executes a single external command
*/
void executeBasic(char** argv){
	if(fork()>0){
		//parent
		wait(NULL);
	}
	else{
		//child
		execvp(argv[0],argv);
		//in case exec is not successfull, exit
		perror(ANSI_COLOR_RED   "invalid input"   ANSI_COLOR_reset_colour "\n");
		exit(1);
	}
}

/*
loads and executes a series of external commands that are piped together
*/
void piping_func(char** buf,int nr){//can support up to 10 piped commands
	if(nr>10) return;
	
	int fd[10][2],i,pc;
	char *argv[100];

	for(i=0;i<nr;i++){
		Token(argv,&pc,buf[i]," ");
		if(i!=nr-1){
			if(pipe(fd[i])<0){
				perror("pipe creating was not successfull\n");
				return;
			}
		}
		if(fork()==0){//child1
			if(i!=nr-1){
				dup2(fd[i][1],1);
				close(fd[i][0]);
				close(fd[i][1]);
			}

			if(i!=0){
				dup2(fd[i-1][0],0);
				close(fd[i-1][1]);
				close(fd[i-1][0]);
			}
			execvp(argv[0],argv);
			perror("invalid input ");
			exit(1);//in case exec is not successfull, exit
		}
		//parent
		if(i!=0){//second process
			close(fd[i-1][0]);
			close(fd[i-1][1]);
		}
		wait(NULL);
	}
}

// pipe_parse(char *input) {
//     char *arg; 
//     char **args = malloc(INPUT_SIZE);  
//     int count; 

//     //parse first for pipes and pass to pipe_handler: if no pipes, pass input to io_parse 
//     if(strchr(input, '|')) { 
//         int pipe_number = count_pipes(input); 
//         count = 0;  
//         while((arg = strtok_r(input, "|", &input))) {
//             args[count] = arg; 
//             count ++; 
//         }
//         pipe_handler(args, pipe_number); 
//         free(args); 
//     } else {
//         io_parse(input); 
//     }
//     return; 
// }


/*
loads and executes a series of external commands that have to be run asyncronously
*/
void executeAsync(char** buf,int nr){
	int i,pc;
	char *argv[100];
	for(i=0;i<nr;i++){
		Token(argv,&pc,buf[i]," ");
		if(fork()==0){
			execvp(argv[0],argv);
			perror("invalid input ");
			exit(1);//in case exec is not successfull, exit
		}
	}
	for(i=0;i<nr;i++){
		wait(NULL);
	}

}
/*trying to add function to check history and handles input such as '!!' and
//  '!<no>' which are required to re-run previously executed commands from history.*/
// int historycheck(char input[inputval], int histcounter, char *history[max_hist]){
//     /* This if statement prevents inputs which are line breaks being entered into the history. */
//     if(strstr(input,"\n")){
//     }
//     else{
//         /* If the program passes this if statement, the first char in the input is a ! or the input is "history" */
//         if(strncmp("!", input, 1) != 0 && strncmp("history", input, 512) != 0 ){
            
//             /* When array is full, move each element in the array down one location. */
//             if(histcounter == max_hist){
//                 int i = 0;
//                 while(i<(histcounter-1)){
//                     history[i] = history[i+1];
//                     i++;
//                 }
//                 /* Add the new element to history. */
//                 history[(max_hist-1)] = strdup(input);
//             }
//             else{
//                 /* Add the new element to history straight away. Then increment counter */
//                 history[histcounter] = strdup(input);
//                 histcounter = histcounter + 1;
//             }
//         }
//         else{
//             /* Checks if input is to run the last command. (!!) If so, then execute it,
//              or display an error if there is no history to run. */
//             if(strncmp("!!", input, 512) == 0){
//                 if(history[0] != 0){
//                     if(histcounter == 0){
//                         strcpy(input,history[19]);
//                     }
//                     else{
//                         strcpy(input,history[histcounter-1]);
//                     }
//                 }
//                 else{
//                     printf("There is no history to run\n");
//                 }
//             }
//             else{
//                 long length = strlen(input);
//                 if (length > 1){
//                     int location = atoi(&input[1]); /* Converts char to int. */
//                     if(location>0 && location <21){
//                         location = location - 1;
//                         if(history[location] != NULL){
//                             /* Because the history command prints out from most to last recent, this converts the users
//                              input into an array location, as !1 would be location in an full array. */
//                             if((histcounter-location) < 0){
//                                 location = (max_hist - (histcounter-(location+1)));
//                             }
//                             else{
//                                 location = (histcounter-(location+1));
//                             }
//                             /* The command from history is copied into input overwriting the previous command.
//                              The command is displayed before it runs. */
//                             strcpy(input,history[location]);
//                             printf("%s\n",input);
//                         }
//                     }
//                     else{
//                         if(location != 0){
//                             /*If the user enters a number outwith the range then they are
//                               prompted to change their number */
//                             printf("The character following ! must be a number between 1 and 20 to invoke a history command\n");
//                         }
//                     }
//                 }
//             }
//         }
//     }
    
//     return histcounter;
// }

/*
loads and executes a an external command that needs file redirection(input, output or append)
*/
void Redirection_token(char** buf,int nr,int mode){
	int pc,fd;
	char *argv[100];
	removeWhiteSpace(buf[1]);
	Token(argv,&pc,buf[0]," ");
	if(fork()==0){

		switch(mode){
		case INPUT:  fd=open(buf[1],O_RDONLY); break;
		case OUTPUT: fd=open(buf[1],O_WRONLY); break;
		case APPEND: fd=open(buf[1],O_WRONLY | O_APPEND); break;
		default: return;
		}

		if(fd<0){
			perror("cannot open file\n");
			return;
		}

		switch(mode){
		case INPUT:  		dup2(fd,0); break;
		case OUTPUT: 		dup2(fd,1); break;
		case APPEND: 		dup2(fd,1); break;
		default: return;
		}
		execvp(argv[0],argv);
		perror("invalid input ");
		exit(1);//in case exec is not successfull, exit
	}
	wait(NULL);
}


// void 
// input_redir(char **cmd, char *input) {
//     int exit_value;  
//     int stdin = dup(0);  
//     int file_fd = open(input, O_RDONLY); 
//     if(file_fd == -1){
//         perror("open"); 
//         return; 
//     }
//     dup2(file_fd, 0); 

//     //fork child process 
//     pid_t pid; 
//     pid = fork(); 
//     if (pid == -1) {
//         perror("fork"); 
//         return; 
//     } else if(pid == 0) {
//         execvp(cmd[0], cmd); 
//         perror("execvp"); 
//         exit(1); 
//     }
//     wait(&exit_value); 
//     dup2(stdin, 0); 
//     close(stdin); 
//     close(file_fd);
//     return; 
// }


// void 
// output_redir(char **cmd, char *output, int append_flag) {
//     int exit_value;  
//     int flags; 
//     int stdout = dup(1);
//     if(append_flag == 1) {
//         flags = (O_RDWR | O_CREAT | O_APPEND); 
//     } else {
//         flags = (O_RDWR | O_CREAT); 
//     }
//     int file_fd = open(output, flags, 0644); 
//     if(file_fd == -1){
//         perror("open"); 
//         return; 
//     }
//     dup2(file_fd, 1); 

//     //fork child process 
//     pid_t pid; 
//     pid = fork(); 
//     if (pid == -1) {
//         perror("fork"); 
//         return; 
//     } else if(pid == 0) {
//         execvp(cmd[0], cmd); 
//         perror("execvp"); 
//         exit(1); 
//     }
//     wait(&exit_value); 
//     dup2(stdout, 1); 
//     close(stdout); 
//     close(file_fd);
//     return; 
// }


int main(char** argv,int argc)
{       


       char p_id = getpid(); /*process id*/
       int  p_pid = getpid(); /*parent process id*/
	char buf[500],*Input[100],buf2[500],buf3[500], *st[100],*params2[100],*token,cwd[1024];
	int nr=0;
        screenfetch();
	while(1){
		

		//print prompt
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf( ANSI_COLOR_BLUE "12041500_sudhir_sharma ~~> " " "reset_colour);
		else 	perror("getcwd failed\n");

		//read user input
		fgets(buf, 500, stdin);//Input overflow cannot happen

		//check if only a simple command needs to be executed or multiple piped commands or other types
		if(strchr(buf,'|')){//tokenize pipe commands
			Token(Input,&nr,buf,"|");
			piping_func(Input,nr);
		}
		
                
		else if(strchr(buf,'&')){//asyncronous execution
			Token(Input,&nr,buf,"&");
			executeAsync(Input,nr);
		}
		else if(strstr(buf,">>")){//append output to file
			Token(Input,&nr,buf,">>");
			if(nr==2)Redirection_token(Input,nr,APPEND);
			else printf("error look the help page");
		}
		else if(strchr(buf,'>')){//redirect output to file
			Token(Input,&nr,buf,">");
			if(nr==2)Redirection_token(Input,nr, OUTPUT);
			else printf("error look the help page ");
		}
		else if(strchr(buf,'<')){//redirect file to input
			Token(Input,&nr,buf,"<");
			if(nr==2)Redirection_token(Input,nr, INPUT);
			else printf("error look the help page");
		}
		else if(strstr(buf,"PID")){// PARENT ID
			printf(p_id);
			
		}
		else{//single command including internal ones
			Token(st,&nr,buf," ");
			if(strstr(st[0],"cd")){//cd builtin command
				chdir(st[1]);
			}
			else if(strstr(st[0],"help")||strstr(st[0],"Help")||strstr(st[0],"HELP")){//help builtin command
				showHelp();
			}
			else if(strstr(st[0],"exit")||strstr(st[0],"Exit")||strstr(st[0],"EXIT")){//exit builtin command
				exit(0);
			}
			else executeBasic(st);
		}
	}

	return 0;
}
/* mimic screenfetch like logo functionality from ubuntu*/
void screenfetch()
{
    char* welcomestr = RED "\n                           ./+o+-\n                  yyyyy- -yyyyyy+\n               ://+//////-yyyyyyo\n           .++ .:/++++++/-.+sss/`\n         .:++o:  /++++++++/:--:/-\n        o:+o+:++.`..```.-/oo+++++/\n       .:+o:+o/.          `+sssoo+/\n  .++/+:+oo+o:`             /sssooo.\n /+++//+:`oo+o               /::--:.\n \\+/+o+++`o++o               ++////.\n  .++.o+++oo+:`             /dddhhh.\n       .+.o+oo:.          `oddhhhh+\n        \\+.++o+o``-````.:ohdhhhhh+\n         `:o+++ `ohhhhhhhhyo++os:\n           .o:`.syhhhhhhh/.oo++o`\n               /osyyyyyyo++ooo+++/\n                   ````` +oo+++o\\:    My_OWN_Shell\n                       `oo++. "  MAG "   Made by Sudhir Sharma\n\n"reset_colour;

    printf("%s",welcomestr);
}

/* about this shell*/
void about()
{
    // Source - http://ascii.co.uk/art/seashell
    char* descr = "           _.-''|''-._\n        .-'     |     `-.\n      .'\\       |       /`.\n    .'   \\      |      /   `.        MY_OWN_shell\n    \\     \\     |     /     /        Made by @Sudhir878786\n     `\\    \\    |    /    /'\n       `\\   \\   |   /   /'\n         `\\  \\  |  /  /'\n        _.-`\\ \\ | / /'-._ \n       {_____`\\\\|//'_____}\n               `-'\n\n";

    printf("%s",descr);
}







