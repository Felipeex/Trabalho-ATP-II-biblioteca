# Requisitos Funcionais

### Livro - @Felipe

- [ ] Deve ser possivel cadastrar um livro
- [ ] Deve ser possivel editar um livro
- [ ] Deve ser possivel excluir um livro logicamente
- [ ] Deve ser possivel excluir um livro fisicamente
- [ ] Deve ser possivel consultar todos os dados dos livros

### Autor - @Lucas

- [x] Deve ser possivel cadastrar um autor
- [x] Deve ser possivel editar um autor
- [x] Deve ser possivel excluir um autor logicamente
- [ ] Deve ser possivel excluir um autor fisicamente
- [ ] Deve ser possivel consultar todos os dados dos autores

### Emprestimo @Felipe

- [ ] Deve ser possivel cadastrar um emprestimo
- [ ] Deve ser possivel editar um emprestimo
- [ ] Deve ser possivel excluir um emprestimo logicamente
- [ ] Deve ser possivel excluir um emprestimo fisicamente
- [ ] Deve ser possivel consultar todos os dados dos emprestimos
- [ ] Deve ser possivel associar um livro a uma pessoa por emprestimo
- [ ] Deve ser possivel uma pessoa emprestar varios livros

### Pessoa - @Felipe

- [ ] Deve ser possivel cadastrar uma pessoa
- [ ] Deve ser possivel editar uma pessoa
- [ ] Deve ser possivel excluir uma pessoa logicamente
- [ ] Deve ser possivel excluir uma pessoa fisicamente
- [ ] Deve ser possivel consultar todos os dados das pessoas

### Relacionamento Livro Autor @Lucas

- [ ] Deve ser possivel cadastrar um livro a um autor
- [ ] Deve ser possivel excluir um livro a um autor logicamente
- [ ] Deve ser possivel excluir um livro a um autor fisicamente
- [ ] Deve ser possivel consultar todos os livros escrevidos pelos autores
- [ ] Deve ser possivel associar vários autores a um livro
- [ ] Deve ser possivel associar vários livros a um autor

### Relatório

- [ ] Deve ser possivel exibir os dados de cada Tabela, mostrando os dados completos - @Lucas e Felipe
- [ ] Deve ser possivel buscar os autores que começam com uma determinada letra ordenado pela nacionalidade - @Lucas
- [ ] Deve ser possivel buscar os livros com titulo que contenham uma determinada palavra ordenados pelo ano de publicação @Felipe
- [ ] Deve ser possivel buscar todos os empréstimos de uma pessoa específica - @Lucas
- [ ] Deve ser possivel buscar todos os dados de livros de um autor específico - @Lucas
- [ ] Deve ser possivel buscar todos os empréstimos com os dados detalhados separados por pessoa - @Lucas

# Requisitos Não Funcionais

- [x] Todos os “id” são valores inteiros.
- [x] A data é definida por uma struct, onde dia, mês e ano são inteiros.
- [x] Cada tabela deve ter uma chave primária e relacionamentos entre elas
- [ ] As datas deveram ser validadas.
- [ ] Gerar dados para os arquivos
- [ ] Livro Autor: Os dois campos juntos (ID Autor, ID Livro), formam a chave primária desta tabela.

# Regras de Negócio

- [ ] As datas deveram ser validas.
- [ ] Emprestimo: A data de emprestimo tem que ser depois da data de devolução
