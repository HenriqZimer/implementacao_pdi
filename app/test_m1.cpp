/**
 * @file test_m1.cpp
 * @brief Aplicativo de teste completo para todas as funcionalidades da M1.1
 * @details
 *   Este executável demonstra todas as operações implementadas:
 *   - Conversão para tons de cinza (média aritmética e ponderada)
 *   - Operações aritméticas (imagem-imagem e imagem-escalar)
 *   - Limiarização (vários tipos)
 *   - Isolamento de canais de cores
 *   - Histogramas (computação e visualização)
 *   - Inversão de imagem
 *
 * @author PDI 2025 - M1.1 Implementation
 * @date 2025-08-27
 * @version 1.0.0
 */

#include <iostream>
#include <opencv2/opencv.hpp>

// Inclui todos os módulos implementados
#include "imageinfo.hpp"
#include "conv/grayscale.hpp"
#include "conv/channel_isolator.hpp"
#include "arit/arithmetic.hpp"
#include "thre/threshold.hpp"
#include "histo/histogram.hpp"

/**
 * @brief Demonstra conversões para tons de cinza
 */
void demo_grayscale_conversion(const cv::Mat& image)
{
  std::cout << "\n=== DEMONSTRACAO: CONVERSAO PARA TONS DE CINZA ===" << std::endl;

  GrayScale converter(image);

  // Média aritmética
  cv::Mat gray_arithmetic = converter.get_gray_arithmetic();
  ImageInfo::image_show(gray_arithmetic, "Tons de Cinza - Media Aritmetica");
  cv::imshow("Original", image);
  cv::imshow("Gray - Media Aritmetica", gray_arithmetic);

  // Média ponderada
  cv::Mat gray_weighted = converter.get_gray_weighted();
  ImageInfo::image_show(gray_weighted, "Tons de Cinza - Media Ponderada");
  cv::imshow("Gray - Media Ponderada", gray_weighted);

  std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();
}

/**
 * @brief Demonstra operações aritméticas
 */
void demo_arithmetic_operations(const cv::Mat& image)
{
  std::cout << "\n=== DEMONSTRACAO: OPERACOES ARITMETICAS ===" << std::endl;

  ArithmeticOperations arith;

  // Operações com escalar
  cv::Mat brightened = arith.add_scalar(image, 50);
  cv::Mat darkened = arith.subtract_scalar(image, 50);
  cv::Mat enhanced = arith.multiply_scalar(image, 1.5);
  cv::Mat reduced = arith.divide_scalar(image, 2.0);

  cv::imshow("Original", image);
  cv::imshow("Mais Claro (+50)", brightened);
  cv::imshow("Mais Escuro (-50)", darkened);
  cv::imshow("Realcado (*1.5)", enhanced);

  std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();

  // Operações entre imagens (usando a própria imagem)
  cv::Mat sum_result = arith.add_images(image, brightened);
  cv::Mat diff_result = arith.subtract_images(image, darkened);

  cv::imshow("Original", image);
  cv::imshow("Soma com versao clara", sum_result);
  cv::imshow("Diferenca com versao escura", diff_result);

  std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();
}

/**
 * @brief Demonstra operações de limiarização
 */
void demo_threshold_operations(const cv::Mat& image)
{
  std::cout << "\n=== DEMONSTRACAO: LIMIARIZACAO ===" << std::endl;

  ThresholdOperations thresh;

  // Converte para tons de cinza primeiro
  GrayScale converter(image);
  cv::Mat gray = converter.get_gray_arithmetic();

  // Diferentes tipos de limiarização
  cv::Mat binary = thresh.binary_threshold(gray, 128);
  cv::Mat binary_inv = thresh.binary_threshold_inv(gray, 128);
  cv::Mat truncate = thresh.truncate_threshold(gray, 128);
  cv::Mat to_zero = thresh.to_zero_threshold(gray, 128);

  cv::imshow("Original (Cinza)", gray);
  cv::imshow("Binaria (limiar=128)", binary);
  cv::imshow("Binaria Invertida", binary_inv);
  cv::imshow("Truncada", truncate);
  cv::imshow("To Zero", to_zero);

  std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();

  // Limiarização em imagem colorida
  cv::Mat color_binary = thresh.binary_threshold_color(image, 128);
  cv::imshow("Original (Colorida)", image);
  cv::imshow("Limiarizacao Colorida", color_binary);

  std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();
}

/**
 * @brief Demonstra isolamento de canais de cores
 */
void demo_channel_isolation(const cv::Mat& image)
{
  std::cout << "\n=== DEMONSTRACAO: ISOLAMENTO DE CANAIS ===" << std::endl;

  ChannelIsolator isolator;

  // Extração de canais como tons de cinza
  cv::Mat blue_channel = isolator.extract_blue_channel(image);
  cv::Mat green_channel = isolator.extract_green_channel(image);
  cv::Mat red_channel = isolator.extract_red_channel(image);

  cv::imshow("Original", image);
  cv::imshow("Canal Azul", blue_channel);
  cv::imshow("Canal Verde", green_channel);
  cv::imshow("Canal Vermelho", red_channel);

  std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();

  // Isolamento de canais (mantém colorido)
  cv::Mat only_blue = isolator.isolate_blue_channel(image);
  cv::Mat only_green = isolator.isolate_green_channel(image);
  cv::Mat only_red = isolator.isolate_red_channel(image);

  cv::imshow("Original", image);
  cv::imshow("Apenas Azul", only_blue);
  cv::imshow("Apenas Verde", only_green);
  cv::imshow("Apenas Vermelho", only_red);

  std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();

  // Inversão de imagem
  cv::Mat inverted = isolator.invert_image(image);
  cv::imshow("Original", image);
  cv::imshow("Invertida", inverted);

  std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();
}

/**
 * @brief Demonstra computação e visualização de histogramas
 */
void demo_histogram_processing(const cv::Mat& image)
{
  std::cout << "\n=== DEMONSTRACAO: HISTOGRAMAS ===" << std::endl;

  HistogramProcessor hist_proc;

  // Histograma de imagem colorida
  cv::Mat color_hist_viz = hist_proc.visualize_histogram_color(image);
  cv::imshow("Original", image);
  cv::imshow("Histograma Colorido (B=Azul, G=Verde, R=Vermelho)", color_hist_viz);

  std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();

  // Histograma de imagem em tons de cinza
  GrayScale converter(image);
  cv::Mat gray = converter.get_gray_arithmetic();
  cv::Mat gray_hist_viz = hist_proc.visualize_histogram_gray(gray);

  cv::imshow("Imagem Cinza", gray);
  cv::imshow("Histograma Tons de Cinza", gray_hist_viz);

  // Mostra estatísticas
  std::vector<int> gray_hist = hist_proc.compute_histogram_gray(gray);
  int min_val, max_val;
  double mean_val;
  hist_proc.compute_histogram_stats(gray_hist, min_val, max_val, mean_val);

  std::cout << "Estatisticas do histograma em tons de cinza:" << std::endl;
  std::cout << "  Minimo: " << min_val << std::endl;
  std::cout << "  Maximo: " << max_val << std::endl;
  std::cout << "  Media: " << mean_val << std::endl;

  std::cout << "Pressione qualquer tecla para finalizar..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();
}

/**
 * @brief Função principal do programa de teste
 */
int main(int argc, char** argv)
{
    // Limpa o terminal
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif

  std::cout << "===================================================" << std::endl;
  std::cout << "   TESTE COMPLETO - PDI M1.1 IMPLEMENTACAO" << std::endl;
  std::cout << "===================================================" << std::endl;
  std::cout << "Algoritmos implementados:" << std::endl;
  std::cout << "- Conversao para Tons de Cinza (Media Aritmetica e Ponderada)" << std::endl;
  std::cout << "- Operacoes Aritmeticas (Imagem-Imagem e Imagem-Escalar)" << std::endl;
  std::cout << "- Limiarizacao (tons de cinza e colorida)" << std::endl;
  std::cout << "- Isolamento de Canais de Cores (R/G/B)" << std::endl;
  std::cout << "- Histograma (computacao e visualizacao)" << std::endl;
  std::cout << "- Inverso da imagem" << std::endl;
  std::cout << "===================================================" << std::endl;

  // Carrega a imagem
  cv::Mat image = cv::imread("../data/ave-02.jpeg", cv::IMREAD_COLOR);

  if (image.empty())
  {
    std::cerr << "Erro ao carregar a imagem ../data/ave-02.jpeg!" << std::endl;
    std::cerr << "Verifique se o arquivo existe no diretorio data/" << std::endl;
    return EXIT_FAILURE;
  }

  // Mostra informações da imagem
  ImageInfo::image_show(image, "Imagem de Teste");

  // Executa todas as demonstrações
  demo_grayscale_conversion(image);
  demo_arithmetic_operations(image);
  demo_threshold_operations(image);
  demo_channel_isolation(image);
  demo_histogram_processing(image);

  std::cout << "\n===================================================" << std::endl;
  std::cout << "   TESTE CONCLUIDO COM SUCESSO!" << std::endl;
  std::cout << "   Todos os algoritmos da M1.1 foram demonstrados." << std::endl;
  std::cout << "===================================================" << std::endl;

  return EXIT_SUCCESS;
}
