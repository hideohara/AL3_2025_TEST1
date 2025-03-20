#include <Windows.h>
#include <KamataEngine.h>

using namespace KamataEngine;
//using namespace MathUtility;

// --------------------------------
// 仮に、ここに入力
// ワールド変換データ
WorldTransform worldTransform_;
// モデル
Model* model_ = nullptr;
// テクスチャハンドル
uint32_t textureHandle_ = 0u;
// カメラ
Camera camera_;
// DirectXCommon
DirectXCommon* dxCommon_ = nullptr;
// --------------------------------

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow();

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(1280, 720, true);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize();

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	//TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::GetInstance()->Initialize("Resources/");
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

#pragma endregion


	// カメラ初期化
	camera_.Initialize();

	// ワールド変換の初期化
	worldTransform_.Initialize();

	// 3Dモデルの生成
	model_ = Model::Create();

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	dxCommon_ = DirectXCommon::GetInstance();

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		// 軸表示の更新
		//axisIndicator->Update();
		// ImGui受付終了
		imguiManager->End();

		// ----------------------------
		// 更新処理
		worldTransform_.translation_.x += 0.1f;
		worldTransform_.UpdateMatrix();
		//camera_.translation_.y += 0.1f;
		//camera_.UpdateMatrix();
		// ----------------------------

		// 描画開始
		dxCommon->PreDraw();
		// ImGui描画
		imguiManager->Draw();

		// ----------------------------
		// 描画処理
		
		// コマンドリストの取得
		ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

		// 3Dオブジェクト描画前処理
		Model::PreDraw(commandList);
		model_->Draw(worldTransform_, camera_);

		// 3Dオブジェクト描画後処理
		Model::PostDraw();
		// ------------------------------
		
		// 描画終了
		dxCommon->PostDraw();
	}

	// --------------------------------
	// 仮に、ここで削除
	delete model_;
	// --------------------------------
	
	// 3Dモデル解放
	Model::StaticFinalize();
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}
