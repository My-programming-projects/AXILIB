TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    include/Axi.hpp \
    include/Matrix/Algorithms.hpp \
    include/Matrix/Aliases.hpp \
    include/Matrix/Axilib_compare.hpp \
    include/Matrix/Base_experimental.hpp \
    include/Matrix/Base_experimental.tcc \
    include/Matrix/Concepts.hpp \
    include/Matrix/Conversions.hpp \
    include/Matrix/Delivered_iterator.hpp \
    include/Matrix/Exceptions.hpp \
    include/Matrix/From_string.hpp \
    include/Matrix/From_string.tcc \
    include/Matrix/Generated.hpp \
    include/Matrix/Io.hpp \
    include/Matrix/Iterator.hpp \
    include/Matrix/Iterator_support.hpp \
    include/Matrix/Macros.hpp \
    include/Matrix/Math.hpp \
    include/Matrix/Matrix.h.autosave \
    include/Matrix/Matrix.hpp \
    include/Matrix/Matrix.tcc \
    include/Matrix/Matrix_initializer.hpp \
    include/Matrix/Matrix_initializer.tcc \
    include/Matrix/Matrix_reference.hpp \
    include/Matrix/Matrix_reference.tcc \
    include/Matrix/Matrix_support_funcs.hpp \
    include/Matrix/Operations.hpp \
    include/Matrix/Ops.hpp \
    include/Matrix/Range.hpp \
    include/Matrix/Size.hpp \
    include/Matrix/Size.tcc \
    include/Matrix/Square.hpp \
    include/Matrix/Square_matrix.hpp.autosave \
    include/Matrix/Square_matrix.tcc.autosave \
    include/Matrix/Tags.hpp \
    include/Matrix/Traits.hpp \
    include/Matrix/Vector.hpp \
    include/Matrix/Vector.tcc \
    include/axi_config.hpp

INCLUDEPATH += C:\Armadillo1\armadillo-9.800.1\include
DEPENDPATH += C:\Armadillo1\armadillo-9.800.1\include
