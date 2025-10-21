# Comandos Dockerfile

> **Referência oficial:** [Dockerfile reference](https://docs.docker.com/reference/dockerfile/)

> Um **Dockerfile** é um script que instrui o Docker sobre como construir uma **imagem personalizada**.

## FROM

Define a imagem base.

```Dockerfile
FROM python:3.11
```

> Sempre deve ser o **primeiro comando**, exceto instruções `ARG` globais.

**Documentação:** [FROM](https://docs.docker.com/reference/dockerfile/#from)

## RUN

Executa comandos **em tempo de build**.

```Dockerfile
RUN apt-get update && apt-get install -y curl
```

> Cada `RUN` cria uma nova **camada** na imagem.

**Documentação:** [RUN](https://docs.docker.com/reference/dockerfile/#run)

## CMD

Define o **comando padrão** quando o container é iniciado.

```Dockerfile
CMD ["python", "app.py"]
```

* Pode ser sobrescrito com argumentos no `docker run`
* Aceita formato:

  * `['exec', 'form']` (preferido)
  * `'shell form'` (menos seguro)

**Documentação:** [CMD](https://docs.docker.com/reference/dockerfile/#cmd)

## ENTRYPOINT

Define o **comando principal** que sempre será executado.

```Dockerfile
ENTRYPOINT ["python", "main.py"]
```

> Usado quando o container **sempre executa o mesmo binário** (ex: CLI, scripts).

**Documentação:** [ENTRYPOINT](https://docs.docker.com/reference/dockerfile/#entrypoint)

## COPY

Copia arquivos da máquina host para a imagem.

```Dockerfile
COPY . /app
COPY requirements.txt /app/
```

> Use com `.dockerignore` para evitar copiar arquivos desnecessários.

**Documentação:** [COPY](https://docs.docker.com/reference/dockerfile/#copy)

## ADD

Como `COPY`, mas com recursos extras:

* Descompacta arquivos `.tar.gz`
* Pode copiar de URLs

```Dockerfile
ADD https://example.com/file.tar.gz /src/
```

> Use `COPY` na maioria dos casos — é mais previsível.

**Documentação:** [ADD](https://docs.docker.com/reference/dockerfile/#add)

## WORKDIR

Define o diretório de trabalho **dentro da imagem**.

```Dockerfile
WORKDIR /app
```

> Evita precisar digitar caminhos absolutos no `RUN`, `CMD` etc.

**Documentação:** [WORKDIR](https://docs.docker.com/reference/dockerfile/#workdir)

## ENV

Define variáveis de ambiente.

```Dockerfile
ENV NODE_ENV=production
ENV PATH="/custom/bin:$PATH"
```

**Documentação:** [ENV](https://docs.docker.com/reference/dockerfile/#env)

## ARG

Define variáveis **em tempo de build**.

```Dockerfile
ARG VERSION=1.0.0
RUN echo "Building version $VERSION"
```

* Só funciona **durante o build**
* Para passar: `docker build --build-arg VERSION=2.0.0`

**Documentação:** [ARG](https://docs.docker.com/reference/dockerfile/#arg)

## EXPOSE

Documenta a **porta** usada pela aplicação.

```Dockerfile
EXPOSE 3000
```

> Não publica a porta automaticamente (use `-p` no `docker run`).

**Documentação:** [EXPOSE](https://docs.docker.com/reference/dockerfile/#expose)

## VOLUME

Indica que o container espera um volume nesse caminho.

```Dockerfile
VOLUME /data
```

> Gera um volume **anônimo** se nenhum for especificado no `run`.

**Documentação:** [VOLUME](https://docs.docker.com/reference/dockerfile/#volume)

## LABEL

Adiciona metadados à imagem.

```Dockerfile
LABEL maintainer="seu@email.com"
LABEL version="1.0"
```

**Documentação:** [LABEL](https://docs.docker.com/reference/dockerfile/#label)

## USER

Define o usuário que executa os comandos seguintes.

```Dockerfile
USER node
```

> Recomendado por segurança (evitar rodar como root).

**Documentação:** [USER](https://docs.docker.com/reference/dockerfile/#user)

## ONBUILD

Comando que será **executado em builds filhos** (herdeiros dessa imagem).

```Dockerfile
ONBUILD COPY . /app
ONBUILD RUN npm install
```

> Útil para imagens base, mas pode confundir — use com cuidado.

**Documentação:** [ONBUILD](https://docs.docker.com/reference/dockerfile/#onbuild)

## .dockerignore

Crie um arquivo `.dockerignore` como o `.gitignore`:

```
node_modules
*.log
.env
```

> Melhora performance e segurança ao evitar copiar arquivos desnecessários para a imagem.

**Documentação:** [.dockerignore](https://docs.docker.com/build/building/context/#dockerignore-files)

## Exemplo completo

```Dockerfile
FROM node:20

WORKDIR /app

COPY package.json .
RUN npm install

COPY . .

ENV NODE_ENV=production

EXPOSE 3000

CMD ["node", "index.js"]
```
