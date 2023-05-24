#ifndef _PE_MATERIAL_H__
#define _PE_MATERIAL_H__

#include <filesystem/ResourceManager.h>
#include "Shader.h"

namespace PalmEngine
{
	enum class TextureType
	{
		Albedo,
		Normal
	};
	
	struct Texture
	{
		unsigned int mID = 0;
		TextureType mType = TextureType::Albedo;
	};

	class Material
	{
	public:
		Material(const Shader& shader = Shader(), const Texture& albedoTexture = Texture(), const Texture& normalTexture = Texture());
		~Material();

		const Shader& GetShader() const;
		const Texture& GetAlbedoTexture() const;
		const Texture& GetNormalTexture() const;

	private:
		Shader _shader;
		Texture _albedoTexture;
		Texture _normalTexture;
	};
}

#endif