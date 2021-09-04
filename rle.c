
#include <stdio.h>

#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>

#include <unistd.h>

#include <string.h>
//Tanisha Joshi, Taylor Streff, Nawal Cheema - Group 5 Lab 1 submission
#pragma warning( disable : _WARNING_NUMBER_)

int main(int argc, char** argv) {
        const char* input_file = argv[1];
        const char* output_file = argv[2];
        int k = atoi(argv[3]);
        int  mode =atoi( argv[4]);

//printf("rle <input file>, <output file>, <compression length>, <mode> (0 or 1)");

if (argc != 5) {
        fprintf(stderr, "usage: <input file>, <output file>, <compression length>, <mode> (0 or 1)");
        exit(1);

}
if (k < 1) {
        fprintf(stderr, "Not a valid compression length");
        exit( 1);
}

/**
*if (mode != 0 || mode != 1) { 
*        fprintf(stderr, "Invalid mode. Enter 0 or 1");
*        exit( 1);
//}
*/

int out = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
//open 2 files seperately, write only flag in 2nd parameter
int fd = open(input_file, O_RDONLY);
if (fd <0) {
        printf("File does not exist or not openable %d", fd);
        exit(1);
}

//printf("fd = %d", fd);

int reps = 1;
char buffer[k];

if (mode == 0) {
        char new_buffer[k]; //declare a new buffer of size k
        int fd1 = read(fd, buffer, k);
        if (fd1 <= 0) {
                perror("Input file not readable");
                exit(-1);
        }
        while (1) {

                int fd2 = read(fd, new_buffer, k);
                if (fd2 == 0) {break;}
                int compare = strcmp(buffer, new_buffer);
                if (compare==0 && reps != 255) {
                        reps++;
                        memset(buffer, k, '\0');
                        memset(new_buffer, k, '\0');
                } else if (compare != 0 || reps == 255) {
			
			printf("reps = %d", reps);
			//char* str[k+1];
                        //int out = open(output_file, O_APPEND);
			//sprintf(str, "%d", reps);;
			//write(out, reps, 1);	
                        //char* rep = itoa(reps);  //convert reps to a string
                        //char* outstr = strcat(rep, buffer); //join reps and buffer
                        write(out, buffer, sizeof(buffer)); //write to the output file
                        reps = 1;
			memcpy(buffer, new_buffer, k);	
                }
        }

}

}
