# Etapa 1 — Build da aplicação
# Usa a imagem oficial do GCC como base para compilação
FROM gcc:latest AS builder

# Define o diretório de trabalho dentro da imagem de build
WORKDIR /src

# Copia o arquivo-fonte C do host para dentro do container
COPY main.c .

# Compila o código-fonte em um binário estático chamado "main"
# O uso de "-static" garante que todas as dependências sejam embutidas no executável,
# permitindo que ele rode em uma imagem mínima (como a 'scratch')
RUN gcc -static -o main main.c

# Etapa 2 — Imagem final mínima
# Usa a imagem 'scratch', que é completamente vazia (sem shell, sem sistema base)
FROM scratch

# Declara um volume /out para exportar dados gerados (ex: logs ou resultados)
VOLUME /out

# Copia o binário compilado da etapa anterior para a raiz da nova imagem
COPY --from=builder /src/main /main

# Define o comando padrão a ser executado ao iniciar o container
CMD ["/main"]