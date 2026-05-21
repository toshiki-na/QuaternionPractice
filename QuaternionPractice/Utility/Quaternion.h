#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
#include <algorithm>
#include <DXLib.h>
#include "Vec3.h"

/*
	四元数(クオータニオン)定義、計算の処理用
*/

//四元数の定義
struct Quaternion
{
public:
	float w{ 1.0f };
	float x{ 0.0f };
	float y{ 0.0f };
	float z{ 0.0f };

	//四元数の長さの取得
	inline float Length() const
	{
		float length = std::sqrt(w * w + x * x + y * y + z * z);
		return length;
	}

	//四元数の長さの2乗の取得
	inline float LengthSq() const
	{
		float length_squared = w * w + x * x + y * y + z * z;
		return length_squared;
	}

	//四元数の正規化
	inline Quaternion Normalized() const
	{
		float length = Length();
		Quaternion result = Identity();

		//0除算防止
		if (length > EPSILON)
		{
			result.w = w / length;
			result.x = x / length;
			result.y = y / length;
			result.z = z / length;
		}

		return result;
	}

	//恒等四元数の取得
	inline static Quaternion Identity()
	{
		return Quaternion{ 1.0f, 0.0f, 0.0f, 0.0f };
	}

	//共役四元数の取得
	inline Quaternion Conjugate() const
	{
		return Quaternion{ w, -x, -y, -z };
	}

	//四元数の逆数の取得
	inline Quaternion Inverse() const
	{
		float lengthsq = LengthSq();
		Quaternion result = Identity();

		//0除算防止
		if (lengthsq > EPSILON)
		{
			Quaternion conjugate = Conjugate();
			result.w = conjugate.w / lengthsq;
			result.x = conjugate.x / lengthsq;
			result.y = conjugate.y / lengthsq;
			result.z = conjugate.z / lengthsq;
		}

		return result;
	}

	//XYZ回転順オイラー角表現の取得
	inline Vec3 ToEulerXYZ() const
	{
		//正規化
		Quaternion norm = Normalized();

		float pitch;
		float yaw;
		float roll;

		//ヨー角のsin計算
		float sin_yaw = 2.0f * norm.x * norm.z - 2.0f * norm.w * norm.y;

		//浮動小数点誤差対策
		sin_yaw = std::clamp(sin_yaw, -1.0f, 1.0f);

		//ジンバルロック確認
		if (std::abs(sin_yaw) > 0.9999f)
		{
			//ジンバルロックしている
			//ヨー角の±確認
			if (sin_yaw > 0.0f)
			{
				yaw = 90.0f * DIGREE_TO_RADIAN;
			}
			else
			{
				yaw = -90.0f * DIGREE_TO_RADIAN;
			}

			//1軸分回転が失われているのでロール角は0°とする
			roll = 0.0f;

			//ピッチ角計算
			pitch = atan2f(2 * norm.y * norm.z - 2 * norm.w * norm.x, 1 - 2 * norm.x * norm.x - 2 * norm.z * norm.z);
		}
		else
		{
			//ジンバルロックしていない
			//各軸周りの回転角計算
			yaw = asinf(sin_yaw);
			pitch = atan2f(-2.0f * norm.y * norm.z + 2.0f * norm.w * norm.x, 1.0f - 2.0f * norm.x * norm.x - 2.0f * norm.y * norm.y);
			roll = atan2f(-2.0f * norm.x * norm.y + 2.0f * norm.w * norm.z, 1.0f - 2.0f * norm.y * norm.y - 2.0f * norm.z * norm.z);
		}

		//結果をオイラー角回転のVec3に入れて返す
		Vec3 result;
		result.x = pitch;
		result.y = yaw;
		result.z = roll;

		return result;
	}

	//DXライブラリMATRIXに変換
	inline DxLib::MATRIX ToDXLibMATRIX() const
	{
		//正規化
		Quaternion norm = Normalized();

		//DXライブラリの回転行列に変換して返す
		/*
		 MATRIX
		 |[1 - 2y^2 - 2z^2]	[2xy + 2wz]			[2xz - 2wy]			[0.0]|
		 |[2xy - 2wz]		[1 - 2x^2 - 2z^2]	[2yz + 2wx]			[0.0]|
		 |[2zx + 2wy]		[2yz - 2wx]			[1 - 2x^2 - 2y^2]	[0.0]|
		 |[0.0]				[0.0]				[0.0]				[1.0]|
		*/
		DxLib::MATRIX result = DxLib::MGetIdent();
		result.m[0][0] = 1 - 2 * norm.y * norm.y - 2 * norm.z * norm.z;
		result.m[0][1] = 2 * norm.x * norm.y + 2 * norm.w * norm.z;
		result.m[0][2] = 2 * norm.x * norm.z - 2 * norm.w * norm.y;
		result.m[1][0] = 2 * norm.x * norm.y - 2 * norm.w * norm.z;
		result.m[1][1] = 1 - 2 * norm.x * norm.x - 2 * norm.z * norm.z;
		result.m[1][2] = 2 * norm.y * norm.z + 2 * norm.w * norm.x;
		result.m[2][0] = 2 * norm.x * norm.z + 2 * norm.w * norm.y;
		result.m[2][1] = 2 * norm.y * norm.z - 2 * norm.w * norm.x;
		result.m[2][2] = 1 - 2 * norm.x * norm.x - 2 * norm.y * norm.y;

		return result;
	}
};

//四元数の加算
inline Quaternion operator+(const Quaternion& quaternion_01_, const Quaternion& quaternion_02_)
{
	Quaternion result;
	result.w = quaternion_01_.w + quaternion_02_.w;
	result.x = quaternion_01_.x + quaternion_02_.x;
	result.y = quaternion_01_.y + quaternion_02_.y;
	result.z = quaternion_01_.z + quaternion_02_.z;

	return result;
}

//四元数の加算代入
inline Quaternion& operator+=(Quaternion& quaternion_01_, const Quaternion& quaternion_02_)
{
	quaternion_01_ = quaternion_01_ + quaternion_02_;

	return quaternion_01_;
}

//四元数の減算
inline Quaternion operator-(const Quaternion& quaternion_01_, const Quaternion& quaternion_02_)
{
	Quaternion result;
	result.w = quaternion_01_.w - quaternion_02_.w;
	result.x = quaternion_01_.x - quaternion_02_.x;
	result.y = quaternion_01_.y - quaternion_02_.y;
	result.z = quaternion_01_.z - quaternion_02_.z;

	return result;
}

//四元数の減算代入
inline Quaternion& operator-=(Quaternion& quaternion_01_, const Quaternion& quaternion_02_)
{
	quaternion_01_ = quaternion_01_ - quaternion_02_;

	return quaternion_01_;
}

//四元数のスカラー倍
inline Quaternion operator*(const Quaternion& quaternion_, const float magnification_)
{
	Quaternion result;
	result.w = quaternion_.w * magnification_;
	result.x = quaternion_.x * magnification_;
	result.y = quaternion_.y * magnification_;
	result.z = quaternion_.z * magnification_;
	
	return result;
}
inline Quaternion operator*(const float magnification_, const Quaternion& quaternion_)
{
	Quaternion result;
	result = quaternion_ * magnification_;

	return result;
}

//四元数のスカラー倍代入
inline Quaternion& operator*=(Quaternion& quaternion_, const float magnification_)
{
	quaternion_ = quaternion_ * magnification_;

	return quaternion_;
}

//四元数の乗算
inline Quaternion operator*(const Quaternion& quaternion_01_, const Quaternion& quaternion_02_)
{
	Quaternion result;
	result.w = quaternion_01_.w * quaternion_02_.w - quaternion_01_.x * quaternion_02_.x - quaternion_01_.y * quaternion_02_.y - quaternion_01_.z * quaternion_02_.z;
	result.x = quaternion_01_.w * quaternion_02_.x + quaternion_01_.x * quaternion_02_.w + quaternion_01_.y * quaternion_02_.z - quaternion_01_.z * quaternion_02_.y;
	result.y = quaternion_01_.w * quaternion_02_.y + quaternion_01_.y * quaternion_02_.w + quaternion_01_.z * quaternion_02_.x - quaternion_01_.x * quaternion_02_.z;
	result.z = quaternion_01_.w * quaternion_02_.z + quaternion_01_.z * quaternion_02_.w + quaternion_01_.x * quaternion_02_.y - quaternion_01_.y * quaternion_02_.x;

	return result;
}

//四元数の乗算代入
inline Quaternion& operator*=(Quaternion& quaternion_01_, const Quaternion& quaternion_02_)
{
	quaternion_01_ = quaternion_01_ * quaternion_02_;

	return quaternion_01_;
}

class QuaternionMath
{
public:
	//四元数の回転差分
	inline static Quaternion RotateDelta(const Quaternion& from_, const Quaternion& to_)
	{
		Quaternion result;
		result = to_ * from_.Inverse();

		return result;
	}

	//四元数の内積
	inline static float Dot(const Quaternion& quaternion_01_, const Quaternion& quaternion_02_)
	{
		float result = quaternion_01_.w * quaternion_02_.w + quaternion_01_.x * quaternion_02_.x + quaternion_01_.y * quaternion_02_.y + quaternion_01_.z * quaternion_02_.z;

		return result;
	}

	//オイラー角から回転四元数の取得
	inline static Quaternion EulerXYZToQuaternion(const Vec3& euler_rotate_)
	{
		//ピッチ、ヨー、ロールの回転四元数
		Quaternion pitch = RotateAngleAndAxisToQuaternion(euler_rotate_.x, Vec3{ 1.0f, 0.0f,0.0f });
		Quaternion yaw	 = RotateAngleAndAxisToQuaternion(euler_rotate_.y, Vec3{ 0.0f, 1.0f,0.0f });
		Quaternion roll	 = RotateAngleAndAxisToQuaternion(euler_rotate_.z, Vec3{ 0.0f, 0.0f,1.0f });

		//回転四元数を合成して返す
		Quaternion result = (pitch * yaw * roll).Normalized();

		return result;
	}

	//回転軸と角度から回転四元数の取得
	inline static Quaternion RotateAngleAndAxisToQuaternion(float angle_, const Vec3& axis_)
	{
		//調整用に保存
		Vec3 axis = axis_;

		//回転軸の正規化確認、できてなかったら正規化
		if (std::abs(axis.LengthSq() - 1.0f) > EPSILON)
		{
			axis = axis.Normalized();
		}

		//回転角の半分計算
		float half_angle = angle_ / 2.0f;

		//sin(回転軸の半分)計算
		float sin_half_angle = sinf(half_angle);

		//四元数に変換して返す
		Quaternion result;
		result.w = cosf(half_angle);
		result.x = axis.x * sin_half_angle;
		result.y = axis.y * sin_half_angle;
		result.z = axis.z * sin_half_angle;
		
		return result.Normalized();
	}

	//四元数による回転
	inline static Vec3 QuaternionRotate(const Vec3& vector_, const Quaternion& rotate_)
	{
		//Vec3を純虚四元数に展開
		Quaternion vector = { 0.0f, vector_.x, vector_.y, vector_.z };

		//回転四元数を正規化
		Quaternion rotate = rotate_.Normalized();

		//回転計算(事前に正規化しているので逆数 = 共役)
		Quaternion quaternion_result = rotate * vector * rotate.Conjugate();

		//Vec3に戻して返す
		Vec3 vector_result;
		vector_result.x = quaternion_result.x;
		vector_result.y = quaternion_result.y;
		vector_result.z = quaternion_result.z;

		return vector_result;
	}

	//球面線形補間
	inline static Quaternion Slerp(const Quaternion& start_, const Quaternion& end_, float rate_)
	{
		//補間値が範囲外の場合は端点を返す
		if(rate_ <= 0.0f)
		{
			return start_;
		}
		if (rate_ >= 1.0f)
		{
			return end_;
		}

		//調整用に保存
		Quaternion start = start_;
		Quaternion end = end_;

		//2四元数の単位四元数確認、違ったら正規化
		if (std::abs(start.LengthSq() - 1.0f) > EPSILON)
		{
			start = start.Normalized();
		}
		if (std::abs(end.LengthSq() - 1.0f) > EPSILON)
		{
			end = end.Normalized();
		}

		//変位角ωのcos( = 単位四元数の内積)
		float cos_omega = Dot(start, end);

		//最短経路確認
		if (cos_omega < 0.0f)
		{
			end = end * -1.0f;
			cos_omega = Dot(start, end);
		}

		//浮動小数点誤差対策
		cos_omega = std::clamp(cos_omega, -1.0f, 1.0f);

		//補間割合
		float from_fraction = 0.0f;
		float to_fraction = 0.0f;
		
		//2四元数がほぼ同じなら線形補間
		if (cos_omega > 0.9999f)
		{
			from_fraction = 1.0f - rate_;
			to_fraction = rate_;
		}
		//球面線形補間割合計算
		else
		{
			//cosΘ^2 + sinΘ^2 = 1よりsin_omegaを計算する
			float sin_omega = std::sqrt(1.0f - cos_omega * cos_omega);

			//変位ω計算
			float omega = atan2f(sin_omega, cos_omega);

			//補間割合計算
			from_fraction = sin((1.0f - rate_) * omega) / sin_omega;
			to_fraction = sin(rate_ * omega) / sin_omega;
		}

		//補間四元数を返す
		return (from_fraction * start + to_fraction * end).Normalized();
	}
};
#endif