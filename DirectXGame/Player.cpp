#include "Player.h"

using namespace MathUtility;

// デストラクタ
Player::~Player()
{
}

// 初期化
void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// システム
	input_ = Input::GetInstance();

	// 引数として受け取ったデータをメンバ変数に記録する
	textureHandle_ = textureHandle;
	model_ = model;

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

// 更新
void Player::Update()
{
	// キャラクターの移動ベクトル
	Vector3 move = { 0, 0, 0 };

	// キャラクターの移動速さ
	const float kCharacterSpeed = 0.2f;

	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	// 押した方向で移動ベクトルを変更（上下）
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}

	worldTransform_.translation_ += move;

	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw(Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}
