# Projeto de Processamento Digital de Imagens - PDI 2025

Projeto de implementação das atividades de M1.1 - PDI 2025-02

## Grupo
Integrantes:
- Henrique Zimermann e Mateus Winter

## Implementação M1.1

Este projeto implementa todos os algoritmos solicitados na avaliação M1.1:

### Operações Implementadas

#### 1. Conversão para Tons de Cinza
- **Média Aritmética**: `GrayScale::get_gray_arithmetic()`
  - Fórmula: `gray = (B + G + R) / 3`
- **Média Ponderada**: `GrayScale::get_gray_weighted()`
  - Fórmula: `gray = 0.114*B + 0.587*G + 0.299*R` (padrão ITU-R BT.709)

#### 2. Operações Aritméticas
- **Imagem com Imagem**: Adição, subtração, multiplicação e divisão
- **Imagem com Escalar**: Operações com valores constantes
- **Suporte**: Imagens coloridas (3 canais) e tons de cinza (1 canal)
- **Proteções**: Clamping para evitar overflow/underflow, proteção contra divisão por zero

#### 3. Limiarização (Thresholding)
- **Tipos disponíveis**:
  - Binária simples e invertida
  - Truncada
  - To zero e to zero invertida
- **Suporte**: Tons de cinza e colorida (aplicada canal por canal)

#### 4. Isolamento de Canais de Cores
- **Extração**: Canais R, G, B como imagens em tons de cinza
- **Isolamento**: Imagens coloridas com apenas um canal ativo
- **Combinação**: Reconstrução de imagem colorida a partir de 3 canais

#### 5. Histograma
- **Computação**: Histogramas para tons de cinza e colorida (por canal)
- **Visualização**: Gráficos dos histogramas com cores correspondentes
- **Estatísticas**: Valores mínimo, máximo e média

#### 6. Inverso da Imagem
- **Operação**: `pixel = 255 - pixel` para todos os canais
- **Suporte**: Imagens coloridas e tons de cinza

### Características Técnicas

- **Tratamento de Overflow/Underflow**: Clamping para range [0, 255]
- **Eficiência**: Acesso direto por ponteiros de linha
- **Compatibilidade**: Suporte para imagens CV_8UC1 e CV_8UC3
- **Validações**: Verificação de dimensões e tipos de imagem
- **Documentação**: Padrão Doxygen conforme solicitado

## Estrutura do projeto

```
pdi_code/
├── CMakeLists.txt              # Configuração CMake
├── Makefile                    # Build manual alternativo  
├── README.md                   # Documentação principal
├── DOCUMENTACAO.md             # Documentação técnica detalhada
├── avaliacao-M1.1_implementacao.pdf # Especificação M1.1
├── app/                        # Programas principais
│   ├── run.cpp                # Programa original
│   ├── test.cpp               # Testes básicos
│   └── test_no_gui.cpp        # Teste completo M1.1 sem GUI
├── include/                    # Headers (.hpp)
│   ├── imageinfo.hpp          # Classe original ImageInfo
│   ├── arit/                  # Operações aritméticas
│   │   └── arithmetic.hpp
│   ├── conv/                  # Conversões (cinza, canais)
│   │   ├── grayscale.hpp
│   │   └── channel_isolator.hpp
│   ├── histo/                 # Histogramas
│   │   └── histogram.hpp
│   └── thre/                  # Limiarização
│       └── threshold.hpp
├── src/                       # Implementações (.cpp)
│   ├── imageinfo.cpp          # Implementação ImageInfo
│   ├── arit/                  # Operações aritméticas
│   │   └── arithmetic.cpp
│   ├── conv/                  # Conversões (cinza, canais)
│   │   ├── grayscale.cpp
│   │   └── channel_isolator.cpp
│   ├── histo/                 # Histogramas
│   │   └── histogram.cpp
│   └── thre/                  # Limiarização
│       └── threshold.cpp
└── data/                      # Imagens de teste
    ├── ave-01.jpeg
    ├── ave-02.jpeg
    └── ave-03.jpeg
```

## Compilação

### CMake (Recomendado)
```bash
# Linux/WSL
mkdir build && cd build
cmake ..
make

# Windows (MSYS2 UCRT64)
cmake -S . -B build_ucrt64 -G "MinGW Makefiles"
cmake --build build_ucrt64 -j4
```

### Makefile Manual (Alternativo)
```bash
# Compila programa principal
make

# Compila teste sem GUI (ideal para WSL)
make no-gui

# Executa teste completo
make run-test
```

## Pré-requisitos

- **Windows**: [MSYS2](https://www.msys2.org/) com pacotes:
  ```bash
  pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-opencv
  ```
- **Linux/WSL**: OpenCV, CMake e g++
  ```bash
  sudo apt update
  sudo apt install g++ cmake pkg-config libopencv-dev
  ```

## Execução

### Teste Completo M1.1 (Sem GUI)
```bash
# Compila e executa automaticamente
make run-test

# Ou manualmente
make no-gui
./test_no_gui

# Resultados salvos em: results/
```

### Programa Original
```bash
make
./pdi_run data/ave-02.jpeg
```

## Documentação
- **README.md**: Documentação principal (este arquivo)
- **DOCUMENTACAO.md**: Documentação técnica detalhada com exemplos de uso
- **Código**: Documentado no padrão Doxygen

## Nomenclatura
- **Arquivos**: tudo minúsculo (snake_case)
- **Classes**: CamelCase

- **Métodos e variáveis**: snake_case (devem ser sugestivos)
