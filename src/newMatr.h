#include "matr.h"
#include "object.h"

class NewMatr : public Matrix, public Object {
public:
	std::string_view type() const override { return "NewMatr"; }

	NewMatr & add(Object const & other) override
	{
		auto cmp{dynamic_cast<Matrix const *>(&other)};
		if (nullptr == cmp)
			throw Object::exceptions::NOT_MATCHING_DERIVED;

		Matrix::add(*cmp);
		return *this;
	}

	bool equal(Object const & other) const override
	{
		auto cmp{dynamic_cast<Matrix const *>(&other)};
		if (nullptr == cmp)
			throw Object::exceptions::NOT_MATCHING_DERIVED;

		return Matrix::isEqualTo(*cmp);
	}

	NewMatr const & print(std::ostream & ost) const override
	{
		if (Matrix::get_line_count() == 0 ||
		    0 == Matrix::get_row_count())
			return *this;

		ost << Matrix::get_line_count() << ' '
		    << Matrix::get_row_count() << '\n';

		Matrix::print(ost);
		return *this;
	}

	NewMatr & read(std::istream & ist) override
	{
		Matrix::read(ist);
		return *this;
	}

	// Конструктор квадратной матрицы, либо пустой
	NewMatr(long const size = 0) : Matrix(size) {}

	// Конструктор прямоугольной матрицы матрицы
	NewMatr(long const lines, long const rows) : Matrix(lines, rows) {}

	// Конструктор копирования
	NewMatr(Matrix const & other) : Matrix(other) {}
};
