#include "Material.h"

namespace PalmEngine
{
	//-----------------------------------------------------------------------

	Material::Material() {}
	
	Material::Material(Shader* shader, Texture* albedoTexture, Texture* normalTexture)
	{
		_shader.reset(shader);
		_albedoTexture.reset(albedoTexture);
		_normalTexture.reset(normalTexture);
	}

	Material::~Material()
	{
		_shader.release();
		_albedoTexture.release();
		_normalTexture.release();
	}

	//-----------------------------------------------------------------------

	Shader* Material::GetShader() const
	{
		return _shader.get();
	}

	Texture* Material::GetAlbedoTexture() const
	{
		return _albedoTexture.get();
	}

	Texture* Material::GetNormalTexture() const
	{
		return _normalTexture.get();
	}
}