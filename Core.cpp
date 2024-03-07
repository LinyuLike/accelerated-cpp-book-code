#include "Core.h"
#include "grade.h"

std::string Core::name() const { return n; }

double Core::grade() const
{
	return ::grade(midterm, final, homework);
}

std::istream& Core::read_common(std::istream& in)
{
	// read and store the student's name and exam grades
	in >> n >> midterm >> final;
	return in;
}

std::istream& Core::read(std::istream& in)
{
	read_common(in);
	read_hw(in, homework); // Core.h->grade.h->Student_info.h
	return in;
}
