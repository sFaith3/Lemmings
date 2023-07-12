#include "Scene.h"

Scene::Scene(){
	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
	audioManager = SingletonManager::getInstanceSingleton()->getAudioManager();

	idMusic = -1;
}

Scene::~Scene(){
}


void Scene::init(){
}


void Scene::clear(){
}


void Scene::update(){
}


void Scene::render(){
}