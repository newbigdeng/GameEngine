#include "Game.h"
#include "TestObject.h"
#include <iostream>

//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

bool Game::Init()
{
	auto& fs = eng::Engine::GetInstance().GetFileSystem();
	//auto path = fs.GetAssetsFolder()/"brick.png";

	//auto texture = eng::Texture::Load("texture/brick.png");

	m_scene = new eng::Scene();
	eng::Engine::GetInstance().SetScene(m_scene);

	auto camera = m_scene->CreateObject("Camera");
	camera->AddComponent(new eng::CameraComponent);
	camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
	camera->AddComponent(new eng::PlayerControllerCompnent);

	m_scene->SetMainCamera(camera);
	//m_scene->CreateObject<TestObject>("TestObject");

	auto material = eng::Material::Load("materials/brick.mat");

	auto mesh = eng::Mesh::CreateCube();

	auto ObjectA = m_scene->CreateObject("ObjectA");
	ObjectA->AddComponent(new eng::MeshComponent(material, mesh));
	ObjectA->SetPosition(glm::vec3(1.5f, 0.8f, -1.0f));

	auto ObjectB = m_scene->CreateObject("ObjectA");
	ObjectB->AddComponent(new eng::MeshComponent(material, mesh));
	ObjectB->SetPosition(glm::vec3(-1.6f, 1.0f, 1.0f));
	ObjectB->SetRotation(glm::quat(glm::vec3(0.0f, 2.0f, 0.0f)));

	auto ObjectC = m_scene->CreateObject("ObjectA");
	ObjectC->AddComponent(new eng::MeshComponent(material, mesh));
	ObjectC->SetPosition(glm::vec3(2.0f, -0.5f, 2.0f));
	ObjectC->SetRotation(glm::quat(glm::vec3(1.0f, 0.0f, 1.0f)));
	ObjectC->SetScale(glm::vec3(1.5f, 1.5f, 1.5f));

	//auto suzanneMesh = eng::Mesh::Load("models/Suzanne.gltf");
	//auto suzanneMaterial = eng::Material::Load("materials/suzanne.mat");

	//auto SuzanneObj = m_scene->CreateObject("Suznana");
	//SuzanneObj->AddComponent(new eng::MeshComponent(suzanneMaterial, suzanneMesh));
	//SuzanneObj->SetPosition(glm::vec3(0.0f, 0.0f, -2.0f));
	auto suzanne = eng::GameObject::LoadGLTF("models/Suzanne.gltf");
	suzanne->SetPosition(glm::vec3(0.0f, 0.0f, -2.0f));

	auto light = m_scene->CreateObject("Light");
	auto lightComp = new eng::LightComponent();
	lightComp->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	light->AddComponent(lightComp);
	light->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));

	return true;
}

void Game::Update(float deltaTime)
{
	m_scene->Update(deltaTime);
}

void Game::Destory()
{
	std::cout << "´Ý»Ù" << std::endl;
}
