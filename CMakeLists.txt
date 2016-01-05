cmake_minimum_required(VERSION 3.3)
project(POSD_104598003_HW7)

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

set(CPPUNITLITE_SOURCE_FILES
        lib/cppunitlite/Failure.cpp
        lib/cppunitlite/SimpleString.cpp
        lib/cppunitlite/Test.cpp
        lib/cppunitlite/TestRegistry.cpp
        lib/cppunitlite/TestResult.cpp

        lib/cppunitlite/Test.h
        lib/cppunitlite/TestRegistry.h
        lib/cppunitlite/TestResult.h
        lib/cppunitlite/TestHarness.h
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

        include/gui/View.h

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
        include/visitor/MoveVisitor.h

        include/commands/CommandManager.h
        include/commands/Command.h
        include/commands/cmd/CreateCircleCommand.h
        include/commands/cmd/CreateRectangleCommand.h
        include/commands/cmd/CreateSquareCommand.h
        include/commands/cmd/DeleteCommand.h
        include/commands/cmd/GroupCommand.h
        include/commands/cmd/UngroupCommnad.h
        include/commands/cmd/UpperCommand.h
        include/commands/cmd/LowerCommand.h
        include/commands/cmd/MoveCommand.h


        include/DrawingController.h
        include/GraphicsModel.h

        include/Observable.h
        include/Observer.h

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

        src/gui/View.cpp

        src/gui/CoordinateAxisGraphicsItem.cpp

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
        src/test/utGraphicsModelObservable.h
        src/test/utObserver.h

        src/visitor/AreaVisitor.cpp
        src/visitor/DescriptionVisitor.cpp
        src/visitor/QtGraphicsViewVisitor.cpp
        src/visitor/QtGraphicsToStandardItemModelVisitor.cpp
        src/visitor/MoveVisitor.cpp

        src/commands/CommandManager.cpp
        src/commands/Command.cpp
        src/commands/cmd/CreateCircleCommand.cpp
        src/commands/cmd/CreateRectangleCommand.cpp
        src/commands/cmd/CreateSquareCommand.cpp
        src/commands/cmd/DeleteCommand.cpp
        src/commands/cmd/GroupCommand.cpp
        src/commands/cmd/UngroupCommnad.cpp
        src/commands/cmd/UpperCommand.cpp
        src/commands/cmd/LowerCommand.cpp
        src/commands/cmd/MoveCommand.cpp

        src/DrawingController.cpp
        src/GraphicsModel.cpp

        src/Observable.cpp
        src/Observer.cpp

        src/main.cpp
        )

add_library(cppunitlite ${CPPUNITLITE_SOURCE_FILES})
add_executable(POSD_104598003_HW7 ${SOURCE_FILES})

target_link_libraries(POSD_104598003_HW7 cppunitlite)
target_link_libraries(POSD_104598003_HW7 Qt5::Widgets)