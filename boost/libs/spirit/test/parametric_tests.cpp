#include <iostream>
#include <cassert>
#include <string>

using namespace std;

#include "boost/spirit/core.hpp"
#include "boost/spirit/attribute/parametric.hpp"
#include "boost/phoenix/primitives.hpp"
#include "boost/phoenix/operators.hpp"
using namespace boost::spirit;
using namespace phoenix;

///////////////////////////////////////////////////////////////////////////////
//
//  Parametric tests
//
///////////////////////////////////////////////////////////////////////////////
void
parametric_tests()
{
    char ch;
    rule<> r = anychar_p[var(ch) = arg1] >> *f_ch_p(const_(ch));

    parse_info<char const*> pi;
    pi = parse("aaaaaaaaa", r);
    assert(pi.hit);
    assert(pi.full);

    pi = parse("aaaaabaaa", r);
    assert(pi.hit);
    assert(!pi.full);
    assert(string(pi.stop) == "baaa");

    char from = 'a';
    char to = 'z';

    rule<> r2 = *f_range_p(const_(from), const_(to));
    pi = parse("abcdefghijklmnopqrstuvwxyz", r2);
    assert(pi.hit);
    assert(pi.full);

    pi = parse("abcdefghijklmnopqrstuvwxyz123", r2);
    assert(pi.hit);
    assert(!pi.full);
    assert(string(pi.stop) == "123");

    char const* start = "kim";
    char const* end = start + strlen(start);
    rule<> r3 = +f_str_p(const_(start), const_(end));

    pi = parse("kimkimkimkimkimkimkimkimkim", r3);
    assert(pi.hit);
    assert(pi.full);

    pi = parse("kimkimkimkimkimkimkimkimkimmama", r3);
    assert(pi.hit);
    assert(!pi.full);
    assert(string(pi.stop) == "mama");

    pi = parse("joel", r3);
    assert(!pi.hit);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Main
//
///////////////////////////////////////////////////////////////////////////////
int
main()
{
    parametric_tests();
    cout << "Tests concluded successfully\n";
    return 0;
}

