# Script para otimizar configurações do Git para melhor performance
# Execute este script após clonar o repositório para melhorar a velocidade das operações Git

Write-Host "Aplicando otimizações do Git para melhor performance..." -ForegroundColor Cyan

# Verifica se estamos em um repositório Git
if (-not (Test-Path .git)) {
    Write-Host "ERRO: Este diretório não é um repositório Git!" -ForegroundColor Red
    Write-Host "Execute este script na raiz do repositório." -ForegroundColor Yellow
    exit 1
}

# Aplica as configurações de otimização
Write-Host "`nConfigurando otimizações..." -ForegroundColor Green

git config --local core.preloadindex true
if ($LASTEXITCODE -eq 0) {
    Write-Host "  ✓ core.preloadindex habilitado" -ForegroundColor Gray
}

git config --local core.fscache true
if ($LASTEXITCODE -eq 0) {
    Write-Host "  ✓ core.fscache habilitado" -ForegroundColor Gray
}

git config --local gc.auto 256
if ($LASTEXITCODE -eq 0) {
    Write-Host "  ✓ gc.auto configurado" -ForegroundColor Gray
}

git config --local submodule.recurse false
if ($LASTEXITCODE -eq 0) {
    Write-Host "  ✓ submodule.recurse desabilitado" -ForegroundColor Gray
}

Write-Host "`n✓ Otimizações aplicadas com sucesso!" -ForegroundColor Green
Write-Host "`nAs operações Git devem estar mais rápidas agora." -ForegroundColor Cyan
Write-Host "Teste com: git status" -ForegroundColor Yellow

