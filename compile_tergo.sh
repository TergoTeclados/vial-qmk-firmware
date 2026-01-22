#!/bin/bash

# Script para gerar firmware no padrão internacional e no padrão ABNT2

# Variáveis de controle
compile_internacional=false
compile_abnt2=false
version="Custom"

# Parse dos argumentos
while [[ $# -gt 0 ]]; do
    case $1 in
        --internacional|-i)
            compile_internacional=true
            shift
            ;;
        --abnt2|-a)
            compile_abnt2=true
            shift
            ;;
        --version|-v)
            version="$2"
            shift 2
            ;;
        --help|-h)
            echo "Uso: $0 [OPÇÕES] [VERSÃO]"
            echo ""
            echo "OPÇÕES:"
            echo "  -i, --internacional    Compila apenas o firmware internacional"
            echo "  -a, --abnt2            Compila apenas o firmware ABNT2"
            echo "  -v, --version VERSÃO   Especifica a versão do firmware"
            echo "  -h, --help             Mostra esta mensagem de ajuda"
            echo ""
            echo "Se nenhuma opção for especificada, compila ambos os firmwares."
            echo "A versão também pode ser passada como primeiro argumento posicional."
            exit 0
            ;;
        *)
            # Se não for uma opção, assume que é a versão
            if [ "$version" = "Custom" ] && [[ ! "$1" =~ ^- ]]; then
                version="$1"
            fi
            shift
            ;;
    esac
done

# Se nenhuma opção foi especificada, compila ambos
if [ "$compile_internacional" = false ] && [ "$compile_abnt2" = false ]; then
    compile_internacional=true
    compile_abnt2=true
fi

# Verifica se a pasta .build_tergo existe, caso contrário a cria
mkdir -p .build_tergo

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

# Função para compilar firmware internacional
compilar_internacional() {
    echo "Compilando firmware internacional..."
    qmk compile -kb tergo_sofle/rev1 -km default -j 0 || {
        echo "Erro: Falha na compilação do firmware internacional!"
        exit 1
    }

    # Aguarda o arquivo ser criado
    aguardar_arquivo "$origem"

    # Copia o arquivo para a pasta de destino com o novo nome
    cp -f "$origem" "$destino_inter"
    echo "Firmware internacional copiado e renomeado com sucesso!"
}

# Função para compilar firmware ABNT2
compilar_abnt2() {
    echo "Compilando firmware ABNT2..."
    qmk compile -kb tergo_sofle/rev1 -km default -j 0 -e USE_LAYOUT_ABNT2=yes || {
        echo "Erro: Falha na compilação do firmware ABNT2!"
        exit 1
    }

    # Aguarda o arquivo ser criado
    aguardar_arquivo "$origem"

    # Copia o arquivo para a pasta de destino com o novo nome
    cp -f "$origem" "$destino_abnt2"
    echo "Firmware ABNT2 copiado e renomeado com sucesso!"
}

# Executa as compilações solicitadas
if [ "$compile_internacional" = true ]; then
    compilar_internacional
fi

if [ "$compile_abnt2" = true ]; then
    compilar_abnt2
fi

echo "Processo concluído!"