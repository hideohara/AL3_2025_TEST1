#include "Player.h"

// デストラクタ
Player::~Player()
{
}

// 初期化
void Player::Initialize(Model* model, uint32_t textureHandle)
{
	// 引数として受け取ったデータをメンバ変数に記録する
	textureHandle_ = textureHandle;
	model_ = model;

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

// 更新
void Player::Update()
{
	// 移動
	worldTransform_.translation_.x += 0.1f;
	worldTransform_.UpdateMatrix();
}

// 描画
void Player::Draw(Camera& camera)
{
	model_->Draw(worldTransform_, camera);
}
