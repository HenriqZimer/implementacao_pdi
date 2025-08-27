#include "thre/threshold.hpp"
#include <iostream>

ThresholdOperations::ThresholdOperations()
{
}

ThresholdOperations::~ThresholdOperations()
{
}

uchar ThresholdOperations::apply_threshold_pixel(uchar pixel_value, uchar threshold_value, ThresholdType type, uchar max_value)
{
    switch (type)
    {
    case BINARY:
        return (pixel_value > threshold_value) ? max_value : 0;
    case BINARY_INV:
        return (pixel_value > threshold_value) ? 0 : max_value;
    case TRUNCATE:
        return (pixel_value > threshold_value) ? threshold_value : pixel_value;
    case TO_ZERO:
        return (pixel_value > threshold_value) ? pixel_value : 0;
    case TO_ZERO_INV:
        return (pixel_value > threshold_value) ? 0 : pixel_value;
    default:
        return pixel_value;
    }
}

// ================ Limiarização para imagens em tons de cinza ================

cv::Mat ThresholdOperations::binary_threshold(const cv::Mat& img, uchar threshold_value, uchar max_value)
{
    return apply_threshold(img, threshold_value, BINARY, max_value);
}

cv::Mat ThresholdOperations::binary_threshold_inv(const cv::Mat& img, uchar threshold_value, uchar max_value)
{
    return apply_threshold(img, threshold_value, BINARY_INV, max_value);
}

cv::Mat ThresholdOperations::truncate_threshold(const cv::Mat& img, uchar threshold_value)
{
    return apply_threshold(img, threshold_value, TRUNCATE);
}

cv::Mat ThresholdOperations::to_zero_threshold(const cv::Mat& img, uchar threshold_value)
{
    return apply_threshold(img, threshold_value, TO_ZERO);
}

cv::Mat ThresholdOperations::to_zero_inv_threshold(const cv::Mat& img, uchar threshold_value)
{
    return apply_threshold(img, threshold_value, TO_ZERO_INV);
}

// ================ Limiarização para imagens coloridas ================

cv::Mat ThresholdOperations::binary_threshold_color(const cv::Mat& img, uchar threshold_value, uchar max_value)
{
    return threshold_color(img, threshold_value, BINARY, max_value);
}

cv::Mat ThresholdOperations::threshold_color(const cv::Mat& img, uchar threshold_value, ThresholdType type, uchar max_value)
{
    return apply_threshold(img, threshold_value, type, max_value);
}

// ================ Método genérico ================

cv::Mat ThresholdOperations::apply_threshold(const cv::Mat& img, uchar threshold_value, ThresholdType type, uchar max_value)
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
                pixel_out[coluna] = apply_threshold_pixel(pixel_in[coluna], threshold_value, type, max_value);
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
                    pixel_out[coluna][canal] = apply_threshold_pixel(pixel_in[coluna][canal], threshold_value, type, max_value);
                }
            }
        }
    }
    else
    {
        std::cerr << "Erro: Tipo de imagem não suportado (deve ser 1 ou 3 canais)!" << std::endl;
        return cv::Mat();
    }

    return result;
}
