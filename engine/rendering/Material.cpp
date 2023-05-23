#include "Material.h"

namespace PalmEngine
{
	Material::Material() {}
	
	Material::Material(Shader* shader, Texture* albedoTexture, Texture* normalTexture)
	{
		mShader.reset(shader);
		mAlbedoTexture.reset(albedoTexture);
		mNormalTexture.reset(normalTexture);
	}

	Material::~Material()
	{
		mShader.release();
		mAlbedoTexture.release();
		mNormalTexture.release();
	}
}