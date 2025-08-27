#include "conv/grayscale.hpp"

GrayScale::GrayScale(const cv::Mat& img1)
{
    // Guarda a referência matricial de entrada.
    // Observação: cv::Mat utiliza contagem de referência; cópia é “shallow”.
    img1_ = img1;

    // Inicializa o buffer de saída (mesmas dimensões, 1 canal de 8 bits).
    // Pré-condição implícita: img1 deve possuir rows/cols > 0.
    result = cv::Mat(img1.rows, img1.cols, CV_8UC(1));
}

/**
 * Converte a imagem BGR em tons de cinza por média aritmética simples.
 * Fórmula: gray = (B + G + R) / 3
 *
 * Observações:
 * - Esta estratégia é suficiente para fins didáticos; para melhor aderência à
 *   luminância humana, considere get_gray_weighted().
 * - O acesso a pixels é feito por ponteiros de linha (ptr) para eficiência.
 */
cv::Mat GrayScale::get_gray_arithmetic()
{
    for (int linha = 0; linha < img1_.rows; linha++)
    {
        // Linha de entrada (3 canais, BGR)
        cv::Vec3b* pixel__in = img1_.ptr<cv::Vec3b>(linha);
        // Linha de saída (1 canal)
        uchar* pixel_out = result.ptr<uchar>(linha);

        for (int coluna = 0; coluna < img1_.cols; coluna++)
        {
            // Média simples dos três canais (conversão para uchar explicitamente).
            pixel_out[coluna] = static_cast<uchar>(
                (
                    pixel__in[coluna][0] +
                    pixel__in[coluna][1] +
                    pixel__in[coluna][2]
                    ) / 3
                );
        }
    }
    return result;
}

/**
 * Converte a imagem BGR em tons de cinza por média ponderada (padrão ITU-R BT.709).
 * Fórmula: gray = 0.114*B + 0.587*G + 0.299*R
 *
 * Observações:
 * - Esta fórmula considera a percepção humana da luminância.
 * - O verde tem maior peso devido à sensibilidade do olho humano.
 * - Clamping para evitar overflow/underflow.
 */
cv::Mat GrayScale::get_gray_weighted()
{
    for (int linha = 0; linha < img1_.rows; linha++)
    {
        // Linha de entrada (3 canais, BGR)
        cv::Vec3b* pixel__in = img1_.ptr<cv::Vec3b>(linha);
        // Linha de saída (1 canal)
        uchar* pixel_out = result.ptr<uchar>(linha);

        for (int coluna = 0; coluna < img1_.cols; coluna++)
        {
            // Média ponderada conforme padrão ITU-R BT.709
            double gray_value = 0.114 * pixel__in[coluna][0] +  // B
                0.587 * pixel__in[coluna][1] +  // G
                0.299 * pixel__in[coluna][2];   // R

// Clamping para garantir range [0, 255]
            gray_value = std::max(0.0, std::min(255.0, gray_value));
            pixel_out[coluna] = static_cast<uchar>(gray_value);
        }
    }
    return result;
}

/**
 * Mantém compatibilidade com código anterior (chama get_gray_arithmetic).
 * @deprecated Use get_gray_arithmetic() ou get_gray_weighted() explicitamente.
 */
cv::Mat GrayScale::get_gray()
{
    return get_gray_arithmetic();
}