#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <string>

#include "Student_info.h"
#include "grade.h"
#include "median.h"

using std::domain_error;
using std::vector;
using std::accumulate;

// compute a student's overall grade from midterm and final exam grades and homework grade
double grade(double midterm, double final, double homework)
{
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

// compute a student's overall grade from midterm and final exam grades
// // and vector of homework grades.
// this function does not copy its argument, because median does so for us.
double grade(double midterm, double final, vector<double>& hw)  // can't invoke const param with param(changeable)
{
	return 0;

	/*if (hw.size() == 0)
		throw domain_error("student has done no homework");
	return grade(midterm, final, median(hw));*/
}

double grade(const Student_info& s)
{
	return 0;

	//return grade(s.midterm, s.final, s.homework);
}

// predicate to determine whether a student failed
bool fgrade(const Student_info& s)
{
	return grade(s) < 60;
}

bool pgrade(const Student_info& s)
{
	return !fgrade(s);
}

double grade_aux(const Student_info& s)
{
	return 0;

	/*try {
		return grade(s);
	}
	catch (domain_error) {
		return grade(s.midterm, s.final, 0);
	}*/
}

// this version works fine
double median_analysis(const vector<Student_info>& students)
{
	vector<double> grades;

	transform(students.begin(), students.end(),
		back_inserter(grades), grade_aux);
	return median(grades);
}

double average(const vector<double>& v)
{
	return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double average_grade(const Student_info& s)
{
	return 0;

	//return grade(s.midterm, s.final, average(s.homework));
}

double average_analysis(const vector<Student_info>& students)
{
	vector<double> grades;
	
	transform(students.begin(), students.end(),
		back_inserter(grades), average_grade);
	return median(grades);
}

// median of the nonzero elements of s.homework, or 0 if no such elements exist
double optimistic_median(const Student_info& s)
{
	return 0;

	//vector<double> nonzero;
	//remove_copy(s.homework.begin(), s.homework.end(),
	//	back_inserter(nonzero), 0);

	//if (nonzero.empty())
	//	return grade(s.midterm, s.final, 0);
	//else
	//	return grade(s.midterm, s.final, median(nonzero));
}

double optimistic_median_analysis(const vector<Student_info>& students)
{
	vector<double> grades;

	transform(students.begin(), students.end(),
		back_inserter(grades), optimistic_median);
	return median(grades);
}

void write_analysis(std::ostream& out, const std::string& name,
	double analysys(const vector<Student_info>&),
	const vector<Student_info>& did,
	const vector<Student_info>& didnt)
{
	out << name << ": median(did) = " << analysys(did) <<
		", median(didnt) = " << analysys(didnt) << std::endl;
}

/*
int main()
{
	// students who did and didn't do all their homework
	vector<Student_info> did, didnt;

	// read the student records and partition them
	Student_info student;
	while (read(cin, student)) {
		if (did_all_hw(student))
			did.push_back(student);
		else
			didnt.push_back(student);
	}

	// verify that the analysys will show us something
	if (did.empty()) {
		cout << "No student did all the homework!" << endl;
		return 1;
	}
	if (didnt.empty()) {
		cout << "Every student did all the homework!" << endl;
		return 1;
	}

	// do the analysys
	write_analysis(cout, "median", median_analysis, did, didnt);
	write_analysis(cout, "average", average_analysis, did, didnt);
	write_analysis(cout, "median if honework turned in",
		optimistic_median_analysis, did, didnt);
	return 0;
}
*/