SRCS:= $(wildcard *.c)
OUTS:= $(patsubst %.c,%,$(SRCS))
COM_OPS:= -Wall -g
.PHONY: clean all rebuild

all:$(OUTS)
% : %.c
	$(CC) $^ -o $@ $(COM_OPS)
clean:
	$(RM) $(OUTS)
rebuild:clean all

