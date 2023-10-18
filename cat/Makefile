all: s21_cat
s21_cat: s21_cat.o
		gcc s21_cat.o -o s21_cat
s21_cat.o: s21_cat.c
		gcc -c s21_cat.c -o s21_cat.o	
clean:
		rm -rf *.o cat/                      