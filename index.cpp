#include <stdio.h>
#include "conio.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h> 
struct Data {
  int dia;
  int mes;
  int ano;
};

struct Livro {
  int id;
  char titulo[100];
  int anoPublicacao;
  int excluido;
};

struct Autor {
  int id;
  char nome[80];
  char nacionalidade[20];
  int excluido;
};

struct Emprestimo {
  int id;
  int idLivro;
  int idPessoa;
  Data dataEmprestimo;
  Data dataDevolucao;
  int excluido;
};

struct Pessoa {
  int id;
  char nome[80];
  char telefone[16];
  char endereco[100];
  int excluido;
};

struct LivroAutor {
  int idLivro;
  int idAutor;
  int excluido;
};

int BuscaAutorId (FILE *ptr, int ID) {
  Autor AuxAutor;

  rewind(ptr);
  fread(&AuxAutor, sizeof(Autor), 1, ptr);

  while (!feof(ptr) && (ID != AuxAutor.id || AuxAutor.excluido != 1))
    fread(&AuxAutor, sizeof(Autor), 1, ptr);
  
  if (!feof(ptr))
    return ftell(ptr) - sizeof(Autor);
  else
    return -1;
}

void CadastrarAutor (void) {
  FILE *ptr;
  Autor AutorAux;

  ptr = fopen ("biblioteca/autor.dat", "ab+");

  if (ptr == NULL)
    AutorAux.id = 0;
  printf ("Nome do Autor: ");
  fflush(stdin);
  gets(AutorAux.nome);
  while (strcasecmp(AutorAux.nome, "\0") != 0) {
    AutorAux.id++;
    printf ("País de Origem do Autor: ");
    fflush(stdin);
    gets(AutorAux.nacionalidade);
    AutorAux.excluido = 1;

    fwrite (&AutorAux, sizeof(Autor), 1, ptr);

    printf ("Nome do Autor: ");
    fflush(stdin);
    gets(AutorAux.nome);
  }
  fclose (ptr);
} 

int main() {}