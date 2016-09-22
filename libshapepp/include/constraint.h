// Copyright (c) 2014 Sofien Bouaziz <sofien.bouaziz@gmail.com>
// Copyright (c) 2014 Bailin Deng <bailin.deng@epfl.ch>
// Copyright (c) 2014 Mario Deuss <mario.deuss@epfl.ch>
// Copyright (c) 2014 LGG EPFL
// Copyright (c) 2016 Kai Wolf <mail@kai-wolf.me>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHAPE_PP_CONSTRAINT_H
#define SHAPE_PP_CONSTRAINT_H

#include "common.h"
#include "types.h"
#include <cmath>
#include <memory>
#include <vector>

namespace shapepp {

enum class ConstraintType {
  Edge,
  Triangle,
  Tetrahedron,
  Area,
  Volume,
  Bending,
  Closeness,
  Line,
  Plane,
  Circle,
  Sphere,
  Similarity,
  Rigid,
  Rectangle,
  Parallelogram,
  Laplacian,
  LaplacianDisplacement
};

class SHAPEPP_EXPORT Constraint {
public:
  Constraint(const std::vector<int> &indices, Scalar weight);
  virtual ~Constraint() = default;

  /// @brief Creates a concrete constraint with a number of indices, a weight
  /// and the initial point positions
  /// @param type      ConstraintType
  /// @param indices   Number of indices of the vertices to be constrained
  /// @param weight    Weight of the constraint to be added relative to the
  ///                  other constraints
  /// @param positions Positions of all the n vertices stacked in a 3 by n
  ///                  matrix
  /// @return A newly created constraint
  static std::unique_ptr<Constraint> create(const ConstraintType type,
                                            const std::vector<int> &indices,
                                            Scalar weight,
                                            const Matrix3X &positions);

  /// @brief Find the closes configuration from the input positions that
  /// satisfy this constraint
  /// @param positions   Positions of all the n vertices stacked in a 3 by n
  ///                    matrix
  /// @param projections Projections of the vertices involved in this
  ///                    constraint
  virtual void project(const Matrix3X &positions,
                       Matrix3X &projections) const = 0;

  /// @brief Add the constraint to the linear system
  /// @param triplets Vector of triplets, each representing an entry in a
  ///                 sparse matrix
  /// @param id0      First row index of this constraint in the sparse matrix.
  ///                 Out: Last row index plus one
  virtual void addConstraint(std::vector<Triplet> &triplets,
                             int &id0) const = 0;

  /// @brief Number of vertices involved in this constraint
  std::size_t numIndices() const { return indices_.size(); }

protected:
  std::vector<int> indices_;
  Scalar weight_;
  mutable int id0_;
};

class SHAPEPP_EXPORT EdgeStrainConstraint : public Constraint {
public:
  /// @brief The target length is set to the distance of the two vertices
  /// in the parameter positions. The parameters rangeMin/rangeMax may be
  /// used to specify a target range for the distance (equivalent to the edge
  /// length) [rangeMin * distance, rangeMax * distance]
  /// @param indices   The two indices of the vertices of the edge
  /// @param weight    Weight of the constraint to be added relative to the
  ///                  other constraints
  /// @param positions Positions of all the n vertices stacked in a 3 by n
  /// matrix
  /// @param rangeMin  Factor to determine the minimal distance from the
  ///                  target length: rangeMin * distance
  /// @param rangeMax  Factor to determine the maximal distance from the
  ///                  target length: rangeMax * distance
  EdgeStrainConstraint(const std::vector<int> &indices, Scalar weight,
                       const Matrix3X &positions, Scalar rangeMin = 1.0,
                       Scalar rangeMax = 1.0);
  virtual ~EdgeStrainConstraint() = default;

  /// @brief Find the closest configuration from the input positions that
  /// satisfy this constraint
  void project(const Matrix3X &positions, Matrix3X &projections) const override;

  void addConstraint(std::vector<Triplet> &triplets, int &id0) const override;
  void setEdgeLength(Scalar length);
  void setRangeMin(Scalar rangeMin);
  void setRangeMax(Scalar rangeMax);

private:
  Scalar rest_;
  Scalar rangeMin_;
  Scalar rangeMax_;
};
}

#endif
