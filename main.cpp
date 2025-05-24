#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <sstream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

// Função que calcula a cor do ponto (x,y)
int calculate_mandelbrot(int x, int y, int width, int height, int max_iter, float zoom, double x_offset, double y_offset) {
    complex<double> c((double)x / (zoom * width) + x_offset, (double)y / (zoom * height) + y_offset);
    complex<double> z(0, 0);
    int iter = 0;

    while (abs(z) < 2 && iter < max_iter) {
        z = z * z + c;
        iter++;
    }

    if (iter < max_iter) {
        return 3 * (255 * iter) / max_iter;
    } else {
        return 0;
    }
}

int main() {
    int width, height, max_iter;
    float zoom;
    double x_offset, y_offset;

    // Solicita ao usuário os parâmetros
    cout << "Digite a largura (width) da imagem: ";
    cin >> width;
    cout << "Digite a altura (height) da imagem: ";
    cin >> height;
    cout << "Digite o numero maximo de iteracoes (foco): ";
    cin >> max_iter;
    cout << "Digite o fator de zoom (amplia): ";
    cin >> zoom;
    cout << "Digite o deslocamento X (ex: -2.0): ";
    cin >> x_offset;
    cout << "Digite o deslocamento Y (ex: -1.0): ";
    cin >> y_offset;

    // Cria nome da pasta com os parâmetros
    stringstream folder_name;
    folder_name << "mandelbrot_w" << width << "_h" << height
                << "_iter" << max_iter << "_zoom" << zoom
                << "_x" << x_offset << "_y" << y_offset;

    string mkdir_cmd = "mkdir \"" + folder_name.str() + "\"";
    system(mkdir_cmd.c_str()); // cria pasta

    // Prepara a imagem em memória
    vector<unsigned char> image(width * height * 3); // RGB
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int val = calculate_mandelbrot(i, j, width, height, max_iter, zoom, x_offset, y_offset);
            int index = (j * width + i) * 3;

            if (val <= 255) {
                image[index] = val; image[index + 1] = 0; image[index + 2] = 0; // vermelho
            } else if (val <= 610) {
                image[index] = 255; image[index + 1] = val - 255; image[index + 2] = 0; // amarelo
            } else {
                image[index] = 255; image[index + 1] = 255; image[index + 2] = val - 610; // branco
            }
        }
    }

    // Salva como PNG
    string png_path = folder_name.str() + "/mandelbrot.png";
    if (stbi_write_png(png_path.c_str(), width, height, 3, image.data(), width * 3)) {
        cout << "Imagem gerada com sucesso: " << png_path << endl;
    } else {
        cerr << "Erro ao salvar a imagem PNG." << endl;
    }

    return 0;
}
