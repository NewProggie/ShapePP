// Copyright (c) 2014 Sofien Bouaziz <sofien.bouaziz@gmail.com>
// Copyright (c) 2014 LGG EPFL
// Copyright (c) 2016 Kai Wolf <mail@kai-wolf.me>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SHAPE_PP_FORCE_H
#define SHAPE_PP_FORCE_H

#include "common.h"
#include "types.h"

/// @file This file contains all the forces (defined as accelerations)

namespace shapepp {

/// @brief Base class of any force, defining an interface.
class SHAPEPP_EXPORT Force {
  public:
    virtual ~Force() = default;
    virtual Vector3 get(const Matrix3X& positions, int id) const = 0;
};

/// @brief Constant force for all vertices
class SHAPEPP_EXPORT GravityForce : public Force {
  public:
    explicit GravityForce(const Vector3& force) : force_(force) {}
    Vector3 get(const Matrix3X& positions, int id) const override {
        return force_;
    }

  private:
    Vector3 force_;
};

/// @brief Constant force for a unique vertex
class SHAPEPP_EXPORT VertexForce : public Force {
  public:
    explicit VertexForce(const Vector3& force = Vector3::Zero(), int id = -1)
        : force_(force), id_(id) {}
    Vector3 get(const Matrix3X& positions, int id) const override {
        return id == id_ ? force_ : Vector3::Zero();
    }
    void setId(int id) {
        id_ = id;
    }
    void setForce(const Vector3& force) {
        force_ = force;
    }

  private:
    Vector3 force_;
    int id_;
};
}

#endif
