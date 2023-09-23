#pragma once 

#include <YAWN/Core/ArrayView.hpp>

#include "Vector3.hpp"

namespace YAWN {
    struct Matrix3 {
        static const Matrix3 Identity;

        static Vector2 ExtractPosition2D(const Matrix3& matrix);

        static Vector3 ExtractEuler(const Matrix3& matrix);

        static float ExtractEuler2D(const Matrix3& matrix);

        static Vector3 ExtractDirection(const Matrix3& matrix);

        static Matrix3 CreateTranslation2D(const Vector2& position);

        static Matrix3 CreateRotation2D(float radians);

        static Matrix3 CreateRotationX(float radians);

        static Matrix3 CreateRotationY(float radians);

        static Matrix3 CreateRotationZ(float radians);

        static Matrix3 CreateRotation(const Vector3& rotation);

        static Matrix3 CreateRotation(float radians, const Vector3& axis);

        static Matrix3 CreateScaling(const Vector3& scale);

        static Matrix3 CreateScaling2D(const Vector2& scale);

        static Matrix3 Invert(const Matrix3& matrix);

        static Matrix3 Transpose(const Matrix3& matrix);

        static Vector3 TransformNormal(const Matrix3& matrix, const Vector3& vector);

        ArrayView<Vector3> AsVectors();

        ArrayView<const Vector3> AsVectors() const;

        float& operator[](int index);

        const float& operator[](int index) const;

        bool operator==(const Matrix3& rhs) const;

        bool operator!=(const Matrix3& rhs) const;

        Matrix3 operator*(const Matrix3& rhs) const;

        Vector3 operator*(const Vector3& rhs) const;

        float Values[9];
    };
}
