#pragma once
#include "object.h"

class Double : public CObject {
public:
	~Double() override { delete n_; }

	Double(Double const & i) : n_{new double{*i.n_}} {}

	Double(double n = 0) : n_{new double{n}} {}

	Double & operator=(Double const & i)
	{
		*n_ = *i.n_;
		return *this;
	}

	std::string_view type() const override { return "Double"; }

	Double const & print(std::ostream & ost) const override;

	Double & add(Object const & other) override;

	Double & read(std::istream & ist) override;

	bool equal(Object const & i) const noexcept(false) override;

	int compare(CObject const & other) const noexcept(false) override;

private:
	double * n_;
};
