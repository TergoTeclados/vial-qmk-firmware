#!/bin/bash
# Script para otimizar configurações do Git para melhor performance
# Execute este script após clonar o repositório para melhorar a velocidade das operações Git

echo "Aplicando otimizações do Git para melhor performance..."

# Verifica se estamos em um repositório Git
if [ ! -d .git ]; then
    echo "ERRO: Este diretório não é um repositório Git!"
    echo "Execute este script na raiz do repositório."
    exit 1
fi

# Aplica as configurações de otimização
echo ""
echo "Configurando otimizações..."

git config --local core.preloadindex true && \
    echo "  ✓ core.preloadindex habilitado"

git config --local core.fscache true && \
    echo "  ✓ core.fscache habilitado"

git config --local gc.auto 256 && \
    echo "  ✓ gc.auto configurado"

git config --local submodule.recurse false && \
    echo "  ✓ submodule.recurse desabilitado"

echo ""
echo "✓ Otimizações aplicadas com sucesso!"
echo ""
echo "As operações Git devem estar mais rápidas agora."
echo "Teste com: git status"

