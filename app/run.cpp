/**
 * @file run.cpp
 * @brief Ponto de entrada da aplicação para demonstrações da M1 (domínio do valor).
 * @details
 *   Este executável realiza uma carga de múltiplas imagens coloridas, converte para escala de cinza
 *   por meio da classe @c GrayScale e apresenta cada par em janelas do OpenCV. O objetivo pedagógico é
 *   exercitar a cadeia de aquisição, pré-processamento (conversão para tons de cinza) e
 *   visualização, alinhado aos conteúdos introdutórios de Processamento de Imagens.
 *
 *   ### Fluxo geral
 *   1. Limpeza do terminal (ambiente POSIX) para facilitar a leitura do log.
 *   2. Mensagem de abertura contextualizando a execução.
 *   3. Loop através de todas as imagens em data/ (ave-01, ave-02, ave-03).
 *   4. Para cada imagem: leitura, validação, conversão e exibição.
 *   5. Pausa entre cada imagem para visualização comparativa.
 *   6. Limpeza de janelas antes da próxima imagem.
 *
 *   ### Dependências principais
 *   - OpenCV (núcleo e módulos de alto nível para leitura/exibição).
 *   - Módulos internos: @c conv/grayscale.hpp e @c imageinfo.hpp .
 *
 *   ### Observações importantes
 *   - Os caminhos das imagens são relativos ao executável: @c ../data/ .
 *     Ajuste conforme a estrutura do seu CMake/instalação.
 *   - A chamada @c system("clear") é específica para ambientes tipo Unix (Linux/macOS).
 *     Em Windows, o equivalente seria @c system("cls") . Recomenda-se condicional de compilação
 *     para portabilidade.
 *   - As janelas são nomeadas dinamicamente e fechadas entre imagens para evitar sobreposição.
 *   - Se uma imagem falhar ao carregar, o programa continua com as próximas ao invés de encerrar.
 *
 * @author
 *   Disciplina de Processamento de Imagens — Univali (exemplo didático).
 * @date 2025-08-26
 * @version 0.1.2
 * @copyright
 *   Código educacional para fins acadêmicos. Sem garantias.
 */

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "conv/grayscale.hpp"
#include "imageinfo.hpp"
/**
 * @brief Função principal.
 *
 * @param argc Número de argumentos de linha de comando.
 * @param argv Vetor de strings C contendo os argumentos. (Não utilizado neste exemplo).
 * @return int Código de status do processo:
 *   - @c EXIT_SUCCESS em caso de execução bem-sucedida.
 *   - @c EXIT_FAILURE se ocorrer falha na leitura de imagem.
 *
 * @post
 *   - Duas janelas do OpenCV são criadas na tela: uma com a imagem colorida e outra com a versão em escala de cinza.
 *   - O processo permanece bloqueado até uma tecla ser pressionada (via @c cv::waitKey ).
 *
 * @throws Não lança exceções C++ explicitamente; falhas críticas resultam em término com @c EXIT_FAILURE .
 *
 * @note
 *   Este exemplo pressupõe que as classes @c GrayScale e @c ImageInfo sigam o padrão de escrita
 *   solicitado na disciplina curso (nomes de classes em @b CamelCase ; métodos/variáveis em @b snake_case ).
 *   A interface pública mínima utilizada aqui é:
 *   - @c GrayScale::GrayScale(const cv::Mat& src)
 *   - @c GrayScale::get_gray() const -> @c cv::Mat
 *   - @c ImageInfo::image_show(const cv::Mat& img, const std::string& title)
 *
 * @see GrayScale, ImageInfo, cv::Mat, cv::imshow, cv::imread
 */
int main(int argc, char** argv)
{
    // Suprime warnings de parâmetros não utilizados
    (void)argc;
    (void)argv;
    // (Portabilidade) Limpa o terminal em sistemas POSIX para manter o log legível.
    // Em Windows prefira: system("cls"); Considere proteger com #ifdef _WIN32 / #else / #endif.  
    system("clear");

    // Contexto da execução: módulo e eixo de conteúdo.
    std::cout << "Implementacoes M1 (dominio do valor)" << std::endl;

    /**
    cv::Mat image = cv::Mat::zeros(300, 600, CV_8UC3);
    cv::putText(image, "OpenCV Funcionando!", cv::Point(100, 150),
               cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
    */

    /**
     * @brief Exemplo alternativo: geração de imagem sintética e escrita de texto.
     * @details
     *   Mantido aqui apenas como referência didática. Pode ser habilitado para testar
     *   a renderização sem depender de arquivos externos.
     *
     * @code
     * cv::Mat image = cv::Mat::zeros(300, 600, CV_8UC3);
     * cv::putText(image, "OpenCV Funcionando!", cv::Point(100, 150),
     *             cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
     * @endcode
     */

    // 1) Lista de imagens para processamento (todas as imagens disponíveis)
    std::vector<std::string> image_paths = {
        "../data/ave-01.jpeg",
        "../data/ave-02.jpeg",
        "../data/ave-03.jpeg",
        "../data/blobs-image.jpg"
    };

    std::vector<std::string> image_names = {
        "Ave 01",
        "Ave 02",
        "Ave 03",
        "Blobs Image"
    };

    // 2) Processa cada imagem da lista
    for (size_t i = 0; i < image_paths.size(); ++i)
    {
        std::cout << "Processando " << image_names[i] << "..." << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;

        // Aquisição: leitura de imagem colorida em BGR
        cv::Mat image = cv::imread(image_paths[i], cv::IMREAD_COLOR);

        // Validação: verifica se a leitura foi bem-sucedida
        if (image.empty())
        {
            std::cerr << "Erro ao carregar a imagem: " << image_paths[i] << std::endl;
            continue; // Pula para próxima imagem ao invés de encerrar
        }

        // Inspeção/Exibição: mostra informações da imagem
        ImageInfo::image_show(image, image_names[i]);

        // Pré-processamento: conversão para tons de cinza
        GrayScale to_gray = GrayScale(image);
        cv::Mat gray_image = cv::Mat(to_gray.get_gray());

        // Visualização: janelas nomeadas para cada imagem
        std::string color_window = image_names[i] + " - Original";
        std::string gray_window = image_names[i] + " - Escala de Cinza";

        cv::imshow(color_window, image);
        cv::imshow(gray_window, gray_image);

        std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
        std::cout << std::endl;

        // Pausa para visualização de cada par de imagens
        cv::waitKey(0);

        // Fecha as janelas antes de processar a próxima imagem
        cv::destroyWindow(color_window);
        cv::destroyWindow(gray_window);
    }

    std::cout << "Processamento de todas as imagens concluído!" << std::endl;

    // Encerramento bem-sucedido.
    exit(EXIT_SUCCESS);
}