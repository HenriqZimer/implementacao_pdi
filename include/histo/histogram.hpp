#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include <opencv2/opencv.hpp>
#include <vector>

/**
 * Classe HistogramProcessor
 * -------------------------
 * Responsável por computar e visualizar histogramas de imagens
 * coloridas (BGR) e em tons de cinza.
 *
 * Funcionalidades:
 * - Cálculo de histograma para imagens em tons de cinza
 * - Cálculo de histograma para cada canal (B, G, R) de imagens coloridas
 * - Visualização gráfica dos histogramas
 * - Normalização de histogramas
 * - Estatísticas básicas (mínimo, máximo, média)
 *
 * Uso típico:
 *   HistogramProcessor hist_proc{};
 *   std::vector<int> hist = hist_proc.compute_histogram_gray(gray_img);
 *   cv::Mat hist_image = hist_proc.visualize_histogram_gray(gray_img);
 */
class HistogramProcessor
{
    public:
        /**
         * Estrutura para armazenar histogramas de imagem colorida.
         */
    struct ColorHistogram
    {
        std::vector<int> blue_hist;   // Histograma do canal azul
        std::vector<int> green_hist;  // Histograma do canal verde
        std::vector<int> red_hist;    // Histograma do canal vermelho
    };

    /**
     * Construtor padrão.
     */
    HistogramProcessor();

    /**
     * Destrutor.
     */
    ~HistogramProcessor();

    // ================ Cálculo de histogramas ================

    /**
     * Calcula histograma de imagem em tons de cinza.
     * @param img Imagem em tons de cinza (CV_8UC1)
     * @return Vetor com 256 elementos (índices 0-255) contendo a frequência de cada intensidade
     */
    std::vector<int> compute_histogram_gray(const cv::Mat& img);

    /**
     * Calcula histogramas dos três canais de imagem colorida.
     * @param img Imagem colorida (CV_8UC3 BGR)
     * @return Estrutura ColorHistogram com histogramas dos canais B, G, R
     */
    ColorHistogram compute_histogram_color(const cv::Mat& img);

    /**
     * Calcula histograma de um canal específico de imagem colorida.
     * @param img Imagem colorida (CV_8UC3 BGR)
     * @param channel Índice do canal (0=B, 1=G, 2=R)
     * @return Vetor com 256 elementos contendo a frequência de cada intensidade do canal
     */
    std::vector<int> compute_histogram_channel(const cv::Mat& img, int channel);

    // ================ Visualização de histogramas ================

    /**
     * Cria visualização gráfica do histograma de imagem em tons de cinza.
     * @param img Imagem em tons de cinza (CV_8UC1)
     * @param hist_height Altura da imagem de visualização (padrão: 400)
     * @param hist_width Largura da imagem de visualização (padrão: 512)
     * @return Imagem (CV_8UC3) contendo o gráfico do histograma
     */
    cv::Mat visualize_histogram_gray(const cv::Mat& img, int hist_height = 400, int hist_width = 512);

    /**
     * Cria visualização gráfica dos histogramas de imagem colorida.
     * @param img Imagem colorida (CV_8UC3 BGR)
     * @param hist_height Altura da imagem de visualização (padrão: 400)
     * @param hist_width Largura da imagem de visualização (padrão: 512)
     * @return Imagem (CV_8UC3) contendo os gráficos dos histogramas dos três canais
     */
    cv::Mat visualize_histogram_color(const cv::Mat& img, int hist_height = 400, int hist_width = 512);

    /**
     * Cria visualização gráfica de um histograma específico.
     * @param histogram Vetor com as frequências (256 elementos)
     * @param hist_height Altura da imagem de visualização
     * @param hist_width Largura da imagem de visualização
     * @param color Cor das barras do histograma (BGR)
     * @return Imagem (CV_8UC3) contendo o gráfico do histograma
     */
    cv::Mat visualize_histogram(const std::vector<int>& histogram, int hist_height, int hist_width, cv::Scalar color);

    // ================ Operações auxiliares ================

    /**
     * Normaliza um histograma para o range [0, max_value].
     * @param histogram Histograma de entrada
     * @param max_value Valor máximo após normalização (padrão: 255)
     * @return Histograma normalizado
     */
    std::vector<double> normalize_histogram(const std::vector<int>& histogram, double max_value = 255.0);

    /**
     * Calcula estatísticas básicas de um histograma.
     * @param histogram Histograma de entrada
     * @param min_value Saída: valor mínimo encontrado
     * @param max_value Saída: valor máximo encontrado
     * @param mean_value Saída: valor médio
     */
    void compute_histogram_stats(const std::vector<int>& histogram, int& min_value, int& max_value, double& mean_value);

    /**
     * Encontra o valor máximo em um histograma.
     * @param histogram Histograma de entrada
     * @return Valor máximo encontrado
     */
    int find_histogram_max(const std::vector<int>& histogram);

    private:
        /**
         * Valida se a imagem é adequada para processamento de histograma.
         * @param img Imagem a ser validada
         * @param expected_channels Número esperado de canais (1 ou 3)
         * @return true se válida, false caso contrário
         */
    bool is_valid_image(const cv::Mat& img, int expected_channels);
};

#endif // HISTOGRAM_HPP
