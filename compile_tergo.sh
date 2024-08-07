#!/bin/bash


echo -e "\033[31mEste arquivo está obsoleto. Para compilar seu programa, use o manual como referência.\033[0m"
echo "https://github.com/TergoTeclados/Tergo-Sofle-Documentation/blob/main/guias/COMO_MODIFICAR_CODIGO_FONTE.md#compilar-firmware-do-seu-teclado"
exit 0

# Verifica se a pasta .build_tergo existe, caso contrário a cria
mkdir -p .build_tergo

# Função para copiar o arquivo UF2 e renomeá-lo
copy_uf2() {
    # Obtém o nome do arquivo UF2 gerado pelo comando de compilação
    uf2_file=$(find .build -name "tergo_sofle_rev1_default_rp2040_ce.uf2")

    # Verifica se o arquivo UF2 foi encontrado
    if [ -n "$uf2_file" ]; then
        # Define o nome do arquivo de destino
        dest_file=".build_tergo/$1"

        # Copia o arquivo UF2 para o destino
        cp "$uf2_file" "$dest_file"

        # Mensagem de confirmação
        echo "Arquivo UF2 copiado para: $dest_file"
    else
        echo "Erro: Arquivo UF2 não encontrado."
    fi
}

# Função para compilar e copiar, recebe as opções de compilação como parâmetros
compile_and_copy() {
    # Compondo o nome do arquivo de saída com base nas opções de compilação
    output_file="tergo_sofle_rev1"
    if [[ "$@" == *"OLED_ENABLE=no"* ]]; then
        output_file="${output_file}_sem_oled"
    else
        output_file="${output_file}_com_oled"
    fi
    if [[ "$@" == *"RGB_MATRIX_ENABLE=no"* ]]; then
        output_file="${output_file}_sem_rgb"
    else
        output_file="${output_file}_com_rgb"
    fi
    output_file="${output_file}.uf2"

    # Compilação com o nome de arquivo de saída composto
    qmk compile -kb tergo_sofle/rev1 -km default -j 0 "$@"

    # Copia o arquivo UF2 para a pasta .build_tergo
    copy_uf2 "$output_file"
}

# Chamadas para compilar com diferentes configurações
compile_and_copy
compile_and_copy -e OLED_ENABLE=no -e RGB_MATRIX_ENABLE=no -e VIALRGB_ENABLE=no
compile_and_copy -e RGB_MATRIX_ENABLE=no -e VIALRGB_ENABLE=no
compile_and_copy -e OLED_ENABLE=no
