#fix var
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif
# var
CC = gcc
NAME = libft_malloc
CFLAGS = -Werror -Wextra -Wall -shared
COFLAGS = -Werror -Wextra -Wall -fPIC
OBJDIR = obj/
HEADERDIR = .
INCLUDES_DIR = header
INCLUDES = $(INCLUDES_DIR)/malloc.h
SRCS = bzero.c \
	   is_alloc.c \
	   print.c \
	   memcpy.c \
	   malloc.c \
	   realloc.c \
	   reallocf.c \
	   calloc.c \
	   free.c \
	   check_size.c \
	   show_alloc_mem.c \
	   show_hex_mem.c

.PHONY: all re clean fclean test

HEADER = libft.h
OBJS = $(addprefix $(OBJDIR),$(subst .c,.o,$(SRCS)))

all: $(NAME).so

$(NAME).so: $(OBJS) $(INCLUDES)
	gcc $(CFLAGS) -o $(NAME)_$(HOSTTYPE).so $(OBJS)
	@if ! [ -f $@ ] ; then \
		ln -s $(NAME)_$(HOSTTYPE).so $@; \
	fi

$(OBJS): | $(OBJDIR)

$(OBJDIR)%.o : %.c $(INCLUDES)
	$(CC) -c $(COFLAGS) -I $(INCLUDES_DIR) $< -o $@

$(OBJDIR):
	@if [ ! -d "$(OBJDIR)" ]; then \
		mkdir $(OBJDIR);\
		fi

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME).so $(NAME)_$(HOSTTYPE).so

proper: all clean

re: fclean all
test: all
	env DYLD_LIBRARY_PATH=`pwd` DYLD_INSERT_LIBRARIES=libft_malloc.so DYLD_FORCE_FLAT_NAMESPACE=1 /bin/ls
