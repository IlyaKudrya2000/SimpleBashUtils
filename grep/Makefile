all: s21_grep
s21_grep: s21_grep.o
		gcc s21_grep.o -o s21_grep
s21_grep.o: s21_grep.c
		gcc -c s21_grep.c -o s21_grep.o
clean:
		rm -rf *.o*                      