# Etapa base: imagem oficial do Python minimalista
FROM python:3.12-slim

# Instala o FFmpeg (necessário para salvar vídeos gerados pelo Matplotlib)
# Usa o modo "no-install-recommends" para evitar pacotes desnecessários
# e remove os caches de listas APT para reduzir o tamanho final da imagem
RUN apt-get update \
    && apt-get install -y --no-install-recommends ffmpeg \
    && rm -rf /var/lib/apt/lists/*

# Declara o diretório /app como volume
# Isso permite persistir dados entre execuções e facilita o uso de bind mounts
VOLUME /app

# Define /app como diretório de trabalho padrão
WORKDIR /app

# Copia o arquivo de dependências do host para o container
COPY app/requirements.txt .

# Instala as dependências Python listadas no requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

# Define o comando padrão ao iniciar o container
# "tail -f /dev/null" mantém o container ativo sem sair imediatamente,
# permitindo executar comandos interativos posteriormente (via docker exec)
CMD ["tail", "-f", "/dev/null"]
