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
#elif defined(_WIN32) || defined(WIN32)
// Conio Dos
#include "./lib/conio-dos.h"
#include "./lib/meuconio.h"
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
void autorMenu();
void tituloMenuAutor();
void ExibirTodosAutores(void);
void exclusaoAutoresMenu ();

// Pessoa
void CadastrarPessoa();
void EditarPessoa(); 
int BuscarPessoaPeloID(FILE * PonteiroPessoaArquivo, int id);

//Livro Funções 
void CadastrarLivro (void);
void AlterarLivro (void);
int BuscaLivroId (FILE *ptr, int Id);
void ExclusaoFisicaTodosDeLivro (void);
void ExclusaoLogicaDeLivro (void);
void livroMenu();
void tituloMenuLivro();

//Livro e Autor Funçoes
int BuscaAutorLivro (FILE *ptrAutorLivro, int idLivro, int idAutor);
void CadastraLivroAutor (void);
void tituloMenuLivroAutor();
void livroAutorMenu();

// Emprestimo Funcoes
void emprestimoMenu();
void tituloMenuEmprestimo();

//Pessoas Funcoes
void pessoasMenu();
void tituloMenuPessoas();


// Outras
int menu(char options[][100], int studentsLogicSize);
void tituloMenuPrincipal();
void limparLinhas(int quantidadeDeOpcoes);
void Executar (int pos);

int main() {
  int opcaoSelecionada;
  char opcoesPrincipais[10][100] = {
    "Autor",
    "Livro",
    "Empréstimos",
    "Pessoas",
    "Livro e Autor"
  };
  
  do {
    clrscr();
    tituloMenuPrincipal();
    fflush(stdin);
    opcaoSelecionada = menu(opcoesPrincipais, 5);

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
    "Exibir Emprestimos",
    "Excluir Emprestimo",
    "Ordenar Emprestimos",
  };

  do {
    clrscr();
    tituloMenuEmprestimo();
    opcaoSelecionada = menu(opcoesEmprestimo, 6);

    switch (opcaoSelecionada) {
      case 0:
        break;
      case 1:
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

void pessoasMenu() {
  int opcaoSelecionada;
  char opcoesPessoas[10][100] = {
    "Cadastrar Pessoa",
    "Alterar Pessoa",
    "Consultar Pessoa",
    "Exibir Pessoas",
    "Excluir Pessoa",
    "Ordenar Pessoa"
  };

  do {
    clrscr();
    tituloMenuPessoas();
    opcaoSelecionada = menu(opcoesPessoas, 6);

    switch (opcaoSelecionada){
      case 0:
        CadastrarPessoa();
        break;
      case 1:
        EditarPessoa();
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

void CadastrarPessoa() {
  FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "ab+");
  Pessoa novaPessoa;
  int ultimoId;

  do {
    if (PonteiroPessoaArquivo != NULL) {
      printf("Nome: ");
      fflush(stdin);
      gets(novaPessoa.nome);

      if (strlen(novaPessoa.nome) > 1) {
        ultimoId = ftell(PonteiroPessoaArquivo) / sizeof(Autor);
        novaPessoa.id = ultimoId + 1;

        printf("Telefone | EX: (18) 99678-5231: ");
        fflush(stdin);
        gets(novaPessoa.telefone);

        printf("Endereço: ");
        fflush(stdin);
        gets(novaPessoa.endereco);

        novaPessoa.excluido = 0;

        fwrite(&novaPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
      }
    } else printf("\n Não foi possivel abrir o arquivo pessoa.");
  } while(PonteiroPessoaArquivo != NULL && strlen(novaPessoa.nome) > 1);
}

void EditarPessoa() {
  FILE * PonteiroPessoaArquivo = fopen("biblioteca/pessoa.dat", "rb+");
  int indice;
  Pessoa PessoaParaEditar;
  do {
    if (PonteiroPessoaArquivo != NULL) {
      printf("Foneça o ID da pessoa para editar ou zero para finalizar: ");
      scanf("%d", &PessoaParaEditar.id);

      indice = BuscarPessoaPeloID(PonteiroPessoaArquivo, PessoaParaEditar.id);

      if (indice >= 0) {
        fseek(PonteiroPessoaArquivo, indice, 0);
        fread(&PessoaParaEditar, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
        printf("Novo Nome (Nome Atual: %s)", PessoaParaEditar.nome);
      } else printf("\n Essa pessoa não existe.");
    } else printf("\n Não foi possivel abrir o arquivo pessoa.");
  } while(PonteiroPessoaArquivo != NULL && PessoaParaEditar.id != 0);
}

int BuscarPessoaPeloID(FILE * PonteiroPessoaArquivo, int id) {
  Pessoa tmpPessoa; 

  fseek(PonteiroPessoaArquivo, 0, 0);
  fread(&tmpPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);
  while(!feof(PonteiroPessoaArquivo) && (tmpPessoa.id != id || !tmpPessoa.excluido))
    fread(&tmpPessoa, sizeof(Pessoa), 1, PonteiroPessoaArquivo);

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
    "Excluir",
    "Ordenar"
  }; 

  do {
    clrscr();
    tituloMenuLivroAutor();
    opcaoSelecionada = menu (opcoesLivroAutor, 6);

    switch (opcaoSelecionada){
      case 0:
        break;
      case 1:
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
  FILE *ptr;
  Autor AutorAux;

  ptr = fopen ("biblioteca/autor.dat", "ab+");
  printf ("Nome do Autor: ");
  fflush(stdin);
  gets(AutorAux.nome);
  while (strlen(AutorAux.nome) > 1) {
    AutorAux.id = ftell(ptr) / sizeof(Autor) + 1;
    printf ("Nacionalidade: ");
    fflush(stdin);
    gets(AutorAux.nacionalidade);
    AutorAux.excluido = 0;

    fwrite (&AutorAux, sizeof(Autor), 1, ptr);

    printf ("Nome do Autor: ");
    fflush(stdin);
    gets(AutorAux.nome);
  }
  fclose (ptr);
} 

void CadastrarLivro (void) {
  FILE *ptr;
  Livro LivroAux;

  ptr = fopen ("biblioteca/livro.dat", "ab+");
  printf ("Titulo do Livro: ");
  fflush(stdin);
  gets(LivroAux.titulo);
  while (strlen(LivroAux.titulo) > 1) {
    LivroAux.id = ftell(ptr) / sizeof(Livro) + 1;
    printf ("Ano de Publicação do Livro: ");
    fflush(stdin);
    scanf ("%d", &LivroAux.anoPublicacao);
    LivroAux.excluido = 0;

    fwrite(&LivroAux, sizeof(Livro), 1, ptr);

    printf ("Titulo do Livro: ");
    fflush(stdin);
    gets(LivroAux.titulo);
  }
  fclose(ptr);
}

void CadastraLivroAutor (void) {
  FILE *ptr = fopen ("biblioteca/autorlivro.dat", "ab+");
  FILE *ptrLivro = fopen ("biblioteca/livro.dat", "rb");
  FILE *ptrAutor = fopen ("biblioteca/autor.dat", "rb");
  LivroAutor Aux;
  int idLivro, posLivro, idAutor, posAutor, posLivroAutor;

  printf ("ID do Livro: ");
  scanf ("%d", &idLivro);
  while (idLivro != 0) {
    fseek(ptrLivro, 0, 0);
    posLivro = BuscaLivroId (ptrLivro, idLivro);
    if (posLivro >= 0) {
      fseek(ptrAutor, 0, 0);
      printf ("ID do Autor: ");
      scanf ("%d", &idAutor);
      posAutor = BuscaAutorId(ptrAutor, idAutor);
      if (posAutor >= 0) {
        posLivroAutor = BuscaAutorLivro (ptr, idLivro, idAutor);
        if (posLivroAutor == -1) {
          Aux.idAutor = idAutor;
          Aux.idLivro = idLivro;
          Aux.excluido = 0;
          fwrite(&Aux, sizeof(LivroAutor), 1, ptr);
        } 
        else 
          printf ("Relacionamento de Autor e Livro já cadastrado!!\n");
      }
      else 
        printf ("Autor não cadastrado!!\n");
    }
    else
      printf ("Livro não cadastrado!!\n");
    printf ("[0] - Sair\n");
    printf ("ID do Livro: ");
    scanf ("%d", &idLivro);
  }
  fclose(ptr);
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
  FILE *ptr;
  int id, pos;
  Autor AuxAutor;

  ptr = fopen ("biblioteca/autor.dat", "rb+");
  if (ptr != NULL) {
    printf ("ID do Autor: ");
    scanf ("%d", &id);
    while (id != 0) {
      pos = BuscaAutorId(ptr, id);
      if (pos >= 0) {
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
      else 
        printf ("Autor desconhecido!!\n");

      printf ("[0] - SAIR\n");
      printf ("ID do Autor: ");
      scanf ("%d", &id);
    }
    fclose(ptr);
  }   
  else 
    printf ("Erro na abertura do Arquivo\n");
}

void AlterarLivro (void) {
  FILE *ptr = fopen ("biblioteca/livro.dat", "rb+");
  Livro AuxLivro;
  int pos;

  if (ptr != NULL) {
    printf ("ID do Livro: ");
    scanf ("%d", AuxLivro.id);
    while (AuxLivro.id != 0) {
      pos = BuscaLivroId (ptr, AuxLivro.id);
      if (pos >= 0) {
        fseek(ptr, pos, 0);
        fread(&AuxLivro, sizeof(Livro), 1, ptr);
        printf ("Dados Encontrados:");
        printf ("ID: %d\n", AuxLivro.id);
        printf ("Titulo do Livro: %s\n", AuxLivro.titulo);
        printf ("Ano de Publicação: %d", AuxLivro.anoPublicacao);
        printf ("---------------------------------------------------\n");
        printf ("Digite o Novo Titulo: ");
        fflush(stdin);
        gets(AuxLivro.titulo);
        printf ("Ano de Publicação: ");
        scanf ("%d", &AuxLivro.anoPublicacao);
        printf ("Deseja fazer a Alteração? (S/N)\n");
        if (toupper(getch()) == 'S') {
          fseek(ptr, pos, 0);
          fwrite(&AuxLivro, sizeof(Livro), 1, ptr);
          printf ("Dados Alterados!!\n");
        } 
        else 
          printf ("Alteraçao cancelada!!\n");
      }     
      else 
        printf ("Livro não cadastrado!!\n");

      printf ("ID do Livro: ");
      scanf ("%d", AuxLivro.id);
    }
    fclose(ptr);
  }   
  else 
    printf ("Erro na Abertura do Arquivo!!\n");
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
    scanf ("%d", AuxLivro.id);
    while (AuxLivro.id != 0) {
      pos = BuscaLivroId (ptr, AuxLivro.id);
      if (pos >= 0) {
        fseek (ptr, pos, 0);
        fread (&AuxLivro, sizeof(Livro), 1, ptr);
        printf ("<<<<<<< Dados do Livro >>>>>>\n");
        printf ("ID: %d\n", AuxLivro.id);
        printf ("Titulo: %s\n", AuxLivro.titulo);
        printf ("Ano de Publicação: %d\n", AuxLivro.anoPublicacao);
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
      scanf ("%d", AuxLivro.id);
    }
  } else printf ("Erro na Abertura do Arquivo\n");
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

// -------------------------------------------------------------------------

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
  printf(" \\______|                                                                                                                     \n\n\n\n\n\n\n");
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
  printf("                        \\__|                                                                          \n\n\n\n\n\n\n\n\n");

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
    printf("\\__|       \\_______|\\_______/ \\_______/  \\______/  \\_______|\\_______/ \n\n\n\n\n\n\n\n\n\n");

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