#pragma once
#include <string>

class Texture
{
public:
	Texture();
	~Texture();
	void free();

	//load the texture
	bool load(const std::string &path, int textureType);

	//atm here, but may be a virtual texture with a wrapping interface for all
	bool createRenderTargetTexture(unsigned int framebufferID, int width, int height);

	// use/activate the texture
	void bind(unsigned int unit = 0);
	void unbind();

	//set para wrappings, filters y borders?

	// get info
	inline unsigned int getID() const { return ID_; };
	inline int getColorMode() const { return colorMode_; };
	inline int getTextureType() const { return textureType_; };
	inline int getWidth() const { return width_; };
	inline int getHeight() const { return height_; };
	inline int getNrChannels() const { return nrChannels_; };

	//static defaults
	static void setFlipVerticallyOnLoad(bool mode = true);
	static int getColorModeFromNrChannels(int nrChannels);
	static int DEFAULT_textureWrap_S, DEFAULT_textureWrap_T, DEFAULT_minFilter, DEFAULT_magFilter;

protected:
	// the texture ID
	unsigned int ID_ = -1;
	int colorMode_, textureType_;
	int width_, height_, nrChannels_;

	bool generate(int textureType);

	//informative errors
	bool loadError(const std::string & path) const;
};
