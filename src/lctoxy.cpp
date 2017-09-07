//////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 Stig Rune Sellevag. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/program_options.hpp>
#include <exception>
#include <fstream>
#include <gsl/gsl>
#include <iostream>
#include <string>
#include <vector>
#include "utils.h"

// Forward declarations:

void get_mass_data(const std::string& filename,
                   std::vector<double>& mass,
                   std::vector<double>& delta_mass);

//
// Program for converting Ultimate 3000 RSCL ASCII chromatograms to XY data.
//
int main(int argc, char* argv[])
{
    namespace po = boost::program_options;

    po::options_description options("Allowed options");
    // clang-format off
    options.add_options()
        ("help,h", "display help message")
        ("mass,m", po::value<std::string>(), "mass file (*.txt)")
        ("chrom,c", po::value<std::string>(), "chromatogram file (*.ascii)");
    // clang-format on
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, options), vm);
    po::notify(vm);

    std::string mass_file;
    std::string chrom_file;

    if (vm.find("help") != vm.end()) {
        std::cout << options << '\n';
        return 0;
    }
    if (vm.find("mass") != vm.end()) {
        mass_file = vm["mass"].as<std::string>();
    }
    else {
        std::cerr << options << '\n';
        return 1;
    }
    if (vm.find("chrom") != vm.end()) {
        chrom_file = vm["chrom"].as<std::string>();
    }
    else {
        std::cerr << options << '\n';
        return 1;
    }

    try {
        std::vector<double> mass;
        std::vector<double> delta_mass;

        get_mass_data(mass_file, mass, delta_mass);
    }
    catch (std::exception& e) {
        std::cerr << "what: " << e.what() << '\n';
        return 1;
    }
}  // main

void get_mass_data(const std::string& filename,
                   std::vector<double>& mass,
                   std::vector<double>& delta_mass)
{
    std::ifstream from;
    fopen(from, filename);

    std::string token;
    double value;

    if (find_section(from, "mass")) {
        while (from >> value) {
            Expects(value > 0.0);
            mass.push_back(value);
        }
    }
    if (find_section(from, "delta_mass")) {
        while (from >> value) {
            Expects(value > 0.0);
            delta_mass.push_back(value);
        }
    }
    Ensures(!mass.empty());
    Ensures(!delta_mass.empty());
    Ensures(mass.size() == delta_mass.size());
}