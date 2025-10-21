# Prática Extra: Compilando e Executando um Jogo em C com Docker

## 0. Objetivo

Nesta prática, você aprenderá a usar o Docker para **compilar e executar um programa em C** de forma isolada, sem precisar instalar o compilador localmente. O exemplo será um jogo de **Tic-Tac-Toe (Jogo da Velha)** que salva o histórico de jogadas.

O processo demonstra o uso de **build multi-stage**, com uma imagem de compilação (`gcc`) e uma imagem final mínima (`scratch`).


## 1. Estrutura de diretórios

```text
extra/
├── Dockerfile
├── main.c
└── pratica.md
```


## 2. Dockerfile explicado

```dockerfile
# Etapa 1 — Compilação
FROM gcc:latest AS builder
WORKDIR /src
COPY main.c .
RUN gcc -static -o main main.c

# Etapa 2 — Imagem final mínima
FROM scratch
VOLUME /out
COPY --from=builder /src/main /main
CMD ["/main"]
```

**Explicação:**

* `FROM gcc:latest AS builder`: usa a imagem oficial do GCC para compilar o código.
* `-static`: gera um binário autossuficiente (sem dependências externas).
* `FROM scratch`: cria uma imagem totalmente vazia, contendo apenas o binário.
* `VOLUME /out`: define um ponto de montagem para exportar dados (como logs e histórico do jogo).
* `CMD ["/main"]`: executa o jogo automaticamente ao iniciar o container.


## 3. Construir a imagem

No diretório `extra/`, execute:

```bash
docker build -f Dockerfile -t tic-tac-toe .
```

Verifique se a imagem foi criada:

```bash
docker images
```

Saída esperada:

```
REPOSITORY     TAG       IMAGE ID       CREATED          SIZE
tic-tac-toe    latest    <id>           few seconds ago  <~1MB>
```
## 4. Criar o diretório out

```bash
mkdir out
```

## 5. Executar o jogo

Monte o diretório `out/` para salvar o histórico de jogadas:

```bash
docker run --rm -it -v "$(pwd)/out":/out:z tic-tac-toe:latest
```
## 6. Conclusão

Mesmo sem ter o `gcc` instalado localmente, você consegue **compilar e executar programas C de forma segura e isolada**, mantendo o sistema do host limpo.
