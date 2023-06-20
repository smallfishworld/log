
#include "log.h"
#include "public_def.h"
#include "time.h"
#include <sys/time.h>
#include <string.h>
#include <unistd.h>





int main((int arg_nums, char* arg[]) {
    const char* filename = "example.txt";
    off_t sizeToRemove = 1000000; // 要删除的字节数

    removeContent(filename, sizeToRemove);

    return 0;
}
