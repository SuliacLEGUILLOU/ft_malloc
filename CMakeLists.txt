cmake_minimum_required(VERSION 3.6)
project(malloc)

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -O0 -g3")

set(SOURCE_FILES
        main.c
        header/malloc.h
    	malloc.c
		check_size.c
		free.c
		calloc.c
		bzero.c
		memcpy.c
		reallocf.c
		realloc.c
		show_alloc_mem.c
		print.c
		show_hex_mem.c
		is_alloc.c
	)

add_executable(malloc ${SOURCE_FILES})
