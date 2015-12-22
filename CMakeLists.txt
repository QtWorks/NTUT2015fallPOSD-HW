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
        include/commands
        include/commands/cmd
        src/test
        lib
)

set(SOURCE_FILES

        include/graphics/graphics.h
        include/graphics/simplegraphics.h
        include/graphics/compositegraphics.h
        include/graphics/RootGraphics.h
        include/graphics/GraphicsFactory.h
        include/graphics/MultiRootGraphicFactory.h

        include/gui/shapegraphicitem/CompositeQGraphicsItem.h
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
        include/visitor/QtGraphicsToStandardItemModelVisitor.h

        include/commands/CommandManager.h
        include/commands/cmd/Command.h
        include/commands/cmd/CreateCircleCmd.h
        include/commands/cmd/CreateSquareCmd.h
        include/commands/cmd/CreateRectangleCmd.h
        include/commands/cmd/GroupCmd.h
        include/commands/cmd/UnGroupCmd.h
        include/commands/cmd/DeleteCmd.h
        include/commands/cmd/MoveCmd.h
        include/commands/cmd/UpperLayerCmd.h
        include/commands/cmd/LowerLayerCmd.h


        src/graphices/compositegraphics.cpp
        src/graphices/graphics.cpp
        src/graphices/GraphicsFactory.cpp
        src/graphices/simplegraphics.cpp
        src/graphices/MultiRootGraphicFactory.cpp
        src/graphices/RootGraphics.cpp

        src/gui/shapegraphicitem/CircleQGraphicsItem.cpp
        src/gui/shapegraphicitem/RectangleQGraphicsItem.cpp
        src/gui/shapegraphicitem/ShapeQGraphicsItem.cpp
        src/gui/shapegraphicitem/SquareQGraphicsItem.cpp
        src/gui/shapegraphicitem/CompositeQGraphicsItem.cpp

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
        src/test/utMultiRootGraphics.h

        src/visitor/AreaVisitor.cpp
        src/visitor/DescriptionVisitor.cpp
        src/visitor/QtGraphicsViewVisitor.cpp
        src/visitor/QtGraphicsToStandardItemModelVisitor.cpp

        src/commands/CommandManager.cpp
        src/commands/cmd/Command.cpp
        src/commands/cmd/CreateCircleCmd.cpp
        src/commands/cmd/CreateSquareCmd.cpp
        src/commands/cmd/CreateRectangleCmd.cpp
        src/commands/cmd/GroupCmd.cpp
        src/commands/cmd/UnGroupCmd.cpp
        src/commands/cmd/DeleteCmd.cpp
        src/commands/cmd/MoveCmd.cpp
        src/commands/cmd/UpperLayerCmd.cpp
        src/commands/cmd/LowerLayerCmd.cpp

        src/main.cpp

        )




add_library(cppunitlite STATIC IMPORTED)
set_property(TARGET cppunitlite PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/lib/cppunitlite/libcppunitlite.a)

add_executable(POSD_104598003_HW5 ${SOURCE_FILES})

target_link_libraries(POSD_104598003_HW5 cppunitlite)
target_link_libraries(POSD_104598003_HW5 Qt5::Widgets)