
#include <stdio.h>

#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <fcntl.h>

#include <unistd.h>

#include <string.h>

#pragma warning( disable : _WARNING_NUMBER_)

int main(int argc, char** argv) {
        const char* input_file = argv[1];
        const char* output_file = argv[2];
        int k = atoi(argv[3]);
        int mode = atoi(argv[4]);

if (argc != 5) {
        fprintf(stderr, "usage: <input file>, <output file>, <compression length>, <mode> (0 or 1)");
        exit(1);

}
if (k < 1) {
        fprintf(stderr, "Not a valid compression length");
        exit(1);
}

if (mode < 0 || mode > 1) { 
        fprintf(stderr, "Invalid mode. Enter 0 or 1");
        exit(1);
}


int out = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
int fd = open(input_file, O_RDONLY);
if (fd < 0) {
        printf("File does not exist or not openable %d", fd);
        exit(1);
}

int reps = 1;
char buffer[k];
char pattern[k];

// Compression method

if (mode == 0) {
        char new_buffer[k]; 
        int fd1 = read(fd, buffer, k);
        if (fd1 <= 0) {
                perror("Input file not readable");
                exit(-1);
        }

        while (1) {
                int fd2 = read(fd, new_buffer, k);
                if (fd2 == 0) {
			write(out, &reps, 1); 
		        write(out, "\n", 1); 	
			break;
		}

                int compare = memcmp(buffer, new_buffer, k);
                if (compare == 0 && reps != 255) {
                        reps++;
                        memset(buffer, k, '\0'); 
                        memset(new_buffer, k, '\0');
                }
	       	else if (compare != 0 || reps == 255) {
			write(out, &reps, 1);	
                        write(out, buffer, sizeof(buffer)); 
                        reps = 1;
			memcpy(buffer, new_buffer, k);	
                } 
        }

}

//Decompression method

else if (mode == 1) {
		int fd1 = read(fd, buffer, 1); //reading first byte
                int n = buffer[0]; //turning byte into int      
                int fd2 = read(fd, pattern, k);
	while(1) {
	
		if (fd1 == 0) {
			break;
                }
	
		for (int i = 0; i < n; i++) {
			write(out, pattern, k);
		
		}
		memset(buffer, k, '\0');
                memset(pattern, k, '\0'); 
		fd1 = read(fd, buffer, 1);
		n = buffer[0];
		fd1 = read(fd, pattern, k); 	
	}
	close(fd1); 
	close(fd2); 
}
close(fd);
close(out);
}
