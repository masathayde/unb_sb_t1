# Universidade de Brasilia - Ciencia da Computacao
# Software Basico - 2/2022
# Prof. Bruno Macchiavello
# Marco Antonio Souza de Athayde - 18/0126814
# Trabalho 1: Montador

* Instruções
Para compilar, utilizar o comando 'make', com o arquivo makefile presente na pasta.
Caso make não esteja disponível ou não funcione, compilar com:
g++ -o montador.exe -std=c++11 main.cpp common.cpp classes.cpp print.cpp preprocessing.cpp error.cpp tokens.cpp

* Argumentos
Modo de uso, seguido de nome completo do arquivo (incluindo extensão). Exemplo:
./montador.exe -o arquivo.asm

* Arquivos adicionais
O arquivo "instructions.txt" contém a lista de instruções do assembly usado no trabalho e precisa estar presente no diretório do programa.