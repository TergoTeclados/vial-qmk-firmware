#!/bin/bash

# Script para gerar firmware no padrão internacional e no padrão ABNT2

# Verifica se a pasta .build_tergo existe, caso contrário a cria
mkdir -p .build_tergo

# Versao do firmware (usa "Custom" como padrão se não for passado parâmetro)
version="${1:-Custom}"

# Caminhos absolutos dos arquivos que serão compilados
origem="$(pwd)/.build/tergo_sofle_rev1_default_rp2040_ce.uf2"
destino_inter="$(pwd)/.build_tergo/firmware_tergo_sofle_v${version}_internacional.uf2"
destino_abnt2="$(pwd)/.build_tergo/firmware_tergo_sofle_v${version}_abnt2.uf2"

# Função para verificar se o arquivo foi criado
aguardar_arquivo() {
    local arquivo=$1
    local tempo_maximo=8  # Tempo máximo de espera em segundos
    local tempo_decorrido=0
    local intervalo=1      # Intervalo de verificação em segundos

    while [ ! -f "$arquivo" ]; do
        if [ "$tempo_decorrido" -ge "$tempo_maximo" ]; then
            echo "Erro: Tempo máximo de espera atingido. O arquivo $arquivo não foi encontrado."
            exit 1
        fi
        echo "Aguardando o arquivo $arquivo ser criado... ($tempo_decorrido segundos)"
        sleep "$intervalo"
        tempo_decorrido=$((tempo_decorrido + intervalo))
    done
}

# Compila primeiramente com o layout internacional (padrão)
echo "Compilando firmware internacional..."
qmk compile -kb tergo_sofle/rev1 -km default -j 0

# Aguarda o arquivo ser criado
aguardar_arquivo "$origem"

# Copia o arquivo para a pasta de destino com o novo nome
cp -f "$origem" "$destino_inter"
echo "Firmware internacional copiado e renomeado com sucesso!"

# Compila com o layout ABNT2
echo "Compilando firmware ABNT2..."
qmk compile -kb tergo_sofle/rev1 -km default -j 0 -e USE_LAYOUT_ABNT2=yes

# Aguarda o arquivo ser criado
aguardar_arquivo "$origem"

# Copia o arquivo para a pasta de destino com o novo nome
cp -f "$origem" "$destino_abnt2"
echo "Firmware ABNT2 copiado e renomeado com sucesso!"

echo "Processo concluído!"