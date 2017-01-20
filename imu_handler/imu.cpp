#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>

#define PORT 5555
#define HOST NULL

using namespace std;

int main(void){
	int portNumber, sockFileDescriptor, newSockFileDescriptor, clientAddressLength, RWcharNumber;
	struct sockaddr_in server_addr, client_addr ;
	char buffer[8192];

	sockFileDescriptor = socket( AF_INET, SOCK_DGRAM, 0);	
	if(sockFileDescriptor  == -1)
		cout << "You don't freaking work biatch !! "<<endl ;

	bzero((char *) &server_addr, sizeof(server_addr));// here it set server_addr in memory with zero values


	server_addr.sin_family = AF_INET;// should alway be that value
	server_addr.sin_port = htons(PORT);// very important to convert using htons
	server_addr.sin_addr.s_addr = INADDR_ANY;// this is a UDP Server, doesn't need to speak with anyone

	if(bind(sockFileDescriptor, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		cout << "it doesn't bind you freaking basterd!!!!"<< endl;

	while(1){
		bzero(buffer,8192);
		RWcharNumber = read(sockFileDescriptor, buffer, 8191);
		if( RWcharNumber < 0 )
			cout << "we are in PLS...." << endl;
		else
			cout << "this is the fucking message :" << buffer << endl ;
	}
	

	return 0;
}
