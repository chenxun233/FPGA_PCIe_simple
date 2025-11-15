#include "PCIe_func.h"


int main (int argc, char *argv[]) {
    int   ret = -1;
    
    uint64_t millisecond;
    char usage_string [1024];
    
    char *dev_name, *file_name;
    char direction;
    uint64_t address, size;
    
    int   dev_fd = -1;
    FILE *file_p = NULL;
    void *buffer = NULL;
    
    sprintf(usage_string, USAGE, argv[0], argv[0], argv[0], argv[0] );
    
    if (argc < 6) {                                                // not enough argument
        puts(usage_string);
        return -1;
    }
    
    
    file_name = argv[1];
    direction = argv[2][0];
    dev_name  = argv[3];
    
    if ( 0 == parse_uint(argv[4], &address) ) {                    // parse the address in the device
        puts(usage_string);
        return -1;
    }
    
    if ( 0 == parse_uint(argv[5], &size ) ) {                      // parse the size in the device
        puts(usage_string);
        return -1;
    }
    
    // print information:
    if        (direction == 't') {                                 // to (write device, host-to-device)
        printf("from : %s\n" , file_name);
        printf("to   : %s   addr=0x%lx\n" , dev_name, address);
        printf("size : 0x%lx\n\n" , size);
    } else if (direction == 'f') {                                 // from (read device, device-to-host)
        printf("from : %s   addr=0x%lx\n" , dev_name, address);
        printf("to   : %s\n" , file_name);
        printf("size : 0x%lx\n\n" , size);
    } else {
        puts(usage_string);
        return -1;
    }
    
    
    if (size > DMA_MAX_SIZE  ||  size == 0) {
        printf("*** ERROR: DMA size must larger than 0 and NOT be larger than %lu\n", DMA_MAX_SIZE);
        return -1;
    }
    
    
    buffer = malloc(size);                                                   // allocate local memory (buffer)
    if (buffer == NULL) {
        printf("*** ERROR: failed to allocate buffer\n");
        goto close_and_clear;
    }
    
    dev_fd = open(dev_name, O_RDWR);                                         // open device
    if (dev_fd < 0) {
        printf("*** ERROR: failed to open device %s\n", dev_name);
        goto close_and_clear;
    }
    
    file_p = fopen(file_name, direction == 't' ? "rb" : "wb");               // open file for read/write
    if (file_p == NULL) {
        printf("*** ERROR: failed to open file %s\n", file_name);
        goto close_and_clear;
    }
    
    millisecond = get_millisecond();                                         // start time
    
    if (direction == 't') {
        if ( size != fread(buffer, 1, size, file_p) ) {                      // local file -> local buffer
            printf("*** ERROR: failed to read %s\n", file_name);
            goto close_and_clear;
        }
        if ( dev_write(dev_fd, address, buffer, size) ) {                    // local buffer -> device
            printf("*** ERROR: failed to write %s\n", dev_name);
            goto close_and_clear;
        }
    } else {
        if ( dev_read(dev_fd, address, buffer, size) ) {                     // device -> local buffer
            printf("*** ERROR: failed to read %s\n", dev_name);
            goto close_and_clear;
        }
        if ( size != fwrite(buffer, 1, size, file_p) ) {                     // local buffer -> local file
            printf("*** ERROR: failed to write %s\n", file_name);
            goto close_and_clear;
        }
    }
    
    millisecond = get_millisecond() - millisecond;                           // get time consumption
    millisecond = (millisecond > 0) ? millisecond : 1;                       // avoid divide-by-zero
    
    printf("time=%lu ms     data rate=%.1lf KBps\n", millisecond, (double)size / millisecond );
    
    ret = 0;
    
close_and_clear:
    
    if (buffer != NULL)
        free(buffer);
    
    if (dev_fd >= 0)
        close(dev_fd);
    
    if (file_p != NULL)
        fclose(file_p);
    
    return ret;
}