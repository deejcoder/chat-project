#include "test_utils.h"

int is_big_endian() {
    short i = 1;
    return (int) (*((char *) &i) );
}

void memdump(void *s, unsigned int len, unsigned int display) {
    if(len == 0) 
        return;
    
    unsigned int bytes_read = 0;
    unsigned char *addr = s;
    char display_buff[17];

    for(int i = 0; i < len; i += 16) {
        printf("0x%p:  ", (void *) addr);
        
        int bytes = (len - bytes_read >= 16) ? 16 : len - bytes_read;

        for(int j = 0; j < 16; j++) {
            
            if(j < bytes) {
                printf("%02X ", *addr);

                if(!display)
                    display_buff[j] = ' ';
                else
                    display_buff[j] = (*addr <= 126 && *addr >=32) ? *addr : '.';    
                
                
                bytes_read++;
                addr++; 
            } else {
                printf("   ");
                display_buff[j] = ' ';
            }
        }
    
        display_buff[16] = '\0';
        printf("  %s\n", display_buff);
    }
}
