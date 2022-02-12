#ifndef TAGS_HPP
#define TAGS_HPP

namespace axilib
{
    struct Matrix_tag { };

    struct Submatrix_tag { };

    struct Vector_iterator_tag { };

    struct Row_iterator_tag { };

    struct Reverse_row_iterator_tag { };

    struct Col_iterator_tag { };

    struct Reverse_col_iterator_tag { };

    struct Diagonal_iterator_tag { };

    struct Reverse_diagonal_iterator_tag { };

    struct Matrix_reference_iterator_tag { };

    struct Matrix_reference_row_iterator_tag { };

    struct Matrix_reference_col_iterator_tag { };

    struct From_functor { };

    struct From_container { };

    struct From_list { };

    struct From_other { };

    //Rotation direction

    struct Left { };

    struct Right { };

    //Sorting direction

    struct Ascend { };

    struct Descend { };

    struct Vector_tag;

    struct Row;

    struct Col;

} // namespace axilib

#endif // TAGS_HPP
