// Copyright (c) 2014 Sofien Bouaziz <sofien.bouaziz@gmail.com>
// Copyright (c) 2014 LGG EPFL
// Copyright (c) 2016 Kai Wolf <mail@kai-wolf.me>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHAPE_PP_TYPES_H
#define SHAPE_PP_TYPES_H

#include <Eigen/Dense>
#include <Eigen/Sparse>

namespace shapepp {

using Scalar = double;

// Dense
template <int Rows, int Cols,
          int Options = (Eigen::ColMajor | Eigen::AutoAlign)>
using MatrixT = Eigen::Matrix<Scalar, Rows, Cols, Options>;

using Vector2 = MatrixT<2, 1>;
using Vector3 = MatrixT<3, 1>;
using Vector4 = MatrixT<4, 1>;
using VectorX = MatrixT<Eigen::Dynamic, 1>;

using Matrix22 = MatrixT<2, 2>;
using Matrix23 = MatrixT<2, 3>;
using Matrix32 = MatrixT<3, 2>;
using Matrix33 = MatrixT<3, 3>;
using Matrix34 = MatrixT<3, 4>;
using Matrix3X = MatrixT<3, Eigen::Dynamic>;
using Matrix44 = MatrixT<4, 4>;
using MatrixXX = MatrixT<Eigen::Dynamic, Eigen::Dynamic>;

// Sparse
template <int Options = Eigen::ColMajor>
using SparseMatrixT = Eigen::SparseMatrix<Scalar, Options>;
using SparseMatrix = SparseMatrixT<>;
using Triplet = Eigen::Triplet<Scalar>;
}

#endif
