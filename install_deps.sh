#!/bin/bash

# Script de instalação das dependências para PDI M1.1
# Execute este script no terminal WSL Ubuntu

echo "=== Instalação das Dependências - PDI M1.1 ==="
echo ""

echo "Verificando se as dependências já estão instaladas..."

# Verifica g++
if command -v g++ &> /dev/null; then
    echo "✓ g++ já está instalado: $(g++ --version | head -n1)"
else
    echo "✗ g++ não encontrado"
    NEED_INSTALL=true
fi

# Verifica make
if command -v make &> /dev/null; then
    echo "✓ make já está instalado: $(make --version | head -n1)"
else
    echo "✗ make não encontrado"
    NEED_INSTALL=true
fi

# Verifica pkg-config
if command -v pkg-config &> /dev/null; then
    echo "✓ pkg-config já está instalado: $(pkg-config --version)"
else
    echo "✗ pkg-config não encontrado"
    NEED_INSTALL=true
fi

# Verifica OpenCV
if pkg-config --exists opencv4 2>/dev/null; then
    echo "✓ OpenCV já está instalado: $(pkg-config --modversion opencv4)"
else
    echo "✗ OpenCV não encontrado"
    NEED_INSTALL=true
fi

if [ "$NEED_INSTALL" = true ]; then
    echo ""
    echo "Algumas dependências precisam ser instaladas."
    echo "Execute os seguintes comandos:"
    echo ""
    echo "sudo apt update"
    echo "sudo apt install build-essential make pkg-config libopencv-dev -y"
    echo ""
    echo "Após a instalação, execute novamente este script para verificar."
else
    echo ""
    echo "✓ Todas as dependências estão instaladas!"
    echo ""
    echo "Testando compilação..."
    
    # Teste simples de compilação
    cat > test_opencv.cpp << 'EOF'
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    cv::Mat img = cv::Mat::zeros(100, 100, CV_8UC3);
    std::cout << "Teste de OpenCV: OK!" << std::endl;
    return 0;
}
EOF

    echo "Compilando teste..."
    if g++ -std=c++17 test_opencv.cpp -o test_opencv $(pkg-config --cflags --libs opencv4) 2>/dev/null; then
        echo "✓ Compilação de teste: OK"
        ./test_opencv
        rm -f test_opencv test_opencv.cpp
        echo ""
        echo "Sistema pronto para compilar o projeto PDI!"
        echo "Execute: make run  ou  make test"
    else
        echo "✗ Erro na compilação de teste"
        echo "Verifique se todas as dependências estão corretamente instaladas."
    fi
fi
