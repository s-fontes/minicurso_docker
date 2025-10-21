# Prática: Criando e Executando Containers Personalizados no Docker

## 0. Objetivo

Nesta prática, você irá construir uma imagem Docker personalizada a partir de um **Dockerfile**, criar e gerenciar containers de forma interativa e efêmera, e compreender o ciclo completo: **build → create → start → exec → stop → rm → run**.

O exemplo usa um código Python que simula uma onda bidimensional e gera uma animação (`onda.mp4`) dentro do container.

## 1. Estrutura de diretórios

```text
pratica/
├── Dockerfile
└── app/
    ├── code/
    │   └── wave.py
    └── requirements.txt
```

## 2. Construir a imagem

Crie a imagem personalizada com o nome `minha_imagem`:

```bash
docker build -f Dockerfile -t minha_imagem .
```

Verifique se a imagem foi criada com sucesso:

```bash
docker images
```

Saída esperada:

```
REPOSITORY     TAG       IMAGE ID       CREATED          SIZE
minha_imagem   latest    <id>           few seconds ago  741MB
```

## 3. Criar e iniciar o container

Crie o container sem executá-lo imediatamente:

```bash
docker create --name meu_container -u $(id -u):$(id -g) -v "$(pwd)/app":/app:z minha_imagem:latest
```

Verifique o status:

```bash
docker ps -a
```

Inicie o container:

```bash
docker start meu_container
```

## 4. Executar comandos dentro do container

Acesse o terminal do container:

```bash
docker exec -it meu_container bash
```

Execute o script Python:

```bash
python code/wave.py
```

Saída esperada:

```
INFO - Iniciando simulação de onda...
INFO - Animação salva em: /app/out/wave.mp4
INFO - Simulação concluída em ~40 segundos.
```

Saia do container:

```bash
exit
```

## 5. Parar e remover o container

Pare o container:

```bash
docker stop meu_container
```

Remova o container:

```bash
docker rm meu_container
```

## 6. Executar container efêmero

Um container efêmero é criado, executa a tarefa e é removido automaticamente após o término:

### 6.1 Modo interativo com shell

```bash
docker run --rm -it -u $(id -u):$(id -g) -v "$(pwd)/app":/app:z minha_imagem bash
```

Dentro do container:

```bash
python code/wave.py
exit
```

### 6.2 Execução direta do script

```bash
docker run --rm -it -u $(id -u):$(id -g) -v "$(pwd)/app":/app:z minha_imagem python code/wave.py
```

Ao final, o container é removido automaticamente (`--rm`), mas o arquivo `wave.mp4` permanece salvo na pasta `app/out` do host.


## 7. Conceitos ilustrados

| Etapa      | Comando         | Descrição                                 |
| ---------- | --------------- | ----------------------------------------- |
| **Build**  | `docker build`  | Cria a imagem personalizada.              |
| **Create** | `docker create` | Cria o container sem iniciar.             |
| **Start**  | `docker start`  | Inicia um container existente.            |
| **Exec**   | `docker exec`   | Executa comandos dentro do container.     |
| **Stop**   | `docker stop`   | Interrompe um container em execução.      |
| **Rm**     | `docker rm`     | Remove o container do sistema.            |
| **Run**    | `docker run`    | Cria e executa um container em uma etapa. |


## 8. Resultado

A prática gera um arquivo de vídeo `wave.mp4` dentro do diretório:

```text
app/out/wave.mp4
```

Esse arquivo contém a animação da propagação de uma onda simulada via Python/NumPy/Matplotlib.

## 9. Conclusão

Esta prática mostrou como o Docker pode tornar a execução de experimentos científicos e educacionais muito mais simples e confiável. Com apenas alguns comandos, é possível construir e executar um **ambiente isolado, controlado e reprodutível**, garantindo que o mesmo código funcione de forma idêntica em qualquer sistema operacional.
