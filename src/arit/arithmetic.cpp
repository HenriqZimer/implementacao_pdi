#include "arit/arithmetic.hpp"
#include <algorithm>
#include <iostream>

ArithmeticOperations::ArithmeticOperations()
{
}

ArithmeticOperations::~ArithmeticOperations()
{
}

uchar ArithmeticOperations::clamp_to_uchar(double value)
{
    return static_cast<uchar>(std::max(0.0, std::min(255.0, value)));
}

bool ArithmeticOperations::are_images_compatible(const cv::Mat& img1, const cv::Mat& img2)
{
    return (img1.rows == img2.rows &&
        img1.cols == img2.cols &&
        img1.type() == img2.type() &&
        !img1.empty() &&
        !img2.empty());
}

// ================ Operações Imagem + Imagem ================

cv::Mat ArithmeticOperations::add_images(const cv::Mat& img1, const cv::Mat& img2)
{
    if (!are_images_compatible(img1, img2))
    {
        std::cerr << "Erro: Imagens não são compatíveis para operação!" << std::endl;
        return cv::Mat();
    }

    cv::Mat result(img1.rows, img1.cols, img1.type());

    if (img1.channels() == 1) // Imagem em tons de cinza
    {
        for (int linha = 0; linha < img1.rows; linha++)
        {
            const uchar* pixel1 = img1.ptr<uchar>(linha);
            const uchar* pixel2 = img2.ptr<uchar>(linha);
            uchar* pixel_out = result.ptr<uchar>(linha);

            for (int coluna = 0; coluna < img1.cols; coluna++)
            {
                double sum = static_cast<double>(pixel1[coluna]) + static_cast<double>(pixel2[coluna]);
                pixel_out[coluna] = clamp_to_uchar(sum);
            }
        }
    }
    else if (img1.channels() == 3) // Imagem colorida
    {
        for (int linha = 0; linha < img1.rows; linha++)
        {
            const cv::Vec3b* pixel1 = img1.ptr<cv::Vec3b>(linha);
            const cv::Vec3b* pixel2 = img2.ptr<cv::Vec3b>(linha);
            cv::Vec3b* pixel_out = result.ptr<cv::Vec3b>(linha);

            for (int coluna = 0; coluna < img1.cols; coluna++)
            {
                for (int canal = 0; canal < 3; canal++)
                {
                    double sum = static_cast<double>(pixel1[coluna][canal]) +
                        static_cast<double>(pixel2[coluna][canal]);
                    pixel_out[coluna][canal] = clamp_to_uchar(sum);
                }
            }
        }
    }

    return result;
}

cv::Mat ArithmeticOperations::subtract_images(const cv::Mat& img1, const cv::Mat& img2)
{
    if (!are_images_compatible(img1, img2))
    {
        std::cerr << "Erro: Imagens não são compatíveis para operação!" << std::endl;
        return cv::Mat();
    }

    cv::Mat result(img1.rows, img1.cols, img1.type());

    if (img1.channels() == 1) // Imagem em tons de cinza
    {
        for (int linha = 0; linha < img1.rows; linha++)
        {
            const uchar* pixel1 = img1.ptr<uchar>(linha);
            const uchar* pixel2 = img2.ptr<uchar>(linha);
            uchar* pixel_out = result.ptr<uchar>(linha);

            for (int coluna = 0; coluna < img1.cols; coluna++)
            {
                double diff = static_cast<double>(pixel1[coluna]) - static_cast<double>(pixel2[coluna]);
                pixel_out[coluna] = clamp_to_uchar(diff);
            }
        }
    }
    else if (img1.channels() == 3) // Imagem colorida
    {
        for (int linha = 0; linha < img1.rows; linha++)
        {
            const cv::Vec3b* pixel1 = img1.ptr<cv::Vec3b>(linha);
            const cv::Vec3b* pixel2 = img2.ptr<cv::Vec3b>(linha);
            cv::Vec3b* pixel_out = result.ptr<cv::Vec3b>(linha);

            for (int coluna = 0; coluna < img1.cols; coluna++)
            {
                for (int canal = 0; canal < 3; canal++)
                {
                    double diff = static_cast<double>(pixel1[coluna][canal]) -
                        static_cast<double>(pixel2[coluna][canal]);
                    pixel_out[coluna][canal] = clamp_to_uchar(diff);
                }
            }
        }
    }

    return result;
}

cv::Mat ArithmeticOperations::multiply_images(const cv::Mat& img1, const cv::Mat& img2)
{
    if (!are_images_compatible(img1, img2))
    {
        std::cerr << "Erro: Imagens não são compatíveis para operação!" << std::endl;
        return cv::Mat();
    }

    cv::Mat result(img1.rows, img1.cols, img1.type());

    if (img1.channels() == 1) // Imagem em tons de cinza
    {
        for (int linha = 0; linha < img1.rows; linha++)
        {
            const uchar* pixel1 = img1.ptr<uchar>(linha);
            const uchar* pixel2 = img2.ptr<uchar>(linha);
            uchar* pixel_out = result.ptr<uchar>(linha);

            for (int coluna = 0; coluna < img1.cols; coluna++)
            {
                // Normaliza para [0,1], multiplica e desnormaliza
                double mult = (static_cast<double>(pixel1[coluna]) / 255.0) *
                    (static_cast<double>(pixel2[coluna]) / 255.0) * 255.0;
                pixel_out[coluna] = clamp_to_uchar(mult);
            }
        }
    }
    else if (img1.channels() == 3) // Imagem colorida
    {
        for (int linha = 0; linha < img1.rows; linha++)
        {
            const cv::Vec3b* pixel1 = img1.ptr<cv::Vec3b>(linha);
            const cv::Vec3b* pixel2 = img2.ptr<cv::Vec3b>(linha);
            cv::Vec3b* pixel_out = result.ptr<cv::Vec3b>(linha);

            for (int coluna = 0; coluna < img1.cols; coluna++)
            {
                for (int canal = 0; canal < 3; canal++)
                {
                    // Normaliza para [0,1], multiplica e desnormaliza
                    double mult = (static_cast<double>(pixel1[coluna][canal]) / 255.0) *
                        (static_cast<double>(pixel2[coluna][canal]) / 255.0) * 255.0;
                    pixel_out[coluna][canal] = clamp_to_uchar(mult);
                }
            }
        }
    }

    return result;
}

cv::Mat ArithmeticOperations::divide_images(const cv::Mat& img1, const cv::Mat& img2)
{
    if (!are_images_compatible(img1, img2))
    {
        std::cerr << "Erro: Imagens não são compatíveis para operação!" << std::endl;
        return cv::Mat();
    }

    cv::Mat result(img1.rows, img1.cols, img1.type());

    if (img1.channels() == 1) // Imagem em tons de cinza
    {
        for (int linha = 0; linha < img1.rows; linha++)
        {
            const uchar* pixel1 = img1.ptr<uchar>(linha);
            const uchar* pixel2 = img2.ptr<uchar>(linha);
            uchar* pixel_out = result.ptr<uchar>(linha);

            for (int coluna = 0; coluna < img1.cols; coluna++)
            {
                if (pixel2[coluna] == 0)
                {
                    pixel_out[coluna] = 255; // Proteção contra divisão por zero
                }
                else
                {
                    double div = (static_cast<double>(pixel1[coluna]) /
                        static_cast<double>(pixel2[coluna])) * 255.0;
                    pixel_out[coluna] = clamp_to_uchar(div);
                }
            }
        }
    }
    else if (img1.channels() == 3) // Imagem colorida
    {
        for (int linha = 0; linha < img1.rows; linha++)
        {
            const cv::Vec3b* pixel1 = img1.ptr<cv::Vec3b>(linha);
            const cv::Vec3b* pixel2 = img2.ptr<cv::Vec3b>(linha);
            cv::Vec3b* pixel_out = result.ptr<cv::Vec3b>(linha);

            for (int coluna = 0; coluna < img1.cols; coluna++)
            {
                for (int canal = 0; canal < 3; canal++)
                {
                    if (pixel2[coluna][canal] == 0)
                    {
                        pixel_out[coluna][canal] = 255; // Proteção contra divisão por zero
                    }
                    else
                    {
                        double div = (static_cast<double>(pixel1[coluna][canal]) /
                            static_cast<double>(pixel2[coluna][canal])) * 255.0;
                        pixel_out[coluna][canal] = clamp_to_uchar(div);
                    }
                }
            }
        }
    }

    return result;
}

// ================ Operações Imagem + Escalar ================

cv::Mat ArithmeticOperations::add_scalar(const cv::Mat& img, double scalar)
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
                double sum = static_cast<double>(pixel_in[coluna]) + scalar;
                pixel_out[coluna] = clamp_to_uchar(sum);
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
                    double sum = static_cast<double>(pixel_in[coluna][canal]) + scalar;
                    pixel_out[coluna][canal] = clamp_to_uchar(sum);
                }
            }
        }
    }

    return result;
}

cv::Mat ArithmeticOperations::subtract_scalar(const cv::Mat& img, double scalar)
{
    return add_scalar(img, -scalar);
}

cv::Mat ArithmeticOperations::multiply_scalar(const cv::Mat& img, double scalar)
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
                double mult = static_cast<double>(pixel_in[coluna]) * scalar;
                pixel_out[coluna] = clamp_to_uchar(mult);
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
                    double mult = static_cast<double>(pixel_in[coluna][canal]) * scalar;
                    pixel_out[coluna][canal] = clamp_to_uchar(mult);
                }
            }
        }
    }

    return result;
}

cv::Mat ArithmeticOperations::divide_scalar(const cv::Mat& img, double scalar)
{
    if (scalar == 0.0)
    {
        std::cerr << "Erro: Divisão por zero!" << std::endl;
        return cv::Mat();
    }

    return multiply_scalar(img, 1.0 / scalar);
}
