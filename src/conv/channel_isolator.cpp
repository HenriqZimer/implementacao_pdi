#include "conv/channel_isolator.hpp"
#include <iostream>

ChannelIsolator::ChannelIsolator()
{
}

ChannelIsolator::~ChannelIsolator()
{
}

bool ChannelIsolator::is_valid_color_image(const cv::Mat& img)
{
    return (!img.empty() && img.channels() == 3 && img.type() == CV_8UC3);
}

bool ChannelIsolator::are_channels_compatible(const cv::Mat& img1, const cv::Mat& img2, const cv::Mat& img3)
{
    return (img1.rows == img2.rows && img1.rows == img3.rows &&
        img1.cols == img2.cols && img1.cols == img3.cols &&
        img1.type() == CV_8UC1 && img2.type() == CV_8UC1 && img3.type() == CV_8UC1 &&
        !img1.empty() && !img2.empty() && !img3.empty());
}

// ================ Extração de canais como tons de cinza ================

cv::Mat ChannelIsolator::extract_blue_channel(const cv::Mat& img)
{
    return extract_channel(img, BLUE);
}

cv::Mat ChannelIsolator::extract_green_channel(const cv::Mat& img)
{
    return extract_channel(img, GREEN);
}

cv::Mat ChannelIsolator::extract_red_channel(const cv::Mat& img)
{
    return extract_channel(img, RED);
}

cv::Mat ChannelIsolator::extract_channel(const cv::Mat& img, Channel channel)
{
    if (!is_valid_color_image(img))
    {
        std::cerr << "Erro: Imagem deve ser colorida (3 canais BGR)!" << std::endl;
        return cv::Mat();
    }

    cv::Mat result(img.rows, img.cols, CV_8UC1);

    for (int linha = 0; linha < img.rows; linha++)
    {
        const cv::Vec3b* pixel_in = img.ptr<cv::Vec3b>(linha);
        uchar* pixel_out = result.ptr<uchar>(linha);

        for (int coluna = 0; coluna < img.cols; coluna++)
        {
            pixel_out[coluna] = pixel_in[coluna][static_cast<int>(channel)];
        }
    }

    return result;
}

// ================ Isolamento de canais (mantém imagem colorida) ================

cv::Mat ChannelIsolator::isolate_blue_channel(const cv::Mat& img)
{
    return isolate_channel(img, BLUE);
}

cv::Mat ChannelIsolator::isolate_green_channel(const cv::Mat& img)
{
    return isolate_channel(img, GREEN);
}

cv::Mat ChannelIsolator::isolate_red_channel(const cv::Mat& img)
{
    return isolate_channel(img, RED);
}

cv::Mat ChannelIsolator::isolate_channel(const cv::Mat& img, Channel channel)
{
    if (!is_valid_color_image(img))
    {
        std::cerr << "Erro: Imagem deve ser colorida (3 canais BGR)!" << std::endl;
        return cv::Mat();
    }

    cv::Mat result = cv::Mat::zeros(img.rows, img.cols, CV_8UC3);

    for (int linha = 0; linha < img.rows; linha++)
    {
        const cv::Vec3b* pixel_in = img.ptr<cv::Vec3b>(linha);
        cv::Vec3b* pixel_out = result.ptr<cv::Vec3b>(linha);

        for (int coluna = 0; coluna < img.cols; coluna++)
        {
            // Zera todos os canais
            pixel_out[coluna][0] = 0; // B
            pixel_out[coluna][1] = 0; // G
            pixel_out[coluna][2] = 0; // R

            // Mantém apenas o canal desejado
            pixel_out[coluna][static_cast<int>(channel)] = pixel_in[coluna][static_cast<int>(channel)];
        }
    }

    return result;
}

// ================ Operações combinadas ================

cv::Mat ChannelIsolator::combine_channels(const cv::Mat& blue_channel, const cv::Mat& green_channel, const cv::Mat& red_channel)
{
    if (!are_channels_compatible(blue_channel, green_channel, red_channel))
    {
        std::cerr << "Erro: Canais não são compatíveis para combinação!" << std::endl;
        return cv::Mat();
    }

    cv::Mat result(blue_channel.rows, blue_channel.cols, CV_8UC3);

    for (int linha = 0; linha < result.rows; linha++)
    {
        const uchar* blue_in = blue_channel.ptr<uchar>(linha);
        const uchar* green_in = green_channel.ptr<uchar>(linha);
        const uchar* red_in = red_channel.ptr<uchar>(linha);
        cv::Vec3b* pixel_out = result.ptr<cv::Vec3b>(linha);

        for (int coluna = 0; coluna < result.cols; coluna++)
        {
            pixel_out[coluna][0] = blue_in[coluna];   // B
            pixel_out[coluna][1] = green_in[coluna];  // G
            pixel_out[coluna][2] = red_in[coluna];    // R
        }
    }

    return result;
}

cv::Mat ChannelIsolator::invert_image(const cv::Mat& img)
{
    if (img.empty())
    {
        std::cerr << "Erro: Imagem vazia!" << std::endl;
        return cv::Mat();
    }

    cv::Mat result(img.rows, img.cols, img.type());

    if (img.channels() == 1) // Imagem em tons de cinza
    {
        for (int linha = 0; linha < img.rows; linha++)
        {
            const uchar* pixel_in = img.ptr<uchar>(linha);
            uchar* pixel_out = result.ptr<uchar>(linha);

            for (int coluna = 0; coluna < img.cols; coluna++)
            {
                pixel_out[coluna] = 255 - pixel_in[coluna];
            }
        }
    }
    else if (img.channels() == 3) // Imagem colorida
    {
        for (int linha = 0; linha < img.rows; linha++)
        {
            const cv::Vec3b* pixel_in = img.ptr<cv::Vec3b>(linha);
            cv::Vec3b* pixel_out = result.ptr<cv::Vec3b>(linha);

            for (int coluna = 0; coluna < img.cols; coluna++)
            {
                for (int canal = 0; canal < 3; canal++)
                {
                    pixel_out[coluna][canal] = 255 - pixel_in[coluna][canal];
                }
            }
        }
    }
    else
    {
        std::cerr << "Erro: Tipo de imagem não suportado!" << std::endl;
        return cv::Mat();
    }

    return result;
}
