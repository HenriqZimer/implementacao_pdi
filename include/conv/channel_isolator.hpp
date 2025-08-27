#ifndef CHANNEL_ISOLATOR_HPP
#define CHANNEL_ISOLATOR_HPP

#include <opencv2/opencv.hpp>

/**
 * Classe ChannelIsolator
 * ----------------------
 * Responsável por isolar canais específicos de imagens coloridas BGR.
 * Permite extrair apenas um canal (R, G ou B) e criar versões da imagem
 * com apenas um canal ativo.
 *
 * Funcionalidades:
 * - Extração de canal individual como imagem em tons de cinza
 * - Criação de imagem colorida com apenas um canal ativo
 * - Suporte completo para canais B, G e R
 *
 * Uso típico:
 *   ChannelIsolator isolator{};
 *   cv::Mat red_channel = isolator.extract_red_channel(bgr_img);
 *   cv::Mat only_red = isolator.isolate_red_channel(bgr_img);
 */
class ChannelIsolator
{
    public:
        /**
         * Enumeração dos canais disponíveis (BGR - ordem do OpenCV).
         */
    enum Channel
    {
        BLUE = 0,   // Canal azul (índice 0 em BGR)
        GREEN = 1,  // Canal verde (índice 1 em BGR)
        RED = 2     // Canal vermelho (índice 2 em BGR)
    };

    /**
     * Construtor padrão.
     */
    ChannelIsolator();

    /**
     * Destrutor.
     */
    ~ChannelIsolator();

    // ================ Extração de canais como tons de cinza ================

    /**
     * Extrai o canal azul como imagem em tons de cinza.
     * @param img Imagem colorida de entrada (CV_8UC3 BGR)
     * @return Imagem em tons de cinza (CV_8UC1) contendo apenas o canal azul
     */
    cv::Mat extract_blue_channel(const cv::Mat& img);

    /**
     * Extrai o canal verde como imagem em tons de cinza.
     * @param img Imagem colorida de entrada (CV_8UC3 BGR)
     * @return Imagem em tons de cinza (CV_8UC1) contendo apenas o canal verde
     */
    cv::Mat extract_green_channel(const cv::Mat& img);

    /**
     * Extrai o canal vermelho como imagem em tons de cinza.
     * @param img Imagem colorida de entrada (CV_8UC3 BGR)
     * @return Imagem em tons de cinza (CV_8UC1) contendo apenas o canal vermelho
     */
    cv::Mat extract_red_channel(const cv::Mat& img);

    /**
     * Extrai um canal específico como imagem em tons de cinza.
     * @param img Imagem colorida de entrada (CV_8UC3 BGR)
     * @param channel Canal a ser extraído (BLUE, GREEN, RED)
     * @return Imagem em tons de cinza (CV_8UC1) contendo apenas o canal especificado
     */
    cv::Mat extract_channel(const cv::Mat& img, Channel channel);

    // ================ Isolamento de canais (mantém imagem colorida) ================

    /**
     * Cria imagem colorida com apenas o canal azul ativo (outros zerados).
     * @param img Imagem colorida de entrada (CV_8UC3 BGR)
     * @return Imagem colorida (CV_8UC3) com apenas canal azul
     */
    cv::Mat isolate_blue_channel(const cv::Mat& img);

    /**
     * Cria imagem colorida com apenas o canal verde ativo (outros zerados).
     * @param img Imagem colorida de entrada (CV_8UC3 BGR)
     * @return Imagem colorida (CV_8UC3) com apenas canal verde
     */
    cv::Mat isolate_green_channel(const cv::Mat& img);

    /**
     * Cria imagem colorida com apenas o canal vermelho ativo (outros zerados).
     * @param img Imagem colorida de entrada (CV_8UC3 BGR)
     * @return Imagem colorida (CV_8UC3) com apenas canal vermelho
     */
    cv::Mat isolate_red_channel(const cv::Mat& img);

    /**
     * Cria imagem colorida com apenas um canal específico ativo.
     * @param img Imagem colorida de entrada (CV_8UC3 BGR)
     * @param channel Canal a ser mantido (BLUE, GREEN, RED)
     * @return Imagem colorida (CV_8UC3) com apenas o canal especificado
     */
    cv::Mat isolate_channel(const cv::Mat& img, Channel channel);

    // ================ Operações combinadas ================

    /**
     * Combina três imagens em tons de cinza em uma imagem colorida BGR.
     * @param blue_channel Canal azul (CV_8UC1)
     * @param green_channel Canal verde (CV_8UC1)
     * @param red_channel Canal vermelho (CV_8UC1)
     * @return Imagem colorida (CV_8UC3 BGR) combinada
     */
    cv::Mat combine_channels(const cv::Mat& blue_channel, const cv::Mat& green_channel, const cv::Mat& red_channel);

    /**
     * Inverte a imagem (complemento): pixel = 255 - pixel.
     * Funciona tanto para imagens coloridas quanto em tons de cinza.
     * @param img Imagem de entrada (CV_8UC1 ou CV_8UC3)
     * @return Imagem invertida
     */
    cv::Mat invert_image(const cv::Mat& img);

    private:
        /**
         * Valida se a imagem é colorida (3 canais) e não está vazia.
         * @param img Imagem a ser validada
         * @return true se válida, false caso contrário
         */
    bool is_valid_color_image(const cv::Mat& img);

    /**
     * Valida se as três imagens têm dimensões compatíveis para combinação.
     * @param img1 Primeira imagem
     * @param img2 Segunda imagem
     * @param img3 Terceira imagem
     * @return true se compatíveis, false caso contrário
     */
    bool are_channels_compatible(const cv::Mat& img1, const cv::Mat& img2, const cv::Mat& img3);
};

#endif // CHANNEL_ISOLATOR_HPP
