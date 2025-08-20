#pragma once
class TitleScene
{
public:
	TitleScene();
	~TitleScene();

	void Init();
	void End();
	void Update();
	void Draw();

	// タイトルシーンが終了しているかどうか
	bool IsSceneEnd() const;

private:
	// シーン終了フラグ
	bool m_isSceneEnd;

};

