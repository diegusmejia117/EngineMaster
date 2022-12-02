#include "Model.h"

#include <vector>

#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleTexture.h"

#include "cimport.h"
#include "postprocess.h"

const std::string Model::s_modelFolderPath = "models/";

Model::Model()
{
}

Model::~Model()
{
}

Model* Model::LoadFromFile(std::string i_fileName)
{
	Model* model = new Model();

	//std::string filePath = s_modelFolderPath + i_fileName;
	const aiScene* scene = aiImportFile(i_fileName.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene)
	{
		model->LoadMaterials(scene);
		model->LoadMeshes(scene->mMeshes, scene->mNumMeshes);
		aiReleaseImport(scene);
		return model;
	}
	else
	{
		std::string errorString = "Error loading " + i_fileName + ": " + aiGetErrorString();
		//App->editor->OutputToConsole(errorString.c_str());
		return nullptr;
	}
}

void Model::Draw()
{
	for (std::list<Mesh*>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it) {
		(*it)->Draw(m_textures);
	}
}

void Model::LoadMaterials(const aiScene* i_scene)
{
	aiString file;

	m_textures.reserve(i_scene->mNumMaterials);

	for (unsigned i = 0; i < i_scene->mNumMaterials; ++i)
	{
		if (i_scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			//m_textures.push_back(App->texture->LoadTextureFromFile(file.data));
		}
	}
}

void Model::LoadMeshes(aiMesh** i_meshes, int i_numMeshes)
{
	for (int i = 0; i < i_numMeshes; ++i) {
		Mesh* mesh = Mesh::LoadMesh(i_meshes[i]);
		m_meshes.push_back(mesh);
	}
}
