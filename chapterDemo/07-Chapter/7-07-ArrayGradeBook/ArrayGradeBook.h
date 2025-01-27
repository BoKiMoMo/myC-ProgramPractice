#include <array>
#include <string>

class GradeBook
{
public:
	static const size_t students = 10;

	GradeBook(const std::string& ,const std::array<int,students> &);
	void setCourseName(const std::string&);
	std::string getCourseName() const;
	void displayMessage() const;
	void processGrades() const;
	int getMinimum() const;
	int getMaximum() const;
	double getAverage() const;
	void outputBarChart() const;
	void outputGrades() const;

private:
	std::string courseName;
	std::array<int, students> grades;
};