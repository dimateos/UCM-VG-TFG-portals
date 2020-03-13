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

	// use/activate the texture
	void bind(unsigned int unit = 0);
	void unbind();

	//set para wrappings, filters y borders?

	// get info
	inline unsigned int getID() const { return _ID; };
	inline int getColorMode() const { return _colorMode; };
	inline int getTextureType() const { return _textureType; };
	inline int getWidth() const { return _width; };
	inline int getHeight() const { return _height; };
	inline int getNrChannels() const { return _nrChannels; };

	//static defaults
	static void setFlipVerticallyOnLoad(bool mode = true);
	static int getColorModeFromNrChannels(int nrChannels);
	static int DEFAULT_textureWrap_S, DEFAULT_textureWrap_T, DEFAULT_minFilter, DEFAULT_magFilter;

protected:
	// the texture ID
	unsigned int _ID = -1;
	int _colorMode, _textureType;
	int _width, _height, _nrChannels;

	//informative errors
	bool loadError(const std::string & path) const;
};
