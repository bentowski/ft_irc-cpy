#include <fstream>

int main()
{
	std::ofstream testfile("ConnexionFile");

	testfile << "CAP LS" << "\r\n";
	testfile << "pass pass" << "\r\n";
	testfile << "nick surLeFil" << "\r\n";
	testfile << "user Ivan Antoine localhost :Ben Antoine Ivan" << "\r\n";
	testfile << "die" << "\r\n";
}
