#ifndef IMAGEINFO_H
#define IMAGEINFO_H
#pragma once
#include <opencv2/opencv.hpp>

/**
 * Imprime no console um sumário de atributos da imagem e, opcionalmente,
 * um rótulo/título para contextualizar.
 *
 * @param image      Imagem válida (cv::Mat) carregada/gerada previamente.
 * @param nomeImagem Rótulo opcional exibido no cabeçalho da janela de visualização da imagem.
 *
 * Pré-condição: `!image.empty()`.
 */

class ImageInfo
{
    public:
        ImageInfo();
        ~ImageInfo();

        static void image_show (const cv::Mat& image, const std::string& nomeImagem = "Imagem");

    private:
        
        /**
         * Converte o código inteiro de tipo (retorno de `cv::Mat::type()`)
         * em uma representação textual da profundidade (p.ex., CV_8U, CV_32F).
         *
         * Limitação: identifica apenas a profundidade (não inclui número de canais).
         *            Para canais, use `image.channels()`.
         */
        static std::string tipo_to_string(int tipo);
};
#endif