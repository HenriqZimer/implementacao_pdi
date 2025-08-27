#ifndef OPERATION_HPP
#define OPERATION_HPP
#include <opencv2/opencv.hpp>
/**
 * Classe GrayScale
 * ----------------
 * Responsável por produzir uma versão em escala de cinza a partir de uma
 * imagem de entrada em BGR (formato padrão do OpenCV).
 *
 * Uso típico:
 *   GrayScale gs{bgr_img};
 *   cv::Mat gray_arithmetic = gs.get_gray_arithmetic();
 *   cv::Mat gray_weighted = gs.get_gray_weighted();
 *
 * Notas:
 * - Não faz cópia profunda da imagem de entrada no construtor; armazena a
 *   referência matricial (cv::Mat) internamente.
 * - Oferece dois métodos de conversão: média aritmética simples e média ponderada.
 */

class GrayScale
{
	public:

		/**
			* Constrói o conversor a partir de uma imagem BGR válida.
			* Pré-condição: img1 não deve estar vazia (img1.empty() == false).
			*/
	GrayScale(const cv::Mat& img1);

	/**
		* Realiza a conversão para escala de cinza por média simples dos canais.
		* Fórmula: gray = (B + G + R) / 3
		* Retorna: matriz CV_8UC1, mesmo tamanho da imagem de entrada.
		* Custo: O(H×W), varrendo a imagem linha a linha.
		*/
	cv::Mat get_gray_arithmetic();

	/**
		* Realiza a conversão para escala de cinza por média ponderada (padrão ITU-R BT.709).
		* Fórmula: gray = 0.114*B + 0.587*G + 0.299*R
		* Retorna: matriz CV_8UC1, mesmo tamanho da imagem de entrada.
		* Custo: O(H×W), varrendo a imagem linha a linha.
		*/
	cv::Mat get_gray_weighted();

	/**
		* Mantém compatibilidade com código anterior (chama get_gray_arithmetic).
		* @deprecated Use get_gray_arithmetic() ou get_gray_weighted() explicitamente.
		*/
	cv::Mat get_gray();

	private:
		// Armazena a imagem de entrada (espera-se tipo CV_8UC3 em BGR).
	cv::Mat img1_;
	// Buffer de saída (CV_8UC1). É inicializado no construtor.
	cv::Mat result;

};
#endif  // OPERATION_HPP