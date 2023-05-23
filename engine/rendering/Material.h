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
		std::unique_ptr<Shader> mShader;
		std::unique_ptr<Texture> mAlbedoTexture;
		std::unique_ptr<Texture> mNormalTexture;
	};
}

#endif