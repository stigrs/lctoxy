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

#ifndef LCTOXY_UTILS_H
#define LCTOXY_UTILS_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

// Stream handling methods:

// Derived class for reporting file opening errors.
struct Fopen_error : std::runtime_error {
    Fopen_error(std::string s) : std::runtime_error(s) {}
};

// Wrapper function for opening file stream for input.
inline void fopen(std::ifstream& from,
                  const std::string& filename,
                  std::ios_base::openmode mode = std::ios_base::in)
{
    from.open(filename.c_str(), mode);
    if (!from.is_open()) {
        throw Fopen_error("cannot open " + filename);
    }
}

// Wrapper function for opening file stream for output.
inline void fopen(std::ofstream& to,
                  const std::string& filename,
                  std::ios_base::openmode mode = std::ios_base::out)
{
    to.open(filename.c_str(), mode);
    if (!to.is_open()) {
        throw Fopen_error("cannot open " + filename);
    }
}

// Find section in input stream.
inline bool find_section(std::istream& from, const std::string& key)
{
    from.clear();
    from.seekg(0, std::ios_base::beg);

    std::string buf;
    while (std::getline(from, buf)) {
        std::istringstream iss(buf);
        iss >> buf;
        if (buf == key) {
            return true;
        }
    }
    return false;
}

// Stream format methods:

template <typename T>
struct Bound_form;

template <typename T>
std::ostream& operator<<(std::ostream& os, const Bound_form<T>& bf);

// Stroustrup's format class, pp. 635-636 in TC++PL (slightly modified).
template <typename T>
class Format {
public:
    explicit Format(int p = 6)
        : prc(p), wdt(0), ch(' '), fmt(std::ios_base::fmtflags(0))
    {
    }

    Bound_form<T> operator()(T vv) const { return Bound_form<T>(*this, vv); }

    // Set width.
    Format<T>& width(std::size_t w)
    {
        wdt = w;
        return *this;
    }

    // Set fill character.
    Format<T>& fill(char c)
    {
        ch = c;
        return *this;
    }

    // Set precision.
    Format<T>& precision(int p)
    {
        prc = p;
        return *this;
    }

    // Set general format.
    Format<T>& general()
    {
        fmt = std::ios_base::fmtflags(0);
        return *this;
    }

    // Set fixed floating point format.
    Format<T>& fixed()
    {
        fmt = std::ios_base::fixed;
        return *this;
    }

    // Set scientific floating point format using e character.
    Format<T>& scientific()
    {
        fmt = std::ios_base::scientific;
        return *this;
    }

    // Set scientific floating point format using E character.
    Format<T>& scientific_E()
    {
        fmt = std::ios_base::scientific | std::ios_base::uppercase;
        return *this;
    }

private:
    int prc;          // precision, default precision is 6
    std::size_t wdt;  // width, 0 means as wide as necessary
    char ch;          // fill character, default is blank

    std::ios_base::fmtflags fmt;  // format flag value

    friend std::ostream& operator<<<>(std::ostream&, const Bound_form<T>&);
};  // Format

// Form plus value.
template <typename T>
struct Bound_form {
    const Format<T>& f;

    T v;

    Bound_form(const Format<T>& ff, T vv) : f(ff), v(vv) {}

private:
    Bound_form& operator=(const Bound_form&);
};

template <typename T>
std::ostream& operator<<(std::ostream& to, const Bound_form<T>& bf)
{
    std::ostringstream s;

    s.width(bf.f.wdt);
    s.precision(bf.f.prc);
    s.fill(bf.f.ch);

    s << std::setiosflags(bf.f.fmt) << bf.v;
    return to << s.str();
}

// String methods:

// Derived class for handling string find errors.
struct String_find_error : std::runtime_error {
    String_find_error(std::string s) : runtime_error(s) {}
};

// Strip suffix from filename.
inline std::string strip_suffix(const std::string& filename,
                                const std::string& suffix)
{
    std::string basename       = filename;
    std::string::size_type pos = basename.rfind(suffix);
    if (pos == std::string::npos) {
        throw String_find_error(filename + " does not contain " + suffix);
    }
    return basename.erase(pos, basename.size() - pos);
}

// Get suffix from filename.
inline std::string get_suffix(const std::string& filename)
{
    std::string suffix         = filename;
    std::string::size_type pos = suffix.rfind(".");
    if (pos == std::string::npos) {
        throw String_find_error(filename + " does not have a suffix");
    }
    return suffix.erase(0, pos);
}

#endif  // LCTOXY_UTILS_H
