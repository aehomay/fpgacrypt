/*
 ============================================================================
 Name        : xc7s100.c
 Author      : Aydin Homay
 Version     :
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "xc7s100.h"
#include "md5.h"

void MD5Hash();
void MD5Print();
void PrintHash();


int main(void) {

	//Total Initialise
	RandomInitialise();
	//Print signal list
	PrintHash(signals);

	return 1;
}



void RandomInitialise() {
	for (int i = 0; i < MAX_IO_XC7S100; i++) {

		char random[15];
		sprintf(random, "%d", rand());
		char tag[50] = "Tag#";
		strcat(tag, random);
		strcpy(signals[i].tag, tag);
		signals[i].index = i;
		signals[i].value = rand();
		MD5Hash(signals[i].tag, signals[i].hash);//Sign the tag
	}
}

void inline WriteSignalValue(int index,long value)
{
	signals[index].value = value;
}


long inline ReadSignalValue(int index)
{
	return signals[index].value;
}

unsigned char inline ReadSignature(int index)
{
	return signals[index].hash;
}

/* Digests a string and prints the result.
 */
void MD5Hash(const char* tag, unsigned char* digest) {
	MD5_CTX context;
	unsigned int len = strlen(tag);
	MD5_Init(&context);
	MD5_Update(&context, tag, len);
	MD5_Final(digest, &context);
}

void PrintHash(Signal* list) {
	for (int i = 0; i < MAX_IO_XC7S100; i++) {
		printf("MD5Hash (\"%s\") = ", list[i].tag);
		MD5Print(list[i].hash);
		printf("\n");
	}
}

void MD5Print(unsigned char digest[16]) {
	unsigned int i;
	for (i = 0; i < 16; i++)
		printf("%02x", digest[i]);
}
