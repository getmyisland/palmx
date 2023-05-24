#include "Material.h"

namespace PalmEngine
{
	//-----------------------------------------------------------------------

	Material::Material(const Shader& shader, const Texture& albedoTexture, const Texture& normalTexture)
		: _shader(shader), _albedoTexture(albedoTexture), _normalTexture(normalTexture)
	{
	}

	Material::~Material()
	{

	}

	//-----------------------------------------------------------------------

	const Shader& Material::GetShader() const
	{
		return _shader;
	}

	const Texture& Material::GetAlbedoTexture() const
	{
		return _albedoTexture;
	}

	const Texture& Material::GetNormalTexture() const
	{
		return _normalTexture;
	}
}