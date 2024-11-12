#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#ifdef __APPLE__
#include "./lib/conio-unix.h"
#elif defined(_WIN32) || defined(WIN32)
#include "./lib/conio-dos.h"
#endif

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

// Autor funções
void CadastrarAutor (void);
int BuscaAutorId(FILE *ptr, int ID);
void AlterarAutor(void);
void ExclusaoLogicaDeAutor (void);
void ExclusaoFisicaTodosDeAutor (void);

int BuscaAutorId(FILE *ptr, int ID) {
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

void AlterarAutor(void) {
  FILE *ptr;
  int id, pos;
  Autor AuxAutor;

  ptr = fopen ("biblioteca/autor.dat", "rb+");
  if (ptr == NULL)
    printf ("Erro na abertura do Arquivo\n");
  else {
    printf ("ID do Autor: ");
    scanf ("%d", &id);
    while (id != 0) {
      pos = BuscaAutorId(ptr, id);
      if (pos == -1)
        printf ("Autor desconhecido!!\n");
      else {
        fseek(ptr, pos, 0);
        fread (&AuxAutor, sizeof(Autor), 1, ptr);
        printf ("<<<<< Dados do Autor >>>>\n");
        printf ("ID: %d\n", id);
        printf ("Nome: %s\n", AuxAutor.nome);
        printf ("Nacionalidade: %s\n", AuxAutor.nacionalidade);
        printf ("--------------------------------------------\n");
        printf ("Digite o Novo nome do Autor: ");
        fflush(stdin);
        gets(AuxAutor.nome);
        printf ("Digite a nacionalidade do Autor: ");
        fflush(stdin);
        gets(AuxAutor.nacionalidade);
        printf ("Confirma Alteração? (S/N)\n");
        if (toupper(getch()) == 'S') {
          fseek(ptr, pos, 0);
          fwrite(&AuxAutor, sizeof(Autor), 1, ptr);
          printf ("Dados Alterados!!\n");
        }
      }
      printf ("[0] - SAIR\n");
      printf ("ID do Autor: ");
      scanf ("%d", &id);
    }
    fclose(ptr);
  }
}

void ExclusaoLogicaDeAutor (void) {
  FILE *ptr = fopen ("biblioteca/autor.dat", "rb+");
  int pos;
  Autor AutorAux;

  if (ptr == NULL)
    printf ("Erro na abertura do arquivo\n");
  else {
    printf ("ID do Autor: ");
    scanf("%d", &AutorAux.id);
    while (AutorAux.id != 0) {
      pos = BuscaAutorId(ptr, AutorAux.id);
      if (pos == -1)
        printf ("Autor Desconhecido!!\n");
      else {
        fseek(ptr, pos, 0);
        fread(&AutorAux, sizeof(Autor), 1, ptr);
        printf ("<<<<< Dados do Autor >>>>\n");
        printf ("ID: %d\n", AutorAux.id);
        printf ("Nome: %s\n", AutorAux.nome);
        printf ("Nacionalidade: %s\n", AutorAux.nacionalidade);
        printf ("--------------------------------------------\n");
        printf ("Confirma a Exclusão? (S/N)");
        if (toupper(getch()) == 'S') {
          fseek(ptr, pos, 0);
          AutorAux.excluido = 0;
          fwrite(&AutorAux, sizeof(Autor), 1, ptr);
          printf ("Autor Excluído Logicamente\n");
        }
        else
          printf ("Exclusão Cancelada!!\n");
      }
      printf ("[0] - SAIR\n");
      printf ("ID do Autor: ");
      scanf("%d", &AutorAux.id);
    }
    fclose (ptr);
  }
}

void ExclusaoFisicaTodosDeAutor (void) {
  FILE *ptr = fopen ("biblioteca/autor.dat", "rb");
  Autor AuxAutor;

  if (ptr == NULL)
    printf ("Erro de abertura!!\n");
  else {
    fread (&AuxAutor, sizeof(Autor), 1, ptr);
    FILE *ptrTemp = fopen("biblioteca/autorTemp.dat", "wb");
    while (!feof(ptr)) {
      if (AuxAutor.excluido)
        fwrite(&AuxAutor, sizeof(Autor), 1, ptrTemp);
      fread (&AuxAutor, sizeof(Autor), 1, ptr);
    }
    fclose (ptr);
    fclose(ptrTemp);
    remove("biblioteca/autor.dat");
    rename("biblioteca/autorTemp,dat", "biblioteca/autor.dat");
    printf ("Dados Excluidos Fisicamente\n");
  }
}

int main() {}