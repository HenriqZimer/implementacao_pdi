#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <opencv2/opencv.hpp>

/**
 * Classe ArithmeticOperations
 * ---------------------------
 * Responsável por realizar operações aritméticas básicas entre imagens
 * e entre imagem e valor escalar.
 *
 * Suporte a:
 * - Adição, subtração, multiplicação e divisão
 * - Operações imagem-imagem e imagem-escalar
 * - Imagens coloridas (3 canais) e em tons de cinza (1 canal)
 * - Tratamento de overflow/underflow com clamping
 *
 * Uso típico:
 *   ArithmeticOperations arith{};
 *   cv::Mat result = arith.add_images(img1, img2);
 *   cv::Mat result2 = arith.multiply_scalar(img1, 1.5);
 */
class ArithmeticOperations
{
    public:
        /**
         * Construtor padrão.
         */
    ArithmeticOperations();

    /**
     * Destrutor.
     */
    ~ArithmeticOperations();

    // ================ Operações Imagem + Imagem ================

    /**
     * Soma duas imagens pixel a pixel.
     * @param img1 Primeira imagem (CV_8UC1 ou CV_8UC3)
     * @param img2 Segunda imagem (mesmo tipo e dimensões de img1)
     * @return Imagem resultante com clamping [0, 255]
     */
    cv::Mat add_images(const cv::Mat& img1, const cv::Mat& img2);

    /**
     * Subtrai duas imagens pixel a pixel.
     * @param img1 Primeira imagem (CV_8UC1 ou CV_8UC3)
     * @param img2 Segunda imagem (mesmo tipo e dimensões de img1)
     * @return Imagem resultante com clamping [0, 255]
     */
    cv::Mat subtract_images(const cv::Mat& img1, const cv::Mat& img2);

    /**
     * Multiplica duas imagens pixel a pixel.
     * @param img1 Primeira imagem (CV_8UC1 ou CV_8UC3)
     * @param img2 Segunda imagem (mesmo tipo e dimensões de img1)
     * @return Imagem resultante com clamping [0, 255]
     */
    cv::Mat multiply_images(const cv::Mat& img1, const cv::Mat& img2);

    /**
     * Divide duas imagens pixel a pixel.
     * @param img1 Primeira imagem (dividendo) (CV_8UC1 ou CV_8UC3)
     * @param img2 Segunda imagem (divisor) (mesmo tipo e dimensões de img1)
     * @return Imagem resultante com proteção contra divisão por zero
     */
    cv::Mat divide_images(const cv::Mat& img1, const cv::Mat& img2);

    // ================ Operações Imagem + Escalar ================

    /**
     * Soma um valor escalar a todos os pixels da imagem.
     * @param img Imagem de entrada (CV_8UC1 ou CV_8UC3)
     * @param scalar Valor a ser somado
     * @return Imagem resultante com clamping [0, 255]
     */
    cv::Mat add_scalar(const cv::Mat& img, double scalar);

    /**
     * Subtrai um valor escalar de todos os pixels da imagem.
     * @param img Imagem de entrada (CV_8UC1 ou CV_8UC3)
     * @param scalar Valor a ser subtraído
     * @return Imagem resultante com clamping [0, 255]
     */
    cv::Mat subtract_scalar(const cv::Mat& img, double scalar);

    /**
     * Multiplica todos os pixels da imagem por um valor escalar.
     * @param img Imagem de entrada (CV_8UC1 ou CV_8UC3)
     * @param scalar Valor multiplicador
     * @return Imagem resultante com clamping [0, 255]
     */
    cv::Mat multiply_scalar(const cv::Mat& img, double scalar);

    /**
     * Divide todos os pixels da imagem por um valor escalar.
     * @param img Imagem de entrada (CV_8UC1 ou CV_8UC3)
     * @param scalar Valor divisor (deve ser != 0)
     * @return Imagem resultante com proteção contra divisão por zero
     */
    cv::Mat divide_scalar(const cv::Mat& img, double scalar);

    private:
        /**
         * Aplica clamping a um valor para o range [0, 255].
         * @param value Valor a ser limitado
         * @return Valor limitado entre 0 e 255
         */
    uchar clamp_to_uchar(double value);

    /**
     * Verifica se duas imagens têm dimensões e tipos compatíveis.
     * @param img1 Primeira imagem
     * @param img2 Segunda imagem
     * @return true se compatíveis, false caso contrário
     */
    bool are_images_compatible(const cv::Mat& img1, const cv::Mat& img2);
};

#endif // ARITHMETIC_HPP
