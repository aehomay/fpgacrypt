
#ifndef NOT_DEFINED
#define _XC7S100_H
#define MAX_IO_XC7S100 (400)//XILNIX Spartan-7 FPGA device XC7S100 max user I/O is 400

typedef struct{
	char  tag[50];
	long value;
	unsigned char hash[16];
	unsigned long  stamp;
	int   index;
}Signal;

Signal signals[MAX_IO_XC7S100];

void RandomInitialise();




#endif
