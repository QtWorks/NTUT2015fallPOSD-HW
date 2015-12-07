#include "cppunitlite/TestHarness.h"

#include "original_test.h"
#include "utHW1.h"
#include "utHW2.h"
#include "utHW3.h"
#include "ta.h"
#include "utGraphicFactory.h"
#include "utTryQt.h"

int main(int argc, char **argv) {
    TestResult tr;
    TestRegistry::runAllTests(tr);
    return 0;
}
