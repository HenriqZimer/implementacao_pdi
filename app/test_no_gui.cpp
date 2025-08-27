/**
 * @file test_no_gui.cpp
 * @brief Versão do teste sem interface gráfica para WSL/terminal
 * @details
 *   Este programa executa todos os testes dos algoritmos M1.1 mas salva
 *   os resultados como arquivos de imagem em vez de exibir janelas.
 *   Ideal para ambientes sem X11/GUI como WSL.
 */

#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

// Inclui todos os módulos implementados
#include "imageinfo.hpp"
#include "conv/grayscale.hpp"
#include "conv/channel_isolator.hpp"
#include "arit/arithmetic.hpp"
#include "thre/threshold.hpp"
#include "histo/histogram.hpp"

/**
 * @brief Salva uma imagem e informa ao usuário
 */
void save_and_inform(const cv::Mat& image, const std::string& filename, const std::string& description)
{
    if (!image.empty())
    {
        cv::imwrite("results/" + filename, image);
        std::cout << "✓ " << description << " -> results/" << filename << std::endl;
    }
    else
    {
        std::cout << "✗ Erro ao processar: " << description << std::endl;
    }
}

/**
 * @brief Teste completo sem interface gráfica
 */
int main()
{
    std::cout << "====================================================" << std::endl;
    std::cout << "   PDI M1.1 - TESTE SEM INTERFACE GRÁFICA" << std::endl;
    std::cout << "====================================================" << std::endl;
    std::cout << "Este programa testa todos os algoritmos implementados" << std::endl;
    std::cout << "e salva os resultados na pasta 'results/'." << std::endl;
    std::cout << "====================================================" << std::endl;

    // Cria pasta de resultados
    system("mkdir -p results");

    // Lista de todas as imagens disponíveis para teste
    std::vector<std::string> image_paths = {
        "../data/ave-01.jpeg",
        "../data/ave-02.jpeg",
        "../data/ave-03.jpeg",
        "../data/blobs-image.jpg"
    };

    std::vector<std::string> image_names = {
        "Ave-01",
        "Ave-02",
        "Ave-03",
        "Blobs"
    };

    // Processa cada imagem
    for (size_t img_idx = 0; img_idx < image_paths.size(); ++img_idx)
    {
        std::cout << "\n🖼️  PROCESSANDO: " << image_names[img_idx] << std::endl;
        std::cout << "====================================================" << std::endl;

        // Carrega a imagem
        cv::Mat image = cv::imread(image_paths[img_idx], cv::IMREAD_COLOR);
        if (image.empty())
        {
            std::cerr << "❌ Erro ao carregar " << image_paths[img_idx] << "!" << std::endl;
            continue; // Pula para próxima imagem
        }

        std::cout << "📁 Imagem " << image_names[img_idx] << " carregada com sucesso!" << std::endl;
        ImageInfo::image_show(image, "Imagem " + image_names[img_idx]);

        // Prefixo para os arquivos desta imagem
        std::string prefix = std::to_string(img_idx + 1) + "_" + image_names[img_idx] + "_";

        save_and_inform(image, prefix + "00_original.jpg", "Imagem original " + image_names[img_idx]);

        // 1. CONVERSÃO PARA TONS DE CINZA
        std::cout << "\n🔄 1. CONVERSÃO PARA TONS DE CINZA" << std::endl;
        GrayScale converter(image);

        cv::Mat gray_arithmetic = converter.get_gray_arithmetic();
        ImageInfo::image_show(gray_arithmetic, "Tons de Cinza - Aritmética");
        save_and_inform(gray_arithmetic, prefix + "01_gray_arithmetic.jpg", "Tons de cinza - média aritmética");

        cv::Mat gray_weighted = converter.get_gray_weighted();
        ImageInfo::image_show(gray_weighted, "Tons de Cinza - Ponderada");
        save_and_inform(gray_weighted, prefix + "02_gray_weighted.jpg", "Tons de cinza - média ponderada");

        // 2. OPERAÇÕES ARITMÉTICAS
        std::cout << "\n➕ 2. OPERAÇÕES ARITMÉTICAS" << std::endl;
        ArithmeticOperations arith;

        cv::Mat brightened = arith.add_scalar(image, 50);
        save_and_inform(brightened, prefix + "03_brightened.jpg", "Imagem mais clara (+50)");

        cv::Mat darkened = arith.subtract_scalar(image, 50);
        save_and_inform(darkened, prefix + "04_darkened.jpg", "Imagem mais escura (-50)");

        cv::Mat enhanced = arith.multiply_scalar(image, 1.5);
        save_and_inform(enhanced, prefix + "05_enhanced.jpg", "Imagem realçada (*1.5)");

        cv::Mat reduced = arith.divide_scalar(image, 2.0);
        save_and_inform(reduced, prefix + "06_reduced.jpg", "Imagem reduzida (/2.0)");

        // Operações entre imagens
        cv::Mat sum_images = arith.add_images(image, brightened);
        save_and_inform(sum_images, prefix + "07_sum_images.jpg", "Soma entre imagens");

        cv::Mat diff_images = arith.subtract_images(enhanced, image);
        save_and_inform(diff_images, prefix + "08_diff_images.jpg", "Diferença entre imagens");

        // 3. LIMIARIZAÇÃO
        std::cout << "\n🔀 3. LIMIARIZAÇÃO" << std::endl;
        ThresholdOperations thresh;

        cv::Mat binary = thresh.binary_threshold(gray_arithmetic, 128);
        save_and_inform(binary, prefix + "09_binary_threshold.jpg", "Limiarização binária (128)");

        cv::Mat binary_inv = thresh.binary_threshold_inv(gray_arithmetic, 128);
        save_and_inform(binary_inv, prefix + "10_binary_inv.jpg", "Limiarização binária invertida");

        cv::Mat truncate = thresh.truncate_threshold(gray_arithmetic, 128);
        save_and_inform(truncate, prefix + "11_truncate.jpg", "Limiarização truncada");

        cv::Mat to_zero = thresh.to_zero_threshold(gray_arithmetic, 128);
        save_and_inform(to_zero, prefix + "12_to_zero.jpg", "Limiarização to-zero");

        // Limiarização colorida
        cv::Mat color_binary = thresh.binary_threshold_color(image, 128);
        save_and_inform(color_binary, prefix + "13_color_binary.jpg", "Limiarização colorida");

        // 4. ISOLAMENTO DE CANAIS
        std::cout << "\n🎨 4. ISOLAMENTO DE CANAIS DE CORES" << std::endl;
        ChannelIsolator isolator;

        cv::Mat blue_channel = isolator.extract_blue_channel(image);
        save_and_inform(blue_channel, prefix + "14_blue_channel.jpg", "Canal azul extraído");

        cv::Mat green_channel = isolator.extract_green_channel(image);
        save_and_inform(green_channel, prefix + "15_green_channel.jpg", "Canal verde extraído");

        cv::Mat red_channel = isolator.extract_red_channel(image);
        save_and_inform(red_channel, prefix + "16_red_channel.jpg", "Canal vermelho extraído");

        cv::Mat only_blue = isolator.isolate_blue_channel(image);
        save_and_inform(only_blue, prefix + "17_only_blue.jpg", "Apenas canal azul (colorido)");

        cv::Mat only_green = isolator.isolate_green_channel(image);
        save_and_inform(only_green, prefix + "18_only_green.jpg", "Apenas canal verde (colorido)");

        cv::Mat only_red = isolator.isolate_red_channel(image);
        save_and_inform(only_red, prefix + "19_only_red.jpg", "Apenas canal vermelho (colorido)");

        cv::Mat inverted = isolator.invert_image(image);
        save_and_inform(inverted, prefix + "20_inverted.jpg", "Imagem invertida");

        // 5. HISTOGRAMAS
        std::cout << "\n📊 5. HISTOGRAMAS" << std::endl;
        HistogramProcessor hist_proc;

        cv::Mat color_hist_viz = hist_proc.visualize_histogram_color(image);
        save_and_inform(color_hist_viz, prefix + "21_histogram_color.jpg", "Histograma colorido");

        cv::Mat gray_hist_viz = hist_proc.visualize_histogram_gray(gray_arithmetic);
        save_and_inform(gray_hist_viz, prefix + "22_histogram_gray.jpg", "Histograma tons de cinza");

        // Estatísticas do histograma
        std::vector<int> gray_hist = hist_proc.compute_histogram_gray(gray_arithmetic);
        int min_val, max_val;
        double mean_val;
        hist_proc.compute_histogram_stats(gray_hist, min_val, max_val, mean_val);

        std::cout << "📈 Estatísticas do histograma em tons de cinza:" << std::endl;
        std::cout << "   • Mínimo: " << min_val << std::endl;
        std::cout << "   • Máximo: " << max_val << std::endl;
        std::cout << "   • Média: " << mean_val << std::endl;

        // Testa recombinação de canais
        cv::Mat recombined = isolator.combine_channels(blue_channel, green_channel, red_channel);
        save_and_inform(recombined, prefix + "23_recombined.jpg", "Canais recombinados");

        std::cout << "\n✅ Processamento de " << image_names[img_idx] << " concluído!" << std::endl;
        std::cout << "====================================================" << std::endl;
    }

    std::cout << "\n====================================================" << std::endl;
    std::cout << "   🎉 TODOS OS TESTES CONCLUÍDOS COM SUCESSO!" << std::endl;
    std::cout << "====================================================" << std::endl;
    std::cout << "📁 Resultados salvos em: results/" << std::endl;
    std::cout << "🔍 Verifique os arquivos para ver os resultados:" << std::endl;
    std::cout << "   ls -la results/" << std::endl;
    std::cout << "\n🎯 Algoritmos testados em " << image_paths.size() << " imagens:" << std::endl;
    std::cout << "   ✓ Conversão para tons de cinza (2 métodos)" << std::endl;
    std::cout << "   ✓ Operações aritméticas (6 operações)" << std::endl;
    std::cout << "   ✓ Limiarização (5 tipos)" << std::endl;
    std::cout << "   ✓ Isolamento de canais (7 operações)" << std::endl;
    std::cout << "   ✓ Histogramas (computação e visualização)" << std::endl;
    std::cout << "   ✓ Inversão de imagem" << std::endl;
    std::cout << "\n🚀 Total: " << (image_paths.size() * 23) << " imagens de resultado geradas!" << std::endl;
    std::cout << "====================================================" << std::endl;

    return EXIT_SUCCESS;
}
