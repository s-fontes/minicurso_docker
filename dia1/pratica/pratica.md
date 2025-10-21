# Prática: Executando Jupyter Notebook com Docker

## 0. Objetivo

Nesta prática, você irá executar um **Jupyter Notebook** dentro de um container Docker, com armazenamento persistente, limitação de recursos e acesso via navegador. O objetivo é entender como o Docker simplifica a criação de ambientes reprodutíveis para ciência de dados e ensino.

## 1. Testar a instalação

Verifique se o Docker está instalado e funcionando corretamente:

```bash
docker --version
```

Para validar a execução de containers, teste com a imagem oficial:

```bash
docker run hello-world
```

## 2. Executar o container do Jupyter

Inicie o container com um volume persistente, limite de CPU e memória, e porta exposta para acesso local:

```bash
docker run -d \
  --name jupyter-lab \
  -p 8888:8888 \
  -v "$(pwd)/notebooks":/home/jovyan/work:z \
  --memory="512m" \
  --cpus="1.0" \
  jupyter/base-notebook
```

**Explicação dos parâmetros:**

| Parâmetro                                   | Função                                                     |
| ------------------------------------------- | ---------------------------------------------------------- |
| `-d`                                        | Executa o container em modo *detached* (segundo plano).    |
| `--name jupyter-lab`                        | Define um nome amigável para o container.                  |
| `-p 8888:8888`                              | Mapeia a porta do container (8888) para a máquina host.    |
| `-v "$(pwd)/notebooks":/home/jovyan/work:z` | Cria um volume persistente para salvar notebooks.          |
| `:z`                                        | Ajusta permissões para sistemas com SELinux (como Fedora). |
| `--memory` e `--cpus`                       | Limitam o uso de memória e CPU.                            |

## 3. Acessar o Jupyter Notebook

Obtenha o token de autenticação gerado pelo container:

```bash
docker logs jupyter-lab
```

O terminal exibirá uma URL semelhante a:

```
http://127.0.0.1:8888/?token=abcdef123456...
```

Abra o link no navegador para acessar o Jupyter Notebook.

Os arquivos criados ou modificados serão salvos no diretório local `notebooks/`.


## 4. Parar e reiniciar o container

Para interromper o container:

```bash
docker stop jupyter-lab
```

Para reiniciá-lo:

```bash
docker start jupyter-lab
```

Se precisar do token novamente:

```bash
docker logs jupyter-lab
```


## 5. Verificar status e logs

Liste containers ativos:

```bash
docker ps
```

Acompanhe os logs em tempo real:

```bash
docker logs -f jupyter-lab
```


## 6. Remover o container e a imagem

Para remover completamente o container:

```bash
docker stop jupyter-lab && docker rm jupyter-lab
```

Para remover a imagem usada:

```bash
docker rmi jupyter/base-notebook
```

Os notebooks continuarão armazenados na pasta local `notebooks/` — o volume persistente garante que os arquivos não sejam perdidos.


## 7. Conceitos abordados

| Conceito               | Descrição                                            |
| ---------------------- | ---------------------------------------------------- |
| **Container**          | Ambiente isolado que executa o Jupyter Notebook.     |
| **Volume persistente** | Permite salvar notebooks fora do container.          |
| **Port mapping**       | Expõe o serviço interno na porta 8888 do host.       |
| **Limite de recursos** | Controla o uso de CPU e memória do container.        |
| **Logs e tokens**      | Permitem monitorar e autenticar o acesso ao Jupyter. |


## 8. Conclusão

Essa prática demonstra como o Docker pode simplificar a execução de ambientes científicos. Com poucos comandos, você cria um **ambiente isolado e reprodutível**, capaz de rodar Jupyter Notebooks em qualquer sistema operacional, sem depender de configurações locais.
