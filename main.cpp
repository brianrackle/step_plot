#include <string>
#include <regex>
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include "ncurses.h"
#include "regex_replace_ext.hpp"

#define GNUPLOT "gnuplot -persist"

//TODO(brian): don't convert file to string to allow large file processing
//TODO(brian): skip, 10 (char '1'), 100 (char '2'), 1000 (char '3'), 10000 (char '4'), etc...
//TODO(brian): run without using gnuplot indexing for faster processing
//TODO(brian): allow binary data input type for reduced file size
FILE *start_gnuplot() {
    //initialize gnuplot
    FILE *gp;
    gp = popen(GNUPLOT, "w");
    if (gp == nullptr) {
        printf("error opening pipe to GNU plot\n");
        fflush(gp);
        throw;
    }

    fprintf(gp, "set term x11 noraise persist\n");
    fflush(gp);
    return gp;
}

void stop_gnuplot(FILE *gp) {
    fprintf(gp, "exit \n");
    fflush(gp);
    fclose(gp);
}

void start_ncurses() {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
}

void stop_ncurses() {
    endwin();
}

std::string file_to_string(std::string file_path) {
    std::ifstream file(file_path);
    std::istreambuf_iterator<char> fbegin(file), fend;
    return {fbegin, fend};
}

int step() {
    return getch();
}

long string_to_long(const std::string &str) {
    noecho();
    std::regex re("\\d+");
    if (std::regex_match(str, re))
        return std::stol(str);
    else
        return 0;
}

long step_to() {
    printw("index: ");
    echo();
    char str[13];
    getstr(str);
    return string_to_long(str);
}

long step_by(const long &m_index, const long &m_max_index, const long &m_step_index) {
    if (m_index + m_step_index < 0) {
        return 0;
    }
    if (m_index + m_step_index >= m_max_index) {
        return m_max_index;
    }
    return m_index + m_step_index;
};

//template <class T>
//T max_value(const std::string & file_contents, const std::regex & re)
//{
//    T max = 0;
//    std::sregex_iterator begin(file_contents.begin(), file_contents.end(), re), end;
//    for (auto it = begin; it != end; ++it)
//        max = std::max<T>(stol((*it)[1]), max);
//    return max;
//}

template<class T>
T count_value(const std::string &file_contents, const std::regex &re) {
    T count = 0;
    std::sregex_iterator begin(file_contents.begin(), file_contents.end(), re), end;
    for (auto it = begin; it != end; ++it)
        ++count;
    return count;
}

//find max sub-indexed plot and return it as the stride
long stride_count(const std::string &file_contents) {
    std::smatch count_match;
    std::regex_search(file_contents, count_match, std::regex("PLOT_COUNT = (\\d+)"));
    return string_to_long(count_match[1]);
}

//insert the dat filename into file_contents
std::string insert_dat_file(const std::string &file_contents, const std::string &dat_name) {
    return std::regex_replace(file_contents, std::regex("\\{DAT\\}"), dat_name);
}

//finx the max occurance of #/d+
long plot_count(const std::string &file_contents) {
    return count_value<unsigned long>(file_contents, std::regex("#(\\d+)"));
}

int main(int argc, char **argv) {
    namespace po = boost::program_options;
    namespace fs = boost::filesystem;

    std::string command_file_option = "command-file";
    std::string data_file_option = "data-file";

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            (command_file_option.c_str(), po::value<fs::path>(), "gnu plot command file")
            (data_file_option.c_str(), po::value<fs::path>(), "plot data file");

    po::positional_options_description p_desc;
    p_desc.add(command_file_option.c_str(), 1).add(data_file_option.c_str(), 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p_desc).run(), vm);
    po::notify(vm);

    if (argc <= 1 || vm.count("help")) {
        std::cout << desc << "\n";
        return EXIT_SUCCESS;
    }

    fs::path command_file_path;
    if (vm.count(command_file_option))
        command_file_path = vm[command_file_option].as<fs::path>();

    fs::path data_file_path;
    if (vm.count(data_file_option))
        data_file_path = vm[data_file_option].as<fs::path>();

    bool failure = false;

    if (!fs::exists(command_file_path)) {
        printf("command file does not exist\n");
        failure = true;
    }

    if (!fs::exists(data_file_path)) {
        printf("data file does not exist\n");
        failure = true;
    }

    if (failure)
        return EXIT_FAILURE;

    auto data = file_to_string(data_file_path.string());
    auto command = file_to_string(command_file_path.string());
    command = insert_dat_file(command, data_file_path.string());

    std::regex re_subindex("\\{(\\d+)\\}");

    //process loop
    long index = 0;
    long stride = stride_count(command);
    long max_index = plot_count(data) - 1;

    auto fmt = [&index, stride](const unsigned m_index, const std::string &match) -> std::string {
        return std::to_string((stride * index) + stol(match));
    }; //index can only be 1


    start_ncurses();
    auto gp = start_gnuplot();

    for (int ch = -1; ch != 'q'; ch = step()) {
        erase();
        move(0, 0);
        long increment = 0;

        switch (ch) {
            case '1':
                increment = -10000;
                break;
            case '2':
                increment = -1000;
                break;
            case '3':
                increment = -100;
                break;
            case '4':
                increment = -10;
                break;
            case '5':
                increment = -1;
                break;
            case '6':
                increment = 1;
                break;
            case '7':
                increment = 10;
                break;
            case '8':
                increment = 100;
                break;
            case '9':
                increment = 1000;
                break;
            case '0':
                increment = 10000;
                break;
            case KEY_LEFT:
                increment = -1;
                break;
            case KEY_RIGHT:
                increment = 1;
                break;
            case 'i': //go to index
                increment = step_to() - index;
                break;
            default:
                break;
        }
        index = step_by(index, max_index, increment);

        erase();
        move(0, 0);
        using namespace bsb::regex_ext;
        std::string formatted_command = regex_replace_ext(command,
                                                          re_subindex,
                                                          fmt);
        //print command for user
        printw("current index:  %d\nmax index: %d\n\nplot:\n%s",
               index,
               max_index,
               formatted_command.c_str());
        //print command for gnuplot
        fprintf(gp, "%s \n", formatted_command.c_str());
        fflush(gp);
    }
    stop_gnuplot(gp);
    stop_ncurses();

    return EXIT_SUCCESS;
}

//TODO: Work with variables http://gnuplot.sourceforge.net/docs_4.2/node60.html
