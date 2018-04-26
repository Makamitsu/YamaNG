#include "Material.h"

Material::Material(const aiMaterial & mat)
{
	mat.Get(AI_MATKEY_NAME, m_Name);
	mat.Get(AI_MATKEY_COLOR_DIFFUSE, m_Diffuse);
	mat.Get(AI_MATKEY_COLOR_SPECULAR, m_Specular);
	mat.Get(AI_MATKEY_COLOR_AMBIENT, m_Ambient);
	mat.Get(AI_MATKEY_COLOR_EMISSIVE, m_Emissive);
	mat.Get(AI_MATKEY_COLOR_TRANSPARENT, m_Transparente);
	mat.Get(AI_MATKEY_ENABLE_WIREFRAME, m_Wireframe);
	mat.Get(AI_MATKEY_TWOSIDED, m_Twosided);
	mat.Get(AI_MATKEY_SHADING_MODEL, m_ShadingModel);
	mat.Get(AI_MATKEY_BLEND_FUNC, m_BlendFunc);
	mat.Get(AI_MATKEY_OPACITY, m_Opacity);
	mat.Get(AI_MATKEY_SHININESS, m_Shininess);
	mat.Get(AI_MATKEY_REFRACTI, m_Refreacti);
//	mat.Get(AI_MATKEY_TEXTURE, m_Texture);
//	mat.Get(AI_MATKEY_TEXBLEND, m_TextureBlend);
//	mat.Get(AI_MATKEY_, m_TextureOperator);
//	mat.Get(AI_MATKEY_, m_UVMapping);
//	mat.Get(AI_MATKEY_, m_UMappingMode);
//	mat.Get(AI_MATKEY_, m_VMappingMode);
//	mat.Get(AI_MATKEY_, m_TextureMapAxi); 
//	mat.Get(AI_MATKEY_, m_TextureFlag);
}
