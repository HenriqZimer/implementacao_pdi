# Instruções de Compilação e Execução - PDI M1.1

## Pré-requisitos

### Sistema Operacional:
- **Linux** (Ubuntu/Debian recomendado)
- **Windows** com MSYS2/MinGW
- **macOS** com Homebrew

### Dependências Obrigatórias:
- **C++ Compiler** com suporte a C++17 (g++ 7.0+ ou clang++ 5.0+)
- **OpenCV 4.x** (com modules: core, imgproc, imgcodecs, highgui)

### Dependências Opcionais:
- **CMake 3.16+** (para build automatizado)
- **pkg-config** (para compilação manual simplificada)

## Instalação das Dependências

### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential cmake pkg-config
sudo apt install libopencv-dev
```

### MSYS2 (Windows):
```bash
pacman -S mingw-w64-ucrt-x86_64-gcc 
pacman -S mingw-w64-ucrt-x86_64-cmake 
pacman -S mingw-w64-ucrt-x86_64-opencv
```

### macOS:
```bash
brew install cmake pkg-config opencv
```

## Métodos de Compilação

### Método 1: CMake (Recomendado)

#### Para o programa de teste completo:
```bash
# Configuração
cmake -S . -B build -DMAIN_FILE="app/test_m1.cpp"

# Compilação
cmake --build build

# Execução
cd build && ./pdi_code
```

#### Para o programa principal:
```bash
cmake -S . -B build -DMAIN_FILE="app/run.cpp"
cmake --build build
cd build && ./pdi_code
```

#### Para a demonstração simples:
```bash
cmake -S . -B build -DMAIN_FILE="app/demo_simple.cpp"
cmake --build build
cd build && ./pdi_code
```

### Método 2: Makefile Manual

```bash
# Compila todos os executáveis
make all

# Executa o teste completo
make test

# Executa o programa principal
make run

# Limpeza
make clean
```

### Método 3: Compilação Manual

#### Teste completo (recomendado para demonstração):
```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic \
    -Iinclude `pkg-config --cflags opencv4` \
    src/imageinfo.cpp \
    src/conv/grayscale.cpp \
    src/conv/channel_isolator.cpp \
    src/arit/arithmetic.cpp \
    src/thre/threshold.cpp \
    src/histo/histogram.cpp \
    app/test_m1.cpp \
    -o pdi_test_m1 \
    `pkg-config --libs opencv4`
```

#### Demonstração simples:
```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic \
    -Iinclude `pkg-config --cflags opencv4` \
    src/imageinfo.cpp \
    src/conv/grayscale.cpp \
    src/conv/channel_isolator.cpp \
    src/arit/arithmetic.cpp \
    src/thre/threshold.cpp \
    src/histo/histogram.cpp \
    app/demo_simple.cpp \
    -o pdi_demo \
    `pkg-config --libs opencv4`
```

## Execução

### Preparação:
1. Certifique-se de que há imagens na pasta `data/`
2. O programa espera encontrar `data/ave-02.jpeg` por padrão
3. Você pode usar suas próprias imagens modificando o caminho no código

### Execução dos Programas:

#### Teste Completo (Interativo):
```bash
./pdi_test_m1
```
- Demonstra todas as funcionalidades implementadas
- Interativo: pressione teclas para avançar entre demonstrações
- Exibe janelas com resultados visuais

#### Demonstração Simples (Automática):
```bash
./pdi_demo
```
- Demonstração rápida das principais funcionalidades
- Exibe todas as janelas simultaneamente
- Pressione qualquer tecla para finalizar

#### Programa Principal:
```bash
./pdi_code  # ou ./pdi_run se usando Makefile
```
- Programa original do projeto
- Demonstra conversão para tons de cinza

## Estrutura de Imagens

### Pasta de Dados:
```
data/
├── ave-01.jpeg
├── ave-02.jpeg    # Imagem principal usada nos testes
├── ave-03.jpeg
└── [suas_imagens...]
```

### Formatos Suportados:
- JPEG (.jpg, .jpeg)
- PNG (.png)
- BMP (.bmp)
- TIFF (.tiff)
- E outros formatos suportados pelo OpenCV

## Solução de Problemas

### Erro "cmake: command not found":
- **Solução**: Instale o CMake ou use compilação manual
```bash
# Ubuntu/Debian
sudo apt install cmake

# MSYS2
pacman -S mingw-w64-ucrt-x86_64-cmake
```

### Erro "opencv not found":
- **Solução**: Instale o OpenCV development headers
```bash
# Ubuntu/Debian
sudo apt install libopencv-dev

# MSYS2
pacman -S mingw-w64-ucrt-x86_64-opencv
```

### Erro "pkg-config not found":
- **Solução**: Use flags manuais do OpenCV
```bash
g++ -std=c++17 -I/usr/include/opencv4 \
    [arquivos...] \
    -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui
```

### Erro "Imagem não encontrada":
- **Solução**: Verifique o caminho da imagem
- Certifique-se de executar o programa a partir do diretório correto
- Copie suas imagens para a pasta `data/`

### Erro de compilação C++17:
- **Solução**: Use um compilador mais recente
```bash
# Verificar versão do g++
g++ --version

# Deve ser 7.0 ou superior para C++17
```

## Verificação da Instalação

### Teste Rápido do OpenCV:
```bash
pkg-config --modversion opencv4
pkg-config --cflags opencv4
pkg-config --libs opencv4
```

### Teste de Compilação Mínima:
```bash
echo '#include <opencv2/opencv.hpp>
int main() { 
    cv::Mat img; 
    std::cout << "OpenCV funciona!" << std::endl; 
    return 0; 
}' > test_opencv.cpp

g++ -std=c++17 test_opencv.cpp -o test_opencv `pkg-config --cflags --libs opencv4`
./test_opencv
```

## Execução Recomendada para Apresentação

Para a apresentação da M1.1, recomenda-se:

1. **Compilar o teste completo**:
```bash
make test  # ou cmake + test_m1.cpp
```

2. **Preparar imagens de teste**:
   - Pelo menos 3 imagens diferentes na pasta `data/`
   - Incluir imagens com diferentes características (clara, escura, colorida)

3. **Executar demonstração**:
```bash
./pdi_test_m1
```

4. **Mostrar código-fonte** dos principais algoritmos durante a apresentação

## Estrutura Final do Projeto

```
pdi_code/
├── CMakeLists.txt         # Build automático
├── Makefile              # Build manual
├── README.md             # Documentação básica
├── DOCUMENTACAO.md       # Documentação detalhada
├── INSTRUCOES.md         # Este arquivo
├── include/              # Headers
│   ├── imageinfo.hpp
│   ├── arit/arithmetic.hpp
│   ├── conv/grayscale.hpp
│   ├── conv/channel_isolator.hpp
│   ├── histo/histogram.hpp
│   └── thre/threshold.hpp
├── src/                  # Implementações
│   ├── imageinfo.cpp
│   ├── arit/arithmetic.cpp
│   ├── conv/grayscale.cpp
│   ├── conv/channel_isolator.cpp
│   ├── histo/histogram.cpp
│   └── thre/threshold.cpp
├── app/                  # Programas principais
│   ├── run.cpp           # Original
│   ├── test_m1.cpp       # Teste completo
│   └── demo_simple.cpp   # Demo simples
└── data/                 # Imagens de teste
    ├── ave-01.jpeg
    ├── ave-02.jpeg
    └── ave-03.jpeg
```

Todos os algoritmos solicitados na M1.1 estão implementados e funcionais!
