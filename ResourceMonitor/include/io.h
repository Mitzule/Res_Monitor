#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/usbdevice_fs.h>

int numberOfIODevices() {
    int fd;
    int num_usb_devices = 0;
    struct usbdevfs_getdriver getdrv;

    fd = open("/dev/bus/usb", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    while(ioctl(fd, USBDEVFS_GETDRIVER, &getdrv) != -1) {
        num_usb_devices++;
    }
    close(fd);
    return num_usb_devices;
}

// int numberOfIODevices() {
//     int fd;
//     int num_input_devices = 0;
//     char buffer[4096];
//     ssize_t bytes_read;

//     fd = open("/proc/bus/input/devices", O_RDONLY);
//     if (fd < 0) {
//         perror("open");
//         return 1;
//     }

//     bytes_read = read(fd, buffer, sizeof(buffer) - 1);
//     if (bytes_read < 0) {
//         perror("read");
//         close(fd);
//         return 1;
//     }
//     buffer[bytes_read] = '\0';

//     char *line = buffer;
//     while (*line) {
//         if (strstr(line, "N: Name=")) {
//             num_input_devices++;
//         }
//         line += strlen(line) + 1;
//     }


//     return num_input_devices;
// } 
