/**
 * @file demo_simple.cpp
 * @brief Demonstração simples das funcionalidades principais
 * @details
 *   Programa de demonstração simplificado que mostra as principais
 *   funcionalidades implementadas na M1.1 de forma mais concisa.
 */

#include <iostream>
#include <opencv2/opencv.hpp>

#include "imageinfo.hpp"
#include "conv/grayscale.hpp"
#include "conv/channel_isolator.hpp"
#include "arit/arithmetic.hpp"
#include "thre/threshold.hpp"
#include "histo/histogram.hpp"

int main()
{
    std::cout << "=== PDI M1.1 - Demonstracao Simples ===" << std::endl;

    // Carrega imagem
    cv::Mat image = cv::imread("../data/ave-02.jpeg", cv::IMREAD_COLOR);
    if (image.empty())
    {
        std::cerr << "Erro: Não foi possível carregar a imagem!" << std::endl;
        std::cerr << "Certifique-se de que o arquivo ../data/ave-02.jpeg existe." << std::endl;
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!" << std::endl;
    ImageInfo::image_show(image, "Imagem Original");

    // 1. Conversão para tons de cinza
    std::cout << "\n1. Convertendo para tons de cinza..." << std::endl;
    GrayScale converter(image);
    cv::Mat gray_arithmetic = converter.get_gray_arithmetic();
    cv::Mat gray_weighted = converter.get_gray_weighted();

    // 2. Operações aritméticas
    std::cout << "2. Aplicando operações aritméticas..." << std::endl;
    ArithmeticOperations arith;
    cv::Mat brightened = arith.add_scalar(image, 50);
    cv::Mat enhanced = arith.multiply_scalar(image, 1.2);

    // 3. Limiarização
    std::cout << "3. Aplicando limiarização..." << std::endl;
    ThresholdOperations thresh;
    cv::Mat binary = thresh.binary_threshold(gray_arithmetic, 128);

    // 4. Isolamento de canais
    std::cout << "4. Isolando canais de cores..." << std::endl;
    ChannelIsolator isolator;
    cv::Mat red_channel = isolator.extract_red_channel(image);
    cv::Mat inverted = isolator.invert_image(image);

    // 5. Histograma
    std::cout << "5. Computando histogramas..." << std::endl;
    HistogramProcessor hist_proc;
    cv::Mat hist_viz = hist_proc.visualize_histogram_color(image);
    cv::Mat gray_hist_viz = hist_proc.visualize_histogram_gray(gray_arithmetic);

    // Exibe resultados
    std::cout << "\nExibindo resultados..." << std::endl;
    cv::imshow("Original", image);
    cv::imshow("Cinza (Aritmetica)", gray_arithmetic);
    cv::imshow("Cinza (Ponderada)", gray_weighted);
    cv::imshow("Mais Clara (+50)", brightened);
    cv::imshow("Realcada (*1.2)", enhanced);
    cv::imshow("Binaria (limiar=128)", binary);
    cv::imshow("Canal Vermelho", red_channel);
    cv::imshow("Invertida", inverted);
    cv::imshow("Histograma Colorido", hist_viz);
    cv::imshow("Histograma Cinza", gray_hist_viz);

    std::cout << "\nPressione qualquer tecla para sair..." << std::endl;
    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "\nDemonstracao concluida com sucesso!" << std::endl;
    std::cout << "Todas as funcionalidades da M1.1 foram implementadas:" << std::endl;
    std::cout << "✓ Conversao para tons de cinza (media aritmetica e ponderada)" << std::endl;
    std::cout << "✓ Operacoes aritmeticas (imagem-imagem e imagem-escalar)" << std::endl;
    std::cout << "✓ Limiarizacao (binaria, invertida, truncada, to-zero)" << std::endl;
    std::cout << "✓ Isolamento de canais de cores (R, G, B)" << std::endl;
    std::cout << "✓ Histogramas (computacao e visualizacao)" << std::endl;
    std::cout << "✓ Inverso da imagem" << std::endl;

    return 0;
}
