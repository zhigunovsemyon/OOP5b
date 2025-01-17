#pragma once
#include "object.h"

class Int : public CObject {
public:
	~Int() override { delete n_; }

	Int(Int const & i) : n_{new int{*i.n_}} {}

	Int(int n = 0) : n_{new int{n}} {}

	Int & operator=(Int const & i);

	std::string_view type() const override { return "Int"; }

	Int const & print(std::ostream & ost) const override;

	Int & read(std::istream & ist) override;

	int compare(CObject const & other) const noexcept(false) override;


	bool equal(Object const & i) const noexcept(false) override;

	Int & add(Object const & other) override;

private:
	int * n_;
};
