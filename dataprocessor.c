#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <pwd.h>
#include <grp.h>
#include <ctype.h>




int main(int argc, char const *argv[]) { 

	  pid_t childPid;
    childPid = fork();
    if(childPid==0){
	char str[12];
	int new_socket = atoi(argv[1]);
	sprintf(str, "%d", new_socket);
	execl("dpchild", "dpchild", str, NULL);
	/*valread = read( new_socket , buffer, 1024); 
    	printf("%s\n",buffer ); 
    	send(new_socket , hello , strlen(hello) , 0 ); 
    	printf("Hello message sent\n");
	exit(0);*/ 
    }else{
	int returnStatus;
    	waitpid(childPid,&returnStatus,0);
	printf("Child process return status: %d\n",returnStatus);
    }

	return 0;
}




