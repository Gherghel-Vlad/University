#include "HTMLFile.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

string HTMLFile::toStringMovie(Movie* movie) const {
	std::stringstream buffer;

    buffer << "<tr>" << endl;
    buffer << "<td>" << movie->getTitle() << "</td>" << endl;
    buffer << "<td>" << movie->getGenre() << "</td>" << endl;
    buffer << "<td>" << movie->getYearOfRelease() << "</td>" << endl;
    buffer << "<td>" << movie->getNumberOfLikes() << "</td>" << endl;
    buffer << "<td> <a href = \"" << movie->getTrailer() << "\" > Link</a> </td>" << endl;
    buffer << "</tr>" << endl;

    return buffer.str();
}

void HTMLFile::saveToFile(const std::vector<Movie> moviesVector) const {

    ofstream f(FILENAME);

    if (!f.is_open()) {
        return;
    }

    f << "<!DOCTYPE html> \n  <html> \n <head> \n <title>Watch list</title> \n </head> \n";
    f << "<body> \n <table border = \"1\"> \n <tr> \n <td>Title</td> \n <td>Genre</td> \n";
    f << "<td>Year of release</td> \n <td>Number of likes</td> \n <td>Youtube link to trailer</td> \n </tr> \n";





    for (auto movie : moviesVector)
        f << this->toStringMovie(&movie);
    f << "</table> \n </body> \n </html> \n";

    f.close();

}

void HTMLFile::openFile() {
    LPCWSTR open = L"open";
    string file = FILENAME;
    wstring fileW = std::wstring(file.begin(), file.end());
    LPCWSTR fileName = fileW.c_str();
    ShellExecute(NULL, open, fileName, NULL, NULL, SW_SHOWNORMAL);
}