#include "SkinAssimp.h"

#include <iostream>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#pragma comment(lib, "assimp-vc140-mt.lib")

void InitAssimp(void)
{
	Assimp::Importer importer;
	std::string file_path = "Lat_Pastry.fbx";

	const aiScene* scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	if (scene == nullptr)
	{
		std::cout << "モデルの読み込みに失敗" << std::endl;
		std::cout << importer.GetErrorString() << std::endl;

	}
	else
	{
		std::cout << "モデルの読み込みに成功" << file_path.c_str() << std::endl;
	}

	rewind(stdin);
	getchar();
}