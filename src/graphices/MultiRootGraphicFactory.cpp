#include "MultiRootGraphicFactory.h"
#include "RootGraphics.h"

#include <fstream>

using namespace std;

Graphics *MultiRootGraphicFactory::buildGraphicsFromFile(const char *fileName) {
    ifstream ifs;
    ifs.open(fileName, ios::in);
    if (!ifs.is_open()) {
        throw string("File does not exist.");
    }
    string line;
    while (!ifs.eof()) {
        getline(ifs, line);
        if (line != "") {
            int level = -1;
            // use the line to generate graphics objects
            Graphics *g = extractGraphicsFromOneLine(line, level);
            // if this level small than previous level, compose the graphics
            while (level > 0 && level < get<0>(_buildStask.top())) {
                compose();
            }
            // finally, push the current graphics and level to stacks
            _buildStask.push(make_pair(level, g));
        }
    }

    RootGraphics *rg = new RootGraphics;

    stack<Graphics *> s;

    // read all files, and then compose all graphics to one graphics
    while (_buildStask.size() > 0) {
        if (get<0>(_buildStask.top()) > 0) {
            compose();
        } else {
            s.push(get<1>(_buildStask.top()));
            _buildStask.pop();
        }
    }
    while (s.size() > 0) {
        rg->add(s.top());
        s.pop();
    }

    return rg;
}
