#include <iostream>
#include <vector>
#include <complex>
#include <fstream>

using namespace std;


vector<double> generate_linspace(double lower_bound, double upper_bound, int num_points) {
    vector<double> linspace(num_points + 1);
    for (int i = 0; i <= num_points + 1; i++) {
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

int main() {
    const int num_idx = 4096;
    const double lower_bound = -2;
    const double upper_bound = 2;
    vector<double> real_line = generate_linspace(lower_bound, upper_bound, num_idx);
    vector<double> imag_line = generate_linspace(lower_bound, upper_bound, num_idx);

    auto img_array = new int[num_idx + 1][num_idx + 1];

    for (int i = 0; i < num_idx; i++) {
        for (int j = 0; j < num_idx; j++) {
            complex<double> test_num(real_line[i], imag_line[j]);
            img_array[i][j] = does_converge(test_num) ? 200 : 0;
        }
    }

    ofstream file;
    file.open("fractal.txt");

    for (int i = 0; i < num_idx; i++) {
        for (int j = 0; j < num_idx; j++) {
            file << img_array[i][j] << " ";
        }
        file << "\n";
    }
    delete[] img_array;
    file.close();

    cout << "finished" << endl;
}
