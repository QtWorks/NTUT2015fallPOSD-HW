#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include <string>
#include <stack>
#include <utility>

using std::string;
using std::stack;
using std::pair;

class Graphics;

class GraphicsFactory {
public:
    GraphicsFactory();

    virtual Graphics *buildGraphicsFromFile(const char *fileName);

    string fileContentsAsString(const char *fileName);

    virtual Graphics *extractGraphicsFromOneLine(std::string &contents, int &level);

    void compose();

    stack<std::pair<int, Graphics *>> &getBuildStack() { return _buildStask; }

protected:
    stack<std::pair<int, Graphics *>> _buildStask;
};

#endif // GRAPHICSFACTORY_H
