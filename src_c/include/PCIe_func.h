#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/timeb.h>

#define  DMA_MAX_SIZE   0x10000000UL
extern char USAGE [];
int dev_read (int dev_fd, uint64_t addr, void *buffer, uint64_t size);
int dev_write (int dev_fd, uint64_t addr, void *buffer, uint64_t size);
uint64_t get_millisecond (); 
int parse_uint (char *string, uint64_t *pvalue);



