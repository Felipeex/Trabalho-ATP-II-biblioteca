# Requisitos Funcionais

### Livro - @Lucas

- [x] Deve ser possivel cadastrar um livro
- [x] Deve ser possivel editar um livro
- [x] Deve ser possivel excluir um livro logicamente
- [x] Deve ser possivel excluir um livro fisicamente
- [ ] Deve ser possivel consultar todos os dados dos livros

### Autor - @Lucas

- [x] Deve ser possivel cadastrar um autor
- [x] Deve ser possivel editar um autor
- [x] Deve ser possivel excluir um autor logicamente
- [x] Deve ser possivel excluir um autor fisicamente
- [x] Deve ser possivel consultar todos os dados dos autores

### Emprestimo @Felipe

- [x] Deve ser possivel cadastrar um emprestimo
- [x] Deve ser possivel editar um emprestimo
- [x] Deve ser possivel consultar um emprestimo
- [x] Deve ser possivel excluir um emprestimo logicamente
- [x] Deve ser possivel excluir um emprestimo fisicamente
- [x] Deve ser possivel associar um livro a uma pessoa por emprestimo
- [x] Deve ser possivel uma pessoa emprestar varios livros
- [x] Deve ser possivel consultar todos os dados dos emprestimos

### Pessoa - @Felipe

- [x] Deve ser possivel cadastrar uma pessoa
- [x] Deve ser possivel editar uma pessoa
- [x] Deve ser possivel consultar uma pessoa
- [x] Deve ser possivel excluir uma pessoa logicamente
- [x] Deve ser possivel excluir uma pessoa fisicamente
- [x] Deve ser possivel consultar todos os dados das pessoas

### Relacionamento Livro Autor @Lucas

- [x] Deve ser possivel cadastrar um livro a um autor
- [x] Deve ser possivel excluir um livro a um autor logicamente
- [x] Deve ser possivel excluir um livro a um autor fisicamente
- [x] Deve ser possivel consultar todos os livros escritos pelos autores
- [ ] Deve ser possivel associar vários autores a um livro
- [ ] Deve ser possivel associar vários livros a um autor

### Relatório

- [x] Deve ser possivel exibir os dados de cada Tabela, mostrando os dados completos - @Felipe
- [x] Deve ser possivel buscar os autores que começam com uma determinada letra ordenado pela nacionalidade - @Lucas
- [x] Deve ser possivel buscar os livros com titulo que contenham uma determinada palavra ordenados pelo ano de publicação @Felipe
- [x] Deve ser possivel buscar todos os empréstimos de uma pessoa específica - @Felipe
- [x] Deve ser possivel buscar todos os dados de livros de um autor específico - @Lucas
- [x] Deve ser possivel buscar todos os empréstimos com os dados detalhados separados por pessoa - @Felipe

# Requisitos Não Funcionais

- [x] Todos os “id” são valores inteiros.
- [x] A data é definida por uma struct, onde dia, mês e ano são inteiros.
- [x] Cada tabela deve ter uma chave primária e relacionamentos entre elas
- [x] As datas deveram ser validadas.
- [x] Gerar dados para os arquivos
- [x] Livro Autor: Os dois campos juntos (ID Autor, ID Livro), formam a chave primária desta tabela.

# Regras de Negócio

- [x] As datas deveram ser validas.
- [x] Emprestimo: A data de emprestimo tem que ser depois da data de devolução
