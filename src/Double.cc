#include "Double.h"

Double const & Double::print(std::ostream & ost) const 
{
	ost << *n_;
	return *this;
}

Double & Double::add(Object const & other) 
{
	auto cmp{dynamic_cast<Double const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_DERIVED;

	*n_ += *(cmp->n_);
	return *this;
}

Double & Double::read(std::istream & ist) 
{
	ist >> *n_;
	return *this;
}

bool Double::equal(Object const & i) const noexcept(false) 
{
	auto cmp{dynamic_cast<Double const *>(&i)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_DERIVED;

	return *n_ == *(cmp->n_);
}

int Double::compare(CObject const & other) const noexcept(false) 
{
	auto cmp{dynamic_cast<Double const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_DERIVED;

	auto diff{*n_ - *cmp->n_};
	return (diff > 0) ? 1 : (diff < 0) ? -1 : 0;
}
