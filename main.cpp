#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <string>
#include <stdexcept>

// Очистка консоли
void clearConsole() {
    system("cls");
}
// Основной класс матрицы
template<typename T> class Matrix {
private:
    std::vector<std::vector<T>> data;
    int rows, cols;
/* Вводы матриц */
// Ввод матрицы с заданными размерами
    void inputDataWithSizes() {
        std::cout << "Enter all elements of matrix ( " << rows * cols << " elements ):\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cin >> data[i][j];
            }
        }
    }
// Ввод матрицы без заданных размеров
     void inputDataNoSizes() {
        std::cout << "Enter number of rows:\n";
        std::cin >> rows;
        std::cout << "Enter number of columns:\n";
        std::cin >> cols;
        data = std::vector<std::vector<T>>(rows, std::vector<T>(cols));
        inputDataWithSizes();
    }

public:
/* Конструкторы */
// Конструктор для считывания матрицы без размеров
    Matrix() : rows(0), cols(0) {
    }
// Конструктор для считывания матрицы с размерами
    Matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        data = std::vector<std::vector<T>>(rows, std::vector<T>(cols));
    }
// Конструктор для матрицы с одинаковыми значениями
    Matrix(int rows, int cols, T value) {
        this->rows = rows;
        this->cols = cols;
        data = std::vector<std::vector<T>>(rows, std::vector<T>(cols, value));
    }
// Конструктор по вектору
    Matrix(std::vector<std::vector<T>> matrix) {
        data = matrix;
        rows = data.size();
        cols = data[0].size();
    }
// Конструктор для считывания матрицы из файла
    Matrix(std::string fileName) {
        std::ifstream fileInput(fileName);
        fileInput >> rows >> cols;
        if (!fileInput.is_open()) {
            std::cout << "There is no such a file in that directory" << std::endl;
            throw std::invalid_argument(":/");
        }
        else {
            data = std::vector<std::vector<T>>(rows, std::vector<T>(cols));
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    fileInput >> data[i][j];
                }
            }
        }
        fileInput.close();
    }

/* Метод для считвания матрицы */
// Метод для считвания матрицы
    void inputMatrix() {
        if (rows == cols && rows == 0) {
            inputDataNoSizes();
        }
        else {
            inputDataWithSizes();
        }
        return ;
    }

/* Методы для вывода матриц */
// Вывод матрицы в файл
    void printMatrixToFile(std::string fileOutName) {
        std::ofstream fileOut(fileOutName);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                fileOut << data[i][j] << " ";
            }
            fileOut << "\n";
        }
        fileOut.close();
    }
// Вывод матрицы в консоль
    void printMatrixToConsole() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

/* Перегрузка <<>> */
// Перегрузка <<>> для консоли
    friend std::ostream& operator<<(std::ostream& os, const Matrix &matrix) {
        for (auto row : matrix.data) {
            for (auto elem : row) {
                os << elem << " ";
            }
            os << "\n";
        }
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Matrix &matrix) {
        if (matrix.rows == matrix.cols && matrix.rows == 0) {
            std::cout << "Enter number of rows:\n";
            is >> matrix.rows;
            std::cout << "Enter number of columns:\n";
            is >> matrix.cols;
            matrix.data = std::vector<std::vector<T>>(matrix.rows, std::vector<T>(matrix.cols));
        }
        std::cout << "Enter all elements of matrix ( " << matrix.rows * matrix.cols << " elements ):\n";
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j) {
                is >> matrix.data[i][j];
            }
        }
        return is;
    }
// Перегрузка <<>> для файла
    friend std::ofstream& operator<<(std::ofstream& ofs, Matrix &matrix) {
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j) {
                ofs << matrix.data[i][j] << " ";
            }
            ofs << "\n";
        }
    }
    friend std::ifstream& operator>>(std::ifstream& ifs, Matrix &matrix) {
        ifs >> matrix.rows >> matrix.cols;
        matrix.data = std::vector<std::vector<T>>(matrix.rows, std::vector<T>(matrix.cols));
        for (int i = 0; i < matrix.rows; ++i) {
            for (int j = 0; j < matrix.cols; ++j) {
                ifs >> matrix.data[i][j];
            }
        }
    }

/* Перегрузка + и - */
    Matrix operator+ (Matrix &other) {
        if (this->rows != other.rows || this->cols != other.cols) {
            throw std::invalid_argument("Sizes of matrixes do not match");
        }
        std::vector<std::vector<T>> result = data;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i][j] += other.data[i][j];
            }
        }
        return Matrix(result);
    }
    Matrix operator- (Matrix &other) {
        if (this->rows != other.rows || this->cols != other.cols) {
            throw std::invalid_argument("Sizes of matrixes do not match");
        }
        std::vector<std::vector<T>> result = data;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i][j] -= other.data[i][j];
            }
        }
        return Matrix(result);
    }

/* Перегрузка * */
    Matrix operator* (int scalar) {
        std::vector<std::vector<T>> result = data;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result[i][j] *= scalar;
            }
        }
        return Matrix(result);
    }
    Matrix operator* (Matrix &other) {
        if (this->cols != other.rows) {
            throw std::invalid_argument("Number of columns of the first matrix should match with number of rows of the second matrix");
        }
        std::vector<std::vector<T>> result(this->rows, std::vector<T>(other.cols, 0));
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < this->cols; ++k) {
                    result[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return Matrix(result);
    }

/* Перегрузка присваивания */
    void operator= (Matrix &other) {
        this->rows = other.rows;
        this->cols = other.cols;
        this->data = other.data;
    }

/* Статические методы для единичных и нулевыех матриц */
    static Matrix zeroMatrix(int rows, int cols) {
        return Matrix(std::vector<std::vector<T>> (rows, std::vector<T>(cols, 0)));
    }
    static Matrix unitMatrix(int rows) {
        std::vector<std::vector<T>> result = std::vector<std::vector<T>>(rows, std::vector<T>(rows, 0));
        for (int i = 0; i < rows; ++i) {
            result[i][i] = 1;
        }
        return Matrix(result);
    }

/* Нахождение обратной матрицы */
    Matrix<double> operator!() {
        if (this->rows != this->cols) {
            throw std::invalid_argument("Rows should match columns");
        }
        int n = this->rows;
        std::vector<std::vector<double>> extendedMatrix(n, std::vector<double>(n * 2, 0.0));
        for (int i = 0; i < n; ++i) {
            extendedMatrix[i][i + n] = 1.0;
            for (int j = 0; j < n; ++j) {
                extendedMatrix[i][j] = this->data[i][j];
            }
        }
        
        for (int i = 0; i < n; ++i) {
            if (extendedMatrix[i][i] == 0) {
                throw std::invalid_argument("Reverse matrix does not exist");
            }
            double div = extendedMatrix[i][i];
            for (int j = 0; j < 2 * n; ++j) {
                extendedMatrix[i][j] /= div;
            }
            for (int k = 0; k < n; ++k) {
                if (k != i) {
                    double f = extendedMatrix[k][i];
                    for (int j = 0; j < 2 * n; ++j) {
                        extendedMatrix[k][j] -= extendedMatrix[i][j] * f;
                    }
                }
            }
        }
        
        std::vector<std::vector<double>> inverse(n, std::vector<double>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                inverse[i][j] = extendedMatrix[i][j + n];
            }
        }
        return Matrix<double>(inverse);
    }

    ~Matrix() {
    }
};

int main() {
    //clearConsole();
    Matrix<int> M("matrixInput.txt");
    Matrix<int> NN({{5, 3, 2}, {5, 4, 1}, {7, 2, 1}});
    Matrix<int> N = NN;
    //std::cout << M + N;
    //std::cout << M - N;
    //std::cout << N * 3;
    //std::cout << N * M;
    //std::cout << Matrix<int>::zeroMatrix(2, 2);
    //std::cout << Matrix<int>::unitMatrix(3);
    std::cout << !NN;
/*
// Матрица с указанными размерами
    Matrix<int> A(2,2);
    A.printMatrixToConsole();
// Матрица без указанных размеров
    Matrix<int> B;
    B.printMatrixToConsole();
// Матрица для считывания из файла
    Matrix<int> C("matrixInput.txt");
    C.printMatrixToConsole();
    C.printMatrixToFile("matrixOutput.txt");
// Матрица и консоль и <<>>
    Matrix<int> D;
    std::cin >> D;
    std::cout << D;
// Матрица и файлы и <<>>
    Matrix<int> E(2, 2);
    ofstream fileOut("matrixOutput.txt");
    ifstream fileIn("matrixInput.txt");
    if (fileIn.is_open() == false) {
        throw std::invalid_argument("File not found");
    }
    fileIn >> E;
    fileOut << E;
*/


    return 0;
}