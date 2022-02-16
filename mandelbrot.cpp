#include <iostream>
#include <vector>
#include <complex>
#include <fstream>

using namespace std;

const int IMG_SIZE = 4096;

vector<double> generate_linspace(double lower_bound, double upper_bound, int num_points) {
    vector<double> linspace(num_points + 1);
    for (int i = 0; i < num_points + 1; i++) {
        linspace[i] = lower_bound + (((upper_bound - lower_bound) / num_points) * i);
    }
    return linspace;
}

bool does_converge(complex<double> add_term) {
    const int num_iters = 100;
    complex<double> z(0, 0);
    for (int i = 0; i < num_iters; i++) {
        z = pow(z, 2) + add_term;
        if (norm(z) > 2) {
            return false;
        }
    }
    return true;
}

void make_image(int array[][IMG_SIZE + 1], const vector<double>& complex_linspace) {
    for (int i = 0; i < IMG_SIZE; i++) {
        for (int j = 0; j < IMG_SIZE; j++) {
            complex<double> test_num(complex_linspace[i], complex_linspace[j]);
            array[i][j] = does_converge(test_num) ? 200 : 0;
        }
    } 
}

void output_to_file(int array[][IMG_SIZE + 1], int num_points) {
    ofstream file;
    file.open("fractal.txt");

    for (int i = 0; i < num_points; i++) {
        for (int j = 0; j < num_points; j++) {
            file << array[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
}

int main() {
    const double lower_bound = -2;
    const double upper_bound = 2;
    const vector<double> complex_line = generate_linspace(lower_bound, upper_bound, IMG_SIZE);

    auto img_array = new int[IMG_SIZE + 1][IMG_SIZE + 1];

    make_image(img_array, complex_line);

    output_to_file(img_array, IMG_SIZE);

    delete[] img_array;

    cout << "finished" << endl;
}
