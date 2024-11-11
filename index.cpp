#include <stdio.h>

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

int main() {}