#pragma once
#include <iostream> /*std::size_t; std::cout; exit()*/

class Matrix {
public:
	/*Вспомогательный класс для доступа к элементам матрицы*/
	class Line {
	public:
		Line(int * const ptr, long const len) : ptr_{ptr}, len_{len} {}

		int & operator[](long i) const;

	private:
		int * const ptr_; // Указатель на строку
		long const len_;  // Размер строки
	};

	// Конструктор квадратной матрицы, либо пустой
	Matrix(long const size = 0);

	// Конструктор прямоугольной матрицы матрицы
	Matrix(long const lines, long const rows);

	// Конструктор копирования
	Matrix(Matrix const & other);

	// Операция присвоения с перезаписью
	Matrix & operator=(Matrix other);

	// Деструктор
	~Matrix();

	// Заполнение матрицы из стандартного ввода
	Matrix & fill(long line = 0, long column = 0);

	// Получение числа строк матрицы
	long get_line_count() const { return this->line_count_; }

	// Получение числа строк матрицы
	long get_row_count() const { return this->row_count_; }

	// Вывод матрицы в stdout
	void print(std::ostream & ost = std::cout) const;

	/*Метод для заполнения матрицы случайными числами*/
	Matrix & randomise(int a, int b = 0);

	/*Метод зануления матрицы*/
	Matrix & zero() { return this->fill_with(0); }

	/*Метод заполнения матрицы одним числом*/
	Matrix & fill_with(int);

	/*Изменение элемента строки line, колонки column матрицы
	 * Поддерживается индексация с конца через индексы <0.
	 * Возврат false при неудаче, true при успехе*/
	bool set_element(long line, long column, int num);

	/*Чтение элемента строки line, колонки column матрицы
	 * Поддерживается индексация с конца через индексы <0*/
	int & get_element(long line, long column) const;

	/*Добавление к данной матрице другой матрицы other.
	 * !Матрицы должны быть одинаковых размеров!*/
	Matrix & add(Matrix const & other);

	/* !!УДАЛЕНО ИЗ ОРИГИНАЛЬНОЙ!!
	Matrix & operator+=(Matrix const & other) { return add(other); }
	*/

	/*Вычитание из данной матрицы другой матрицы other.
	 * !Матрицы должны быть одинаковых размеров!*/
	Matrix & substract(Matrix const & other);

	Matrix & operator-=(Matrix const & other) { return substract(other); }

	/*Умножение данной матрицы на другую матрицу other.
	 * !Матрицы должны быть одинаковых размеров!*/
	Matrix & multiply(Matrix const & other);

	Matrix & operator*=(Matrix const & other) { return multiply(other); }

	/*Умножение данной матрицы на число.*/
	Matrix & multiply(int const);

	Matrix & operator*=(int const n) { return multiply(n); }

	// Сравнение двух матриц на равенство/неравенство
	bool isEqualTo(Matrix const & other) const;

	/* !!УДАЛЕНО ИЗ ОРИГИНАЛЬНОЙ!!
	bool operator==(Matrix const & other) const { return isEqualTo(other); }

	bool operator!=(Matrix const & other) const
	{
		return !isEqualTo(other);
	}
	*/

	// Транспонирование матрицы
	Matrix & transpose()
	{
		return (this->row_count_ == this->line_count_)
			       ? transposeSq_()
			       : transposeNonSq_();
	}

	// Создание новой матрицы, равной сумме двух
	Matrix sum(Matrix other) const;

	/* !!УДАЛЕНО ИЗ ОРИГИНАЛЬНОЙ!!
	Matrix operator+(Matrix & other) const { return sum(other); }
	*/

	// Создание новой матрицы, равной разности двух
	Matrix diff(Matrix & other) const;

	Matrix operator-(Matrix & other) const { return diff(other); }

	// Создание новой матрицы, равной произведению двух
	Matrix product(Matrix & other) const;

	Matrix operator*(Matrix & other) const { return product(other); }

	// Создание новой матрицы, равной произведению матрицы на число
	Matrix product(int const i) const;

	Matrix operator*(int const i) const { return product(i); }

	/*Получение доступа к i-й строке. Поддерживается индексация с конца.
	 *Возвращается вспомогательный объект*/
	Line operator[](long i) const;

	Matrix & read(std::istream & ist)
	{
		int w, h;
		ist >> h >> w;
		if (ist.fail())
			return *this;

		Matrix tmp{h, w};
		for (int i{0}; i < h; ++i) {
			for (int j{0}; j < w; ++j) {
				ist >> tmp[i][j];
				if (ist.fail())
					return *this;
			}
		}

		std::swap(tmp.ptr_, ptr_);
		std::swap(tmp.line_count_, line_count_);
		std::swap(tmp.row_count_, row_count_);
		return *this;
	}
	/* !!УДАЛЕНО ИЗ ОРИГИНАЛЬНОЙ!!
	// Скрещивание матрицы и cout
	friend inline std::ostream & operator<<(std::ostream & ost,
						Matrix const & m)
	{
		if (m.line_count_ == 0 || 0 == m.row_count_)
			return ost;
		ost << m.line_count_ << ' ' << m.row_count_ << '\n';
		m.print(ost);
		return ost;
	}

	// Произвдение числа на матрицу равно произведению матрицы на число
	friend inline Matrix operator*(int const i, Matrix & m)
	{
		return m.product(i);
	}

	friend std::istream & operator>>(std::istream & ist, Matrix & m)
	{
		m.read(ist);
		return ist;
	}
	*/
private:
	/*Сокрытые поля*/
	int ** ptr_;	  // Указатель на непосредственно матрицу
	long row_count_;  // Число столбцов
	long line_count_; // Число строк

	/*Сокрытые методы*/
	Matrix & transposeSq_();    // Транспонирование квадратной матрицы
	Matrix & transposeNonSq_(); // Транспонирование не квадрат матрицы

	void constructor_(long const lines,
			  long const rows); // Общий конструктор

	// Подсчёт ячейки при умножении матриц
	void calcCellForMult_(Matrix const & first,
			      Matrix const & second,
			      int const line,
			      int const row);
};
