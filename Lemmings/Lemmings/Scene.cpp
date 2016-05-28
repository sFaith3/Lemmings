#include "Scene.h"


Scene::Scene(){
	inputManager = SingletonManager::getInstanceSingleton()->getInputManager();
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