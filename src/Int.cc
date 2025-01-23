#include "Int.h"

Int & Int::operator=(Int const & i)
{
	*n_ = *i.n_;
	return *this;
}

Int const & Int::print(std::ostream & ost) const 
{
	ost << *n_;
	return *this;
}

Int & Int::read(std::istream & ist) 
{
	ist >> *n_;
	return *this;
}

int Int::compare(CObject const & other) const noexcept(false) 
{
	auto cmp{dynamic_cast<Int const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_DERIVED;

	return static_cast<int>(*n_ - *cmp->n_);
}

bool Int::equal(Object const & i) const noexcept(false) 
{
	auto cmp{dynamic_cast<Int const *>(&i)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_DERIVED;

	return *n_ == *(cmp->n_);
}

Int & Int::add(Object const & other) 
{
	auto cmp{dynamic_cast<Int const *>(&other)};
	if (nullptr == cmp)
		throw Object::exceptions::NOT_MATCHING_DERIVED;

	*n_ += *(cmp->n_);
	return *this;
}
