# /// \file CMakeLists.txt - m4rc3lo 2025-08-23
# /// \brief Arquivo principal de configuração do CMake para o projeto pdi_code.
# /// \details Este script prepara a árvore de fontes (com subdiretórios),
# ///          seleciona um arquivo principal em app/ com a função main(),
# ///          localiza OpenCV, configura o padrão C++17 e emite informações
# ///          detalhadas de ambiente (CMake, compilador, OpenCV e Qt, se houver).

cmake_minimum_required(VERSION 3.16)
# /// \brief Define a versão mínima do CMake.
# /// \note 3.16 é amplamente suportada em MSYS2/UCRT64 e Linux atuais.


project(pdi_code VERSION 0.1.2 LANGUAGES C CXX)
# /// \brief Declara o projeto, versão e linguagem.

# ---------------------- Padrão e flags de compilação -------------------------


set(CMAKE_CXX_STANDARD 17)
# /// \brief Seleciona o padrão C++ (C++17).

set(CMAKE_CXX_STANDARD_REQUIRED ON)
# /// \brief Torna obrigatório o padrão definido.

set(CMAKE_CXX_EXTENSIONS OFF)
# /// \brief Desabilita extensões do compilador, mantendo C++ “puro”.

option(PDI_ENABLE_WARNINGS "Habilita avisos de compilação adicionais" ON)
# /// \brief Opção para ativar flags de aviso mais estritas (boas práticas).

if(PDI_ENABLE_WARNINGS)
  if(MSVC)
    add_compile_options(/W4)
    # /// \note /W4 = alto nível de avisos no MSVC.
  else()
    add_compile_options(-Wall -Wextra -Wpedantic)
    # /// \note Conjunto clássico de avisos em GCC/Clang.
  endif()
endif()

# ---------------------- Dependências (OpenCV) --------------------------------

find_package(OpenCV REQUIRED)
# /// \brief Localiza o OpenCV instalado.
# /// \note Usa variáveis: OpenCV_INCLUDE_DIRS, OpenCV_LIBS, etc.

# ---------------------- Diretórios do projeto --------------------------------

set(PDI_ROOT_DIR        ${PROJECT_SOURCE_DIR})
# /// \brief Raiz do projeto (diretório contendo este CMakeLists.txt).

set(PDI_INCLUDE_DIR     ${PDI_ROOT_DIR}/include)
# /// \brief Diretório de cabeçalhos públicos (com possíveis subpastas).

set(PDI_SOURCE_DIR      ${PDI_ROOT_DIR}/src)
# /// \brief Diretório de fontes principais (com possíveis subpastas).

set(PDI_APP_DIR         ${PDI_ROOT_DIR}/app)
# /// \brief Diretório dos “drivers”/aplicativos (arquivos com main()).

set(PDI_DATA_DIR        ${PDI_ROOT_DIR}/data)
# /// \brief Diretório de dados (imagens de teste etc.). Não compila.

# ---------------------- Arquivo principal (main) -----------------------------

# /// \brief Define o arquivo com função main() a ser compilado.
# /// \details Caminho relativo à raiz do projeto (ex.: "app/run.cpp").
# /// \note Use a GUI/ccmake para trocar facilmente entre diferentes mains.
set(MAIN_FILE "app/run.cpp" CACHE STRING "Arquivo principal com o ponto de entrada do progrma int main(...)")

# /// \brief Normaliza o caminho do MAIN_FILE para absoluto e valida existência.
if(NOT IS_ABSOLUTE "${MAIN_FILE}")
  set(MAIN_FILE_ABS "${PDI_ROOT_DIR}/${MAIN_FILE}")
else()
  set(MAIN_FILE_ABS "${MAIN_FILE}")
endif()

if(NOT EXISTS "${MAIN_FILE_ABS}")
  message(FATAL_ERROR "MAIN_FILE não encontrado: ${MAIN_FILE_ABS}")
endif()

# ---------------------- Coleta recursiva de fontes ---------------------------

# /// \brief Agrega, de forma recursiva, todos os .cpp em src/.
# /// \details CONFIGURE_DEPENDS faz o CMake reconfigurar ao detectar novos arquivos.
file(GLOB_RECURSE SRC_CORE CONFIGURE_DEPENDS
  ${PDI_SOURCE_DIR}/*.cpp
)

# /// \brief Conjunto final de fontes = fontes do núcleo + arquivo principal.
set(SRC_FILES
  ${SRC_CORE}
  ${MAIN_FILE_ABS}
)

# ---------------------- Executável -------------------------------------------

add_executable(${PROJECT_NAME} ${SRC_FILES})
# /// \brief Cria o binário principal do projeto.

# ---------------------- Includes por alvo ------------------------------------

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${OpenCV_INCLUDE_DIRS}
  PUBLIC
    ${PDI_INCLUDE_DIR}
)
# /// \brief Define diretórios de cabeçalhos.
# /// \param PRIVATE OpenCV somente para este alvo.
# /// \param PUBLIC  Exponibiliza include/ para consumidores, se houver.

# ---------------------- Vinculação de bibliotecas ----------------------------

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    ${OpenCV_LIBS}
)
# /// \brief Liga o executável às libs do OpenCV.

# ---------------------- Organização em IDEs ----------------------------------

source_group(TREE ${PDI_ROOT_DIR} FILES ${SRC_FILES})
# /// \brief Mostra a árvore real de pastas na IDE (útil para subdiretórios).

# ---------------------- Definições de plataforma (opcional) ------------------

if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX)
  # /// \brief Evita conflitos de macros min/max no Windows.
endif()

# ---------------------- (Opcional) Detecção de Qt ----------------------------

# /// \brief Tenta detectar Qt5 ou Qt6; não é obrigatório ao projeto.
find_package(QT NAMES Qt6 Qt5 QUIET)
if(QT_FOUND)
  find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core QUIET)
  # /// \note Tentamos extrair um identificador de versão do módulo Core.
  if(DEFINED Qt${QT_VERSION_MAJOR}Core_VERSION)
    set(QT_REPORTED_VERSION "${Qt${QT_VERSION_MAJOR}Core_VERSION}")
  elseif(DEFINED QT_VERSION)
    set(QT_REPORTED_VERSION "${QT_VERSION}")
  else()
    set(QT_REPORTED_VERSION "Qt${QT_VERSION_MAJOR} (versão específica não encontrada)")
  endif()
else()
  set(QT_REPORTED_VERSION "não encontrado")
endif()

# ---------------------- Mensagens informativas -------------------------------

# /// \brief Caminhos relativos/absolutos para log.
file(RELATIVE_PATH MAIN_FILE_REL "${PDI_ROOT_DIR}" "${MAIN_FILE_ABS}")

message(STATUS "==================== Informações do Build ====================")
message(STATUS "Projeto:                ${PROJECT_NAME}")
message(STATUS "Raiz do projeto:        ${PDI_ROOT_DIR}")
message(STATUS "Include (público):      ${PDI_INCLUDE_DIR}")
message(STATUS "Fonte (núcleo):         ${PDI_SOURCE_DIR}")
message(STATUS "App (mains):            ${PDI_APP_DIR}")
message(STATUS "Arquivo main ativo:     ${MAIN_FILE_REL}")
message(STATUS "Arquivo main (absoluto):${MAIN_FILE_ABS}")
message(STATUS "--------------------------------------------------------------")
message(STATUS "CMake:                  ${CMAKE_VERSION}")
message(STATUS "Compilador C++:         ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Caminho do compilador:  ${CMAKE_CXX_COMPILER}")
message(STATUS "OpenCV include:         ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libs:            ${OpenCV_LIBS}")
message(STATUS "Qt:                     ${QT_REPORTED_VERSION}")
message(STATUS "==============================================================")
