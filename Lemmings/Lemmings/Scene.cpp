#include "Scene.h"


Scene::Scene(){
	inputManager = InputManager::getInstanceInput();
	audioManager = SingletonManager::getInstanceSingleton()->getAudioManager();
}


Scene::~Scene(){
}


void Scene::init(){
}


void Scene::update(){
}


void Scene::render(){
}