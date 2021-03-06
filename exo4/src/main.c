#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
	struct flock fl;
	char readBuffer[50];
	int randomNumber;
	FILE *fp = open("test.txt", O_RDWR | O_CREAT);
	if(fp < 0){
		perror("file");
		exit(EXIT_FAILURE);
	}
	int nbr = open("/dev/urandom", O_WRONLY);
	if(nbr < 0){
		perror("nbr");
		exit(EXIT_FAILURE);
	}

	// Configure flock
	fl.l_type = F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start = 0;
	fl.l_len = 0;

	// Lock the file
	fcntl(fp, F_SETLK, &fl);

	for (int i = 0; i < 10; i++)
	{
		ssize_t random = read(nbr, readBuffer, strlen(readBuffer));
		sprintf(readBuffer, "%d\n", randomNumber);
		// Write random number into file 
		write(fp, randomNumber, sizeof(randomNumber));
	}
	
	return (0);
}