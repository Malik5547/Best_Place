//
//File: sprite.cpp
//

#include "sprite.h"
#include "../render.h"

Sprite::Sprite(IDirect3DDevice9* device, Texture* texture) {
	//Init buffers
	Create(device);
	//Load texture
	SetTexture(texture);
	//Set UV
	SetUV(0.0f, 1.0f, 1.0f, 0.0f);
}

Sprite::Sprite(IDirect3DDevice9* device, float x1, float y1, float x2, float y2, Texture* texture) {
	//Init the buffers
	if (Create(device)) {
		//Set positions
		SetPos(x1, y1, x2, y2);
		//Set texture
		SetTexture(texture);
		//Set UV
		SetUV(0.0f, 1.0f, 1.0f, 0.0f);
	}
}
	
int Sprite::CreateAnimation(int height, int width, int x, int y, int count, float speed) {
	if (_animations == nullptr) {
		//If there is no animations, allocate memory for them
		_animations = new std::vector<Animation>;
	}

	//Create animation
	_animations->push_back({ height, width, x, y, count, speed });

	//Return position
	return _animations->size() - 1;
}

void Sprite::SetPos(float x1, float y1, float x2, float y2) {
	//Set 2 vertices
	_leftBottom.SetPos(x1, y1);
	_rightUpper.SetPos(x2, y2);
	//Set center
	_center = { (x2 - x1) / 2 + x1, (y2 - y1) / 2 + y1 };

	//Fill the vertex buffer with the sprite data
	Vertex* vertices;
	_vertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].SetPos(x1, y1);
	vertices[1].SetPos(x1, y2);
	vertices[2].SetPos(x2, y2);
	vertices[3].SetPos(x2, y1);

	_vertexBuffer->Unlock();
}

void Sprite::SetUV(float u1, float v1, float u2, float v2) {
	//Set vertuces UV
	_leftBottom.SetUV(u1, v1);
	_rightUpper.SetUV(u2, v2);

	//Fill the vertex buffer with the sprite UV data
	Vertex* vertices;
	_vertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	//Set UVs
	vertices[0].SetUV(u1, v1);
	vertices[1].SetUV(u1, v2);
	vertices[2].SetUV(u2, v2);
	vertices[3].SetUV(u2, v1);

	_vertexBuffer->Unlock();
}

char Sprite::SetAnimation(int order) {
	//Check if there are animations
	if (_animations == nullptr)
		return ANIMATIONS_EMPTY;
	
	//Check if the order is correct
	if (order > ((int)_animations->size() - 1))
		return ANIMATIONS_OVERFLOW;

	//Set chosed animatino
	(*_animations)[order].Set();
	_animationCurr = order;

	return ANIMATIONS_SUCCES;
}
	
void Sprite::Draw() {
	RenderPush(this);
}

void Sprite::DrawImpl(IDirect3DDevice9* device, VertexShader* vShader, PixelShader* pShader) {
	if (_animationCurr != ANIMATIONS_EMPTY) {
		//If is set an animation, update UV
		Vector uv1, uv2;	//Return values
		//Get UV from animation
		(*_animations)[_animationCurr].GetSpriteUV(_texture->GetSize().width, _texture->GetSize().height, &uv1, &uv2);
		//Set UV data
		SetUV(uv1.x, uv1.y, uv2.x, uv2.y);
	}

	//Set stream source
	device->SetStreamSource(0, _vertexBuffer, 0, sizeof(Vertex));
	//Set texture 
	pShader->SetTexture(device, _texture->GetTexture());
	//Set stream indices
	device->SetIndices(_indexBuffer);
	//Set FVF
	device->SetFVF(Vertex::FVF);

	//Set scale and center
	if (_size != Vector{1.0f, 1.0f}) {
		vShader->SetScaleVect(device, _size.x, _size.y);
		vShader->SetCenterVect(device, _center.x, _center.y);
	}

	//Draw sprite
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	//Reset scale
	if (_size != Vector{ 1.0f, 1.0f }) {
		vShader->SetScaleVect(device, 1.0f, 1.0f);
		vShader->SetCenterVect(device, 0.0f, 0.0f);
	}

	//Return stream index
	device->SetIndices(0);
	//Unset texture 
	device->SetTexture(0, 0);
}

void Sprite::Release() {
	//Release vertex buffer
	if (_vertexBuffer != nullptr)
		_vertexBuffer->Release();
	//Release index buffer
	if (_indexBuffer != nullptr)
		_indexBuffer->Release();
	//Release animations
	if (_animations != nullptr)
		_animations->clear();
}

Sprite::~Sprite() {
	Release();
	//Delete all data
	delete _animations;
}

bool Sprite::Create(IDirect3DDevice9* device) {
	//Create vertex and index buffer
	HRESULT hr;
	
	//Release buffers if not nullptr
	if (_vertexBuffer != nullptr)
		_vertexBuffer->Release();
	if (_indexBuffer != nullptr)
		_indexBuffer->Release();

	//Create vertex buffer
	hr = device->CreateVertexBuffer(
		4 * sizeof(Vertex),
		0,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&_vertexBuffer,
		0);

	//Check errors
	if (FAILED(hr)) {
		::MessageBox(0, "ERROR. Could not create vertex buffer.", 0, 0);
		_vertexBuffer = nullptr;
		return false;
	}

	//Create index buffer
	hr = device->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_indexBuffer,
		0);

	//Check errors
	if (FAILED(hr)) {
		::MessageBox(0, "ERROR. Could not create index buffer.", 0, 0);
		_indexBuffer = nullptr;
		return false;
	}

	//Fill the index buffer with the sprite data
	WORD* indices = 0;
	_indexBuffer->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	_indexBuffer->Unlock();

	return true;
}

