
#include "log.h"
#include "public_def.h"
#include "time.h"
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

static void get_log_time(INT8 *time_str, size_t str_size)
{
	time_t tt;
	struct tm local_time;

	time(&tt);
	localtime_r(&tt, &local_time);
	strftime(time_str, str_size, "%Y%m%d%H%M%S", &local_time);

	return;
}

void write_log_to_sd(INT8* string)
{

}


void main(int arg_nums, char* arg[])
{
	int8 cur_time[128] = {0};
	int old = dup(1);
	get_log_time(cur_time,sizeof(cur_time));
	
	FILE* hand = freopen("1.log","a+",stdout);
	printf("cur time %s\n",cur_time);
	fflush(hand);
	dup2(old,1);
	printf("cur time %s\n",cur_time);
}

int compare_dates(const char *date1, const char *date2) {
    // 比较两个日期的大小
    // 假设日期的格式为 "YYYYMMDDHHMMSS"

    int year1 = atoi(strncpy(strndup(date1, 4), 4));
    int month1 = atoi(strncpy(strndup(date1 + 4, 2), 2));
    int day1 = atoi(strncpy(strndup(date1 + 6, 2), 2));
    int hour1 = atoi(strncpy(strndup(date1 + 8, 2), 2));
    int minute1 = atoi(strncpy(strndup(date1 + 10, 2), 2));
    int second1 = atoi(strncpy(strndup(date1 + 12, 2), 2));

    int year2 = atoi(strncpy(strndup(date2, 4), 4));
    int month2 = atoi(strncpy(strndup(date2 + 4, 2), 2));
    int day2 = atoi(strncpy(strndup(date2 + 6, 2), 2));
    int hour2 = atoi(strncpy(strndup(date2 + 8, 2), 2));
    int minute2 = atoi(strncpy(strndup(date2 + 10, 2), 2));
    int second2 = atoi(strncpy(strndup(date2 + 12, 2), 2));

    return (year1 != year2) ? ((year1 < year2) ? -1 : 1) :
           (month1 != month2) ? ((month1 < month2) ? -1 : 1) :
           (day1 != day2) ? ((day1 < day2) ? -1 : 1) :
           (hour1 != hour2) ? ((hour1 < hour2) ? -1 : 1) :
           (minute1 != minute2) ? ((minute1 < minute2) ? -1 : 1) :
           (second1 != second2) ? ((second1 < second2) ? -1 : 1) : 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int is_valid_filename(const char *filename) {
    // 检查文件名是否满足年月日时分秒命名规则
    // 这里假设文件名的格式为 "YYYYMMDDHHMMSS"
    if (strlen(filename) != 14) {
        return 0;
    }

    for (int i = 0; i < 14; i++) {
        if (!isdigit(filename[i])) {
            return 0;
        }
    }

    return 1;
}

int compare_dates(const char *date1, const char *date2) {
    // 比较两个日期的先后顺序
    return strcmp(date1, date2);
}

void get_oldest_file(const char *folder_path, char *oldest_file) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;

    char oldest_date[15] = "99999999999999";

    dir = opendir(folder_path);
    if (dir == NULL) {
        printf("无法打开文件夹\n");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char file_path[256];
        sprintf(file_path, "%s/%s", folder_path, entry->d_name);

        if (stat(file_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
            if (is_valid_filename(entry->d_name)) {
                if (compare_dates(entry->d_name, oldest_date) < 0) {
                    if (access(file_path, R_OK) == 0) {
                        strcpy(oldest_date, entry->d_name);
                        strcpy(oldest_file, file_path);
                    }
                }
            }
        }
    }

    closedir(dir);
}

int main() {
    const char *folder_path = "/path/to/folder";
    char oldest_file[256];

    get_oldest_file(folder_path, oldest_file);

    if (oldest_file[0] != '\0') {
        printf("最老的文件：%s\n", oldest_file);
    } else {
        printf("文件夹中没有符合命名规则的文件或无法访问文件\n");
    }

    return 0;
}

#include <stdlib.h>
#include <regex.h>

int is_valid_filename(const char *filename) {
    regex_t regex;
    int ret;

    // 编译正则表达式
    ret = regcomp(&regex, "^[0-9]{8}[0-9]{6}_log$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "无法编译正则表达式\n");
        return 0;
    }

    // 匹配正则表达式
    ret = regexec(&regex, filename, 0, NULL, 0);
    if (!ret) {
        // 匹配成功
        regfree(&regex);
        return 1;
    } else if (ret == REG_NOMATCH) {
        // 未匹配
        regfree(&regex);
        return 0;
    } else {
        // 正则表达式匹配出错
        char errbuf[100];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "正则表达式匹配出错: %s\n", errbuf);
        regfree(&regex);
        return 0;
    }
}

#include <stdio.h>

void convert(char a[8][128], char **converted, int rows, int cols) {
    int i;
    for (i = 0; i < rows; i++) {
        converted[i] = a[i];
    }
}

int main() {
    char a[8][128] = {
        "Hello",
        "World",
        "This",
        "Is",
        "An",
        "Example",
        "For",
        "Conversion"
    };

    char *converted[8];
    convert(a, converted, 8, 128);

    int i;
    for (i = 0; i < 8; i++) {
        printf("%s\n", converted[i]);
    }

    return 0;
}

#include <stdio.h>

struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

// 比较日期时间 dt1 和 dt2 的前后关系
int compareDateTime(struct DateTime dt1, struct DateTime dt2) {
    if (dt1.year != dt2.year)
        return (dt1.year < dt2.year) ? -1 : 1;
    if (dt1.month != dt2.month)
        return (dt1.month < dt2.month) ? -1 : 1;
    if (dt1.day != dt2.day)
        return (dt1.day < dt2.day) ? -1 : 1;
    if (dt1.hour != dt2.hour)
        return (dt1.hour < dt2.hour) ? -1 : 1;
    if (dt1.minute != dt2.minute)
        return (dt1.minute < dt2.minute) ? -1 : 1;
    if (dt1.second != dt2.second)
        return (dt1.second < dt2.second) ? -1 : 1;
    return 0; // 日期时间相等
}

int main() {
    struct DateTime dt1 = {2022, 5, 15, 10, 30, 0};
    struct DateTime dt2 = {2023, 2, 28, 12, 0, 0};

    int result = compareDateTime(dt1, dt2);

    if (result < 0)
        printf("dt1 在 dt2 之前\n");
    else if (result > 0)
        printf("dt1 在 dt2 之后\n");
    else
        printf("dt1 和 dt2 相同\n");

    return 0;
}


#include <stdio.h>
#include <string.h>

// 替换字符串中的子串
void replaceSubstring(char *str, const char *oldSubstr, const char *newSubstr) {
    if (str == NULL || oldSubstr == NULL || newSubstr == NULL) {
        // 参数为空，抛出异常或执行相应的错误处理逻辑
        printf("参数不能为空\n");
        return;
    }

    size_t oldSubstrLen = strlen(oldSubstr);
    size_t newSubstrLen = strlen(newSubstr);

    char *pos = strstr(str, oldSubstr); // 找到第一个匹配子串的位置

    while (pos != NULL) {
        // 检查新字符串长度是否超过原字符串长度
        if (newSubstrLen > oldSubstrLen) {
            // 新字符串长度超过原字符串长度，抛出异常或执行相应的错误处理逻辑
            printf("新字符串长度超过原字符串长度\n");
            return;
        }

        // 将匹配子串之后的部分向前移动
        memmove(pos + newSubstrLen, pos + oldSubstrLen, strlen(pos + oldSubstrLen) + 1);
        
        // 复制新的子串到位置 pos
        memcpy(pos, newSubstr, newSubstrLen);

        // 继续查找下一个匹配子串的位置
        pos = strstr(pos + newSubstrLen, oldSubstr);
    }
}

int main() {
    char str[] = "/mnt/mmc01/log/.temp/1.zip";
    const char *oldSubstr = ".temp/";
    const char *newSubstr = "";

    printf("原始字符串: %s\n", str);

    replaceSubstring(str, oldSubstr, newSubstr);

    printf("替换后字符串: %s\n", str);

    return 0;
}

#include <stdio.h>
#include <string.h>

// 替换字符串中的子串
void replaceSubstring(char *str, const char *oldSubstr, const char *newSubstr) {
    if (str == NULL || oldSubstr == NULL || newSubstr == NULL) {
        // 参数为空，抛出异常或执行相应的错误处理逻辑
        printf("参数不能为空\n");
        return;
    }

    size_t oldSubstrLen = strlen(oldSubstr);
    size_t newSubstrLen = strlen(newSubstr);

    char *pos = strstr(str, oldSubstr); // 找到第一个匹配子串的位置

    while (pos != NULL) {
        // 检查新字符串长度是否超过原字符串长度
        if (newSubstrLen > oldSubstrLen) {
            // 新字符串长度超过原字符串长度，抛出异常或执行相应的错误处理逻辑
            printf("新字符串长度超过原字符串长度\n");
            return;
        }

        // 将匹配子串之后的部分向前移动
        memmove(pos + newSubstrLen, pos + oldSubstrLen, strlen(pos + oldSubstrLen) + 1);
        
        // 复制新的子串到位置 pos
        memcpy(pos, newSubstr, newSubstrLen);

        // 继续查找下一个匹配子串的位置
        pos = strstr(pos + newSubstrLen, oldSubstr);
    }
}

int main() {
    char str[] = "/mnt/mmc01/log/.temp/1.zip";
    const char *oldSubstr = ".temp/";
    const char *newSubstr = "";

    printf("原始字符串: %s\n", str);

    replaceSubstring(str, oldSubstr, newSubstr);

    printf("替换后字符串: %s\n", str);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LOG_FILE "kernel_log.txt"

int main() {
    FILE *logFile = fopen(LOG_FILE, "w");
    if (logFile == NULL) {
        printf("Failed to open the log file.\n");
        return 1;
    }

    FILE *kernelLog = popen("dmesg", "r");
    if (kernelLog == NULL) {
        printf("Failed to open the kernel log.\n");
        fclose(logFile);
        return 1;
    }

    char buffer[512];
    while (1) {
        while (fgets(buffer, sizeof(buffer), kernelLog) != NULL) {
            fprintf(logFile, "%s", buffer);
        }
        fflush(logFile);  // 刷新缓冲区，确保内容实时写入文件

        // 暂停一段时间
        sleep(1);

        // 关闭、重新打开 `kernelLog`，以获取更新的内容
        pclose(kernelLog);
        kernelLog = popen("dmesg", "r");
        if (kernelLog == NULL) {
            printf("Failed to open the kernel log.\n");
            break;
        }
    }

    pclose(kernelLog);
    fclose(logFile);

    return 0;
}
