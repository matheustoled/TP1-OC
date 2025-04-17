compile:
	gcc -o Programa src/instrucao.c src/main.c

run: compile
	./Programa
