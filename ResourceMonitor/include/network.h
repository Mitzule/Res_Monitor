
unsigned long long getBytesRecieved(){
    FILE *fp;
    char line[1024];

    fp = fopen("/proc/net/dev", "r");
    if(fp == NULL) {
        printf("Error opening /proc/net/dev\n");
        return 1;
    }

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    while(fgets(line, sizeof(line), fp)) {
        char *iface;
        unsigned long long rx_bytes;

        iface = strtok(line, ":");
        iface = strtok(NULL, " ");
        rx_bytes = strtoull(strtok(NULL, " "), NULL, 10);

        return rx_bytes;
    }
}


unsigned long long getBytesSent(){
    FILE *fp;
    char line[1024];

    fp = fopen("/proc/net/dev", "r");
    if(fp == NULL) {
        printf("Error opening /proc/net/dev\n");
        return 1;
    }

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    while(fgets(line, sizeof(line), fp)) {
        char *iface;
        unsigned long long tx_bytes;

        iface = strtok(line, ":");
        iface = strtok(NULL, " ");
        tx_bytes = strtoull(strtok(NULL, " "), NULL, 10);

        return tx_bytes;
    }

    fclose(fp);
}