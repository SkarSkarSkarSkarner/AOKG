#include "GameObjectFactory.h"

bool GameObjectFactory::init(std::string filename)
{
	setlocale(LC_ALL, "russian");

	std::vector <std::string> firstLevel { "LightObject", "HeavyObject", "BorderObject", "Player", "Bomb", "Monster" };
	std::vector <std::string> secondLevel { "mesh", "material" };
	std::vector <std::string> thirdLevel { "diffuse", "ambient", "specular", "emission", "shininess" };

	std::ifstream fin;
	fin.open(filename);

	if (!fin.is_open())
	{
		std::cout << "�� ������� ����� ���� " << filename << std::endl;
		return false;
	}

	std::string jsonString;
	getline(fin, jsonString, static_cast<char>(0));
	fin.close();

	rapidjson::Document document;
	document.Parse(jsonString.c_str());

	if (document.GetParseError() != 0)
	{
		std::cout << "�������� ������ �����" << std::endl;
		return false;
	}

	std::vector <Mesh> mesh(6);
	std::vector <Texture> texture(3);
	
	mesh[0].load(document["LightObject"]["mesh"].GetString());
	mesh[1].load(document["BorderObject"]["mesh"].GetString());
	mesh[2].load(document["Player"]["mesh"].GetString());
	mesh[3].load(document["HeavyObject"]["mesh"].GetString());
	mesh[4].load(document["Bomb"]["mesh"].GetString());
	mesh[5].load(document["Monster"]["mesh"].GetString());

	std::vector <Texture> tex(3);
	std::vector <PhongMaterial> material(3);
	std::vector <PhongMaterialWithTexture> materialTexture(3);

	int textureCounter_1 = 0;
	int textureCounter_2 = 0;

	for (int i = 0; i < 6; i++)
	{
		glm::vec4 vec_1;
		glm::vec4 vec_2;
		glm::vec4 vec_3;
		glm::vec4 vec_4;
		GLfloat shininess;

		

		if (document[firstLevel[i].c_str()][secondLevel[1].c_str()]["type"].GetString()[13] != 'W')
		{
			for (int j = 0; j < 4; j++)
			{
				vec_1[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[0].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				vec_2[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[1].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				vec_3[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[2].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				vec_4[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[3].c_str()][j].GetDouble();
			}

			shininess = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[4].c_str()].GetDouble();

			material[textureCounter_1].setDiffuse(vec_1);
			material[textureCounter_1].setAmbient(vec_2);
			material[textureCounter_1].setSpecular(vec_3);
			material[textureCounter_1].setEmission(vec_4);
			material[textureCounter_1].setShininess(shininess);

			textureCounter_1++;
		}
		if (document[firstLevel[i].c_str()][secondLevel[1].c_str()]["type"].GetString()[13] == 'W')
		{
			for (int j = 0; j < 4; j++)
			{
				vec_1[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[0].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				vec_2[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[1].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				vec_3[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[2].c_str()][j].GetDouble();
			}

			for (int j = 0; j < 4; j++)
			{
				vec_4[j] = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[3].c_str()][j].GetDouble();
			}

			shininess = document[firstLevel[i].c_str()][secondLevel[1].c_str()][thirdLevel[4].c_str()].GetDouble();

			materialTexture[textureCounter_2].setDiffuse(vec_1);
			materialTexture[textureCounter_2].setAmbient(vec_2);
			materialTexture[textureCounter_2].setSpecular(vec_3);
			materialTexture[textureCounter_2].setEmission(vec_4);
			materialTexture[textureCounter_2].setShininess(shininess);

			std::shared_ptr <Texture> texture = std::make_shared<Texture> (tex[textureCounter_2]);
			texture.get()->load(document[firstLevel[i].c_str()][secondLevel[1].c_str()]["texture"].GetString());
			this->textures.push_back(texture);
			textureCounter_2++;
		}
	}


	this->meshes.push_back(std::make_shared<Mesh>(mesh[0]));
	this->meshes.push_back(std::make_shared<Mesh>(mesh[1]));
	this->meshes.push_back(std::make_shared<Mesh>(mesh[2]));

	materialTexture[0].setTexture(this->textures[0]);
	materialTexture[1].setTexture(this->textures[1]);
	materialTexture[2].setTexture(this->textures[2]);


	this->materials.push_back(std::make_shared<PhongMaterialWithTexture>(materialTexture[0]));
	this->materials.push_back(std::make_shared<PhongMaterialWithTexture>(materialTexture[1]));
	this->materials.push_back(std::make_shared<PhongMaterialWithTexture>(materialTexture[2]));
	this->materials.push_back(std::make_shared<PhongMaterial>(material[0]));
	this->materials.push_back(std::make_shared<PhongMaterial>(material[1]));
	this->materials.push_back(std::make_shared<PhongMaterial>(material[2]));
}

std::shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y)
{
	GraphicObject* gr = new GraphicObject;
		
	switch (type)
	{
	case GameObjectType::LIGHT_OBJECT:
		gr->setMaterial(this->materials[0]);
		gr->setMesh(this->meshes[0]);

		break;
	case GameObjectType::HEAVY_OBJECT:
		gr->setMaterial(this->materials[1]);
		gr->setMesh(this->meshes[0]);
		break;
	case GameObjectType::BORDER_OBJECT:
		gr->setMaterial(this->materials[2]);
		gr->setMesh(this->meshes[1]);
		break;
	case GameObjectType::PLAYER:
		gr->setMaterial(this->materials[3]);
		gr->setMesh(this->meshes[2]);
		break;
	case GameObjectType::BOMB:
		gr->setMaterial(this->materials[4]);
		gr->setMesh(this->meshes[2]);
		break;
	case GameObjectType::MONSTER:
		gr->setMaterial(this->materials[5]);
		gr->setMesh(this->meshes[2]);
		break;
	default:
		break;
	}

	gr->setPosition(x - 10, 0, y - 10);
 	GameObject* gm = new GameObject;
	gm->setGraphicObject(*gr);
	gm->setPosition(x, y);

	return std::shared_ptr<GameObject>(gm);
}


std::shared_ptr<Monster> GameObjectFactory::create(GameObjectType type, int x, int y, bool monster)
{
	GraphicObject* gr = new GraphicObject;

	switch (type)
	{
	case GameObjectType::LIGHT_OBJECT:
		gr->setMaterial(this->materials[0]);
		gr->setMesh(this->meshes[0]);
		break;
	case GameObjectType::HEAVY_OBJECT:
		gr->setMaterial(this->materials[1]);
		gr->setMesh(this->meshes[0]);
		break;
	case GameObjectType::BORDER_OBJECT:
		gr->setMaterial(this->materials[2]);
		gr->setMesh(this->meshes[1]);
		break;
	case GameObjectType::PLAYER:
		gr->setMaterial(this->materials[3]);
		gr->setMesh(this->meshes[2]);
		break;
	case GameObjectType::BOMB:
		gr->setMaterial(this->materials[4]);
		gr->setMesh(this->meshes[2]);
		break;
	case GameObjectType::MONSTER:
		gr->setMaterial(this->materials[5]);
		gr->setMesh(this->meshes[2]);
		break;
	default:
		break;
	}

	gr->setPosition(x - 10, 0, y - 10);
	Monster* gm = new Monster;
	gm->setGraphicObject(*gr);
	gm->setPosition(x, y);

	return std::shared_ptr<Monster>(gm);
}

