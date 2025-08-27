#include <iostream>
#include <opencv2/opencv.hpp>

#include "conv/grayscale.hpp"

int main() {
    std::cout << "Projeto OpenCV Funcionando!" << std::endl;
  
    // Exemplo simples com OpenCV
    cv::Mat image = cv::Mat::zeros(300, 600, CV_8UC3);
    cv::putText(image, "OpenCV Funcionando!", cv::Point(100, 150), 
               cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(0, 255, 0), 2);
    cv::imshow("Janela OpenCV", image);
    cv::waitKey(0);
    return 0;
}