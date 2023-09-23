#include <YAWN/Math/Matrix3.hpp>
#include <YAWN/Core/Assert.hpp>
#include <YAWN/Core/Memory.hpp>

using namespace YAWN;

const Matrix3 Matrix3::Identity = {
    1, 0, 0,
    0, 1, 0,
    0, 0, 1,
};

Vector2 Matrix3::ExtractPosition2D(const Matrix3& matrix) {
    return Vector2(matrix[6], matrix[7]);
}

Vector3 Matrix3::ExtractEuler(const Matrix3& matrix) {
    YAWN_ASSERT(0 && "Not implemented");

    return Vector3::Zero;
}

float Matrix3::ExtractEuler2D(const Matrix3& matrix) {
    return Math::Atan2(matrix[1], matrix[0]); 
}

Vector3 Matrix3::ExtractDirection(const Matrix3& matrix) {
    return Vector3::Normalize(TransformNormal(matrix, Vector3::AxisZ));
}

Matrix3 Matrix3::CreateTranslation2D(const Vector2& position) {
    return {
        1, 0, 0,
        0, 1, 0,
        position.X, position.Y, 1.0
    };
}

Matrix3 Matrix3::CreateRotation2D(float radians) {
    return CreateRotationZ(radians);
}

Matrix3 Matrix3::CreateRotationX(float radians) {
    const float c = Math::Cos(radians);
    const float s = Math::Sin(radians);

    return {
        1, 0, 0,
        0, c, s,
        0, -s, c,
    };
}

Matrix3 Matrix3::CreateRotationY(float radians) {
    const float c = Math::Cos(radians);
    const float s = Math::Sin(radians);

    return {
        c, 0, -s,
        0, 1, 0,
        s, 0, c,
    };
}

Matrix3 Matrix3::CreateRotationZ(float radians) {
    const float c = Math::Cos(radians);
    const float s = Math::Sin(radians);

    return {
        c, s, 0, 
        -s, c, 0,
        0, 0, 1
    };
}

Matrix3 Matrix3::CreateRotation(const Vector3& rotation) {
    return CreateRotationY(rotation.Y) * CreateRotationX(rotation.X) * CreateRotationZ(rotation.Z);
}

Matrix3 Matrix3::CreateRotation(float radians, const Vector3& axis) {
    const float a = radians;
    const float c = Math::Cos(a);
    const float s = Math::Sin(a);
    const Vector3 naxis = Vector3::Normalize(axis);
    const Vector3 temp = naxis * (1.0f - c);

    Matrix3 result = Matrix3::Identity;
    result[0] = c + temp[0] * naxis[0];
    result[1] = 0 + temp[0] * naxis[1] + s * naxis[2];
    result[2] = 0 + temp[0] * naxis[2] - s * naxis[1];

    result[4] = 0 + temp[1] * naxis[0] - s * naxis[2];
    result[5] = c + temp[1] * naxis[1];
    result[6] = 0 + temp[1] * naxis[2] + s * naxis[0];

    result[8] = 0 + temp[2] * naxis[0] + s * naxis[1];
    result[9] = 0 + temp[2] * naxis[1] - s * naxis[0];
    result[10] = c + temp[2] * naxis[2];
    return result;
}

Matrix3 Matrix3::CreateScaling(const Vector3& scale) {
    return {
        scale.X, 0, 0,
        0, scale.Y, 0,
        0, 0, scale.Z,
    };
}

Matrix3 Matrix3::CreateScaling2D(const Vector2& scale) {
    return {
        scale.X, 0, 0,
        0, scale.Y, 0,
        0, 0, 1.0,
    };
}

Matrix3 Matrix3::Invert(const Matrix3& matrix) {
    Matrix3 out;
    out[0] = matrix[4] * matrix[8] - matrix[5] * matrix[7];
    out[1] = matrix[2] * matrix[7] - matrix[1] * matrix[8];
    out[2] = matrix[1] * matrix[5] - matrix[2] * matrix[4];
    out[3] = matrix[5] * matrix[6] - matrix[3] * matrix[8];
    out[4] = matrix[0] * matrix[8] - matrix[2] * matrix[6];
    out[5] = matrix[2] * matrix[3] - matrix[0] * matrix[5];
    out[6] = matrix[3] * matrix[7] - matrix[4] * matrix[6];
    out[7] = matrix[1] * matrix[6] - matrix[0] * matrix[7];
    out[8] = matrix[0] * matrix[4] - matrix[1] * matrix[3];

    const float det = matrix[0] * matrix[4] * matrix[8] + matrix[1] * matrix[5] * matrix[6] + matrix[2] * matrix[3] * matrix[7] -
        matrix[2] * matrix[4] * matrix[6] + matrix[0] * matrix[5] * matrix[7] + matrix[1] * matrix[3] * matrix[8];
    const float invDet = det != 0 ? (1 / det) : 0;

    return {
        out[0] * invDet, out[1] * invDet, out[2] * invDet,
        out[3] * invDet, out[4] * invDet, out[5] * invDet,
        out[6] * invDet, out[7] * invDet, out[8] * invDet,
    };
}

Matrix3 Matrix3::Transpose(const Matrix3& matrix) {
    return {
        matrix[0], matrix[3], matrix[6],
        matrix[1], matrix[4], matrix[7], 
        matrix[2], matrix[5], matrix[8],
    };
}

Vector3 Matrix3::TransformNormal(const Matrix3& matrix, const Vector3& vector) {
    return Vector3(
        vector.X * matrix[0] + vector.Y * matrix[3] + vector.Z * matrix[6],
        vector.X * matrix[1] + vector.Y * matrix[4] + vector.Z * matrix[7],
        vector.X * matrix[2] + vector.Y * matrix[5] + vector.Z * matrix[8]
    );
}

ArrayView<Vector3> Matrix3::AsVectors() {
    return ArrayView<Vector3>(reinterpret_cast<Vector3*>(&Values[0]), 3);
}

ArrayView<const Vector3> Matrix3::AsVectors() const {
    return ArrayView<const Vector3>(reinterpret_cast<const Vector3*>(&Values[0]), 3);
}

Matrix3 Matrix3::operator*(const Matrix3& rhs) const {
    const Matrix3& lhs = *this;

    return {
        lhs[0] * rhs[0] + lhs[3] * rhs[1] + lhs[6] * rhs[2],
        lhs[1] * rhs[0] + lhs[4] * rhs[1] + lhs[7] * rhs[2],
        lhs[2] * rhs[0] + lhs[5] * rhs[1] + lhs[8] * rhs[2],

        lhs[0] * rhs[3] + lhs[3] * rhs[4] + lhs[6] * rhs[5],
        lhs[1] * rhs[3] + lhs[4] * rhs[4] + lhs[7] * rhs[5],
        lhs[2] * rhs[3] + lhs[5] * rhs[4] + lhs[8] * rhs[5],

        lhs[0] * rhs[6] + lhs[3] * rhs[7] + lhs[6] * rhs[8],
        lhs[1] * rhs[6] + lhs[4] * rhs[7] + lhs[7] * rhs[8],
        lhs[2] * rhs[6] + lhs[5] * rhs[7] + lhs[8] * rhs[8],
    };
}

Vector3 Matrix3::operator*(const Vector3& rhs) const {
    return TransformNormal(*this, rhs);
}

float& Matrix3::operator[](int index) {
    YAWN_ASSERT(index >= 0 && index < 9);
    return Values[index];
}

const float& Matrix3::operator[](int index) const {
    YAWN_ASSERT(index >= 0 && index < 9);
    return Values[index];
}

bool Matrix3::operator==(const Matrix3& rhs) const {
    return Memory::Compare(Values, rhs.Values, sizeof(Values)) == 0;
}

bool Matrix3::operator!=(const Matrix3& rhs) const {
    return Memory::Compare(Values, rhs.Values, sizeof(Values)) != 0;
}
