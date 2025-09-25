#STRUCTURE OF MAKEFILE: first variables, then rules.

#STRUCTURE OF A RULE IN MAKEFILE:
# target: prerequisites
#	recipe

#target-> the thing you want to create/do
#prerequisites-> the conditions for the recipe to "shoot" (recipe shoots only is prerequisites are ok)
#recipe-> the list of commands that builds the target

#INSERT A VARIABLE:
# easy, just write $(VAR_NAME)

#CONVENTIONALLY USED NAMES FOR TARGETS:
#all-> to build everything. 
#clean-> to remove temporary files.
#fclean-> to remove everything (including executables) (fullclean)
#re-> to rebuild from scratch. 
#name-> name of the variable you want to create

#ECHO: is a comment that is shown in the terminal while the program is running. Example:
#clean:
#    echo "Cleaning up temporary files..."
#    rm -f *.o
#    echo "Cleaning complete!"

# rm -f -> f means 'force', so if the file does not exist yet an error is not returned

# ar -> stands for archiver (requires at least an option after it)

# rcs -> 
#c creates the archive if it does not exist,
# r replaces or add files in the archive,
# s creates/updates the index for the linker,
# NOTE: The order of rcs is not fixed, but it's a good habit to follow the convention.

# LINKING: To create an executable file, the object files need to be linked (the various parts of the
# code need to be linked together). This is done by the linker. Using an index makes the linking
# process much faster (just like for us humans, an index is useful to quickly find information).

#INFO:
# -c (compile)-> creates the file without linking (only .o)
# -o (output) -> you can choose the output name (ex: gcc ft_1.c -o ft_1.o)
#  if you don't use -o the file will be created with a standard name

NAME = libft.a

# Updated source files with new folder structure
SRCS = SRC/ft_is/ft_isalnum.c SRC/ft_is/ft_isalpha.c SRC/ft_is/ft_isascii.c \
		SRC/ft_is/ft_isdigit.c SRC/ft_is/ft_isprint.c SRC/ft_mem/ft_bzero.c \
		SRC/ft_mem/ft_calloc.c SRC/ft_mem/ft_memchr.c SRC/ft_mem/ft_memcmp.c \
		SRC/ft_mem/ft_memcpy.c SRC/ft_mem/ft_memmove.c SRC/ft_mem/ft_memset.c \
		SRC/ft_put/ft_putchar_fd.c SRC/ft_put/ft_putendl_fd.c SRC/ft_put/ft_putnbr_fd.c \
		SRC/ft_put/ft_putstr_fd.c SRC/ft_str/ft_split.c SRC/ft_str/ft_strchr.c \
		SRC/ft_str/ft_strdup.c SRC/ft_str/ft_striteri.c SRC/ft_str/ft_strjoin.c \
		SRC/ft_str/ft_strlcat.c SRC/ft_str/ft_strlcpy.c SRC/ft_str/ft_strlen.c \
		SRC/ft_str/ft_strmapi.c SRC/ft_str/ft_strncmp.c SRC/ft_str/ft_strnstr.c \
		SRC/ft_str/ft_strrchr.c SRC/ft_str/ft_strtrim.c SRC/ft_str/ft_substr.c \
		SRC/ft_to/ft_atoi.c SRC/ft_to/ft_itoa.c SRC/ft_to/ft_tolower.c SRC/ft_to/ft_toupper.c \
		SRC/ft_printf/ft_printf.c SRC/ft_printf/ft_print_char.c SRC/ft_printf/ft_print_hex.c \
		SRC/ft_printf/ft_print_int.c SRC/ft_printf/ft_print_nbr_base.c \
		SRC/ft_printf/ft_print_ptr.c SRC/ft_printf/ft_print_str.c SRC/ft_printf/ft_strlen.c \
		SRC/get_next_line/get_next_line.c SRC/get_next_line/get_next_line_utils.c


OBJS = ${SRCS:.c=.o}


CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror -I./INC

.c.o:
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}


all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all