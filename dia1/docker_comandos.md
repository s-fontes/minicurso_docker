# Comandos e Parâmetros Principais do Docker CLI

> **Referência oficial:** [Docker CLI Command Reference](https://docs.docker.com/engine/reference/commandline/)

## docker run

Executa um novo container.

```bash
docker run [OPÇÕES] IMAGEM [COMANDO]
```

**Documentação:** [docker run](https://docs.docker.com/engine/reference/commandline/run/)

### Prâmetros mais usados:

| Parâmetro      | Descrição                                           |
| -------------- | --------------------------------------------------- |
| `-d`           | Executa em segundo plano (*detached*).              |
| `--name`       | Nome customizado para o container.                  |
| `-p`           | Mapeia portas (formato `HOST:CONTAINER`).           |
| `-v`           | Monta diretórios (bind mount ou volume).            |
| `--mount`      | Forma mais moderna e estruturada de montar volumes. |
| `--rm`         | Remove o container automaticamente ao parar.        |
| `-it`          | Modo interativo com terminal.                       |
| `--user`       | Executa como UID/GID específico.                    |
| `-e`           | Define variáveis de ambiente.                       |
| `--entrypoint` | Substitui o comando padrão da imagem.               |

## docker ps

Lista containers em execução.

```bash
docker ps          # Ativos
docker ps -a       # Inclui os parados
```

**Documentação:** [docker ps](https://docs.docker.com/engine/reference/commandline/ps/)

## docker logs

Exibe os logs de um container.

```bash
docker logs CONTAINER
docker logs -f CONTAINER  # acompanha em tempo real
```

**Documentação:** [docker logs](https://docs.docker.com/engine/reference/commandline/logs/)

## docker exec

Executa comandos dentro de um container já em execução.

```bash
docker exec -it CONTAINER bash
docker exec -it jupyter-hello ls /home/jovyan
```

**Documentação:** [docker exec](https://docs.docker.com/engine/reference/commandline/exec/)

## docker stop / start / rm

Controla o ciclo de vida dos containers.

```bash
docker stop CONTAINER
docker start CONTAINER
docker rm CONTAINER
```

**Documentação:**
[docker stop](https://docs.docker.com/engine/reference/commandline/stop/) • [docker start](https://docs.docker.com/engine/reference/commandline/start/) • [docker rm](https://docs.docker.com/engine/reference/commandline/rm/)

## docker rmi

Remove uma imagem local.

```bash
docker rmi IMAGEM
```

**Documentação:** [docker rmi](https://docs.docker.com/engine/reference/commandline/rmi/)

## docker images

Lista imagens disponíveis localmente.

```bash
docker images
```

**Documentação:** [docker images](https://docs.docker.com/engine/reference/commandline/images/)

## docker pull

Baixa uma imagem do Docker Hub.

```bash
docker pull jupyter/base-notebook
```

**Documentação:** [docker pull](https://docs.docker.com/engine/reference/commandline/pull/)

## docker build

Cria uma imagem a partir de um Dockerfile.

```bash
docker build -t minha-imagem .
```

**Documentação:** [docker build](https://docs.docker.com/engine/reference/commandline/build/)

## SELinux: uso de `:z` em `-v`

Em sistemas com **SELinux** (ex: Fedora), é necessário adicionar `:z` ao bind mount:

```bash
-v "$(pwd)":/home/jovyan/work:z
```

**Referência:** [Bind mounts & SELinux](https://docs.docker.com/storage/bind-mounts/#configure-the-selinux-label)

> No Ubuntu e Debian, o uso de `:z` normalmente **não é necessário**.
