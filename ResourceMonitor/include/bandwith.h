#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void getBandwidth() {
    printf("\033[23;4H"); 
    unsigned long long int rx_bytes, tx_bytes;
    char line[200], interface_name[20];
    FILE* net_dev = fopen("/proc/net/dev", "r");

    while (fgets(line, sizeof(line), net_dev)) {
        if (strstr(line, ":")) {
            sscanf(line, "%[^:]: %llu %*u %*u %*u %*u %*u %*u %*u %llu", interface_name, &rx_bytes, &tx_bytes);
            printf("\033[23;4H\033[2k"); // Clear the line and move cursor to the beginning of the line
            printf(" Received: %llu  Transmitted: %llu", rx_bytes/1000, tx_bytes/1000);
            fflush(stdout); // Flush the output buffer
            sleep(1); // Wait for 1 second before updating the information again
        }
    }

    fclose(net_dev);
}


