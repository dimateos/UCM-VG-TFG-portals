#pragma once

#include "../Logic/Node.h"
#include "../Render/Shader.h"
#include "../Render/Texture.h"
#include "../Render/Mesh.h"
#include "../Render/RenderTarget.h"

#include "../Platform/Listening.h"
typedef union SDL_Event; //forwarded

class ScreenPostFiltering : public Node, Listener<SDL_Event>
{
public:
	ScreenPostFiltering(Node* father, RenderTarget* renderTarget);
	virtual ~ScreenPostFiltering();

	void setOption(int n);

	virtual bool handleEvent(SDL_Event const & e);
	virtual void render();

protected:
	Shader postFilterShader_;
	Texture rtt_;

	RenderTarget* renderTarget_;
	Mesh* mesh_;

	float res_, preview_res_; //resolution for the texture (multi/down sampling)

	bool readingInput_ = false;
	int option_ = 0;
};
