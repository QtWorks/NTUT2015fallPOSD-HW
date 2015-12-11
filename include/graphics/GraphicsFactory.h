#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include <string>
#include <stack>
#include <utility>

class Graphics;

using std::string;

class GraphicsFactory {
public:
    GraphicsFactory();

    virtual Graphics *buildGraphicsFromFile(const char *fileName);

    string fileContentsAsString(const char *fileName);

    virtual Graphics *extractGraphicsFromOneLine(std::string &contents, int &level);

    void compose();

    std::stack<std::pair<int, Graphics *>> &getBuildStack() { return _buildStask; }

protected:
    std::stack<std::pair<int, Graphics *>> _buildStask;
};

#endif // GRAPHICSFACTORY_H
