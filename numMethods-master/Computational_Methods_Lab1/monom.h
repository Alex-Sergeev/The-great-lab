#pragma once

#include <string>
#include <sstream>
#include <vector>
struct Monom {
	const static int size = 10;
	//int indx[size];
	int pows[size];
	double coff;
	Monom() {
		for (int i = 0; i < size; i++)
			pows[i] = 0;
		coff = 1;
	}
	Monom(double c) {
		for (int i = 0; i < size; i++)
			pows[i] = 0;
		coff = c;
	}
	Monom(const Monom& rhs) {
		for (int i = 0; i < size; i++)
			pows[i] = rhs.pows[i];
		coff = rhs.coff;
	}

	bool operator==(const Monom& rhs) const {
		for (int i = 0; i < size; i++)
			if (pows[i] != rhs.pows[i])
				return false;
		return coff == rhs.coff ? true : false;
	}
	bool operator!=(const Monom& rhs) const {
		return !(*this == rhs);
	}
	Monom operator+(const Monom& rhs) {
		if (!(*this == rhs)) return Monom();
		else {
			Monom tmp(*this);
			tmp.coff += rhs.coff;
			return tmp;
		}
	}

	Monom operator-(const Monom& rhs) {
		if (!(*this == rhs)) return Monom();
		else {
			Monom tmp(*this);
			tmp.coff -= rhs.coff;
			return tmp;
		}
	}

	Monom operator*(const Monom& rhs) {
		Monom tmp(*this);
		tmp.coff *= rhs.coff;
		if (tmp.coff == 0) return tmp;
		for (int i = 0; i < size; i++)
			tmp.pows[i] += rhs.pows[i];		
		return tmp;
	}



	double getVal(const std::vector<double>& vals) const
	{
		double res = coff;
		for (int i = 0; i < vals.size(); i++)
			res *= std::pow(vals[i], pows[i]);
		return res;
	}

	std::string toString(bool is_first = false) {
		std::stringstream ss;
		if (coff == 0) return "";
		if (!is_first) {
			if (coff > 0) ss << " + ";
			else ss << ' ';
		}
		ss << coff << '*';
		for (int i = 0; i < size; i++)
			if (pows[i]) {
				ss << "p" << i + 1;
				if (pows[i] > 1) ss << "^" << pows[i];
			}
				
		return ss.str();
	}
};
