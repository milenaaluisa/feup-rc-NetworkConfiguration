// Copyright (C) 2020 Diogo Rodrigues, Breno Pimentel
// Distributed under the terms of the GNU General Public License, version 3

#include "download.h"

struct hostent* get_ip(char *hostname){
	struct hostent *h;

    if ((h=gethostbyname(hostname)) == NULL) {  
            herror("gethostbyname");
            exit(1);
    }

    printf("Host name  : %s\n", h->h_name);
    printf("IP Address : %s\n",inet_ntoa(*((struct in_addr *)h->h_addr)));

	return h;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {  
        fprintf(stderr,"usage: download ftp://[<user>:<password>@]<host>/<url-path> \n");
        exit(1);
    }

	if(is_valid_url(argv[1]) != 0){
		fprintf(stderr,"url format: ftp://[<user>:<password>@]<host>/<url-path> \n");
		exit(1);
	}
	
    int sockfd;
	int sockfd_b;
	struct sockaddr_in server_addr_a;
	struct sockaddr_in server_addr_b;

	char *user     = (char*)malloc(MAX_STR_LEN); // optional
	char *pwd      = (char*)malloc(MAX_STR_LEN); // optional
	char *host     = (char*)malloc(MAX_STR_LEN);
	char *url_path = (char*)malloc(MAX_STR_LEN);

	parse_url(argv[1], user, pwd, host, url_path);

	struct hostent *h = get_ip(host);

	/*server address handling*/

	bzero((char *)&server_addr_a, sizeof(server_addr_a));
	server_addr_a.sin_family = AF_INET;
	/// 32 bit Internet address network byte ordered
	server_addr_a.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)h->h_addr)));
	/// server TCP port must be network byte ordered
	server_addr_a.sin_port = htons(SERVER_PORT);

	/*open an TCP socket*/
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket()");
		exit(0);
	}

	/*connect to the server*/
	if (connect(sockfd,
				(struct sockaddr *)&server_addr_a,
				sizeof(server_addr_a)) < 0)
	{
		perror("connect()");
		exit(0);
	}

	// Read connect reply

	char reply_code;

	reply_code = read_reply(sockfd);
	if(reply_code == '4' || reply_code == '5'){
		close(sockfd);
		exit(0);
	}

	// login host

	write_cmd(sockfd, "user ", user);
	reply_code = read_reply(sockfd);
	if(reply_code == '4' || reply_code == '5'){
		close(sockfd);
		exit(0);
	}

	write_cmd(sockfd, "pass ", pwd);
	reply_code = read_reply(sockfd);
	if(reply_code == '4' || reply_code == '5'){
		close(sockfd);
		exit(0);
	}

	// Enter passive mode
	int port = write_pasv(sockfd);
	printf("Port: %d\n\n", port);

	/*server address handling*/
	bzero((char *)&server_addr_b, sizeof(server_addr_b));
	server_addr_b.sin_family = AF_INET;
	server_addr_b.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)h->h_addr)));
	server_addr_b.sin_port = htons(port);

	/*open an TCP socket*/
	if ((sockfd_b = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket()");
		exit(0);
	}

	/*connect to the server*/
	if (connect(sockfd_b,
				(struct sockaddr *)&server_addr_b,
				sizeof(server_addr_b)) < 0)
	{
		perror("connect()");
		exit(0);
	}

	// Save file if successfull
	write_cmd(sockfd, "retr ", url_path);
	reply_code = read_reply(sockfd);
	if(reply_code == '4' || reply_code == '5'){
		close(sockfd); close(sockfd_b);
		exit(0);
	}

	download_file(sockfd_b, url_path);
	reply_code = read_reply(sockfd);
	if(reply_code == '4' || reply_code == '5'){
		close(sockfd); close(sockfd_b);
		exit(0);
	}

	// Quit

	write_cmd(sockfd, "quit", "");
	reply_code = read_reply(sockfd);
	if(reply_code == '4' || reply_code == '5'){
		close(sockfd); close(sockfd_b);
		exit(0);
	}

	close(sockfd);
	close(sockfd_b);
	free(user);
	free(pwd);
	free(host);
	free(url_path);
	exit(0);
}
