#include "histo/histogram.hpp"
#include <iostream>
#include <algorithm>
#include <numeric>

HistogramProcessor::HistogramProcessor()
{
}

HistogramProcessor::~HistogramProcessor()
{
}

bool HistogramProcessor::is_valid_image(const cv::Mat& img, int expected_channels)
{
    return (!img.empty() &&
        img.channels() == expected_channels &&
        (img.type() == CV_8UC1 || img.type() == CV_8UC3));
}

// ================ Cálculo de histogramas ================

std::vector<int> HistogramProcessor::compute_histogram_gray(const cv::Mat& img)
{
    if (!is_valid_image(img, 1))
    {
        std::cerr << "Erro: Imagem deve ser em tons de cinza (1 canal)!" << std::endl;
        return std::vector<int>();
    }

    std::vector<int> histogram(256, 0);

    for (int linha = 0; linha < img.rows; linha++)
    {
        const uchar* pixel = img.ptr<uchar>(linha);
        for (int coluna = 0; coluna < img.cols; coluna++)
        {
            histogram[pixel[coluna]]++;
        }
    }

    return histogram;
}

HistogramProcessor::ColorHistogram HistogramProcessor::compute_histogram_color(const cv::Mat& img)
{
    ColorHistogram result;

    if (!is_valid_image(img, 3))
    {
        std::cerr << "Erro: Imagem deve ser colorida (3 canais)!" << std::endl;
        return result;
    }

    result.blue_hist = std::vector<int>(256, 0);
    result.green_hist = std::vector<int>(256, 0);
    result.red_hist = std::vector<int>(256, 0);

    for (int linha = 0; linha < img.rows; linha++)
    {
        const cv::Vec3b* pixel = img.ptr<cv::Vec3b>(linha);
        for (int coluna = 0; coluna < img.cols; coluna++)
        {
            result.blue_hist[pixel[coluna][0]]++;   // Canal B
            result.green_hist[pixel[coluna][1]]++;  // Canal G
            result.red_hist[pixel[coluna][2]]++;    // Canal R
        }
    }

    return result;
}

std::vector<int> HistogramProcessor::compute_histogram_channel(const cv::Mat& img, int channel)
{
    if (!is_valid_image(img, 3))
    {
        std::cerr << "Erro: Imagem deve ser colorida (3 canais)!" << std::endl;
        return std::vector<int>();
    }

    if (channel < 0 || channel > 2)
    {
        std::cerr << "Erro: Canal deve estar entre 0-2 (B, G, R)!" << std::endl;
        return std::vector<int>();
    }

    std::vector<int> histogram(256, 0);

    for (int linha = 0; linha < img.rows; linha++)
    {
        const cv::Vec3b* pixel = img.ptr<cv::Vec3b>(linha);
        for (int coluna = 0; coluna < img.cols; coluna++)
        {
            histogram[pixel[coluna][channel]]++;
        }
    }

    return histogram;
}

// ================ Visualização de histogramas ================

cv::Mat HistogramProcessor::visualize_histogram_gray(const cv::Mat& img, int hist_height, int hist_width)
{
    std::vector<int> histogram = compute_histogram_gray(img);
    if (histogram.empty())
    {
        return cv::Mat();
    }

    return visualize_histogram(histogram, hist_height, hist_width, cv::Scalar(255, 255, 255)); // Branco
}

cv::Mat HistogramProcessor::visualize_histogram_color(const cv::Mat& img, int hist_height, int hist_width)
{
    ColorHistogram color_hist = compute_histogram_color(img);
    if (color_hist.blue_hist.empty())
    {
        return cv::Mat();
    }

    // Cria imagem para visualização
    cv::Mat hist_image = cv::Mat::zeros(hist_height, hist_width, CV_8UC3);

    // Encontra o valor máximo entre todos os canais para normalização
    int max_blue = find_histogram_max(color_hist.blue_hist);
    int max_green = find_histogram_max(color_hist.green_hist);
    int max_red = find_histogram_max(color_hist.red_hist);
    int max_value = std::max({ max_blue, max_green, max_red });

    if (max_value == 0) return hist_image;

    int bin_width = hist_width / 256;

    // Desenha histogramas dos três canais sobrepostos
    for (int i = 0; i < 256; i++)
    {
        // Normaliza as alturas
        int blue_height = static_cast<int>((static_cast<double>(color_hist.blue_hist[i]) / max_value) * hist_height);
        int green_height = static_cast<int>((static_cast<double>(color_hist.green_hist[i]) / max_value) * hist_height);
        int red_height = static_cast<int>((static_cast<double>(color_hist.red_hist[i]) / max_value) * hist_height);

        // Desenha linhas verticais para cada canal
        cv::Point pt1_b(i * bin_width, hist_height);
        cv::Point pt2_b(i * bin_width, hist_height - blue_height);
        cv::line(hist_image, pt1_b, pt2_b, cv::Scalar(255, 0, 0), 1); // Azul

        cv::Point pt1_g(i * bin_width, hist_height);
        cv::Point pt2_g(i * bin_width, hist_height - green_height);
        cv::line(hist_image, pt1_g, pt2_g, cv::Scalar(0, 255, 0), 1); // Verde

        cv::Point pt1_r(i * bin_width, hist_height);
        cv::Point pt2_r(i * bin_width, hist_height - red_height);
        cv::line(hist_image, pt1_r, pt2_r, cv::Scalar(0, 0, 255), 1); // Vermelho
    }

    return hist_image;
}

cv::Mat HistogramProcessor::visualize_histogram(const std::vector<int>& histogram, int hist_height, int hist_width, cv::Scalar color)
{
    if (histogram.size() != 256)
    {
        std::cerr << "Erro: Histograma deve ter 256 elementos!" << std::endl;
        return cv::Mat();
    }

    cv::Mat hist_image = cv::Mat::zeros(hist_height, hist_width, CV_8UC3);

    int max_value = find_histogram_max(histogram);
    if (max_value == 0) return hist_image;

    int bin_width = hist_width / 256;

    for (int i = 0; i < 256; i++)
    {
        int height = static_cast<int>((static_cast<double>(histogram[i]) / max_value) * hist_height);
        cv::Point pt1(i * bin_width, hist_height);
        cv::Point pt2(i * bin_width, hist_height - height);
        cv::line(hist_image, pt1, pt2, color, 1);
    }

    return hist_image;
}

// ================ Operações auxiliares ================

std::vector<double> HistogramProcessor::normalize_histogram(const std::vector<int>& histogram, double max_value)
{
    if (histogram.empty())
    {
        return std::vector<double>();
    }

    int max_count = find_histogram_max(histogram);
    if (max_count == 0)
    {
        return std::vector<double>(histogram.size(), 0.0);
    }

    std::vector<double> normalized(histogram.size());
    for (size_t i = 0; i < histogram.size(); i++)
    {
        normalized[i] = (static_cast<double>(histogram[i]) / max_count) * max_value;
    }

    return normalized;
}

void HistogramProcessor::compute_histogram_stats(const std::vector<int>& histogram, int& min_value, int& max_value, double& mean_value)
{
    if (histogram.empty())
    {
        min_value = max_value = 0;
        mean_value = 0.0;
        return;
    }

    // Encontra min e max
    auto min_it = std::min_element(histogram.begin(), histogram.end());
    auto max_it = std::max_element(histogram.begin(), histogram.end());
    min_value = *min_it;
    max_value = *max_it;

    // Calcula média
    long long sum = std::accumulate(histogram.begin(), histogram.end(), 0LL);
    mean_value = static_cast<double>(sum) / histogram.size();
}

int HistogramProcessor::find_histogram_max(const std::vector<int>& histogram)
{
    if (histogram.empty())
    {
        return 0;
    }

    return *std::max_element(histogram.begin(), histogram.end());
}
