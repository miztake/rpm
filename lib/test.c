#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "header.h"
#include "rpmlib.h"

void main(int argc, char **argv)
{
    Header h, h2, h3, h4;
    int fd;
    char *sa[] = {"one", "two", "three"};
    int_32 i32 = 400;
    int_32 i32a[] = {100, 200, 300};
    int_16 i16 = 1;
    int_16 i16a[] = {100, 200, 300};
    char ca[] = "char array";

    h = headerNew();

    headerAddEntry(h, RPMTAG_NAME, RPM_STRING_TYPE, "MarcEwing", 1);
    headerAddEntry(h, RPMTAG_VERSION, RPM_STRING_TYPE, "1.1", 1);
    headerAddEntry(h, RPMTAG_VERSION, RPM_STRING_ARRAY_TYPE, sa, 3);
    headerAddEntry(h, RPMTAG_SIZE, RPM_INT32_TYPE, &i32, 1);
    headerAddEntry(h, RPMTAG_SIZE, RPM_INT16_TYPE, &i16, 1);
    headerAddEntry(h, RPMTAG_SIZE, RPM_INT16_TYPE, i16a, 3);
    headerAddEntry(h, RPMTAG_VENDOR, RPM_CHAR_TYPE, ca, strlen(ca));
    headerAddEntry(h, RPMTAG_SIZE, RPM_INT32_TYPE, i32a, 3);

    printf("Original = %d\n", headerSizeof(h));
    fd = open("test.out", O_WRONLY|O_CREAT);
    headerWrite(fd, h);
    close(fd);
    h2 = headerCopy(h);
    printf("Copy     = %d\n", headerSizeof(h2));

    fd = open("test.out", O_RDONLY);
    h3 = headerRead(fd);
    close(fd);
   
    printf("From disk    = %d\n", headerSizeof(h3));
    h4 = headerCopy(h3);
    printf("Copy of disk = %d\n", headerSizeof(h4));
   
    printf("=====================\n");
    printf("Original\n");
    headerDump(h, stdout, 1);
    printf("=====================\n");
    printf("From disk\n");
    headerDump(h3, stdout, 1);
    printf("=====================\n");
    printf("Copy of disk\n");
    headerDump(h4, stdout, 1);

#if 0
    convertDB("");
#endif
}
