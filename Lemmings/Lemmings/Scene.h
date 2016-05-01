#pragma once

class Scene
{
public:
	Scene();
	~Scene();

	virtual void init();
	virtual void update();
	virtual void render();
};