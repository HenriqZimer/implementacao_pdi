#ifndef THRESHOLD_HPP
#define THRESHOLD_HPP

#include <opencv2/opencv.hpp>

/**
 * Classe ThresholdOperations
 * --------------------------
 * Responsável por aplicar operações de limiarização (thresholding)
 * em imagens coloridas e em tons de cinza.
 *
 * Suporte a:
 * - Limiarização binária simples
 * - Limiarização binária invertida
 * - Limiarização truncada
 * - Limiarização para zero
 * - Limiarização para zero invertida
 * - Suporte para imagens coloridas (aplica em todos os canais)
 *
 * Uso típico:
 *   ThresholdOperations thresh{};
 *   cv::Mat binary = thresh.binary_threshold(gray_img, 128);
 *   cv::Mat color_thresh = thresh.binary_threshold_color(color_img, 128);
 */
class ThresholdOperations
{
    public:
        /**
         * Enumeração dos tipos de limiarização disponíveis.
         */
    enum ThresholdType
    {
        BINARY,          // pixel > thresh ? max_val : 0
        BINARY_INV,      // pixel > thresh ? 0 : max_val
        TRUNCATE,        // pixel > thresh ? thresh : pixel
        TO_ZERO,         // pixel > thresh ? pixel : 0
        TO_ZERO_INV      // pixel > thresh ? 0 : pixel
    };

    /**
     * Construtor padrão.
     */
    ThresholdOperations();

    /**
     * Destrutor.
     */
    ~ThresholdOperations();

    // ================ Limiarização para imagens em tons de cinza ================

    /**
     * Aplica limiarização binária em imagem em tons de cinza.
     * @param img Imagem de entrada (CV_8UC1)
     * @param threshold_value Valor limiar [0, 255]
     * @param max_value Valor máximo a ser atribuído [0, 255]
     * @return Imagem limiarizada
     */
    cv::Mat binary_threshold(const cv::Mat& img, uchar threshold_value, uchar max_value = 255);

    /**
     * Aplica limiarização binária invertida em imagem em tons de cinza.
     * @param img Imagem de entrada (CV_8UC1)
     * @param threshold_value Valor limiar [0, 255]
     * @param max_value Valor máximo a ser atribuído [0, 255]
     * @return Imagem limiarizada
     */
    cv::Mat binary_threshold_inv(const cv::Mat& img, uchar threshold_value, uchar max_value = 255);

    /**
     * Aplica limiarização truncada em imagem em tons de cinza.
     * @param img Imagem de entrada (CV_8UC1)
     * @param threshold_value Valor limiar [0, 255]
     * @return Imagem limiarizada
     */
    cv::Mat truncate_threshold(const cv::Mat& img, uchar threshold_value);

    /**
     * Aplica limiarização "to zero" em imagem em tons de cinza.
     * @param img Imagem de entrada (CV_8UC1)
     * @param threshold_value Valor limiar [0, 255]
     * @return Imagem limiarizada
     */
    cv::Mat to_zero_threshold(const cv::Mat& img, uchar threshold_value);

    /**
     * Aplica limiarização "to zero invertida" em imagem em tons de cinza.
     * @param img Imagem de entrada (CV_8UC1)
     * @param threshold_value Valor limiar [0, 255]
     * @return Imagem limiarizada
     */
    cv::Mat to_zero_inv_threshold(const cv::Mat& img, uchar threshold_value);

    // ================ Limiarização para imagens coloridas ================

    /**
     * Aplica limiarização binária em imagem colorida (canal por canal).
     * @param img Imagem de entrada (CV_8UC3)
     * @param threshold_value Valor limiar [0, 255]
     * @param max_value Valor máximo a ser atribuído [0, 255]
     * @return Imagem limiarizada
     */
    cv::Mat binary_threshold_color(const cv::Mat& img, uchar threshold_value, uchar max_value = 255);

    /**
     * Aplica limiarização genérica em imagem colorida.
     * @param img Imagem de entrada (CV_8UC3)
     * @param threshold_value Valor limiar [0, 255]
     * @param type Tipo de limiarização
     * @param max_value Valor máximo (usado apenas em tipos BINARY)
     * @return Imagem limiarizada
     */
    cv::Mat threshold_color(const cv::Mat& img, uchar threshold_value, ThresholdType type, uchar max_value = 255);

    // ================ Método genérico ================

    /**
     * Aplica limiarização genérica (funciona para tons de cinza e colorida).
     * @param img Imagem de entrada (CV_8UC1 ou CV_8UC3)
     * @param threshold_value Valor limiar [0, 255]
     * @param type Tipo de limiarização
     * @param max_value Valor máximo (usado apenas em tipos BINARY)
     * @return Imagem limiarizada
     */
    cv::Mat apply_threshold(const cv::Mat& img, uchar threshold_value, ThresholdType type, uchar max_value = 255);

    private:
        /**
         * Aplica limiarização em um único pixel.
         * @param pixel_value Valor do pixel [0, 255]
         * @param threshold_value Valor limiar [0, 255]
         * @param type Tipo de limiarização
         * @param max_value Valor máximo (usado apenas em tipos BINARY)
         * @return Valor do pixel após limiarização
         */
    uchar apply_threshold_pixel(uchar pixel_value, uchar threshold_value, ThresholdType type, uchar max_value);
};

#endif // THRESHOLD_HPP
