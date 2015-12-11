cmake_minimum_required(VERSION 3.3)
project(POSD_104598003_HW5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.5.1\\5.5\\mingw492_32\\lib\\cmake")

find_package(Qt5Widgets)

include_directories(
        include
        include/graphics
        include/gui
        include/gui/shapegraphicitem
        include/shapes
        include/visitor
        src/test
        lib
)

set(SOURCE_FILES
        include/graphics/compositegraphics.h
        include/graphics/graphics.h
        include/graphics/GraphicsFactory.h
        include/graphics/simplegraphics.h

        include/gui/shapegraphicitem/CircleQGraphicsItem.h
        include/gui/shapegraphicitem/RectangleQGraphicsItem.h
        include/gui/shapegraphicitem/ShapeQGraphicsItem.h
        include/gui/shapegraphicitem/SquareQGraphicsItem.h

        include/gui/DrawingArea.h
        include/gui/DrawingWindow.h

        include/gui/CoordinateAxisGraphicsItem.h

        include/shapes/boundingbox.h
        include/shapes/circle.h
        include/shapes/line.h
        include/shapes/point.h
        include/shapes/rectangle.h
        include/shapes/shape.h
        include/shapes/square.h

        include/visitor/AreaVisitor.h
        include/visitor/DescriptionVisitor.h
        include/visitor/GraphicsVisitor.h
        include/visitor/QtGraphicsViewVisitor.h


        src/graphices/compositegraphics.cpp
        src/graphices/graphics.cpp
        src/graphices/GraphicsFactory.cpp
        src/graphices/simplegraphics.cpp

        src/gui/shapegraphicitem/CircleQGraphicsItem.cpp
        src/gui/shapegraphicitem/RectangleQGraphicsItem.cpp
        src/gui/shapegraphicitem/ShapeQGraphicsItem.cpp
        src/gui/shapegraphicitem/SquareQGraphicsItem.cpp

        src/gui/CoordinateAxisGraphicsItem.cpp



        src/gui/DrawingArea.cpp
        src/gui/DrawingWindow.cpp

        src/shapes/boundingbox.cpp
        src/shapes/circle.cpp
        src/shapes/line.cpp
        src/shapes/point.cpp
        src/shapes/rectangle.cpp
        src/shapes/shape.cpp
        src/shapes/square.cpp

        src/test/original_test.h
        src/test/ta.h
        src/test/utGraphicFactory.h
        src/test/utHW1.h
        src/test/utHW2.h
        src/test/utHW3.h
        src/test/utTryQt.h

        src/visitor/AreaVisitor.cpp
        src/visitor/DescriptionVisitor.cpp
        src/visitor/QtGraphicsViewVisitor.cpp

        src/main.cpp


        src/gui/shapegraphicitem/CompositeQGraphicsItem.cpp include/gui/shapegraphicitem/CompositeQGraphicsItem.h)

add_library(cppunitlite STATIC IMPORTED)
set_property(TARGET cppunitlite PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/cppunitlite/libcppunitlite.a)

add_executable(POSD_104598003_HW5 ${SOURCE_FILES})

target_link_libraries(POSD_104598003_HW5 cppunitlite)
target_link_libraries(POSD_104598003_HW5 Qt5::Widgets)