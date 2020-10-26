#pragma once
//
//File: sprite.h
//Desc: Here are described methods and fields of Sprite class.
//

#include "vertex.h"
#include "animation.h"
#include "../shaders/pixelShader.h"
#include "../shaders/vertexShader.h"
#include "texture.h"
#include  <d3dx9.h>

#include <vector>

#define INDEXBUF_USAGE (D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY)	//Index buffer usage

#define ANIMATIONS_EMPTY			-1	//Return value if there are no aminations
#define ANIMATIONS_OVERFLOW			-2	//Return value if the order of animation is worong
#define ANIMATIONS_SUCCES			-3

class Sprite {
	//We need just 2 vertex position for left-bottom and right-upper vertex 
	Vertex _leftBottom, _rightUpper;	//Left-bottom and right-upper vertex
	Vector _size = { 1.0f, 1.0f };		//Sprite size
	Vector _center;						//Center of the sprite(need for scaling)

	IDirect3DVertexBuffer9* _vertexBuffer;	//Vertex buffer (nullptr)
	IDirect3DIndexBuffer9* _indexBuffer;	//Index buffer	(nullptr)

	Texture* _texture = nullptr;			//Texture
	
	char _animationCurr = ANIMATIONS_EMPTY;							//Current animation, or ANIMATION_EMPTY if there is is no animation
	std::vector<Animation>* _animations = nullptr;		//All animations are contained in a vector

	bool Create(IDirect3DDevice9* device);	//Create vertex and index buffer
public:
	Sprite(IDirect3DDevice9* device, Texture* texture);	//Just init buffers
	Sprite(IDirect3DDevice9* device, float x1, float y1, float x2, float y2, Texture* texture);	//Init a sprite from 2 2D coordinates

	void SetPos(float x1, float y1, float x2, float y2); //Set new positions for sprite
	void SetUV(float u1, float v1, float u2, float v2);		//Set new UV position
	void SetSize(Vector sizeVect) { _size = sizeVect; }		//Set size vector
	char SetAnimation(int order);						//Set animation

	void SetTexture(Texture* texture) { _texture = texture; }		//Set new texture
	int CreateAnimation(int height, int width, int x, int y, int count, float speed);	//Create an animation, and return its position

	void Draw();																//Send sprite to render system
	virtual void DrawImpl(IDirect3DDevice9* device, VertexShader* vShader, PixelShader* pShader);		//Draw implimentation used by the render system

	void Release();	//Releases all vertices
	~Sprite();
};