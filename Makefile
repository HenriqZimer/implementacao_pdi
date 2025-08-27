# Makefile para compilação manual do projeto PDI M1.1
# Use este arquivo caso o CMake não esteja disponível

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
OPENCV_CFLAGS = `pkg-config --cflags opencv4`
OPENCV_LIBS = `pkg-config --libs opencv4`

# Diretórios
SRCDIR = src
INCDIR = include
APPDIR = app
BUILDDIR = build_manual

# Arquivos fonte
SOURCES = $(SRCDIR)/imageinfo.cpp \
          $(SRCDIR)/conv/grayscale.cpp \
          $(SRCDIR)/conv/channel_isolator.cpp \
          $(SRCDIR)/arit/arithmetic.cpp \
          $(SRCDIR)/thre/threshold.cpp \
          $(SRCDIR)/histo/histogram.cpp

# Objetos
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Executáveis
TARGET_RUN = $(BUILDDIR)/pdi_run
TARGET_NO_GUI = $(BUILDDIR)/pdi_no_gui

.PHONY: all clean run no-gui run-test help

all: $(TARGET_RUN) $(TARGET_NO_GUI)

# Executável principal (run.cpp)
$(TARGET_RUN): $(OBJECTS) $(BUILDDIR)/run.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(OPENCV_LIBS)

# Executável sem GUI (test_no_gui.cpp)
$(TARGET_NO_GUI): $(OBJECTS) $(BUILDDIR)/test_no_gui.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(OPENCV_LIBS)

# Regra para objetos dos fontes principais
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $(OPENCV_CFLAGS) -c $< -o $@

# Regra para objeto do run.cpp
$(BUILDDIR)/run.o: $(APPDIR)/run.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $(OPENCV_CFLAGS) -c $< -o $@

# Regra para objeto do test_no_gui.cpp
$(BUILDDIR)/test_no_gui.o: $(APPDIR)/test_no_gui.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $(OPENCV_CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(BUILDDIR)

# Execução dos programas
run: $(TARGET_RUN)
	cd $(BUILDDIR) && QT_LOGGING_RULES="*=false" ./pdi_run ../data/ave-02.jpeg

no-gui: $(TARGET_NO_GUI)
	cd $(BUILDDIR) && ./pdi_no_gui

# Target conveniente para executar teste completo sem GUI
run-test: no-gui

# Ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make all      - Compila todos os executáveis"
	@echo "  make run      - Compila e executa o programa principal (com imagem padrão)"
	@echo "  make no-gui   - Compila e executa teste sem interface gráfica"
	@echo "  make run-test - Alias para make no-gui (recomendado para WSL)"
	@echo "  make clean    - Remove arquivos de compilação"
	@echo "  make help     - Mostra esta ajuda"
	@echo ""
	@echo "Recomendado para WSL/terminal: make run-test"
	@echo ""
	@echo "Observação: O aviso QStandardPaths foi suprimido no make run"
