#ifndef _PE_MATERIAL_H__
#define _PE_MATERIAL_H__

#include "Shader.h"

#include <memory>

namespace PalmEngine
{
	enum class TextureType
	{
		Albedo,
		Normal
	};

	//-----------------------------------------------------------------------

	struct Texture
	{
		unsigned int mID = 0;
		TextureType mType;
	};

	class Material
	{
	public:
		Material(Shader* shader, Texture* albedoTexture, Texture* normalTexture);
		~Material();

	private:
		Material();

	public:
		Shader* GetShader() const;
		Texture* GetAlbedoTexture() const;
		Texture* GetNormalTexture() const;

	private:
		std::unique_ptr<Shader> _shader;
		std::unique_ptr<Texture> _albedoTexture;
		std::unique_ptr<Texture> _normalTexture;
	};
}

#endif