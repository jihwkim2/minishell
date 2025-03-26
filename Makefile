# 변수 정의
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline
SRC = $(wildcard *.c)   # 현재 디렉토리의 모든 .c 파일
OBJ = $(SRC:.c=.o)      # .c 파일을 .o 파일로 변환
TARGET = minishell      # 최종 실행 파일 이름

# 기본 타겟
all: $(TARGET)

# 실행 파일을 만드는 규칙
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# .c 파일을 .o 파일로 변환하는 규칙
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# clean: 생성된 파일 삭제
clean:
	rm -f $(OBJ)

# fclean: 실행 파일 및 .o 파일 삭제
fclean: clean
	rm -f $(TARGET)

# re: 모든 것을 다시 빌드
re: fclean all

