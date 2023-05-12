
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