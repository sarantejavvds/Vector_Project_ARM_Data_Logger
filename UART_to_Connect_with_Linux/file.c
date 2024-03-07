#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include <unistd.h>

#include <termios.h>


#define UART_DEVICE "/dev/ttyUSB0" /* Change this to your UART device */

#define FILE_PATH "uart_data.txt"


void writeToLogFile(const char *data)
{

    FILE *file = fopen("data.xls", "a"); /* Open the file in append mode */

    if (file == NULL) 
    {
        perror("Error opening file");

        exit(EXIT_FAILURE);
    }


    fprintf(file, "%s", data); /* Write data to the file */

    fclose(file);

}


int main()
{
    int uartFile = open(UART_DEVICE, O_RDWR | O_NOCTTY);

    if (uartFile == -1)
    {
        perror("Error opening UART");

        exit(EXIT_FAILURE);
    }

    struct termios options;

    tcgetattr(uartFile, &options);

    cfsetispeed(&options, B9600); /* Set baud rate (adjust as needed) */

    cfsetospeed(&options, B9600);

    options.c_cflag |= (CLOCAL | CREAD); /* Enable the receiver and set local mode */

    options.c_cflag &= ~PARENB; /* No parity bit */

    options.c_cflag &= ~CSTOPB; /* One stop bit */

    options.c_cflag &= ~CSIZE;

    options.c_cflag |= CS8; /* 8 data bits */

    tcsetattr(uartFile, TCSANOW, &options);

    char buffer[256];

    ssize_t bytesRead;


    while (1) 
    {

        bytesRead = read(uartFile, buffer, sizeof(buffer) - 1);

        if (bytesRead > 0)
        {

            buffer[bytesRead] = '\0'; /* Null-terminate the received data */

            printf("%s", buffer);


            writeToLogFile(buffer); /* Update the data to the log file */
	}
    }    
    printf("\n");

    close(uartFile);

    return 0;
}
