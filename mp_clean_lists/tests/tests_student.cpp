#include <catch2/catch_test_macros.hpp>
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include "List.h"

using namespace cs225;

// THESE TESTS ARE NOT GRADED AND ARE FOR YOU ONLY

TEST_CASE("List::tripleRotate size 3", "[mine]") {
    List<int> list;

    list.insertBack(2);
    list.insertBack(5);
    list.insertBack(2);

    list.sort();

    stringstream s;
    list.print(s);

    REQUIRE(s.str() == "< 2 2 5 >");
}

// TEST_CASE("List::tripleRotate size 3", "[mine]") {
//     List<int> list;
//     for (int i = 1; i <= 14; ++i)
//         list.insertBack(i);

//     list.reverseNth(4);
//     list.tripleRotate();
//     list.reverseNth(5);
//     list.tripleRotate();
//     list.tripleRotate();
//     list.reverseNth(5);
//     list.reverse();
//     stringstream s;
//     list.print(s);
//     REQUIRE("" == s.str());
// }
// TEST_CASE("List::reverse", "[mine]") {
//   PNG in;        in.readFromFile("../tests/alma.png");
//   PNG expected;  expected.readFromFile("../tests/expected-reverse.png");

//   List<HSLAPixel> list = imageToList(in);
//   list.reverse();
//   PNG out = listToImage(list, in.width(), in.height());
//   out.writeToFile("actual-reverse.png");
//   INFO("Output image `out` saved as actual-reverse.png");

//   REQUIRE( out == expected );
// }
