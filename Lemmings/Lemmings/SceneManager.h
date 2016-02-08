#pragma once
class SceneManager
{
private:
	int currentScene;

public:
	SceneManager();
	void Init(int scene);
	void Update();
	void Render();
	~SceneManager();
};

