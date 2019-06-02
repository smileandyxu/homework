SRCS = $(wildcard *.c ./lib/*.c)    #wildcard把 指定目录 ./ 和 ../lib 下的所有后缀是c的文件全部展开。

OBJS = $(SRCS:.c = .o)    #OBJS将$(SRCS)下的.c文件转化为.o文件

CC = gcc   #代表所使用的编译器

INCLUDES = -I./include   #头文件查找路径

LIBS = -L./lib   #链接库查找地址

CCFLAGS = -g -Wall    #附加参数

OUTPUT = test   #输出程序名称

all:$(OUTPUT)

$(OUTPUT) : $(OBJS)
	$(CC) $^ -o $@ $(INCLUDES) $(LIBS)

%.o : %.c
	$(CC) -c $< $(CCFLAGS)

clean:
	rm -rf *.out *.o

.PHONY:clean