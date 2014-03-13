
int main();


char* itoa(unsigned int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	if(val == 0){
	    buf[31] = '0';
	    return &buf[31];
	}
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

void putc(char c) {
    volatile unsigned char* r = (volatile unsigned char*)(0xbf000900+5);
    volatile unsigned char* w = (volatile unsigned char*)(0xbf000900);

    while(*r == 0);
    *w = c;
}

void print(char * s){
    while(*s != '\0') {
        putc(*s);
        s++;
    }
}

unsigned int * terminate = (unsigned int *)0x80000000;

void fail() {
    print("test failed!\n");
    *terminate = 1;    
}

void pass(){
    print("test passed!\n");
    *terminate = 0;
}

void abort(){
    fail();
}

void exit(int val){
    *terminate = val;
}

void kmain(void)
{
#if 0
    print("kernel starting\n");

    if( main() != 0 ){
        fail();
    }
    else {
        pass();
    }
#endif
    if( main() != 0 ){
        fail();
    }
    pass();
}



