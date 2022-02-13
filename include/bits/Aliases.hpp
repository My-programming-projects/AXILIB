#ifndef TYPE_ALIASES_H
#define TYPE_ALIASES_H

#include "Matrix.tcc"

namespace axilib
{
    using smatrix       = Matrix<short>;
    using imatrix       = Matrix<int>;
    using fmatrix       = Matrix<float>;
    using dmatrix       = Matrix<double>;

    using cplx_smatrix  = Matrix<std::complex<short>>;
    using cplx_imatrix  = Matrix<std::complex<int>>;
    using cplx_fmatrix  = Matrix<std::complex<float>>;
    using cplx_dmatrix  = Matrix<std::complex<double>>;

    template<typename T>
    using Rowvec        = Vector<Row, T>;

    template<typename T>
    using Colvec        = Vector<Col, T>;

} // namespace linarg

#endif // TYPE_ALIASES_H
