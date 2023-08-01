#include "SceneCodeLevel.h"

SceneCodeLevel* SceneCodeLevel::gInstance = NULL;

SceneCodeLevel::SceneCodeLevel()
{
}

SceneCodeLevel::~SceneCodeLevel()
{
}


SceneCodeLevel* SceneCodeLevel::getInstanceSceneCodeLevel(){
	if (gInstance == NULL)
		gInstance = new SceneCodeLevel();

	return gInstance;
}


void SceneCodeLevel::init(){

}


void SceneCodeLevel::update(){

}


void SceneCodeLevel::render(){

}