# Minicurso Ambientes Reprodutíveis com Docker

## Objetivo Geral

Apresentar os fundamentos do **Docker** e demonstrar sua aplicação prática na criação de ambientes computacionais reprodutíveis, destacando vantagens, limitações e casos de uso em **pesquisa** e **ensino**.

Ao final do minicurso, o participante será capaz de:

* Compreender o conceito de **container** e **imagem Docker**;
* Executar e gerenciar containers com persistência de dados;
* Construir suas **próprias imagens** a partir de um **Dockerfile**;
* Utilizar volumes e bind mounts para integração com o sistema host;
* Criar **pipelines de build** mais eficientes com multi-stage builds.

## Estrutura do Curso

O minicurso é dividido em **dois dias** principais e um módulo extra opcional:

| Dia       | Tópicos                                                                                | Duração  | Material                                                                                   |
| --------- | -------------------------------------------------------------------------------------- | -------- | ------------------------------------------------------------------------------------------ |
| **1**     | Conceitos fundamentais, execução de containers, imagens, volumes e persistência.       | ~1h30    | [`dia1/slides.pdf`](dia1/slides.pdf), [`dia1/pratica/pratica.md`](dia1/pratica/pratica.md) |
| **2**     | Construção de imagens personalizadas, Dockerfiles, multi-stage builds e boas práticas. | ~1h30    | [`dia2/slides.pdf`](dia2/slides.pdf), [`dia2/pratica/pratica.md`](dia2/pratica/pratica.md) |
| **Extra** | Imagens minimalistas e compilação estática em C com multi-stage.                       | Opcional | [`extra/pratica.md`](extra/pratica.md)                                                     |

## Pré-requisitos

* Conhecimentos básicos de **linha de comando** (bash ou zsh)
* Docker instalado (versão ≥ 24)

### Instalação recomendada no Linux

Consulte a [documentação oficial](https://docs.docker.com/engine/install/).

Após a instalação, adicione seu usuário ao grupo Docker e reinicie a sessão:

```bash
sudo usermod -aG docker $USER
```

## Como Executar as Práticas

### Dia 1 - Executando Containers e Salvando Progresso

```bash
cd dia1/pratica

docker run \
  --name jupyter-lab \
  -p 8888:8888 \
  -v "$(pwd)/notebooks":/home/jovyan/work:z \
  --memory="512m" \
  --cpus="1.0" \
  jupyter/base-notebook
```

Acesse o link exibido no terminal (porta 8888) e crie seus notebooks. Os arquivos serão salvos na pasta local.

### Dia 2 - Criando sua Própria Imagem

```bash
cd dia2/pratica

mkdir out
docker build -f Dockerfile -t minha_imagem .
docker run --rm -it -u $(id -u):$(id -g) -v "$(pwd)/app":/app:z minha_imagem python code/wave.py
```

O script Python (`app/code/wave.py`) gera uma simulação visual de ondas e salva o vídeo em `app/out/wave.mp4`.

### Extra - Multi-stage Build em C

```bash
cd extra

mkdir out
docker build -f Dockerfile -t tic-tac-toe .
docker run --rm -it -v "$(pwd)/out":/out:z tic-tac-toe:latest
```

Esse exemplo mostra como compilar um programa em C estaticamente e gerar uma imagem **mínima e portátil** usando `scratch`.

## Materiais Complementares

* [Documentação Oficial do Docker](https://docs.docker.com)
* [Docker Hub – Imagens Oficiais](https://hub.docker.com/search?q=&type=image)

## Licença

Distribuído sob a licença MIT. Veja o arquivo [`LICENSE`](LICENSE) para mais detalhes.