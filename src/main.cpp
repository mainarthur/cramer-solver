#include <cmath>
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::pow;

#define fixCin cin.clear(); \
	       cin.ignore()

template<typename T>
void menu();

int main(int argc, char **argv) {
	system("clear");
	cout << "Hello!" << endl;
	while(true) {
		menu<float>();
	}
	return 0;
}

template<typename T>
void print_matr(T** matrix, int size) {
	for(int i = 0; i < size; i++) {
		cout << "| ";
		for(int j = 0; j < size; j++)
			cout << matrix[i][j] << " ";
		cout << "|" << endl;
	}
}

template<typename T>
T** get_minor(T **matrix, int size, int im, int jm) {
	int minor_size = size - 1;
	T **minor = new T*[minor_size];
	for(int i = 0; i < size; i++) {
		minor[i] = new T[minor_size];
		for(int j = 0; j < size; j++) {
			if( i < im && j < jm) {
				minor[i][j] = matrix[i][j];
			} else if( i > im || j > jm) {
				if(i > im && j > jm) {
					minor[i-1][j-1] = matrix[i][j];
				} else if( i > im) {
					minor[i-1][j] = matrix[i][j];
				} else {
					minor[i][j-1] = matrix[i][j];
				}
			}
		}
	}

	return minor;
}

template<typename T>
T calc_det(T **matrix, int size) {
	if(size == 1) {
		return matrix[0][0];
	} else if(size == 2) {
		return (matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]);
	} else {
		T res = T();
		int i = 0;
		for(int j = 0; j < size; j++) {
			T **minor = get_minor<T>(matrix, size, i, j);
			res += matrix[i][j] * pow(-1, (i+1)+(j+1)) * calc_det(minor, size - 1);
			delete[] minor;
		}
		return res;
	}
}

template<typename T>
T get_value() {
	T value;
	if(cin >> value && !cin.fail())
		return value;
	cout << "Please enter value again: ";
	fixCin;
	return get_value<T>();
}

template<typename T>
void menu() {
	int dimension = 0;
	do {
		cout << "Write determinant dimension: ";
		cin >> dimension;
		if(cin.fail()) {
			dimension = 0;
			fixCin;
		}
	} while(dimension <= 0);
	cout << "Determinant dimension is " << dimension << endl;
	T ** matrix = new T *[dimension];
	for(int i = 0; i < dimension; i++) {
		matrix[i] = new T[dimension];
		for(int j = 0; j < dimension; j++) {
			cout << "Enter value for matrix[" << (i+1) << "][" << (j+1) << "]: ";
			matrix[i][j] = get_value<T>();
		}
	}

	cout << "delta = " << endl;
	print_matr<T>(matrix, dimension);
	T delta = calc_det<T>(matrix, dimension);
	cout << "equals to " << delta << endl;
	if(delta == 0) {
		cout << "Determinant equals to 0, no solutions" << endl;
		delete[] matrix;
		return;
	}

	T * adding_elements = new T[dimension];
        T * temp = new T[dimension];

	for(int i = 0; i < dimension; i++) {
                cout << "Enter adding element value [" << (i+1) << "]:";
                adding_elements[i] = get_value<T>();
        }

	T *deltas = new T[dimension];
	for(int i = 0; i < dimension; i++) {
		for(int j = 0; j < dimension; j++) {
			temp[j] = matrix[j][i];
			matrix[j][i] = adding_elements[j];
		}
		cout << "delta" << (i+1) << " = " << endl;
		print_matr<T>(matrix, dimension);
		T delta_i = calc_det<T>(matrix, dimension);
		cout << "equals to" << delta_i << endl;
		deltas[i] = delta_i;
		for(int j = 0; j < dimension; j++) {
                        matrix[j][i] = temp[j];
                }
	}

	cout << "Linear solutions: " << endl;

	for(int i = 0; i < dimension; i++) {
		cout << "result[" << (i+1) << "] = " << (deltas[i]/delta) << endl;
	}
	delete[] matrix;
	delete[] temp;
	delete[] adding_elements;
	delete[] deltas;
}
