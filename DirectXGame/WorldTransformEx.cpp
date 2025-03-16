
//#include "MathUtilityForText.h"
//#include "WorldTransform.h"

#include <KamataEngine.h>

using namespace KamataEngine;
using namespace MathUtility;

void WorldTransform::UpdateMatrix() {
	// スケール、回転、平行移動を合成して行列を計算する
	//matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	// スケーリング行列の作成
	Matrix4x4 matScale = MakeScaleMatrix(scale_);

	Matrix4x4 matRotX = MakeRotateXMatrix(rotation_.x);
	Matrix4x4 matRotY = MakeRotateYMatrix(rotation_.y);
	Matrix4x4 matRotZ = MakeRotateZMatrix(rotation_.z);
	// 回転行列の合成
	Matrix4x4 matRot = matRotZ * matRotX * matRotY;

	// 平行移動行列の作成
	Matrix4x4 matTrans = MakeTranslateMatrix(translation_);

	// スケーリング、回転、平行移動の合成
	//Matrix4x4 matTransform = matScale * matRot * matTrans;
	matWorld_ = matScale * matRot * matTrans;

	// 定数バッファに転送する
	TransferMatrix();
}