#include "../include/memory.h"

struct sysinfo info;

struct statvfs stat;

double getTotalMemory() {

    double totalRam;
    
    if(sysinfo(&info) < 0) perror("sysinfo");

    totalRam = (double) info.totalram / (MEM_GB);

    return totalRam;
}

double getAvailableMemory() {

    double freeRam;

    if(sysinfo(&info) < 0) perror("sysinfo");

    freeRam  = (double) info.freeram / (MEM_GB);

    return freeRam;
}

double getCurrentMemoryUsage() {

    double totalRam, freeRam, ramUsage;

    if(sysinfo(&info) < 0) perror("sysinfo");

    totalRam = getTotalMemory();
    freeRam = getAvailableMemory();
    ramUsage = totalRam - freeRam;

    return ramUsage;
}

double getTotalDiskSpace() {

    double spaceAvailable, totalSpace, spaceUsed;
    const char *path = "/root";

    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    totalSpace = (double)(stat.f_frsize * stat.f_blocks) / (MEM_GB);

    return totalSpace;
}

double getAvailableDiskSpace() {

    double spaceAvailable, totalSpace, spaceUsed;
    const char *path = "/root";

    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    spaceAvailable = (double) (stat.f_bsize * stat.f_bavail) / (MEM_GB);

    return spaceAvailable;
}


//---------------------------------------------------------------------------------
// getCurrentDiskSpace(): get current disk space allocated on the system
//
// output:                return spaceUsed
//---------------------------------------------------------------------------------

double getCurrentDiskSpace() {

    double spaceAvailable, totalSpace, spaceUsed;
    const char *path = "/root";

    if(statvfs(path, &stat) < 0) perror("sysStatvfs");

    totalSpace = (double)(stat.f_frsize * stat.f_blocks) / (MEM_GB);
    spaceAvailable = (double) (stat.f_bsize * stat.f_bavail) / (MEM_GB);
    spaceUsed = totalSpace - spaceAvailable;

    return spaceUsed;
}


//---------------------------------------------------------------------------------