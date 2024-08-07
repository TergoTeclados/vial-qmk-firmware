# Tergo Sofle

Este repositório contém a definição do teclado Tergo Sofle e suas configurações.

Consulte a [documentação do Tergo Sofle](https://github.com/TergoTeclados/Tergo-Sofle-Documentation) caso tenha chegado aqui por acidente.

# Como modificar e compilar

Este repositório é importado como submódulo para os [forks do firmware QMK disponibilizados pela Tergo](https://github.com/TergoTeclados/vial-qmk-firmware). 

Assim, caso queira modificá-lo e compilá-lo, faça um `git clone` de algum dos firmwares disponibilizados e baixe os submódulos usando `qmk git-submodules` pelo [terminal QMK MSYS](https://msys.qmk.fm/). Assim, este repositório será baixado junto.

Para mais detalhes consulte a [documentação de modificação de software do Tergo Sofle](https://github.com/TergoTeclados/Tergo-Sofle-Documentation/blob/main/MANUAL_FIRMWARE_MODDING.md)

# Como importar isto para meu próprio fork do QMK

Os forks do firmware QMK disponibilizados pela Tergo já possuem este repositório e também possuem modificações especiais, então a princípio você não deve precisar seguir este passo.

Mas caso queira, no seu fork, execute `git submodule add https://github.com/TergoTeclados/Tergo-Sofle-firmware-config keyboards/tergo_sofle`. Atenção: é essencial que o caminho da pasta seja igual ao do exemplo.

Então, `git submodule update --init` para iniciar e baixar o submódulo. Então, modifique diretamente os arquivos na pasta dele.
