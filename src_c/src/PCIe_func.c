#include "PCIe_func.h"
#include <errno.h>
#include <string.h>




// function : dev_read
// description : read data from device to local memory (buffer), (i.e. device-to-host)
// parameter :
//       dev_fd : device instance
//       addr   : source address in the device
//       buffer : buffer base pointer
//       size   : data size
// return:
//       int : 0=success,  -1=failed
int dev_read (int dev_fd, uint64_t addr, void *buffer, uint64_t size) {
    if ( addr != lseek(dev_fd, addr, SEEK_SET) )                                 // seek
        return -1;                                                               // seek failed
    if ( size != read(dev_fd, buffer, size) )                                    // read device to buffer
        return -1;                                                               // read failed
    return 0;
}


// function : dev_write
// description : write data from local memory (buffer) to device, (i.e. host-to-device)
// parameter :
//       dev_fd : device instance
//       addr   : target address in the device
//       buffer : buffer base pointer
//       size   : data size
// return:
//       int : 0=success,  -1=failed
int dev_write (int dev_fd, uint64_t addr, void *buffer, uint64_t size) {
    uint64_t cur_addr = lseek(dev_fd,addr,SEEK_SET);
    if ( cur_addr != addr ){                                 // seek
        printf("*** faild to seek address. Current address is %lx while input is %lx.\n" ,cur_addr,addr);
        return -1; 
    }
    ssize_t act_size  = write(dev_fd,buffer,size);                                                              // write device from buffer
    if ( act_size != size ){                                 // write device from buffer
        printf("*** faild to write. Actual size is %ld while input is %ld. error: %s\n" ,act_size,size, strerror(errno));
        return -1; 
    }
    return 0;
}




// function : get_millisecond
// description : get time in millisecond
uint64_t get_millisecond () {
    struct timeb tb;
    ftime(&tb);
    return (uint64_t)tb.millitm + (uint64_t)tb.time * 1000UL;
    // tb.time is the number of seconds since 00:00:00 January 1, 1970 UTC time;
    // tb.millitm is the number of milliseconds in a second
}



// function : parse_uint
// description : get a uint64 value from string (support hexadecimal and decimal)
int parse_uint (char *string, uint64_t *pvalue) {
    if ( string[0] == '0'  &&  string[1] == 'x' )                // HEX format "0xXXXXXXXX"
        return sscanf( &(string[2]), "%lx", pvalue);
    else                                                         // DEC format
        return sscanf(   string    , "%lu", pvalue);
}



char USAGE [] = 
    "Usage: \n"
    "\n"
    "  write device (host-to-device):\n"
    "    %s <file_name> to <device_name> <address_in_the_device> <size>\n"
    "  example:\n"
    "    %s data.bin to /dev/xdma0_h2c_0 0x100000 0x10000\n"
    "\n"
    "  read device (device-to-host):\n"
    "    %s <file_name> from <device_name> <address_in_the_device> <size>\n"
    "  example:\n"
    "    %s data.bin from /dev/xdma0_c2h_0 0x100000 0x10000\n" ;
