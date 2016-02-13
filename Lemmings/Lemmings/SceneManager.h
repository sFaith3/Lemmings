#include "Utils.h"

class SceneManager
{
private:
	static SceneManager* smInstance;

	int currentScene;

public:
	SceneManager();
	~SceneManager();

	static SceneManager* getInstanceSM();

	void Init(int scene);
	void Update();
	void Render();
};