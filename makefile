#--------------------------------------------------------------
#               OpenLinux
#   
#--------------------------------------------------------------
APP_NAME = happy 

#CROSS_COMPILER=arm-oe-linux-gnueabi-
GCC_VERSION=4.9.2

#--------------------------------------------------------------
# Include definition
#--------------------------------------------------------------
LOCAL_INC_DIR = -I./inc
#USR_INC_DIR = -I../../include

#--------------------------------------------------------------
# LIB
#--------------------------------------------------------------
STD_LIB_FILES =	-lpthread -ldl -lrt
#USR_LIB_FILES =	-L ../../libs -l

#--------------------------------------------------------------
# Source code files
#--------------------------------------------------------------
DIRS = $(shell find . -maxdepth 3 -type d)
LOCAL_SRC_FILES = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c)) 
LOCAL_OBJECTS = $(notdir $(patsubst %.c, %.o,$(LOCAL_SRC_FILES)))
		
#--------------------------------------------------------------
# Compilation options
#--------------------------------------------------------------
#LOCAL_CFLAGS = -march=armv7-a -mfpu=neon -g -Wl,--export-dynamic -lm


.PHONY: $(APP_NAME)

$(APP_NAME) : $(LOCAL_SRC_FILES)
	$(CC) $(LOCAL_CFLAGS) $(LOCAL_INC_DIR) $(USR_INC_DIR) $(LOCAL_SRC_FILES) $(STD_LIB_FILES) $(USR_LIB_FILES)  -o $@
	rm -rf  *.o *.a
	@echo ----Building is finished! ----

.PHONY: clean
clean:
	rm -rf $(APP_NAME)
	rm -rf  *.o *.a
