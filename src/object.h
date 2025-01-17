#pragma once
#include <istream>
#include <ostream>
#include <string_view>

/* Предусмотреть:
 * 	+1.Загрузку объекта из текстовой строки.
 * 	+2.Выгрузки объекта в текстовую строку в динамической памяти.
 * 	+3.Возврат уникального идентификатора класса.
 * 	+4.Возврат указателя на строку с именем класса.
 * 	+5.Сравнение двух объектов.
 * 	+6."Сложение" (Объединение) двух объектов.
 * 	+7.Создание динамической копии объекта.
 * Сделать разработанный класс производным от абстрактного базового класса
 * object. Взять любой другой простой класс (например, класс целых чисел) и
 * также сделать его производным от абстрактного базового класса object. Создать
 * статическую структуру данных, содержащую указатели object* на объекты обоих
 * классов. Показать возможность одновременной работы через виртуальные функции.
 */
class Object {
public:
	enum class exceptions {
		NOT_MATCHING_DERIVED
	};

	/*Виртуальный деструктор*/
	virtual ~Object() = default;

	/*Возврат уникального идентификатора*/
	int id() const { return id_; }

	/*Возврат строки с типом объекта*/
	virtual std::string_view type() const = 0;

	/*Вывод содержимого в переданный поток*/
	virtual Object const & print(std::ostream & ost) const = 0;

	/*Чтение из переданного потока*/
	virtual Object & read(std::istream & ist) = 0;

	/*Сравнение на равенство с другим объектом*/
	virtual bool equal(Object const &) const = 0;

	/*Добавление в текущий объект другого*/
	virtual Object & add(Object const &) = 0;

	/*Добавление в первый объект второго*/
	friend Object & operator+=(Object & a, Object const & b)
	{
		return a.add(b);
	}

	/*Сравнение на неравенство с другим объектом*/
	friend bool operator!=(Object const & a, Object const & b)
	{
		return !a.equal(b);
	}

	/*Сравнение на равенство с другим объектом*/
	friend bool operator==(Object const & a, Object const & b)
	{
		return a.equal(b);
	}

	/*Чтение содержимого из потока*/
	friend std::istream & operator>>(std::istream & ist, Object & obj)
	{
		obj.read(ist);
		return ist;
	}

	/*Вывод содержимого в поток*/
	friend std::ostream & operator<<(std::ostream & ost, Object const & obj)
	{
		obj.print(ost);
		return ost;
	}

protected:
	/*Сокрытый конструктор, инициализирующийся идентификатором*/
	Object() : id_{count_++} {}

private:
	static inline int count_; // Счётчик объектов
	int const id_;		  // Идентификатор класса
};

class CObject : public Object {
public:
	/* Функция сравнения. Возврат 1 если this > other, -1 если this < other,
	 * 0 при равенстве*/
	virtual int compare(CObject const & other) const = 0;
	
	friend bool operator>(const CObject &a, const CObject &b)
	{
		return (a.compare(b) > 0) ? true : false;
	}

	friend bool operator<=(const CObject &a, const CObject &b)
	{
		return !(a > b);
	}

	friend bool operator<(const CObject &a, const CObject &b)
	{
		return (a.compare(b) < 0) ? true : false;
	}

	friend bool operator>=(const CObject &a, const CObject &b)
	{
		return !(a < b);
	}
};
