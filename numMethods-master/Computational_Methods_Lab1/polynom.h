#pragma once
#include "monom.h"
#include <vector>
#include <string>
#include <sstream>
class polynom
{
	std::vector<Monom> poly;

	int contains(const std::vector<Monom>& vec, const Monom& m)
	{
		for (int i = 0; i < vec.size(); i++)
			if (vec[i] == m) return i;
		return -1;
	}
public:
	polynom() {}
	polynom(const polynom& rhs) {
		poly = rhs.poly;
	}
	polynom(int ind) {
		Monom tmp;
		tmp.pows[ind] = 1;
		poly.emplace_back(tmp);
	}
	polynom(double coff) {
		Monom tmp;
		tmp.coff = coff;
		poly.emplace_back(tmp);
	}
	polynom operator+(const polynom& rhs) {
		polynom tmp(*this);
		for (int j = 0; j < rhs.poly.size(); j++) {
			int ind = contains(tmp.poly, rhs.poly[j]);
			if (ind > -1) tmp.poly[ind] = tmp.poly[ind] + rhs.poly[j];
			else tmp.poly.push_back(rhs.poly[j]);
		}
		return tmp;
	}

	polynom operator-(const polynom& rhs) {
		polynom tmp(*this);
		for (int j = 0; j < rhs.poly.size(); j++) {
			int ind = contains(tmp.poly, rhs.poly[j]);
			if (ind > -1) tmp.poly[ind] = tmp.poly[ind] - rhs.poly[j];
			else tmp.poly.push_back(Monom(-1.0) * rhs.poly[j]);
		}
		return tmp;
	}

	polynom operator*(const polynom& rhs) {
		polynom tmp;
		for (int i = 0; i < poly.size(); i++) {
			for (int j = 0; j < rhs.poly.size(); j++) {
				Monom t;
				t = poly[i] * rhs.poly[j];
				if (t.coff != 0) tmp.poly.emplace_back(t);
			}
		}
		return tmp;
	}


	double getVal(const std::vector<double>& vals)
	{
		double res = 0.0;
		for (const auto& m : poly)
		{
			res += m.getVal(vals);
		}
		return res;
	}

	auto gen_getVal()
	{
		return [this](const std::vector<double>& vals) {
			double res = 0.0;
			for (const auto& m : poly)
			{
				res += m.getVal(vals);
			}
			return res;
		};		
	}

	std::string toString(bool is_first = false) {
		std::stringstream ss;
		if (poly.size() > 0) ss << poly[0].toString(true);
		for (int i = 1; i < poly.size(); i++)
			ss << poly[i].toString();
		return ss.str();
	}
};

