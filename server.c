// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>

#define PORT 8080

 
int main(int argc, char const *argv[]) 
{ 

if(argc < 2){
printf("int the parent %d\n", argc);
    int server_fd, new_socket, valread; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    //char buffer[1024] = {0}; 
    //char *hello = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
	
	int portNumber = 8080;
	printf("\nPlease Enter the port number you want to use: \n");
	scanf("%d",&portNumber);

    address.sin_port = htons( portNumber ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address,  
                                 sizeof(address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,  
                       (socklen_t*)&addrlen))<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 
    

	FILE *fs;
	char fs_name[100]="";
	printf("\nPlease Enter the file name you want to send: \n");
	scanf("%s",&fs_name);

	fs=fopen(fs_name,"r");
	if(fs == NULL){
		perror("\nFile Open unsuccess!"); 
        	exit(EXIT_FAILURE);
	}
	

	int fff = fileno(fs);

	char fpd[12];
	sprintf(fpd, "%d", fff);


    pid_t childPid;
    childPid = fork();
    if(childPid==0){
	char str[12];
	sprintf(str, "%d", new_socket);
	execl("server", "server", str, fpd, NULL);
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
    }else{
	printf("int the child %d\n", argc);

 	pid_t childPid2;
    	childPid2 = fork();
    	if(childPid2==0){
		char str[12];
		int new_socket = atoi(argv[1]);
		sprintf(str, "%d", new_socket);
		execl("dpchild", "dpchild", str, argv[2], NULL);
    	}else{
		int returnStatus;
    		waitpid(childPid2,&returnStatus,0);
		printf("Child process return status: %d\n",returnStatus);
    	}
    }
    return 0; 
} 
