#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *strIn){
	int strLen = strlen(strIn);
	for(int i=strLen-2;i>=0;i--)	// strIn[strLen-1] == "\n"
		printf("%c", strIn[i]);
	printf("\n");
}

void split(char *strIn, char *delimiters){
	int start = 0, end = -1;
	int lenDe = strlen(delimiters);
	char *dest = malloc(lenDe * sizeof(char));	//	allocate a new array to get substrings equal length to the delimiter

	for(int i=0;i<(strlen(strIn)-lenDe+1);i++){
		strncpy(dest, strIn + i, lenDe);	//	get substring equal length to the delimiter
		dest[lenDe] = '\0';

		if(strcmp(dest, delimiters) == 0){
			// match
			strIn[i] = ' ';	// set blank
			for(int j = 1; j < strlen(strIn) - 1; ++j){
				if((i + j + lenDe - 1) < strlen(strIn))
					strIn[i + j] = strIn[i + j + lenDe - 1];	//	shift char to front
				else
					strIn[i + j] = '\n';	// put '\0' to end of the string
			}
		}
	}
	int i = 0;
	while(strIn[i] != '\n'){
		printf("%c", strIn[i++]);
	}
	printf("\n");
	
	free(dest);
}

void deal(char *str, char *delimiters){	//	deal with to the whole input string
	if(strcmp(str, "exit\n") == 0)
		exit(0);
	else{
		char *pstr = strtok(str, " ");	// get command

		if(strcmp(pstr,"reverse") == 0){
			pstr = strtok(NULL, "");
			reverse(pstr);
		}
		else if(strcmp(pstr, "split") == 0){
			pstr = strtok(NULL, "");
			split(pstr, delimiters);
		}
		else{
			printf("file command error...\n");
		}	
	}
}

int main(int argc, char *argv[])
{	
	if(argc < 2){
		printf("parameter error...\n");
		exit(0);
	}
	
	FILE *pfile;
	pfile = fopen(argv[1],"r");
	
	if(pfile == NULL){
		printf("file open error...\n");
		exit(0);
	}
	else{
		//	*********************************
		//		Deal with commands in FILE
		//	*********************************
		printf("-------------------Input file example.txt-------------------\n");
		char line[100];
		while(fgets(line, 100, pfile) != 0){
			printf("%s", line);
			deal(line, argv[2]);
		}
		printf("----------------End of input file example.txt--------------\n");
		//	**********************************
		//		Deal with commands by INPUT
		//	**********************************
		printf("*************************User input*************************\n");
		while(fgets(line, 100, stdin) != 0)
			deal(line, argv[2]);

	}
	
	fclose(pfile);
	return 0;
}