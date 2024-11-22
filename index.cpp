// Padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

// Headers
#include "./headers/figuras.h"
#include "./headers/acoes.h"


#ifdef __APPLE__
// Conio Unix
#include "./lib/conio-unix.h"

#define UNIX
#elif defined(_WIN32) || defined(WIN32)
// Conio Dos
#include <windows.h>
#include "./lib/conio-dos.h"
#include "./lib/meuconio.h"

#define DOS
#endif

#include "./headers/cores.h"

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
void autorMenu();
void tituloMenuAutor();
void ExibirTodosAutores(void);
void exclusaoAutoresMenu ();
void ConsultarAutor(void);
void BuscaAutorPelaLetra (void);
void OrdenaAutorNacionalidade (FILE * PtrAutor);

// Emprestimo
void CadastrarEmprestimo();
void EditarEmprestimo();
void ConsultarEmprestimo();
void ExcluirEmprestimo();
void TodosEmprestimos();
int BuscarEmprestimo(FILE * PonteiroEmprestimoArquivo, int idPessoa, int idLivro);
void emprestimoMenu();
void tituloMenuEmprestimo();
int dataDeDevolucaoValida(Data emprestimo, Data devolucao);
void EmprestimosPorPessoa();
void TodosOsEmprestimosPorPessoa();
void BuscaEmprestimoPorPessoa (void);

// Pessoa
void CadastrarPessoa();
void EditarPessoa();
void ConsultarPessoa(); 
void ExcluirPessoa(); 
void TodasPessoas();
int BuscarPessoaPeloID(FILE * PonteiroPessoaArquivo, int id);
void pessoasMenu();
void tituloMenuPessoas();

//Livro Funções 
void CadastrarLivro (void);
void AlterarLivro (void);
int BuscaLivroId (FILE *ptr, int Id);
void TodosLivroPorPalavra();
void ExclusaoFisicaTodosDeLivro (void);
void ExclusaoLogicaDeLivro (void);
void livroMenu();
void tituloMenuLivro();

//Livro e Autor Funçoes
int BuscaAutorLivro (FILE *ptrAutorLivro, int idLivro, int idAutor);
void CadastraLivroAutor (void);
void tituloMenuLivroAutor();
void livroAutorMenu();
void ExclusaoLogicaLivroAutor (void);
void ExclusaoFisicaTodosDeLivroAutor (void);
void ConsultarLivroAutor (void);

// Outras
int menu(char options[][100], int studentsLogicSize);
void tituloMenuPrincipal();
void limparLinhas(int quantidadeDeOpcoes);
int request(const char message[]);
void moldura(int width, int height, int color);
void tituloMenuRelatorio(void);
void relatorioMenu(void);


void ExcluirPessoasFisicamente() {
  FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb");
  Pessoa tempPessoa;

  if (PonteiroPessoaArquivo != NULL) {
    FILE * TempPonteiroPessoaArquivo = fopen("biblioteca/pessoa-temp.dat", "wb");

    fread(&tempPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
    while(!feof(PonteiroPessoaArquivo)) {
      if (!tempPessoa.excluido) {
        fwrite(&tempPessoa, sizeof(Pessoa), 1, TempPonteiroPessoaArquivo); 
      }

      fread(&tempPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
    }

    fclose(PonteiroPessoaArquivo);
    fclose(TempPonteiroPessoaArquivo);

    remove("biblioteca/pessoa.dat");
    rename("biblioteca/pessoa-temp.dat", "biblioteca/pessoa.dat");
  }
}

void ExcluirEmprestimosFisicamente() {
  FILE * PonteiroEmprestimoArquivo = fopen("biblioteca/emprestimo.dat", "rb");
  Emprestimo tempEmprestimo;

  if (PonteiroEmprestimoArquivo != NULL) {
    FILE * TempPonteiroEmprestimoArquivo = fopen("biblioteca/emprestimo-temp.dat", "wb");

    fread(&tempEmprestimo, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
    while(!feof(PonteiroEmprestimoArquivo)) {
      if (!tempEmprestimo.excluido) {
        fwrite(&tempEmprestimo, sizeof(Emprestimo), 1, TempPonteiroEmprestimoArquivo); 
      }

      fread(&tempEmprestimo, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
    }

    fclose(PonteiroEmprestimoArquivo);
    fclose(TempPonteiroEmprestimoArquivo);

    remove("biblioteca/emprestimo.dat");
    rename("biblioteca/emprestimo-temp.dat", "biblioteca/emprestimo.dat");
  }
}

int main() {
  #ifdef DOS
    SetConsoleOutputCP(CP_UTF8);
  #endif

  ExcluirPessoasFisicamente();
  ExcluirEmprestimosFisicamente();

  int opcaoSelecionada;
  char opcoesPrincipais[10][100] = {
    "Autor",
    "Livro",
    "Empréstimos",
    "Pessoas",
    "Livro e Autor",
    "Relatório"
  };
  
  do {
    clrscr();
    tituloMenuPrincipal();
    fflush(stdin);
    opcaoSelecionada = menu(opcoesPrincipais, 6);

    switch (opcaoSelecionada) {
      case 0:
        autorMenu();
        break;
      case 1:
        livroMenu();
        break;
      case 2: 
        emprestimoMenu();
        break;
      case 3:
        pessoasMenu();
        break;
      case 4:
        livroAutorMenu();;
        break;
      case 5: 
        relatorioMenu();
        break;
    }
  } while (opcaoSelecionada != -1);
}

void autorMenu() {
  int opcaoSelecionada;
  char opcoesAutor[10][100] = {
    "Cadastrar Autor",
    "Alterar Autor",
    "Consultar Autor",
    "Exibir Autores",
    "Excluir Autor",
    "Ordenar Autor",
  };

  do {
    clrscr();
    tituloMenuAutor();
    fflush(stdin);
    opcaoSelecionada = menu(opcoesAutor, 6);
    switch(opcaoSelecionada) {
      case 0:
        CadastrarAutor();
        break;
      case 1:
        AlterarAutor();
        break;
      case 2:
        ConsultarAutor();
        break;
      case 3:
        ExibirTodosAutores();
        getch();
        break;
      case 4:
        exclusaoAutoresMenu();
        break;
      case 5:
        break;
    }
  } while(opcaoSelecionada != -1);
}

void livroMenu () {
  int opcaoSelecionada;
  char opcoesLivro [10][100] = {
    "Cadastrar Livro",
    "Alterar Livro",
    "Consultar Livro",
    "Exibir Livros",
    "Excluir Livro",
    "Ordenar Livro"
  };

  do {
    clrscr();
    tituloMenuLivro();
    opcaoSelecionada = menu (opcoesLivro, 6);

    switch (opcaoSelecionada) {
      case 0:
        CadastrarLivro();
        break;
      case 1:
        AlterarLivro();
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
        break;
    }
  } while (opcaoSelecionada != -1);
}

void emprestimoMenu() {
  int opcaoSelecionada;
  char opcoesEmprestimo[10][100] = {
    "Cadastrar Emprestimo",
    "Alterar Emprestimo",
    "Consultar Emprestimo",
    "Excluir Emprestimo",
    "Todos Emprestimos"
  };

  do {
    clrscr();
    tituloMenuEmprestimo();
    opcaoSelecionada = menu(opcoesEmprestimo, 5);

    switch (opcaoSelecionada) {
      case 0:
        CadastrarEmprestimo();
        break;
      case 1:
        EditarEmprestimo();
        break;
      case 2:
        ConsultarEmprestimo();
        break;
      case 3:
        ExcluirEmprestimo();
        break;
      case 4:
        TodosEmprestimos();
        break;
    }
  } while (opcaoSelecionada != -1);
}

void CadastrarEmprestimo() {
  FILE * PonteiroEmprestimoArquivo = fopen("biblioteca/emprestimo.dat", "ab+");
  Emprestimo novoEmprestimo;
  Pessoa emprestimoPessoa;
  Livro emprestimoLivro;
  int ultimoId, indiceLivro, indicePessoa, indiceEmprestimo;
  
  do {
    if (PonteiroEmprestimoArquivo != NULL) {
      fseek(PonteiroEmprestimoArquivo, 0, 2);
      ultimoId = ftell(PonteiroEmprestimoArquivo) / sizeof(Pessoa);
      novoEmprestimo.id = ultimoId + 1;

      printf(NORMAL "\nForneça o ID da " CYAN "PESSOA" NORMAL " para o emprestimo ou zero para sair: ");
      scanf("%d", &emprestimoPessoa.id);

      if (emprestimoPessoa.id != 0) {
        FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb+");

        if (PonteiroPessoaArquivo != NULL) {
          indicePessoa = BuscarPessoaPeloID(PonteiroPessoaArquivo, emprestimoPessoa.id);

          if (indicePessoa >= 0) {
            fseek(PonteiroPessoaArquivo, indicePessoa, 0);
            fread(&emprestimoPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
            fclose(PonteiroPessoaArquivo);

            printf(CYAN "ID: " NORMAL "%d\n", emprestimoPessoa.id);
            printf(CYAN "Nome: " NORMAL "%s\n", emprestimoPessoa.nome);
            printf(CYAN "Telefone: " NORMAL "%s\n", emprestimoPessoa.telefone);
            printf(CYAN "Endereço: " NORMAL "%s\n", emprestimoPessoa.endereco);

            if (request("Os dados da " CYAN "PESSOA" NORMAL " estão corretos?")) {
              printf(NORMAL "\nForneça o ID do " CYAN "LIVRO" NORMAL " para o emprestimo: ");
              scanf("%d", &emprestimoLivro.id);

              FILE * PonteiroLivroArquivo = fopen("biblioteca/livro.dat", "rb+");

              if (PonteiroLivroArquivo != NULL) {
                indiceLivro = BuscaLivroId(PonteiroLivroArquivo, emprestimoLivro.id);

                if (indiceLivro >= 0) {
                  fseek(PonteiroLivroArquivo, indiceLivro, 0);
                  fread(&emprestimoLivro, sizeof(Livro), 1, PonteiroLivroArquivo);
                  fclose(PonteiroLivroArquivo);

                  printf(CYAN "ID: " NORMAL "%d\n", emprestimoLivro.id);
                  printf(CYAN "Titulo: " NORMAL "%s\n", emprestimoLivro.titulo);
                  printf(CYAN "Ano de publicação: " NORMAL "%d\n", emprestimoLivro.anoPublicacao);

                  if (request("Os dados do " CYAN "LIVRO" NORMAL " estão corretos?")) {
                    indiceEmprestimo = BuscarEmprestimo(PonteiroEmprestimoArquivo, emprestimoPessoa.id, emprestimoLivro.id);

                    if (indiceEmprestimo < 0) {
                      novoEmprestimo.idPessoa = emprestimoPessoa.id;
                      novoEmprestimo.idLivro = emprestimoLivro.id;
                      novoEmprestimo.excluido = 0;

                      printf(NORMAL "\nForneça a data de emprestimo (EX: 00 00 0000): ");
                      scanf("%d%d%d", &novoEmprestimo.dataEmprestimo.dia, &novoEmprestimo.dataEmprestimo.mes, &novoEmprestimo.dataEmprestimo.ano);
                      printf(NORMAL "Forneça a data de devolução (EX: 00 00 0000): ");
                      scanf("%d%d%d", &novoEmprestimo.dataDevolucao.dia, &novoEmprestimo.dataDevolucao.mes, &novoEmprestimo.dataDevolucao.ano);

                      if (dataDeDevolucaoValida(novoEmprestimo.dataEmprestimo, novoEmprestimo.dataDevolucao) == 1) {
                        fwrite(&novoEmprestimo, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
                      } else { printf(RED "[ERROR] Você precisa definir uma data de devolução valida.\n" NORMAL); getch(); limparLinhas(18); }
                    } else { printf(YELLOW "[AVISO] O %s já emprestou esse o livro de titulo \"%s\".\n" NORMAL, emprestimoPessoa.nome, emprestimoLivro.titulo); getch(); limparLinhas(18); }
                  }
                } else { printf(YELLOW "[AVISO] O ID do livro: \"%d\" não existe.\n" NORMAL, emprestimoLivro.id); getch(); limparLinhas(12); }
              } else printf("\nNão foi possivel abrir o arquivo livro.");
            } else { limparLinhas(9); }
          } else { printf(YELLOW "[AVISO] O ID da pessoa: \"%d\" não existe.\n" NORMAL, emprestimoPessoa.id); getch(); limparLinhas(3); }
        } else printf("\nNão foi possivel abrir o arquivo pessoa."); 
      }
    }
  } while(PonteiroEmprestimoArquivo != NULL && emprestimoPessoa.id != 0);
  fclose(PonteiroEmprestimoArquivo);
}

void EditarEmprestimo() {
  FILE * PonteiroEmprestimoArquivo = fopen("biblioteca/emprestimo.dat", "rb+");
  Emprestimo emprestimoEditar;
  Pessoa emprestimoPessoa;
  Livro emprestimoLivro;
  int ultimoId, indiceLivro, indicePessoa, indiceEmprestimo;
  
  do {
    if (PonteiroEmprestimoArquivo != NULL) {
      printf(NORMAL "\nForneça o ID da " CYAN "PESSOA" NORMAL " para o editar o emprestimo ou zero para sair: ");
      scanf("%d", &emprestimoPessoa.id);

      if (emprestimoPessoa.id != 0) {
        FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb+");

        if (PonteiroPessoaArquivo != NULL) {
          indicePessoa = BuscarPessoaPeloID(PonteiroPessoaArquivo, emprestimoPessoa.id);

          if (indicePessoa >= 0) {
            fseek(PonteiroPessoaArquivo, indicePessoa, 0);
            fread(&emprestimoPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
            fclose(PonteiroPessoaArquivo);

            printf(CYAN "ID: " NORMAL "%d\n", emprestimoPessoa.id);
            printf(CYAN "Nome: " NORMAL "%s\n", emprestimoPessoa.nome);
            printf(CYAN "Telefone: " NORMAL "%s\n", emprestimoPessoa.telefone);
            printf(CYAN "Endereço: " NORMAL "%s\n", emprestimoPessoa.endereco);

            if (request("Os dados da " CYAN "PESSOA" NORMAL " estão corretos?")) {
              printf(NORMAL "\nForneça o ID do " CYAN "LIVRO" NORMAL " para editar o emprestimo: ");
              scanf("%d", &emprestimoLivro.id);

              FILE * PonteiroLivroArquivo = fopen("biblioteca/livro.dat", "rb+");

              if (PonteiroLivroArquivo != NULL) {
                indiceLivro = BuscaLivroId(PonteiroLivroArquivo, emprestimoLivro.id);

                if (indiceLivro >= 0) {
                  fseek(PonteiroLivroArquivo, indiceLivro, 0);
                  fread(&emprestimoLivro, sizeof(Livro), 1, PonteiroLivroArquivo);
                  fclose(PonteiroLivroArquivo);

                  printf(CYAN "ID: " NORMAL "%d\n", emprestimoLivro.id);
                  printf(CYAN "Nome: " NORMAL "%s\n", emprestimoLivro.titulo);
                  printf(CYAN "Ano de publicação: " NORMAL "%d\n", emprestimoLivro.anoPublicacao);

                  if (request("Os dados do " CYAN "LIVRO" NORMAL " estão corretos?")) {
                    indiceEmprestimo = BuscarEmprestimo(PonteiroEmprestimoArquivo, emprestimoPessoa.id, emprestimoLivro.id);

                    if (indiceEmprestimo >= 0) {
                      fseek(PonteiroEmprestimoArquivo, indiceEmprestimo, 0);
                      fread(&emprestimoEditar, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);

                      printf(CYAN "\nData de empretimo: " NORMAL "%d/%d/%d\n", emprestimoEditar.dataEmprestimo.dia, emprestimoEditar.dataEmprestimo.mes, emprestimoEditar.dataEmprestimo.ano);
                      printf(CYAN "Data de devolução: " NORMAL "%d/%d/%d\n", emprestimoEditar.dataDevolucao.dia, emprestimoEditar.dataDevolucao.mes, emprestimoEditar.dataDevolucao.ano);

                      if (request("Você deseja editar esses dados?")) {
                        printf(NORMAL "\nForneça a nova data de emprestimo (EX: 00 00 0000): ");
                        scanf("%d%d%d", &emprestimoEditar.dataEmprestimo.dia, &emprestimoEditar.dataEmprestimo.mes, &emprestimoEditar.dataEmprestimo.ano);
                        printf(NORMAL "Forneça a nova data de devolução (EX: 00 00 0000): ");
                        scanf("%d%d%d", &emprestimoEditar.dataDevolucao.dia, &emprestimoEditar.dataDevolucao.mes, &emprestimoEditar.dataDevolucao.ano);

                        if (dataDeDevolucaoValida(emprestimoEditar.dataEmprestimo, emprestimoEditar.dataDevolucao) == 1) {
                          fseek(PonteiroEmprestimoArquivo, indiceEmprestimo, 0);
                          fwrite(&emprestimoEditar, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
                        } else { printf(RED "[ERROR] Você precisa definir uma data de devolução valida.\n" NORMAL); getch(); limparLinhas(18); }
                      } else { limparLinhas(23); }
                    } else { printf(YELLOW "[AVISO] Esse emprestimo não existe.\n" NORMAL); getch(); limparLinhas(18); }
                  } else { limparLinhas(17); }
                } else { printf(YELLOW "[AVISO] O ID do livro: \"%d\" não existe.\n" NORMAL, emprestimoLivro.id); getch(); limparLinhas(12); }
              } else printf("\nNão foi possivel abrir o arquivo livro.");
            } else { limparLinhas(9); }
          } else { printf(YELLOW "[AVISO] O ID da pessoa: \"%d\" não existe.\n" NORMAL, emprestimoPessoa.id); getch(); limparLinhas(3); }
        } else printf("\nNão foi possivel abrir o arquivo pessoa."); 
      }
    }
  } while(PonteiroEmprestimoArquivo != NULL && emprestimoPessoa.id != 0);
  fclose(PonteiroEmprestimoArquivo);
}
void ConsultarEmprestimo() {
  FILE * PonteiroEmprestimoArquivo = fopen("biblioteca/emprestimo.dat", "rb+");
  Emprestimo emprestimoConsultar;
  Pessoa emprestimoPessoa;
  Livro emprestimoLivro;
  int ultimoId, indiceLivro, indicePessoa, indiceEmprestimo;
  
  do {
    if (PonteiroEmprestimoArquivo != NULL) {
      printf(NORMAL "\nForneça o ID da " CYAN "PESSOA" NORMAL " para o editar o emprestimo ou zero para sair: ");
      scanf("%d", &emprestimoPessoa.id);

      if (emprestimoPessoa.id != 0) {
        FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb+");

        if (PonteiroPessoaArquivo != NULL) {
          indicePessoa = BuscarPessoaPeloID(PonteiroPessoaArquivo, emprestimoPessoa.id);

          if (indicePessoa >= 0) {
            fseek(PonteiroPessoaArquivo, indicePessoa, 0);
            fread(&emprestimoPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
            fclose(PonteiroPessoaArquivo);

            printf(CYAN "ID: " NORMAL "%d\n", emprestimoPessoa.id);
            printf(CYAN "Nome: " NORMAL "%s\n", emprestimoPessoa.nome);
            printf(CYAN "Telefone: " NORMAL "%s\n", emprestimoPessoa.telefone);
            printf(CYAN "Endereço: " NORMAL "%s\n", emprestimoPessoa.endereco);

            if (request("Os dados da " CYAN "PESSOA" NORMAL " estão corretos?")) {
              printf(NORMAL "\nForneça o ID do " CYAN "LIVRO" NORMAL " para consultar o emprestimo: ");
              scanf("%d", &emprestimoLivro.id);

              FILE * PonteiroLivroArquivo = fopen("biblioteca/livro.dat", "rb+");

              if (PonteiroLivroArquivo != NULL) {
                indiceLivro = BuscaLivroId(PonteiroLivroArquivo, emprestimoLivro.id);

                if (indiceLivro >= 0) {
                  fseek(PonteiroLivroArquivo, indiceLivro, 0);
                  fread(&emprestimoLivro, sizeof(Livro), 1, PonteiroLivroArquivo);
                  fclose(PonteiroLivroArquivo);

                  printf(CYAN "ID: " NORMAL "%d\n", emprestimoLivro.id);
                  printf(CYAN "Nome: " NORMAL "%s\n", emprestimoLivro.titulo);
                  printf(CYAN "Ano de publicação: " NORMAL "%d\n", emprestimoLivro.anoPublicacao);

                  if (request("Os dados do " CYAN "LIVRO" NORMAL " estão corretos?")) {
                    indiceEmprestimo = BuscarEmprestimo(PonteiroEmprestimoArquivo, emprestimoPessoa.id, emprestimoLivro.id);

                    if (indiceEmprestimo >= 0) {
                      fseek(PonteiroEmprestimoArquivo, indiceEmprestimo, 0);
                      fread(&emprestimoConsultar, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);

                      printf(CYAN "\nData de empretimo: " NORMAL "%d/%d/%d\n", emprestimoConsultar.dataEmprestimo.dia, emprestimoConsultar.dataEmprestimo.mes, emprestimoConsultar.dataEmprestimo.ano);
                      printf(CYAN "Data de devolução: " NORMAL "%d/%d/%d\n", emprestimoConsultar.dataDevolucao.dia, emprestimoConsultar.dataDevolucao.mes, emprestimoConsultar.dataDevolucao.ano);

                      getch();
                      limparLinhas(20);
                    } else { printf(YELLOW "[AVISO] Esse emprestimo não existe.\n" NORMAL); getch(); limparLinhas(18); }
                  } else { limparLinhas(17); }
                } else { printf(YELLOW "[AVISO] O ID do livro: \"%d\" não existe.\n" NORMAL, emprestimoLivro.id); getch(); limparLinhas(12); }
              } else printf("\nNão foi possivel abrir o arquivo livro.");
            } else { limparLinhas(9); }
          } else { printf(YELLOW "[AVISO] O ID da pessoa: \"%d\" não existe.\n" NORMAL, emprestimoPessoa.id); getch(); limparLinhas(3); }
        } else printf("\nNão foi possivel abrir o arquivo pessoa."); 
      }
    }
  } while(PonteiroEmprestimoArquivo != NULL && emprestimoPessoa.id != 0);
  fclose(PonteiroEmprestimoArquivo);
}

void ExcluirEmprestimo() {
  FILE * PonteiroEmprestimoArquivo = fopen("biblioteca/emprestimo.dat", "rb+");
  Emprestimo emprestimoExcluir;
  Pessoa emprestimoPessoa;
  Livro emprestimoLivro;
  int ultimoId, indiceLivro, indicePessoa, indiceEmprestimo;
  
  do {
    if (PonteiroEmprestimoArquivo != NULL) {
      printf(NORMAL "\nForneça o ID da " CYAN "PESSOA" NORMAL " para o editar o emprestimo ou zero para sair: ");
      scanf("%d", &emprestimoPessoa.id);

      if (emprestimoPessoa.id != 0) {
        FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb+");

        if (PonteiroPessoaArquivo != NULL) {
          indicePessoa = BuscarPessoaPeloID(PonteiroPessoaArquivo, emprestimoPessoa.id);

          if (indicePessoa >= 0) {
            fseek(PonteiroPessoaArquivo, indicePessoa, 0);
            fread(&emprestimoPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
            fclose(PonteiroPessoaArquivo);

            printf(CYAN "ID: " NORMAL "%d\n", emprestimoPessoa.id);
            printf(CYAN "Nome: " NORMAL "%s\n", emprestimoPessoa.nome);
            printf(CYAN "Telefone: " NORMAL "%s\n", emprestimoPessoa.telefone);
            printf(CYAN "Endereço: " NORMAL "%s\n", emprestimoPessoa.endereco);

            if (request("Os dados da " CYAN "PESSOA" NORMAL " estão corretos?")) {
              printf(NORMAL "\nForneça o ID do " CYAN "LIVRO" NORMAL " para excluir o emprestimo: ");
              scanf("%d", &emprestimoLivro.id);

              FILE * PonteiroLivroArquivo = fopen("biblioteca/livro.dat", "rb+");

              if (PonteiroLivroArquivo != NULL) {
                indiceLivro = BuscaLivroId(PonteiroLivroArquivo, emprestimoLivro.id);

                if (indiceLivro >= 0) {
                  fseek(PonteiroLivroArquivo, indiceLivro, 0);
                  fread(&emprestimoLivro, sizeof(Livro), 1, PonteiroLivroArquivo);
                  fclose(PonteiroLivroArquivo);

                  printf(CYAN "ID: " NORMAL "%d\n", emprestimoLivro.id);
                  printf(CYAN "Nome: " NORMAL "%s\n", emprestimoLivro.titulo);
                  printf(CYAN "Ano de publicação: " NORMAL "%d\n", emprestimoLivro.anoPublicacao);

                  if (request("Os dados do " CYAN "LIVRO" NORMAL " estão corretos?")) {
                    indiceEmprestimo = BuscarEmprestimo(PonteiroEmprestimoArquivo, emprestimoPessoa.id, emprestimoLivro.id);

                    if (indiceEmprestimo >= 0) {
                      fseek(PonteiroEmprestimoArquivo, indiceEmprestimo, 0);
                      fread(&emprestimoExcluir, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);

                      printf(CYAN "\nData de empretimo: " NORMAL "%d/%d/%d\n", emprestimoExcluir.dataEmprestimo.dia, emprestimoExcluir.dataEmprestimo.mes, emprestimoExcluir.dataEmprestimo.ano);
                      printf(CYAN "Data de devolução: " NORMAL "%d/%d/%d\n", emprestimoExcluir.dataDevolucao.dia, emprestimoExcluir.dataDevolucao.mes, emprestimoExcluir.dataDevolucao.ano);

                      if (request("Você deseja excluir esse emprestimo")) {
                        emprestimoExcluir.excluido = 1;

                        fseek(PonteiroEmprestimoArquivo, indiceEmprestimo, 0);
                        fwrite(&emprestimoExcluir, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
                      } else { limparLinhas(23); }
                    } else { printf(YELLOW "[AVISO] Esse emprestimo não existe.\n" NORMAL); getch(); limparLinhas(18); }
                  } else { limparLinhas(17); }
                } else { printf(YELLOW "[AVISO] O ID do livro: \"%d\" não existe.\n" NORMAL, emprestimoLivro.id); getch(); limparLinhas(12); }
              } else printf("\nNão foi possivel abrir o arquivo livro.");
            } else { limparLinhas(9); }
          } else { printf(YELLOW "[AVISO] O ID da pessoa: \"%d\" não existe.\n" NORMAL, emprestimoPessoa.id); getch(); limparLinhas(3); }
        } else printf("\nNão foi possivel abrir o arquivo pessoa."); 
      }
    }
  } while(PonteiroEmprestimoArquivo != NULL && emprestimoPessoa.id != 0);
  fclose(PonteiroEmprestimoArquivo);
}

void TodosEmprestimos() {
  FILE * PonteiroEmprestimoArquivo = fopen("biblioteca/emprestimo.dat", "rb");
  Emprestimo emprestimo;
  Pessoa emprestimoPessoa;
  Livro emprestimoLivro;
  int indicePessoa, indiceLivro;

  if (PonteiroEmprestimoArquivo != NULL) {
    fread(&emprestimo, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
    while(!feof(PonteiroEmprestimoArquivo)) {
      FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb");

      if (PonteiroPessoaArquivo != NULL) {
        indicePessoa = BuscarPessoaPeloID(PonteiroPessoaArquivo, emprestimo.idPessoa);

        if (indicePessoa >= 0) {
          fseek(PonteiroPessoaArquivo, indicePessoa, 0);
          fread(&emprestimoPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);

          printf(CYAN "\nEmprestimo de ID: " NORMAL "%d\n", emprestimoLivro.id);
          printf(CYAN "\nID: " NORMAL "%d\t", emprestimoPessoa.id);
          printf(CYAN "Nome: " NORMAL "%s\n", emprestimoPessoa.nome);
          printf(CYAN "Telefone: " NORMAL "%s\n", emprestimoPessoa.telefone);
          printf(CYAN "Endereço: " NORMAL "%s\n", emprestimoPessoa.endereco);

          FILE * PonteiroLivroArquivo = fopen("biblioteca/livro.dat", "rb");

          if (PonteiroLivroArquivo != NULL) {
            indiceLivro = BuscaLivroId(PonteiroLivroArquivo, emprestimo.idLivro);

            if (indiceLivro >= 0) {
              fseek(PonteiroLivroArquivo, indiceLivro, 0);
              fread(&emprestimoLivro, sizeof(Livro), 1, PonteiroLivroArquivo);
              fclose(PonteiroLivroArquivo);

              printf(CYAN "Nome: " NORMAL "%s\n", emprestimoLivro.titulo);
              printf(CYAN "Ano de publicação: " NORMAL "%d\n", emprestimoLivro.anoPublicacao);
              printf(CYAN "Data de empretimo: " NORMAL "%d/%d/%d\n", emprestimo.dataEmprestimo.dia, emprestimo.dataEmprestimo.mes, emprestimo.dataEmprestimo.ano);
              printf(CYAN "Data de devolução: " NORMAL "%d/%d/%d\n", emprestimo.dataDevolucao.dia, emprestimo.dataDevolucao.mes, emprestimo.dataDevolucao.ano);
            }
          }
        }
      }

      fread(&emprestimo, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
    }
  } else printf("\nNão foi possivel abrir o arquivo emprestimo."); 
  fclose(PonteiroEmprestimoArquivo);
  getch();
}

int BuscarEmprestimo(FILE * PonteiroEmprestimoArquivo, int idPessoa, int idLivro) {
  Emprestimo tempEmprestimo;

  fseek(PonteiroEmprestimoArquivo, 0, 0);
  fread(&tempEmprestimo, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
  while(!feof(PonteiroEmprestimoArquivo) && (tempEmprestimo.idPessoa != idPessoa || tempEmprestimo.idLivro != idLivro || tempEmprestimo.excluido != 0))
    fread(&tempEmprestimo, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);

  if (!feof(PonteiroEmprestimoArquivo)) {
    return ftell(PonteiroEmprestimoArquivo) - sizeof(Emprestimo);
  }

  return -1;
}

int dataDeDevolucaoValida(Data emprestimo, Data devolucao) {
  if (emprestimo.ano < devolucao.ano) {
    return 0;
  }

  if (emprestimo.ano == devolucao.ano) {
    if (emprestimo.mes < devolucao.mes) {
      return 0;
    }

    if (emprestimo.mes == devolucao.mes) {
      return emprestimo.dia <= devolucao.dia;
    }
  }

  return 1;
}

void pessoasMenu() {
  int opcaoSelecionada;
  char opcoesPessoas[10][100] = {
    "Cadastrar Pessoa",
    "Alterar Pessoa",
    "Consultar Pessoa",
    "Excluir Pessoa",
    "Todas Pessoas",
  };

  do {
    clrscr();
    tituloMenuPessoas();
    opcaoSelecionada = menu(opcoesPessoas, 5);

    switch (opcaoSelecionada){
      case 0:
        CadastrarPessoa();
        break;
      case 1:
        EditarPessoa();
        break;
      case 2:
        ConsultarPessoa();
        break;
      case 3:
        ExcluirPessoa();
        break;
      case 4:
        TodasPessoas();
        break;
    }
  } while (opcaoSelecionada != -1);
}

void CadastrarPessoa() {
  FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "ab+");
  Pessoa novaPessoa;
  int ultimoId;

  do {
    if (PonteiroPessoaArquivo != NULL) {
      fseek(PonteiroPessoaArquivo, 0, 2);
      ultimoId = ftell(PonteiroPessoaArquivo) / sizeof(Pessoa);
      novaPessoa.id = ultimoId + 1;

      printf(RED "\nDados do nova pessoa de número " NORMAL "#%d\n", novaPessoa.id);

      printf("Nome: ");
      fflush(stdin);
      gets(novaPessoa.nome);

      if (strlen(novaPessoa.nome) >= 1) {
        printf("Telefone EX: (18) 99678-5231: ");
        fflush(stdin);
        gets(novaPessoa.telefone);

        printf("Endereço: ");
        fflush(stdin);
        gets(novaPessoa.endereco);

        novaPessoa.excluido = 0;

        fwrite(&novaPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
      }

      limparLinhas(5);
    } else printf("\nNão foi possivel abrir o arquivo pessoa.");
  } while(PonteiroPessoaArquivo != NULL && strlen(novaPessoa.nome) >= 1);
  fclose(PonteiroPessoaArquivo);
}

void EditarPessoa() {
  FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb+");
  Pessoa PessoaEditar;
  int indice;

  do {
    if (PonteiroPessoaArquivo != NULL) {
      printf(NORMAL "\nForneça o ID da pessoa para editar ou zero para finalizar: ");
      scanf("%d", &PessoaEditar.id);

      indice = BuscarPessoaPeloID(PonteiroPessoaArquivo, PessoaEditar.id);

      if (indice >= 0) {
        fseek(PonteiroPessoaArquivo, indice, 0);
        fread(&PessoaEditar, sizeof(Pessoa), 1, PonteiroPessoaArquivo);

        printf(CYAN "ID: " NORMAL "%d\n", PessoaEditar.id);
        printf(CYAN "Nome: " NORMAL "%s\n", PessoaEditar.nome);
        printf(CYAN "Telefone: " NORMAL "%s\n", PessoaEditar.telefone);
        printf(CYAN "Endereço: " NORMAL "%s\n", PessoaEditar.endereco);

        if (request("Você quer editar essa Pessoa?")) {
          printf(RED "\nNovos dados da pessoa de número " NORMAL "#%d\n", PessoaEditar.id);

          printf("Nome: ");
          fflush(stdin);
          gets(PessoaEditar.nome);

          printf("Telefone | EX: (18) 99678-5231: ");
          fflush(stdin);
          gets(PessoaEditar.telefone);

          printf("Endereço: ");
          fflush(stdin);
          gets(PessoaEditar.endereco);

          if (request("Você deseja salvar as alterações")) {
            fseek(PonteiroPessoaArquivo, indice, 0);
            fwrite(&PessoaEditar, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
            limparLinhas(17);
          }
        } else limparLinhas(9);
      } else printf(YELLOW "[AVISO] O ID: \"%d\" não existe.\n" NORMAL, PessoaEditar.id);
    } else printf("\nNão foi possivel abrir o arquivo pessoa.");
  } while(PonteiroPessoaArquivo != NULL && PessoaEditar.id != 0);
  fclose (PonteiroPessoaArquivo);
}

void ConsultarPessoa() {
  FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb+");
  Pessoa PessoaConsultar;
  int indice;

  do {
    if (PonteiroPessoaArquivo != NULL) {
      printf(NORMAL "\nForneça o ID da pessoa para consultar ou zero para finalizar: ");
      scanf("%d", &PessoaConsultar.id);

      indice = BuscarPessoaPeloID(PonteiroPessoaArquivo, PessoaConsultar.id);

      if (indice >= 0) {
        fseek(PonteiroPessoaArquivo, indice, 0);
        fread(&PessoaConsultar, sizeof(Pessoa), 1, PonteiroPessoaArquivo);

        printf(CYAN "ID: " NORMAL "%d\n", PessoaConsultar.id);
        printf(CYAN "Nome: " NORMAL "%s\n", PessoaConsultar.nome);
        printf(CYAN "Telefone: " NORMAL "%s\n", PessoaConsultar.telefone);
        printf(CYAN "Endereço: " NORMAL "%s\n", PessoaConsultar.endereco);

        getch();
        limparLinhas(6);
      } else printf(YELLOW "[AVISO] O ID: \"%d\" não existe.\n" NORMAL, PessoaConsultar.id);
    } else printf("\nNão foi possivel abrir o arquivo pessoa.");
  } while(PonteiroPessoaArquivo != NULL && PessoaConsultar.id != 0);
  fclose (PonteiroPessoaArquivo);
}

void ExcluirPessoa() {
  FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb+");
  Pessoa PessoaExcluir;
  int indice;

  do {
    if (PonteiroPessoaArquivo != NULL) {
      printf(NORMAL "\nForneça o ID da pessoa para excluir ou zero para finalizar: ");
      scanf("%d", &PessoaExcluir.id);

      indice = BuscarPessoaPeloID(PonteiroPessoaArquivo, PessoaExcluir.id);

      if (indice >= 0) {
        fseek(PonteiroPessoaArquivo, indice, 0);
        fread(&PessoaExcluir, sizeof(Pessoa), 1, PonteiroPessoaArquivo);

        printf(CYAN "ID: " NORMAL "%d\n", PessoaExcluir.id);
        printf(CYAN "Nome: " NORMAL "%s\n", PessoaExcluir.nome);
        printf(CYAN "Telefone: " NORMAL "%s\n", PessoaExcluir.telefone);
        printf(CYAN "Endereço: " NORMAL "%s\n", PessoaExcluir.endereco);

        if (request("Você quer excluir essa Pessoa?")) {
          PessoaExcluir.excluido = 1;

          fseek(PonteiroPessoaArquivo, indice, 0);
          fwrite(&PessoaExcluir, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
        } else limparLinhas(9);
      } else printf(YELLOW "[AVISO] O ID: \"%d\" não existe.\n" NORMAL, PessoaExcluir.id);
    } else printf("\nNão foi possivel abrir o arquivo pessoa.");
  } while(PonteiroPessoaArquivo != NULL && PessoaExcluir.id != 0);
  fclose (PonteiroPessoaArquivo);
}

void TodasPessoas() {
  FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb");
  Pessoa pessoa;
  if (PonteiroPessoaArquivo != NULL) {
    fread(&pessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
    while(!feof(PonteiroPessoaArquivo)) {
      printf(CYAN "\nID: " NORMAL "%d\t", pessoa.id);
      printf(CYAN "Nome: " NORMAL "%s\n", pessoa.nome);
      printf(CYAN "Telefone: " NORMAL "%s\n", pessoa.telefone);
      printf(CYAN "Endereço: " NORMAL "%s\n", pessoa.endereco);

      fread(&pessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
    }
  } else printf("\nNão foi possivel abrir o arquivo pessoa.");

  fclose(PonteiroPessoaArquivo);
  getch();
}

int BuscarPessoaPeloID(FILE * PonteiroPessoaArquivo, int id) {
  Pessoa tempPessoa;

  fseek(PonteiroPessoaArquivo, 0, 0);
  fread(&tempPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
  while(!feof(PonteiroPessoaArquivo) && (tempPessoa.id != id || tempPessoa.excluido != 0))
    fread(&tempPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);

  if (!feof(PonteiroPessoaArquivo)) {
    return ftell(PonteiroPessoaArquivo) - sizeof(Pessoa);
  }

  return -1;
}

void livroAutorMenu() {
  int opcaoSelecionada;
  char opcoesLivroAutor[10][100] = {
    "Cadastrar Livro a um Autor",
    "Alterar",
    "Consultar",
    "Exibir Todos",
    "Excluir Relacionamento",
    "Excluir Todos",
    "Ordenar"
  }; 

  do {
    clrscr();
    tituloMenuLivroAutor();
    opcaoSelecionada = menu (opcoesLivroAutor, 6);

    switch (opcaoSelecionada){
      case 0:
        CadastraLivroAutor();
        break;
      case 1:
        break;
      case 2:
        ConsultarLivroAutor();
        break;
      case 3:
        break;
      case 4:
        ExclusaoLogicaLivroAutor();
        break;
      case 5:
      ExclusaoFisicaTodosDeLivroAutor();
        break;
      case 6: 
        break;
    }
  } while (opcaoSelecionada != -1);
}

void relatorioMenu(void) {
  int opcaoSelecionada;
  char opcoesRelatorio[10][100] = {
    "Autores que começam com uma determinada letra ordenado pela nacionalidade",
    "Livros com titulo que contenham uma determinada palavra ordenados pelo ano de publicação",
    "Empréstimos de uma pessoa específica",
    "Dados de livros de um autor específico",
    "Empréstimos com os dados detalhados separados por pessoa"
  };

  do {
    clrscr();
    tituloMenuRelatorio();
    opcaoSelecionada = menu (opcoesRelatorio, 5);

    switch (opcaoSelecionada) {
      case 0:
        BuscaAutorPelaLetra ();
        break;
      case 1:
        TodosLivroPorPalavra();
        break;
      case 2:
        EmprestimosPorPessoa();
        break;
      case 3:
        break;
      case 4:
        TodosOsEmprestimosPorPessoa();
        break;
    }

  } while (opcaoSelecionada != -1);
}

void EmprestimosPorPessoa() {
  FILE * PonteiroEmprestimoArquivo = fopen("biblioteca/emprestimo.dat", "rb+");
  Emprestimo emprestimo;
  Pessoa emprestimoPessoa;
  Livro emprestimoLivro;
  int indicePessoa, indiceLivro;
  
  do {
    if (PonteiroEmprestimoArquivo != NULL) {
      printf(NORMAL "\nForneça o ID da " CYAN "PESSOA" NORMAL " para listar os emprestimos: ");
      scanf("%d", &emprestimoPessoa.id);

      if (emprestimoPessoa.id != 0) {
        FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb+");

        if (PonteiroPessoaArquivo != NULL) {
          indicePessoa = BuscarPessoaPeloID(PonteiroPessoaArquivo, emprestimoPessoa.id);

          if (indicePessoa >= 0) {
            fseek(PonteiroPessoaArquivo, indicePessoa, 0);
            fread(&emprestimoPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);

            printf(CYAN "\nID: " NORMAL "%d\t", emprestimoPessoa.id);
            printf(CYAN "Nome: " NORMAL "%s\n", emprestimoPessoa.nome);
            printf(CYAN "Telefone: " NORMAL "%s\n", emprestimoPessoa.telefone);
            printf(CYAN "Endereço: " NORMAL "%s\n", emprestimoPessoa.endereco);

            fseek(PonteiroEmprestimoArquivo, 0, 0);
            fread(&emprestimo, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
            while(!feof(PonteiroEmprestimoArquivo)) {
              if (emprestimo.idPessoa == emprestimoPessoa.id) {
                FILE * PonteiroLivroArquivo = fopen("biblioteca/livro.dat", "rb+");

                if (PonteiroLivroArquivo != NULL) {
                  indiceLivro = BuscaLivroId(PonteiroLivroArquivo, emprestimo.idLivro);

                  if (indiceLivro >= 0) {
                    fseek(PonteiroLivroArquivo, indiceLivro, 0);
                    fread(&emprestimoLivro, sizeof(Livro), 1, PonteiroLivroArquivo);
                    fclose(PonteiroLivroArquivo);

                    printf(CYAN "\nEmprestimo de ID: " NORMAL "%d\n", emprestimoLivro.id);
                    printf(CYAN "Nome: " NORMAL "%s\n", emprestimoLivro.titulo);
                    printf(CYAN "Ano de publicação: " NORMAL "%d\n", emprestimoLivro.anoPublicacao);
                    printf(CYAN "Data de empretimo: " NORMAL "%d/%d/%d\n", emprestimo.dataEmprestimo.dia, emprestimo.dataEmprestimo.mes, emprestimo.dataEmprestimo.ano);
                    printf(CYAN "Data de devolução: " NORMAL "%d/%d/%d\n", emprestimo.dataDevolucao.dia, emprestimo.dataDevolucao.mes, emprestimo.dataDevolucao.ano);
                  }
                } else printf("\nNão foi possivel abrir o arquivo emprestimo."); 
              }

              fread(&emprestimo, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
            }
          } else { printf(YELLOW "[AVISO] O ID da pessoa: \"%d\" não existe.\n" NORMAL, emprestimoPessoa.id); getch(); limparLinhas(3); }
        } else printf("\nNão foi possivel abrir o arquivo pessoa."); 

        fclose(PonteiroPessoaArquivo);
      }
    }
  } while(PonteiroEmprestimoArquivo != NULL && emprestimoPessoa.id != 0);
  fclose(PonteiroEmprestimoArquivo);
}

void OrdernadarLivroPorAnoDePublicacao(FILE * PonteiroLivroArquivo) {
  int Qtd, i;
  Livro livroA, livroB;

  fseek(PonteiroLivroArquivo, 0, 2);
  Qtd = ftell(PonteiroLivroArquivo) / sizeof (Livro);
  for (; Qtd > 1; Qtd--) {
    i=0; 
    while (i < Qtd-1) {
      fseek (PonteiroLivroArquivo, i*sizeof(Livro), 0);
      fread (&livroA, sizeof(Livro), 1, PonteiroLivroArquivo);

      fseek (PonteiroLivroArquivo, (i+1)*sizeof(Livro), 0);
      fread (&livroB, sizeof(Livro), 1, PonteiroLivroArquivo);
      if (livroA.anoPublicacao > livroB.anoPublicacao) {
        fseek (PonteiroLivroArquivo, (i+1)*sizeof(Livro), 0);
        fwrite (&livroA, sizeof(Livro), 1, PonteiroLivroArquivo);

        fseek (PonteiroLivroArquivo, i*sizeof(Livro), 0);
        fwrite (&livroB, sizeof(Livro), 1, PonteiroLivroArquivo);
      }
      i++;
    }
  }
}

void TodosLivroPorPalavra() {
  FILE * PonteiroLivroArquivo = fopen("biblioteca/livro.dat", "rb+");
  Livro livro;
  char palavra[100];

  OrdernadarLivroPorAnoDePublicacao(PonteiroLivroArquivo);

  do {
    if (PonteiroLivroArquivo != NULL) {
      fflush(stdin);
      printf("Foneça uma palavra para buscar livros pelo titulo: ");
      gets(palavra);

      fseek(PonteiroLivroArquivo, 0, 0);
      fread(&livro, sizeof(Livro), 1, PonteiroLivroArquivo);
      while(!feof(PonteiroLivroArquivo)) {
        if (strstr(palavra, livro.titulo)) {
          printf(CYAN "ID: " NORMAL "%d\n", livro.id);
          printf(CYAN "Titulo: " NORMAL "%s\n", livro.titulo);
          printf(CYAN "Ano de publicação: " NORMAL "%d\n", livro.anoPublicacao);
        }
        
        fread(&livro, sizeof(Livro), 1, PonteiroLivroArquivo);
      }
    } else printf("\nNão foi possivel abrir o arquivo livro."); 
  } while(PonteiroLivroArquivo != NULL);
  fclose(PonteiroLivroArquivo);
}

void TodosOsEmprestimosPorPessoa() {
  FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb");
  Emprestimo emprestimo;
  Pessoa emprestimoPessoa;
  Livro emprestimoLivro;
  int indicePessoa, indiceLivro;
  
  if (PonteiroPessoaArquivo != NULL) {
    fread(&emprestimoPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
    while(!feof(PonteiroPessoaArquivo)) {
      printf(CYAN "\nID: " NORMAL "%d\t", emprestimoPessoa.id);
      printf(CYAN "Nome: " NORMAL "%s\n", emprestimoPessoa.nome);
      printf(CYAN "Telefone: " NORMAL "%s\n", emprestimoPessoa.telefone);
      printf(CYAN "Endereço: " NORMAL "%s\n", emprestimoPessoa.endereco);

      FILE * PonteiroEmprestimoArquivo = fopen("biblioteca/emprestimo.dat", "rb");
      fread(&emprestimo, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
      while(!feof(PonteiroEmprestimoArquivo)) {
        if (emprestimo.idPessoa == emprestimoPessoa.id) {
          FILE * PonteiroLivroArquivo = fopen("biblioteca/livro.dat", "rb+");

          if (PonteiroLivroArquivo != NULL) {
            indiceLivro = BuscaLivroId(PonteiroLivroArquivo, emprestimo.idLivro);

            if (indiceLivro >= 0) {
              fseek(PonteiroLivroArquivo, indiceLivro, 0);
              fread(&emprestimoLivro, sizeof(Livro), 1, PonteiroLivroArquivo);
              fclose(PonteiroLivroArquivo);

              printf(CYAN "\nEmprestimo de ID: " NORMAL "%d\n", emprestimoLivro.id);
              printf(CYAN "Nome: " NORMAL "%s\n", emprestimoLivro.titulo);
              printf(CYAN "Ano de publicação: " NORMAL "%d\n", emprestimoLivro.anoPublicacao);
              printf(CYAN "Data de empretimo: " NORMAL "%d/%d/%d\n", emprestimo.dataEmprestimo.dia, emprestimo.dataEmprestimo.mes, emprestimo.dataEmprestimo.ano);
              printf(CYAN "Data de devolução: " NORMAL "%d/%d/%d\n", emprestimo.dataDevolucao.dia, emprestimo.dataDevolucao.mes, emprestimo.dataDevolucao.ano);
            }
          } else printf("\nNão foi possivel abrir o arquivo emprestimo."); 
        }

        fread(&emprestimo, sizeof(Emprestimo), 1, PonteiroEmprestimoArquivo);
      }

      fread(&emprestimoPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo); 
    }
  }
  fclose(PonteiroPessoaArquivo);
  getch();
}

void exclusaoAutoresMenu () {
  int opcaoSelecionada;
  char opcoesExclusao[10][100] = {
    "Exclusão Lógica",
    "Exclusão Fiísica de um Dado",
    "Exclusão Física dos Excluidos Lógicos"
  };

  do {
    clrscr();
    tituloMenuAutor();
    opcaoSelecionada = menu (opcoesExclusao, 3);
    switch (opcaoSelecionada) {
      case 0:
        ExclusaoLogicaDeAutor();
        break;
      case 1:
        break;
      case 2:
        ExclusaoFisicaTodosDeAutor();
        break;
    }
  } while (opcaoSelecionada != -1);
}

// Buscas 

int BuscaLivroId (FILE *ptr, int Id) {
  Livro Aux;

  fseek(ptr, 0, 0);
  fread(&Aux, sizeof(Livro), 1, ptr);

  while (!feof(ptr) && (Id != Aux.id || Aux.excluido != 0)) 
    fread(&Aux, sizeof(Livro), 1, ptr);

  if (!feof(ptr))
    return ftell(ptr) - sizeof(Livro);
  else  
    return -1;
}

int BuscaAutorId(FILE *ptr, int ID) {
  Autor AuxAutor;

  fseek(ptr, 0, 0);
  fread(&AuxAutor, sizeof(Autor), 1, ptr);

  while (!feof(ptr) && (ID != AuxAutor.id || AuxAutor.excluido != 0))
    fread(&AuxAutor, sizeof(Autor), 1, ptr);
  
  if (!feof(ptr))
    return ftell(ptr) - sizeof(Autor);
  else
    return -1;
}

int BuscaAutorLivro (FILE *ptrAutorLivro, int idLivro, int idAutor) {
  LivroAutor Aux;

  fseek (ptrAutorLivro, 0, 0);
  fread (&Aux, sizeof(LivroAutor), 1, ptrAutorLivro);
  while (!feof(ptrAutorLivro) && (Aux.idAutor != idAutor || Aux.idLivro != idLivro || Aux.excluido != 0))
    fread (&Aux, sizeof(LivroAutor), 1, ptrAutorLivro);
  if (!feof(ptrAutorLivro))
    return ftell(ptrAutorLivro) - sizeof(LivroAutor);
  else 
    return -1;

}
//--------------------------------------------------------------------------------

// Cadastros
void CadastrarAutor (void) {
  FILE *ptr = fopen ("biblioteca/autor.dat", "ab+");;
  Autor AutorAux;

  do {
    fseek(ptr, 0, 2);
    AutorAux.id = ftell(ptr) / sizeof(Autor) + 1;

    printf (RED"\n Dados do novo autor de número " NORMAL "#%d\n", AutorAux.id);
    
    printf ("Nome do Autor: ");
    fflush(stdin);
    gets(AutorAux.nome);

    if (strlen(AutorAux.nome) >= 1) {
      printf ("Nacionalidade: ");
      fflush(stdin);
      gets(AutorAux.nacionalidade);

      AutorAux.excluido = 0;
  
      fwrite (&AutorAux, sizeof(Autor), 1, ptr);
    }
    limparLinhas(5);
  } while (strlen(AutorAux.nome) >= 1);
  fclose (ptr);
} 

void CadastrarLivro (void) {
  FILE *ptr = fopen ("biblioteca/livro.dat", "ab+");
  Livro LivroAux;

  do {
    fseek(ptr, 0, 2);
    LivroAux.id = ftell(ptr) / sizeof(Livro) + 1;

    printf (RED"\nDados do novo livro de número " NORMAL "#%d\n", LivroAux.id);

    printf ("Titulo do Livro: ");
    fflush(stdin);
    gets(LivroAux.titulo);

    if ((strlen(LivroAux.titulo) >= 1)) {
      printf ("Ano de Publicação do Livro: ");
      fflush(stdin);
      scanf ("%d", &LivroAux.anoPublicacao);

      LivroAux.excluido = 0;

      fwrite(&LivroAux, sizeof(Livro), 1, ptr);
    }
    limparLinhas(5);
  } while (strlen(LivroAux.titulo) >= 1);
  fclose(ptr);
}

void CadastraLivroAutor (void) {
  FILE *ptrLivroAutor = fopen ("biblioteca/autorlivro.dat", "ab+");
  FILE *ptrLivro = fopen ("biblioteca/livro.dat", "rb");
  FILE *ptrAutor = fopen ("biblioteca/autor.dat", "rb");
  LivroAutor Aux;
  int idLivro, posLivro, idAutor, posAutor, posLivroAutor;

  do {
    fseek(ptrLivroAutor, 0, 2);

    printf (RED"\nDados do novo relacionamento de livro e autor:\n" NORMAL);

    printf ("ID do Livro: ");
    fflush(stdin);
    scanf ("%d", &idLivro);

    if (idLivro > 0) {
      fseek (ptrLivro, 0, 0);
      posLivro = BuscaLivroId (ptrLivro, idLivro);

      if (posLivro >= 0) {
        fseek(ptrAutor, 0, 0);

        printf ("ID Autor: ");
        scanf("%d", &idAutor);

        posAutor = BuscaAutorId (ptrAutor, idAutor);
        if (posAutor >= 0) {
          posLivroAutor = BuscaAutorLivro(ptrLivroAutor, idLivro, idAutor);
          if (posLivroAutor == -1) {
            Aux.idAutor = idAutor;
            Aux.idLivro = idLivro;
            Aux.excluido = 0;
            fwrite (&Aux, sizeof(LivroAutor), 1, ptrLivroAutor);
          } else (RED "Relacionamento já feito!\n" NORMAL);
        } else (RED "Autor não cadastrado!\n" NORMAL);
      } else (RED "Livro não cadastrado!\n" NORMAL);
    } 
    limparLinhas (5);
    printf ("%d\n", idLivro);
  } while (ptrLivroAutor != NULL && idLivro > 0);
  fclose(ptrLivroAutor);
  fclose(ptrAutor);
  fclose(ptrLivro);
}
//------------------------------------------------------------------
// Exibir Todos

void ExibirTodosAutores(void) {
  FILE *ptr = fopen("biblioteca/autor.dat", "rb");
  Autor AuxAutor;

  if (ptr != NULL) {
    fread(&AuxAutor, sizeof(Autor), 1, ptr);
    printf ("\nDados dos Autores: \n");
    while (!feof(ptr)) {
      if (AuxAutor.excluido != 1) {
        printf ("ID do Autor: %d\n", AuxAutor.id);
        printf ("Nome do Autor: %s\n", AuxAutor.nome);
        printf ("Nacionalidade: %s\n", AuxAutor.nacionalidade);
        printf ("-------------------------------------------\n");
      }
      fread(&AuxAutor, sizeof(Autor), 1, ptr);
    }
    fclose(ptr);
  }
  else  
    printf ("Erro na Abertura do Arquivo!!\n");
} 

//------------------------------------------------------------------

// Altera
void AlterarAutor(void) {
  FILE *ptr = fopen ("biblioteca/autor.dat", "rb+");;
  int pos;
  Autor AuxAutor;

  do {
    if (ptr != NULL) {
      printf(NORMAL "\nForneça o ID do autor para editar ou zero para finalizar: ");
      scanf("%d", &AuxAutor.id);

      pos = BuscaAutorId (ptr, AuxAutor.id);
      if (pos >= 0) {
        fseek(ptr, pos, 0);
        fread (&AuxAutor, sizeof(Autor), 1, ptr);

        printf (CYAN "ID: " NORMAL "%d\n", AuxAutor.id);
        printf (CYAN "Nome: " NORMAL "%s\n", AuxAutor.nome);
        printf (CYAN "Nacionalidade: " NORMAL "%s\n", AuxAutor.nacionalidade);

        if (request("Você quer editar esse Autor?")) {
          printf (RED "\nNovos dados do autor de número " NORMAL "#%d\n", AuxAutor.id);

          printf ("Nome: ");
          fflush(stdin);
          gets(AuxAutor.nome);

          printf ("Nacionalidade: ");
          fflush(stdin);
          gets(AuxAutor.nacionalidade);

          if (request("Você deseja salvar as alterações?")) {
            fseek (ptr, pos, 0);
            fwrite (&AuxAutor, sizeof(Autor), 1, ptr);
            limparLinhas (17);
          }
        } else limparLinhas (9);
      } else printf (YELLOW "[AVISO] O ID: \"%d\" não existe.\n" NORMAL, AuxAutor.id);
    } else printf("\nNão foi possivel abrir o arquivo pessoa.");
  } while (ptr != NULL && AuxAutor.id != 0);
  fclose(ptr);
}

void AlterarLivro (void) {
  FILE *ptr = fopen ("biblioteca/livro.dat", "rb+");
  Livro AuxLivro;
  int pos;

  do {
    if (ptr != NULL) {
      printf(NORMAL "\nForneça o ID do livro para editar ou zero para finalizar: ");
      scanf("%d", &AuxLivro.id);

      pos = BuscaLivroId (ptr, AuxLivro.id);

      if (pos >= 0) {
        fseek (ptr, pos, 0);
        fread (&AuxLivro, sizeof(Livro), 1, ptr);

        printf (CYAN "ID: " NORMAL "%d\n", AuxLivro.id);
        printf (CYAN "Titulo: " NORMAL "%s\n", AuxLivro.titulo);
        printf (CYAN "Ano de Publicação: " NORMAL "%d\n", AuxLivro.anoPublicacao);

        if (request("Você quer editar esse Livro?")) {
          printf (RED "\nNovos dados do livro de número " NORMAL "#%d\n", AuxLivro.id);

          printf ("Título: ");
          fflush (stdin);
          gets (AuxLivro.titulo);

          printf ("Ano de Publicação: ");
          fflush(stdin);
          scanf ("%d", &AuxLivro.anoPublicacao);

          if (request("Você deseja salvar as alterações?")) {
            fseek(ptr, pos, 0);
            fwrite (&AuxLivro, sizeof(Livro), 1, ptr);
            limparLinhas (17);
          }
        } limparLinhas(9);
      } else printf (YELLOW "[AVISO] O ID: \"%d\" não existe.\n" NORMAL, AuxLivro.id);
    } else printf("\nNão foi possivel abrir o arquivo pessoa.");
  } while (ptr != NULL && AuxLivro.id != 0);
  fclose (ptr);
}

//-------------------------------------------------------------------------

// Exclusao Logica
void ExclusaoLogicaDeAutor (void) {
  FILE *ptr = fopen ("biblioteca/autor.dat", "rb+");
  int pos;
  Autor AutorAux;
  char opcao;

  if (ptr != NULL) {
    printf ("ID do Autor: ");
    scanf("%d", &AutorAux.id);
    while (AutorAux.id != 0) {
      pos = BuscaAutorId(ptr, AutorAux.id);
      if (pos >= 0) {
        fseek(ptr, pos, 0);
        fread(&AutorAux, sizeof(Autor), 1, ptr);
        printf ("<<<<< Dados do Autor >>>>\n");
        printf ("ID: %d\n", AutorAux.id);
        printf ("Nome: %s\n", AutorAux.nome);
        printf ("Nacionalidade: %s\n", AutorAux.nacionalidade);
        printf ("--------------------------------------------\n");
        printf ("\nConfirma a Exclusão? (S/N)\n");
        fflush(stdin);
        opcao = toupper(getch());
        if (opcao == 'S') {
          fseek(ptr, pos, 0);
          AutorAux.excluido = 1;
          fwrite(&AutorAux, sizeof(Autor), 1, ptr);
          printf ("Autor Excluído Logicamente\n");
        }
        else
          printf ("Exclusão Cancelada!!\n");
      }   
      else 
        printf ("Autor Desconhecido!!\n");
      printf ("[0] - SAIR\n");
      printf ("ID do Autor: ");
      scanf("%d", &AutorAux.id);
    }
    fclose (ptr);
  }
  else 
    printf ("Erro na abertura do arquivo\n");
}

void ExclusaoLogicaDeLivro (void) {
  FILE *ptr = fopen("biblioteca/livro.dat", "rb+");
  Livro AuxLivro;
  int pos;

  if (ptr != NULL) {  

    printf ("Id do Livro que deseja excluir: ");
    scanf ("%d", &AuxLivro.id);

    while (AuxLivro.id != 0) {
      pos = BuscaLivroId (ptr, AuxLivro.id);
      if (pos >= 0) {

        fseek (ptr, pos, 0);
        fread (&AuxLivro, sizeof(Livro), 1, ptr);

        printf (NORMAL "<<<<<<< Dados do Livro >>>>>>\n");
        printf (CYAN "ID: " NORMAL "%d\n", AuxLivro.id);
        printf (CYAN "Titulo:" NORMAL "%s\n", AuxLivro.titulo);
        printf (CYAN "Ano de Publicação:" NORMAL "%d\n", AuxLivro.anoPublicacao);
        printf ("--------------------------------------------\n");
        printf ("Deseja Realizar a Exclusão? (S/N)");
        if (toupper(getch()) == 'S') {
          AuxLivro.excluido = 1;
          fseek (ptr, pos, 0);
          fwrite (&AuxLivro, sizeof(Livro), 1, ptr);
          printf ("Livro excluído logicamente\n");
        } else printf ("Exclusão Cancelada!!\n");
      } else printf ("Livro não encontrado!!\n");

      printf ("[0] - SAIR\n");
      printf ("Id do Livro que deseja excluir: ");
      scanf ("%d", &AuxLivro.id);
    }
  } else printf ("Erro na Abertura do Arquivo\n");
}

void ExclusaoLogicaLivroAutor (void) {
  FILE * PtrLivroAutor = fopen ("biblioteca/autorlivro.dat", "rb+");
  FILE * PtrAutor = fopen ("biblioteca/autor.dat", "rb");
  FILE * PtrLivro = fopen ("biblioteca/livro.dat", "rb");
  int idAutor, posAutor, idLivro, posLivro, posLivroAutor;
  Autor AutorAux;
  Livro LivroAux;
  LivroAutor LivroAutorAux;

  if (PtrLivroAutor != NULL) {
    do {
      printf ("Id do Autor: ");
      scanf ("%d", &idAutor);

      if (idAutor > 0) {
        fseek (PtrAutor, 0, 0);
        posAutor = BuscaAutorId(PtrAutor, idAutor);

        if (posAutor != -1) {
          printf ("ID do Livro: ");
          scanf ("%d", &idLivro);

          fseek (PtrLivro, 0, 0);
          posLivro = BuscaLivroId (PtrLivro, idLivro);

          if (posLivro != -1) {

            fseek (PtrLivroAutor, 0, 0);
            posLivroAutor = BuscaAutorLivro(PtrLivroAutor, idLivro, idAutor);

            if (posLivroAutor != -1) {

              fseek (PtrAutor, posAutor, 0);
              fread (&AutorAux, sizeof(Autor), 1, PtrAutor);

              printf (CYAN "\nID do Autor: " NORMAL "%d\n", AutorAux.id);
              printf (CYAN "Nome do Autor: " NORMAL "%s\n", AutorAux.nome);

              fseek (PtrLivro, posLivro, 0);
              fread(&LivroAux, sizeof(Livro), 1, PtrLivro);

              printf (CYAN "ID do Livro: " NORMAL "%d\n", LivroAux.id);
              printf (CYAN "Nome do Livro: " NORMAL "%s\n", LivroAux.titulo);

              if (request("Os dados do " CYAN "LIVRO E AUTOR" NORMAL " estão corretos?")) {

                if (request (RED "Deseja excluir?" NORMAL)) {
                  
                  fseek (PtrLivroAutor, posLivroAutor, 0);
                  fread(&LivroAutorAux, sizeof(LivroAutor), 1, PtrLivroAutor);

                  LivroAutorAux.excluido = 1;

                  fseek(PtrLivroAutor, posLivroAutor, 0);
                  fwrite (&LivroAutorAux, sizeof(LivroAutor), 1, PtrLivroAutor);

                  printf (GREEN "\nRelacionameto excluído!!\n" NORMAL);
                } else (RED "\nExclusão cancelada!!\n" NORMAL);
              } 
            } else printf (RED "\nRelacionamento não encontrado!!\n" NORMAL);
          } else printf (RED "\nLivro não cadastrado\n" NORMAL);
        } else printf (RED "\nAutor não encontrado\n" NORMAL);
      }
    } while (idAutor > 0);
  }
}

// ----------------------------------------------------------------

// Exclusao Fisica
void ExclusaoFisicaTodosDeAutor (void) {
  FILE *ptr = fopen ("biblioteca/autor.dat", "rb");
  Autor AuxAutor;
  if (ptr != NULL) {
    fread (&AuxAutor, sizeof(Autor), 1, ptr);
    FILE *ptrTemp = fopen("biblioteca/autorTemp.dat", "wb");
    while (!feof(ptr)) {
      if (!AuxAutor.excluido)
        fwrite(&AuxAutor, sizeof(Autor), 1, ptrTemp);
      fread (&AuxAutor, sizeof(Autor), 1, ptr);
    }
    fclose (ptr);
    fclose(ptrTemp);
    remove("biblioteca/autor.dat");
    rename("biblioteca/autorTemp,dat", "biblioteca/autor.dat");
    printf ("Dados Excluidos Fisicamente\n");
  }  
  else 
    printf ("Erro de abertura!!\n");
}



void ExclusaoFisicaTodosDeLivro (void) {
  FILE *ptr = fopen ("biblioteca/livro.dat", "rb");
  Livro AuxLivro;

  if (ptr != NULL) {
    fread (&AuxLivro, sizeof(Livro), 1, ptr);
    FILE *ptrTemp = fopen ("biblioteca/livroTemp.dat", "wb");
    while (!feof(ptr)) {
      if (!AuxLivro.excluido) 
        fwrite(&AuxLivro, sizeof(Livro), 1, ptrTemp);
      fread (&AuxLivro, sizeof(Livro), 1, ptr);
    }
    fclose(ptr);
    fclose(ptrTemp);
    remove ("biblioteca/livro.dat");
    rename ("biblioteca/livroTemp.dat", "biblioteca/livro.dat");
    printf ("Alunos Excluidos");
  }
}

void ExclusaoFisicaTodosDeLivroAutor (void) {
  FILE * PtrLivroAutor = fopen ("biblioteca/autorlivro.dat", "rb");
  LivroAutor AuxLivroAutor;

  if (PtrLivroAutor != NULL) {
    
    fread (&AuxLivroAutor, sizeof(LivroAutor), 1, PtrLivroAutor);
    FILE * PtrLivroAutorTemp = fopen ("biblioteca/autorlivro-temp.dat", "wb");

    while (!feof(PtrLivroAutor)) {
      if (!AuxLivroAutor.excluido)
        fwrite (&AuxLivroAutor, sizeof(LivroAutor), 1, PtrLivroAutorTemp);
      fread (&AuxLivroAutor, sizeof(LivroAutor), 1, PtrLivroAutor);
    }
    fclose (PtrLivroAutor);
    fclose (PtrLivroAutorTemp);
    remove ("biblioteca/autorlivro.dat");
    rename ("biblioteca/autorlivro-temp.dat", "autorlivro.dat");
    printf (CYAN "\nExcluídos com sucesso!!\n" NORMAL);
  }
}

// -------------------------------------------------------------------------

// Consultar

void ConsultarAutor(void) {
  FILE * ptrAutor = fopen("biblioteca/autor.dat", "rb");
  FILE * ptrLivroAutor = fopen ("biblioteca/autorlivro.dat", "rb");
  FILE * ptrLivro = fopen ("biblioteca/livro.dat", "rb");

  Autor AuxAutor;
  Livro AuxLivro; 
  LivroAutor AuxLivroAutor;
  int pos, idLivro;

  do {
    if (ptrAutor != NULL) {
      printf(NORMAL "\nForneça o ID do autor para consultar ou zero para finalizar: ");
      scanf("%d", &AuxAutor.id);   

      pos = BuscaAutorId (ptrAutor, AuxAutor.id);
      if (pos >= 0) {
        fseek (ptrAutor, pos, 0);
        fread (&AuxAutor, sizeof(Autor), 1, ptrAutor);

        printf (CYAN "ID: " NORMAL "#\"%d\"\n", AuxAutor.id);
        printf (CYAN "Nome: " NORMAL "%s\n", AuxAutor.nome);
        printf (CYAN "Nacionalidade: " NORMAL "%s\n", AuxAutor.nacionalidade);
        printf (CYAN "\n----------------------------------------------\n" NORMAL);
        
        
        if (ptrLivroAutor != NULL) {

          fseek (ptrLivroAutor, 0, 0);
          fread (&AuxLivroAutor, sizeof(LivroAutor), 1, ptrLivroAutor);
          while (!feof(ptrLivroAutor)) {
            if (AuxAutor.id == AuxLivroAutor.idAutor) {
              fseek(ptrLivro, 0, 0);
              fread (&AuxLivro, sizeof(Livro), 1, ptrLivro);
              while (!feof(ptrLivro)) {
                if (AuxLivro.id == AuxLivroAutor.idLivro) {
                  printf (CYAN "ID: " NORMAL "#\"%d\"\n", AuxLivro.id);
                  printf (CYAN "Titulo: " NORMAL "%s\n", AuxLivro.titulo);
                  printf (CYAN "Ano de Publicação: " NORMAL "%d\n", AuxLivro.anoPublicacao);
                }
                fread (&AuxLivro, sizeof(Livro), 1, ptrLivro);
              }
            }
            fread (&AuxLivroAutor, sizeof(LivroAutor), 1, ptrLivroAutor);
          }
        } else printf (RED "Nenhum livro relacionado ao autor!\n" NORMAL);
      } else printf (YELLOW "[AVISO] O ID: \"%d\" não existe.\n" NORMAL, AuxAutor.id);
    } else printf("\nNão foi possivel abrir o arquivo pessoa.");
  } while (ptrAutor != NULL && AuxAutor.id != 0);
  fclose (ptrLivroAutor);
  fclose (ptrLivro);
  fclose(ptrAutor);
}

void ConsultarLivroAutor (void) {
  FILE * ptrAutor = fopen("biblioteca/autor.dat", "rb");
  FILE * ptrLivroAutor = fopen ("biblioteca/autorlivro.dat", "rb");
  FILE * ptrLivro = fopen ("biblioteca/livro.dat", "rb");

  int idAutor, posAutor, idLivro, posLivro, posLivroAutor;
  Autor AutorAux;
  Livro LivroAux;
  LivroAutor LivroAutorAux;

  if (ptrLivroAutor != NULL) {
    do {
      printf (CYAN "\nID do Autor: " NORMAL);
      scanf ("%d", &idAutor);
      if (idAutor > 0) {
      
        fseek (ptrAutor, 0, 0);
        posAutor = BuscaAutorId (ptrAutor, idAutor);
        if (posAutor >= 0) {
          fseek(ptrAutor, posAutor, 0);
          fread(&AutorAux, sizeof(Autor), 1, ptrAutor);
          
          printf (CYAN "\nID do Autor: " NORMAL "%d\n", AutorAux.id);
          printf (CYAN "Nome do Autor: " NORMAL "%s\n", AutorAux.nome);
          printf (CYAN "Nacionalidade: " NORMAL "%s\n", AutorAux.nacionalidade);
          printf (NORMAL "\n---------------------------------------\n");

          fseek (ptrLivroAutor, 0, 0);
          fread (&LivroAutorAux, sizeof(LivroAutor), 1, ptrLivroAutor);
          while (!feof(ptrLivroAutor)) {
            if (LivroAutorAux.idAutor == idAutor) {
              fseek (ptrLivro, 0, 0);
              posLivro = BuscaLivroId(ptrLivro, LivroAutorAux.idLivro);
              fseek (ptrLivro, posLivro, 0);
              fread(&LivroAux, sizeof(Livro), 1, ptrLivro);

              printf (CYAN "\nID do Livro: " NORMAL "%d\n", LivroAux.id);
              printf (CYAN "Titulo: " NORMAL "%s\n", LivroAux.titulo);
              printf (CYAN "Ano de Publicação: " NORMAL "%d\n", LivroAux.anoPublicacao);             
            }
            fread (&LivroAutorAux, sizeof(LivroAutor), 1, ptrLivroAutor);
          }
        } else (RED "\nAutor não cadastrado\n" NORMAL);
      }
    } while (idAutor > 0);
  }
}
//---------------------------------------------------------------------------------------
// Ordenar

//Ordenação por bolha
void OrdenaAutorNacionalidade (FILE * PtrAutor) {
  int Qtd, i;
  Autor Reg1, Reg2;

  fseek(PtrAutor, 0, 2);
  Qtd = ftell(PtrAutor) / sizeof (Autor);
  for ( ; Qtd > 1; Qtd--) {
    i=0; 
    while (i < Qtd-1) {
      fseek (PtrAutor, i*sizeof(Autor), 0);
      fread (&Reg1, sizeof(Autor), 1, PtrAutor);

      fseek (PtrAutor, (i+1)*sizeof(Autor), 0);
      fread (&Reg2, sizeof(Autor), 1, PtrAutor);
      if (strcasecmp(Reg1.nacionalidade, Reg2.nacionalidade) > 0) {
        fseek (PtrAutor, (i+1)*sizeof(Autor), 0);
        fwrite (&Reg1, sizeof(Autor), 1, PtrAutor);

        fseek (PtrAutor, i*sizeof(Autor), 0);
        fwrite (&Reg2, sizeof(Autor), 1, PtrAutor);
      }
      i++;
    }
  }
}

// Relatórios

void BuscaAutorPelaLetra (void) {
  FILE * PtrAutor = fopen("biblioteca/autor.dat", "rb+");
  char letra;
  Autor AutorAux;
  int cont;

  do {
    if (PtrAutor != NULL) {
      cont = 0;
      OrdenaAutorNacionalidade(PtrAutor);
      printf ("\nInical do Autor: ");
      fflush(stdin);
      letra =  toupper(getche());

      fseek (PtrAutor, 0, 0);
      fread (&AutorAux, sizeof(Autor), 1, PtrAutor);

      while (!feof(PtrAutor)) {
        if (toupper(AutorAux.nome[0]) == letra && AutorAux.excluido == 0) {

          printf(CYAN "\nID: " NORMAL "%d\n", AutorAux.id);
          printf(CYAN "Nome: " NORMAL "%s\n", AutorAux.nome);
          printf(CYAN "Nacionalidade: " NORMAL "%s\n", AutorAux.nacionalidade);
          cont++;
        }
        fread (&AutorAux, sizeof(Autor), 1, PtrAutor);
      }
      if (!cont) 
        printf (RED "\nUsuário com inicial " NORMAL "[%c]" RED " não encontrado\n" NORMAL, letra); 
    } else printf("\nNão foi possivel abrir o arquivo pessoa."); 
  } while (PtrAutor != NULL && letra != 27);
  fclose (PtrAutor);
}

 
int menu(char opcoes[][100], int quantidadeDeOpcoes) {
  int opcaoSelecionada = 0;
  int acao;

  do {
    printf("\e[?25l"); // hide cursor
    limparLinhas(quantidadeDeOpcoes);

    for(int index = 0; index < quantidadeDeOpcoes; index++) {
      if (index == opcaoSelecionada) {
        textcolor(15);
        printf("%c %s\n", PONTEIRO, opcoes[opcaoSelecionada]);
        textcolor(8);
      } else {
        textcolor(8);
        printf("  %s\n", opcoes[index]);
        textcolor(15);
      }
    }

    acao = getch();
    
    switch(acao) {
      case SETA_CIMA_NUMERO:
        if (opcaoSelecionada + 1 < quantidadeDeOpcoes)
          opcaoSelecionada++;
        break;
      case SETA_BAIXO_NUMERO:
        if (opcaoSelecionada > 0)
          opcaoSelecionada--;
      break;
    }
  } while(acao != ESC_NUMERO && acao != ENTER_NUMERO);

  printf("\e[?25h");
  textcolor(15);

  if (acao != ESC_NUMERO) {
    return opcaoSelecionada;
  }

  return -1;
}

void limparLinhas(int quantidadeDeOpcoes) {
  for(int index = 0; index < quantidadeDeOpcoes; index++) {
    printf("\x1b[1F");
    printf("\33[2K\r");
  }
}

void tituloMenuPrincipal() {
  clrscr();
  textcolor(2);
  printf("                                                            $$\\                                              $$\\               \n");
  printf("                                                            \\__|                                             $$ |              \n");
  printf(" $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\  $$$$$$$\\   $$$$$$$\\ $$\\  $$$$$$\\  $$$$$$\\$$$$\\   $$$$$$\\  $$$$$$$\\ $$$$$$\\    $$$$$$\\  \n");
  printf("$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|$$ | \\____$$\\ $$  _$$  _$$\\ $$  __$$\\ $$  __$$\\\\_$$  _|  $$  __$$\\ \n");
  printf("$$ /  $$ |$$$$$$$$ |$$ |  \\__|$$$$$$$$ |$$ |  $$ |$$ /      $$ | $$$$$$$ |$$ / $$ / $$ |$$$$$$$$ |$$ |  $$ | $$ |    $$ /  $$ |\n");
  printf("$$ |  $$ |$$   ____|$$ |      $$   ____|$$ |  $$ |$$ |      $$ |$$  __$$ |$$ | $$ | $$ |$$   ____|$$ |  $$ | $$ |$$\\ $$ |  $$ |\n");
  printf("\\$$$$$$$ |\\$$$$$$$\\ $$ |      \\$$$$$$$\\ $$ |  $$ |\\$$$$$$$\\ $$ |\\$$$$$$$ |$$ | $$ | $$ |\\$$$$$$$\\ $$ |  $$ | \\$$$$  |\\$$$$$$  |\n");
  printf(" \\____$$ | \\_______|\\__|       \\_______|\\__|  \\__| \\_______|\\__| \\_______|\\__| \\__| \\__| \\_______|\\__|  \\__|  \\____/  \\______/ \n");
  printf("$$\\   $$ |                                                                                                                     \n");
  printf("\\$$$$$$  |                                                                                                                     \n");
  printf(" \\______|                                                                                                                     \n\n\n\n\n\n\n\n");
  textcolor(15);
}

void tituloMenuAutor() {
  clrscr();
  textcolor(2);
  printf(" $$$$$$\\              $$\\                         \n");
  printf("$$  __$$\\             $$ |                        \n");
  printf("$$ /  $$ |$$\\   $$\\ $$$$$$\\    $$$$$$\\   $$$$$$\\  \n");
  printf("$$$$$$$$ |$$ |  $$ |\\_$$  _|  $$  __$$\\ $$  __$$\\ \n");
  printf("$$  __$$ |$$ |  $$ |  $$ |    $$ /  $$ |$$ |  \\__|\n");
  printf("$$ |  $$ |$$ |  $$ |  $$ |$$\\ $$ |  $$ |$$ |      \n");
  printf("$$ |  $$ |\\$$$$$$  |  \\$$$$  |\\$$$$$$  |$$ |      \n");
  printf("\\__|  \\__| \\______/    \\____/  \\______/ \\__|      \n\n\n\n\n\n\n\n\n");
  textcolor(15);
}

void tituloMenuLivro() {
    clrscr();     
    textcolor(2);     

    printf("$$\\       $$\\                                \n");
    printf("$$ |      \\__|                               \n");
    printf("$$ |      $$\\ $$\\    $$\\  $$$$$$\\   $$$$$$\\  \n");
    printf("$$ |      $$ |\\$$\\  $$  |$$  __$$\\ $$  __$$\\ \n");
    printf("$$ |      $$ | \\$$\\$$  / $$ |  \\__|$$ /  $$ |\n");
    printf("$$ |      $$ |  \\$$$  /  $$ |      $$ |  $$ |\n");
    printf("$$$$$$$$\\ $$ |   \\$  /   $$ |      \\$$$$$$  |\n");
    printf("\\________|\\__|    \\_/    \\__|       \\______/\n\n\n\n\n\n\n\n\n");

    textcolor(15); 
}

void tituloMenuEmprestimo() {
  clrscr();        
  textcolor(2);    

  printf("$$$$$$$$\\                                                         $$\\     $$\\                         \n");
  printf("$$  _____|                                                        $$ |    \\__|                        \n");
  printf("$$ |      $$$$$$\\$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$$\\ $$$$$$\\   $$\\ $$$$$$\\$$$$\\   $$$$$$\\  \n");
  printf("$$$$$\\    $$  _$$  _$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  _____|\\_$$  _|  $$ |$$  _$$  _$$\\ $$  __$$\\ \n");
  printf("$$  __|   $$ / $$ / $$ |$$ /  $$ |$$ |  \\__|$$$$$$$$ |\\$$$$$$\\    $$ |    $$ |$$ / $$ / $$ |$$ /  $$ |\n");
  printf("$$ |      $$ | $$ | $$ |$$ |  $$ |$$ |      $$   ____| \\____$$\\   $$ |$$\\ $$ |$$ | $$ | $$ |$$ |  $$ |\n");
  printf("$$$$$$$$\\ $$ | $$ | $$ |$$$$$$$  |$$ |      \\$$$$$$$\\ $$$$$$$  |  \\$$$$  |$$ |$$ | $$ | $$ |\\$$$$$$  |\n");
  printf("\\________|\\__| \\__| \\__|$$  ____/ \\__|       \\_______|\\_______/    \\____/ \\__|\\__| \\__| \\__| \\______/ \n");
  printf("                        $$ |                                                                          \n");
  printf("                        $$ |                                                                          \n");
  printf("                        \\__|                                                                          \n\n\n\n\n");

  textcolor(15);  
}

void tituloMenuPessoas() {
    clrscr();         
    textcolor(2);     

    printf("$$$$$$$\\                                                              \n");
    printf("$$  __$$\\                                                             \n");
    printf("$$ |  $$ | $$$$$$\\   $$$$$$$\\  $$$$$$$\\  $$$$$$\\   $$$$$$\\   $$$$$$$\\ \n");
    printf("$$$$$$$  |$$  __$$\\ $$  _____|$$  _____|$$  __$$\\  \\____$$\\ $$  _____|\n");
    printf("$$  ____/ $$$$$$$$ |\\$$$$$$\\  \\$$$$$$\\  $$ /  $$ | $$$$$$$ |\\$$$$$$\\  \n");
    printf("$$ |      $$   ____| \\____$$\\  \\____$$\\ $$ |  $$ |$$  __$$ | \\____$$\\ \n");
    printf("$$ |      \\$$$$$$$\\ $$$$$$$  |$$$$$$$  |\\$$$$$$  |\\$$$$$$$ |$$$$$$$  |\n");
    printf("\\__|       \\_______|\\_______/ \\_______/  \\______/  \\_______|\\_______/ \n\n\n\n\n\n\n");

    textcolor(15);    
}


void tituloMenuLivroAutor() {
    clrscr();         
    textcolor(2);    

    printf("$$\\       $$\\                                                       $$$$$$\\              $$\\                         \n");
    printf("$$ |      \\__|                                                     $$  __$$\\             $$ |                        \n");
    printf("$$ |      $$\\ $$\\    $$\\  $$$$$$\\   $$$$$$\\         $$$$$$\\        $$ /  $$ |$$\\   $$\\ $$$$$$\\    $$$$$$\\   $$$$$$\\  \n");
    printf("$$ |      $$ |\\$$\\  $$  |$$  __$$\\ $$  __$$\\       $$  __$$\\       $$$$$$$$ |$$ |  $$ |\\_$$  _|  $$  __$$\\ $$  __$$\\ \n");
    printf("$$ |      $$ | \\$$\\$$  / $$ |  \\__|$$ /  $$ |      $$$$$$$$ |      $$  __$$ |$$ |  $$ |  $$ |    $$ /  $$ |$$ |  \\__|\n");
    printf("$$ |      $$ |  \\$$$  /  $$ |      $$ |  $$ |      $$   ____|      $$ |  $$ |$$ |  $$ |  $$ |$$\\ $$ |  $$ |$$ |      \n");
    printf("$$$$$$$$\\ $$ |   \\$  /   $$ |      \\$$$$$$  |      \\$$$$$$$\\       $$ |  $$ |\\$$$$$$  |  \\$$$$  |\\$$$$$$  |$$ |      \n");
    printf("\\________|\\__|    \\_/    \\__|       \\______/        \\_______|      \\__|  \\__| \\______/    \\____/  \\______/ \\__|      \n\n\n\n\n\n\n\n\n");

    textcolor(15);    
}

void tituloMenuRelatorio(void) {
    clrscr();         
    textcolor(2); 

    printf("$$$$$$$\\            $$\\            $$\\                         $$\\           \n");
    printf("$$  __$$\\           $$ |           $$ |                        \\__|          \n");
    printf("$$ |  $$ | $$$$$$\\  $$ | $$$$$$\\ $$$$$$\\    $$$$$$\\   $$$$$$\\  $$\\  $$$$$$\\  \n");
    printf("$$$$$$$  |$$  __$$\\ $$ | \\____$$\\\\_$$  _|  $$  __$$\\ $$  __$$\\ $$ |$$  __$$\\ \n");
    printf("$$  __$$< $$$$$$$$ |$$ | $$$$$$$ | $$ |    $$ /  $$ |$$ |  \\__|$$ |$$ /  $$ |\n");
    printf("$$ |  $$ |$$   ____|$$ |$$  __$$ | $$ |$$\\ $$ |  $$ |$$ |      $$ |$$ |  $$ |\n");
    printf("$$ |  $$ |\\$$$$$$$\\ $$ |\\$$$$$$$ | \\$$$$  |\\$$$$$$  |$$ |      $$ |\\$$$$$$  |\n");
    printf("\\__|  \\__| \\_______|\\__| \\_______|  \\____/  \\______/ \\__|      \\__| \\______/ \n\n\n\n\n\n\n");

    textcolor(15);
}

int request(const char message[]) {
  printf("\n%s" GREEN "\n[S] Sim" RED " [N] Não\n" NORMAL, message);

  int answer;

  do {
    answer = toupper(getch());
  } while(answer != 'S' && answer != 'N');

  if (answer == 'S') {
    return 1;
  }

   return 0;
}