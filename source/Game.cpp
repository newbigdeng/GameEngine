#include "Game.h"
#include "TestObject.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

bool Game::Init()
{
	auto& fs = eng::Engine::GetInstance().GetFileSystem();
	auto path = fs.GetAssetsFolder()/"brick.png";
	int width, height, channels;
	unsigned char* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);

	std::shared_ptr<eng::Texture> texture;
	if (data)
	{
		texture = std::make_shared<eng::Texture>(width, height, channels, data);
		std::cout << "Image succeed" << std::endl;
		stbi_image_free(data);
	}

	m_scene = new eng::Scene();

	auto camera = m_scene->CreateObject("Camera");
	camera->AddComponent(new eng::CameraComponent);
	camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
	camera->AddComponent(new eng::PlayerControllerCompnent);

	m_scene->SetMainCamera(camera);
	m_scene->CreateObject<TestObject>("TestObject");
	

	std::string vertexShaderSource = R"(
		#version 330 core
		layout(location=0)in vec3 position;
		layout(location=1)in vec3 color;
		layout(location=2)in vec2 uv;

		uniform mat4 uModel;
		uniform mat4 uView;
		uniform mat4 uProjection;

		out vec3 vColor;
		out vec2 vUV;
		void main()
		{
			vColor = color;
			vUV = uv;
			gl_Position = uProjection * uView * uModel * vec4(position,1.0);
		}
	)";
	std::string fragmentShaderSource = R"(
		#version 330 core
		in vec3 vColor;
		in vec2 vUV;
		out vec4 FragColor;
		
		uniform sampler2D brick;
		uniform vec4 uColor;
		
		void main()
		{
			vec4 texColor = texture(brick,vUV);
			FragColor = texColor * vec4(vColor,1.0f);
		}
	)";

	auto& graphicsAPI = eng::Engine::GetInstance().GetGraphicsAPI();
	auto shaderProgram = graphicsAPI.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

	auto material = std::make_shared<eng::Material>();
	material->SetShaderProgram(shaderProgram);
	material->SetParam("brick", texture);


	std::vector<float>vertices{
		//前面
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	   -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	   -0.5f,-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

		//上面
		0.5f, 0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	   -0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	   -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

		//右面
		0.5f, 0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f,-0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

		//左边
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

		//底部
		0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	   -0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	   -0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

		//后面
	   -0.5f, 0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	    0.5f,-0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	   -0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	};
	std::vector<unsigned int>indices{
		//前面
		0,1,2,
		0,2,3,
		//上面
		4,5,6,
		4,6,7,
		//右面
		8,9,10,
		8,10,11,
		//左面
		12,13,14,
		12,14,15,
		//底面
		16,17,18,
		16,18,19,
		//后面
		20,21,22,
		20,22,23
	};
	eng::VertexLayout layout;

	//Position
	layout.elements.push_back({ 0,3,GL_FLOAT,0 });
	//color
	layout.elements.push_back({ 1,3,GL_FLOAT,sizeof(float) * 3 });
	//UV
	layout.elements.push_back({ 2,2,GL_FLOAT,sizeof(float) * 6 });

	layout.stride = sizeof(float) * 8;
	auto mesh = std::make_shared<eng::Mesh>(layout, vertices, indices);

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

	eng::Engine::GetInstance().SetScene(m_scene);
	return true;
}

void Game::Update(float deltaTime)
{
	m_scene->Update(deltaTime);
}

void Game::Destory()
{
	std::cout << "摧毁" << std::endl;
}
