#include "imageinfo.hpp"

ImageInfo::ImageInfo()
{
}
ImageInfo::~ImageInfo()
{
}


/**
 * Mapeia o "depth" codificado em `cv::Mat::type()` para uma string legível.
 *
 * Observação: `cv::Mat::type()` combina profundidade e canais. Aqui extraímos
 * apenas a profundidade usando `CV_MAT_DEPTH_MASK`. O número de canais deve ser
 * obtido separadamente por `image.channels()`.
 */
std::string ImageInfo::tipo_to_string(int tipo)
{
    int profundidade = tipo & CV_MAT_DEPTH_MASK;
    switch (profundidade) {
    case CV_8U:  return "CV_8U (8-bit unsigned integer)";
    case CV_8S:  return "CV_8S (8-bit signed integer)";
    case CV_16U: return "CV_16U (16-bit unsigned integer)";
    case CV_16S: return "CV_16S (16-bit signed integer)";
    case CV_32S: return "CV_32S (32-bit signed integer)";
    case CV_32F: return "CV_32F (32-bit float)";
    case CV_64F: return "CV_64F (64-bit double)";
    default:     return "Tipo desconhecido";
    }
}

/**
 * Emite no console um relatório compacto com propriedades da imagem.
 * Útil para depuração/relato em sala (inspeção de domínio e memória).
 *
 * Campos exibidos:
 *  - Dimensões (linhas x colunas)
 *  - Quantidade de canais
 *  - Total de elementos (pixels * canais)
 *  - Tamanho em bytes (aproximado por `total() * elemSize()`)
 *  - Profundidade (depth) traduzida por `tipo_to_string`
 *
 * Complexidade: O(1) (apenas leitura de metadados; não percorre pixels).
 */
void ImageInfo::image_show(const cv::Mat& image, const std::string& nomeImagem)
{
    std::cout << "--------------------------------------------------" << std::endl << std::endl;
    std::cout << "--- Info da Imagem: " << nomeImagem << " ---" << std::endl;

    // 1) Geometria: altura (rows) x largura (cols)
    std::cout << "Dimensoes (Linhas x Colunas): " << image.rows << " x " << image.cols << std::endl;

     // 2) Canais (1=cinza, 3=BGR, 4=BGRA, etc.)
    std::cout << "Quantidade de Canais: " << image.channels() << std::endl;

    // 3) Cardinalidade total de elementos (pixels * canais)
    std::cout << "Tamanho (Total de elementos): " << image.total() << std::endl;

    // 4) Estimativa de memória ocupada em bytes (útil para análises de custo)
    std::cout << "Tamanho em bytes: " << image.total() * image.elemSize() << " bytes" << std::endl;

    // 5) Profundidade do elemento (tipo do canal), ex.: CV_8U, CV_32F
    std::cout << "Profundidade (Depth): " << tipo_to_string(image.type()) << std::endl;

    std::cout << "--------------------------------------------------" << std::endl << std::endl;
}