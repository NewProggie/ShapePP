// Copyright (c) 2014-2015 Sofien Bouaziz <sofien.bouaziz@gmail.com>
// Copyright (c) 2014-2015 LGG EPFL
// Copyright (c) 2016 Kai Wolf <mail@kai-wolf.me>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "constraint.h"
#include "check.h"
#include <algorithm>
#include <cassert>

namespace shapepp {
namespace {
template <typename T> T clamp(const T &val, const T &low, const T &high) {
  return std::max(low, std::min(val, high));
}
}

Constraint::Constraint(const std::vector<int> &indices, Scalar weight)
    : indices_(indices), weight_(std::sqrt(weight)) {}

std::unique_ptr<Constraint> Constraint::create(const ConstraintType type,
                                               const std::vector<int> &indices,
                                               Scalar weight,
                                               const Matrix3X &positions) {

  switch (type) {
  case ConstraintType::Edge:
    CHECK_EQ(indices.size(), 2);
    return std::make_unique<EdgeStrainConstraint>(indices, weight, positions);
    default:
    return nullptr;
  }
}

EdgeStrainConstraint::EdgeStrainConstraint(const std::vector<int> &indices,
                                           Scalar weight,
                                           const Matrix3X &positions,
                                           Scalar rangeMin,
                                           Scalar rangeMax)
    : Constraint(indices, weight), rangeMin_(rangeMin), rangeMax_(rangeMax) {
  CHECK_EQ(indices.size(), 2);
  Scalar length = (positions.col(indices[1]) - positions.col(indices[0])).norm();
  rest_ = 1.0 / length;
  weight_ *= std::sqrt(length);
}

void EdgeStrainConstraint::project(const Matrix3X &positions,
                                   Matrix3X &projections) const {
  Vector3 edge = positions.col(indices_[1]) - positions.col(indices_[0]);
  Scalar length = edge.norm();
  edge /= length;
  length = clamp(length * rest_, rangeMin_, rangeMax_);
  projections.col(id0_) = weight_ * length * edge;
}

void EdgeStrainConstraint::addConstraint(std::vector<Triplet> &triplets,
                                         int &id0) const {
  id0_ = id0;
  triplets.emplace_back(Triplet(id0_, indices_[0], -weight_ * rest_));
  triplets.emplace_back(Triplet(id0_, indices_[1], weight_ * rest_));
  id0 += 1;
}

void EdgeStrainConstraint::setEdgeLength(Scalar length) {
  rest_ = 1.0 / length;
}

void EdgeStrainConstraint::setRangeMin(Scalar rangeMin) {
  rangeMin_ = rangeMin;
}

void EdgeStrainConstraint::setRangeMax(Scalar rangeMax) {
  rangeMax_ = rangeMax;
}
}
