#include "GraphicsFactory.h"
#include "simplegraphics.h"
#include "compositegraphics.h"
#include "circle.h"
#include "rectangle.h"
#include "square.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

GraphicsFactory::GraphicsFactory() {
    //ctor
}

Graphics *GraphicsFactory::buildGraphicsFromFile(const char *fileName) {
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

    // read all files, and then compose all graphics to one graphics
    while (_buildStask.size() > 1) {
        compose();
    }
    Graphics *res = get<1>(_buildStask.top());

    return res;
}

string GraphicsFactory::fileContentsAsString(const char *fileName) {
    ostringstream oss;
    ifstream ifs;

    ifs.open(fileName, ios::in);

    if (!ifs.is_open()) {
        throw string("File does not exist.");
    }

    while (!ifs.eof()) {
        string o;
        getline(ifs, o);
        if (o != "") {
            oss << o << "\n";
        }
    }
    ifs.close();

    return oss.str();
}

Graphics *GraphicsFactory::extractGraphicsFromOneLine(std::string &contents, int &level) {
    istringstream iss(contents);
    string s;
    iss >> s;

    // process space to determine level
    int i = 0;
    while (contents[i] == ' ') {
        i++;
    }
    level = i / 2;

    // to determine is composite or simple graphic
    if (s == "Comp") {
        return new CompositeGraphics();
    } else {
        // split string to arg array
        unsigned int sstart = 0, send = 0;
        string arg[5];
        int id = 0;
        while (true) {
            if (send >= s.size()) {
                throw std::string("Format Error");
            }
            if (s[send + 1] == ')') {
                arg[id] = s.substr(sstart, send - sstart + 1);
                id++;
                sstart = send + 2;
                break;
            }
            if (s[send + 1] == ',') {
                arg[id] = s.substr(sstart, send - sstart + 1);
                id++;
                sstart = send + 2;
            }
            if (s[send] == '(') {
                sstart = send + 1;
            }
            send++;
        }

        // To construct Shape
        Shape *shape;
        if (s[0] == 'C') {
            int x = -1, y = -1, r = -1;
            x = atoi(arg[0].c_str());
            y = atoi(arg[1].c_str());
            r = atoi(arg[2].c_str());
            shape = new Circle(x, y, r);
        } else if (s[0] == 'R') {
            int x, y, w, h;
            x = atoi(arg[0].c_str());
            y = atoi(arg[1].c_str());
            w = atoi(arg[2].c_str());
            h = atoi(arg[3].c_str());
            shape = new Rectangle(x, y, w, h);
        } else if (s[0] == 'S') {
            int x, y, l;
            x = atoi(arg[0].c_str());
            y = atoi(arg[1].c_str());
            l = atoi(arg[2].c_str());
            shape = new Square(x, y, l);
        } else {
            throw string("Unknown Shape");
        }
        return new SimpleGraphics(shape);
    }
}

void GraphicsFactory::compose() {
    if (_buildStask.empty()) return;
    int currentLevel = get<0>(_buildStask.top());

    stack<Graphics *> tmpStack;

    while (get<0>(_buildStask.top()) == currentLevel) {
        tmpStack.push(get<1>(_buildStask.top()));
        _buildStask.pop();
    }

    while (!tmpStack.empty()) {
        (static_cast<CompositeGraphics *>(get<1>(_buildStask.top())))->add(tmpStack.top());
        tmpStack.pop();
    }
}
