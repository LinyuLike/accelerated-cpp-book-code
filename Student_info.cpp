#include <list>
#include <algorithm>
#include <numeric>
#include <stdexcept>

#include "Student_info.h"

using std::istream;
using std::vector;
using std::list;
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

double grade(const double midterm, const double final,
	const vector<double>& hw)
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

std::string letter_grade(double grade)
{
	// range posts for numeric grades
	static const double numbers[] = {
		97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
	};

	// names for the letter  grades
	static const char* const letters[] = {
		"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
	};

	// compute the number of grades given the size of the array
	// and the size of a single element
	static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

	// given a numeric grade, find and return the associated letter grade
	for (size_t i = 0; i < ngrades; ++i)
	{
		if (grade > numbers[i])
			return letters[i];
	}

	return "?\?\?";
}



istream& Student_info::read(istream& is)
{
	char ch;
	is >> ch;

	if (ch == 'U')
		cp = new Core(is);
	else
		cp = new Grad(is);
	return is;
}

void Student_info::regrade(double final, double thesis)
{
	cp.make_unique();

	if (cp)
		cp->regrade(final, thesis);
	else
		throw std::runtime_error("regrade of unknow student");
}

// read homework grades from an input stream into a vector<double>
istream& read_hw(istream& in, vector<double>& hw)
{
	if (in) {
		// get rid of previous contents
		hw.clear();

		// read homework grades
		double x;
		while (in >> x)
			hw.push_back(x);

		// clear the stream so that input will work for the next student
		in.clear();
	}
	return in;
}

list<Student_info> 
extract_fails(list<Student_info>& students)
{
	list<Student_info> fail;

	// copy all the students that didn't pass to fail
	remove_copy_if(students.begin(), students.end(),
		back_inserter(fail), pgrade);
	// move all the students that pass to the front,
	// then delete the records which didn't moved.
	students.erase(remove_if(students.begin(), students.end(),
		fgrade), students.end());
	return fail;
}

// compute the median of a vector<double>
double median(vector<double> vec)
{
	typedef vector<double>::size_type vec_sz;
	vec_sz size = vec.size();
	if (size == 0)
		throw domain_error("median of an empty vector");
	std::sort(vec.begin(), vec.end());
	vec_sz mid = size / 2;
	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}
