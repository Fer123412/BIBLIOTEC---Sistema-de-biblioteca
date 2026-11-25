# 📚 BIBLIATEC — Sistema de Gerenciamento de Livros em C

Sistema de gerenciamento de biblioteca em linha de comando, desenvolvido em **C**, que utiliza **lista encadeada** para armazenar os livros e **pilha** para o histórico de ações, permitindo **desfazer** operações. Os dados são salvos em arquivo binário e é possível gerar um relatório em texto.

## ✨ Funcionalidades

- **Cadastrar livros** no início, no meio (após um código informado) ou no fim da lista
- **Listar** todos os livros cadastrados
- **Atualizar** título e valor de um livro a partir do código
- **Excluir** livros, com confirmação (`s/n`)
- **Desfazer ação** (cadastro, atualização ou exclusão) usando uma pilha
- **Histórico** das ações realizadas na sessão
- **Relatório** em `.txt` com todos os livros e o total
- **Persistência de dados** em `Ficha.dat` (carregado ao iniciar, salvo ao sair)

## 🧠 Estruturas de dados utilizadas

| Estrutura | Uso |
|-----------|-----|
| Lista encadeada simples (`n1`) | Armazena os livros em memória |
| Pilha (`Acao`) | Guarda o histórico para a função desfazer (LIFO) |
| `struct Livro` | Formato gravado no arquivo binário |
| `enum tipoacao` | Identifica o tipo de ação: `CADASTRO`, `ATUALIZACAO`, `EXCLUIR` |

### Como funciona o "Desfazer"

Cada operação empilha um registro com o estado **antes** e **depois** do livro e sua posição na lista. Ao desfazer, a ação do topo é removida da pilha e revertida:

| Ação | Como é desfeita |
|------|-----------------|
| Cadastro | O livro é removido da lista |
| Atualização | Título e valor antigos são restaurados |
| Exclusão | O livro é reinserido na posição original |

## 📁 Estrutura do projeto

```
.
├── BIBLIOTEC.c            # Código-fonte
├── Ficha.dat              # Banco de dados binário (gerado automaticamente)
└── relatorio_livros.txt   # Relatório gerado pelo sistema
```

## 🚀 Como executar

### Requisitos

- Compilador C (GCC/MinGW, Dev-C++, Code::Blocks, etc.)
- Windows (o código inclui `windows.h`)

### Compilando

```bash
gcc BIBLIOTEC.c -o bibliotec
```

### Executando

```bash
./bibliotec
```

## 🖥️ Menu

```
=========================
=      BIBLIATEC        =
=========================
= [1]Cadastrar livros   =
= [2]listar livros      =
= [3]Atualizar livros   =
= [4]Excluir livros     =
= [5]Desfazer acao      =
= [6]Historico          =
= [7]Imprimir Relatorio =
= [0]Sair               =
=========================
```

### Exemplo de uso

**Cadastrando no fim da lista:**

```
> 1
Qual sera a posicao?(Inicio(i),Meio(m),Fim(f)) f
Quantos livros? 1

Codigo: 20
Titulo: Rust
Valor: 60.00
```

**Listagem:**

```
(20, Rust, 60.00) -> (4, Java, 30.00) -> (3, Python, 20.00) -> NULL
```

### Exemplo de relatório (`relatorio_livros.txt`)

```
================================
       RELATORIO DE LIVROS      
================================

Codigo: 20
Titulo: Rust
Valor: 60.00
----------------------------
Codigo: 4
Titulo: Java
Valor: 30.00
----------------------------

Total de livros: 2
```

## 💾 Persistência

- Ao iniciar, o programa lê o arquivo `Ficha.dat` (se existir) e monta a lista.
- Os dados são salvos ao **sair (0)** ou ao **gerar o relatório (7)**.
- O histórico de ações (pilha) **não** é salvo: ele vale apenas durante a sessão.

## 🔧 Melhorias futuras

- Compatibilidade com Linux/macOS (remover `windows.h` e `fflush(stdin)`)
- Leitura de títulos com espaços em todas as opções de cadastro
- Busca de livros por título
- Ordenação da lista (por código, título ou valor)
- Salvar o histórico em arquivo
- Liberar a memória da lista e da pilha ao encerrar

## 🎓 Conceitos praticados

Ponteiros e ponteiros duplos · alocação dinâmica (`malloc`/`free`) · listas encadeadas · pilhas · structs e enums · manipulação de arquivos binários e de texto · modularização com funções

## 📄 Licença

Projeto de estudo, de uso livre para fins educacionais.
