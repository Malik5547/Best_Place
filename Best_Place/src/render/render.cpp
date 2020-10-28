#include "render.h"

//Sprite and background queue to draw
std::queue<Sprite*> Render_queue;
std::queue<Background_Sprite*> Background_queue;

Render::Render(Window* wind) {
	HRESULT hr;

	_wnd = wind;

	//
	//Init d3d9
	//
	IDirect3D9* d3d9 = 0;
	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	//
	//Parameters
	//
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = _wnd->GetWidth();
	d3dpp.BackBufferHeight = _wnd->GetWidth();
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8; //pixel format
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = _wnd->GetHndl();
	d3dpp.Windowed = _wnd->IsWindowed(); // fullscreen
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; // depth format
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//Create the device

	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		D3DDEVTYPE_HAL, // device type
		_wnd->GetHndl(), // window associated with device
		D3DCREATE_HARDWARE_VERTEXPROCESSING, // vertex processing type
		&d3dpp, // present parameters
		&_device); // returned created device

	if (FAILED(hr))
	{
		// try again using a 16-bit depth buffer
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			_wnd->GetHndl(),
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&_device);

		if (FAILED(hr))
		{
			d3d9->Release(); // done with d3d9 object
			::MessageBox(0, "CreateDevice() - FAILED", 0, 0);
			_device = nullptr;
			return;
		}
	}

	//Done with d3d9
	d3d9->Release();

	//
	//Create vertex shader
	//

	_vShader = new VertexShader();
	if (_vShader->Compile("src/render/shaders/vShader.txt", SHADER_TYPE_VERTEX))
		_vShader->Create(_device);
	else {
		_vShader->Release();
		_vShader = nullptr;
	}
	//Set window size in shader
	_vShader->SetWindowSize(_device, _wnd->GetWidth(), _wnd->GetHeight());

	//
	//Create pixel shader
	//

	_pShader = new PixelShader();
	if (_pShader->Compile("src/render/shaders/pShader.txt", SHADER_TYPE_PIXEL))
		_pShader->Create(_device);
	else {
		_pShader->Release();
		_pShader = nullptr;
	}

	//
	//Initialize camera
	//
	_cam = new Camera;
	SetCamDist(CAM_DIST);

	//Init GUI
	GUI::Init("Times New Roman", 20, _device, _cam);
	GUI::SetWindowSize({ (float)_wnd->GetWidth(), (float)_wnd->GetHeight() });
}

void Render::SetCamPos(float x, float y) {
	//Set camera position
	_cam->SetPos(x, y);

	if (!_vShader->SetViewPos(_device, x, y))
		::MessageBox(0, "Could not change camera position.", 0, 0);
}

void Render::SetCamDist(float dist) {
	//Set camera distantion
	_cam->SetDist(dist);

	if (!_vShader->SetViewDist(_device, dist))
		::MessageBox(0, "Could not change camera distantion.", 0, 0);
}

void Render::CameraUpdate() {
	if (_cam != nullptr) {
		//Update camera 
		_cam->Update();
		if (!_vShader->SetViewPos(_device, _cam->GetX(), _cam->GetY()))
			::MessageBox(0, "Could not change camera position.", 0, 0);
	}
}

void Render::CameraFollow(Object* object) {
	_cam->Follow(object);
}

void Render::RenderWorld(float timeDelta) {
	//Update animation time
	Animation::Update(timeDelta);

	if (_device)
	{
		if (::GetAsyncKeyState('Q') & 0x8000f) {
			SetCamDist(_cam->GetDist() + 1.0f * timeDelta);
		}
		if (::GetAsyncKeyState('E') & 0x8000f) {
			SetCamDist(_cam->GetDist() - 1.0f * timeDelta);
		}

		CameraUpdate();

		//
		//Draw scene
		//

		_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			0x00000000, 1.0f, 0);

		_device->BeginScene();		//Begin scene rendering
		//_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		_device->SetVertexShader(_vShader->GetShader());		//Set our vertex shader
		_device->SetPixelShader(_pShader->GetShader());			//Set our pixel shader

		//
		//First draw background
		//
		while (!Background_queue.empty()) {
			Background_Sprite* this_Background = Background_queue.front();	//Get background
			this_Background->DrawImpl(_device, _vShader, _pShader, _cam);			//Draw background
			Background_queue.pop();											//Pop this background
		}

		//
		//Draw all sprites that are in queue
		//
		while (!Render_queue.empty()) {
			Sprite* this_Sprite = Render_queue.front(); //Get sprite
			this_Sprite->DrawImpl(_device, _vShader, _pShader);	//Draw sprite
			Render_queue.pop();							//Pop this sprite
		}

		//
		//Show FPS and other GUI datas
		//
		
		GUI::DrawFPS();
		std::string xRow = "X: " + std::to_string(World::Player()->GetPosition().x);
		std::string yRow = "Y: " + std::to_string(World::Player()->GetPosition().y);
		GUI::TextDraw(xRow);
		GUI::TextDraw(yRow);
		//Draw menu
		if (_vShader->SetVertexProc(_device, VPROC_WND)) {
			//Set raw drawing
			GUI::Update();
			_vShader->SetVertexProc(_device, VPROC_DEF);	//Reset raw drawing
		}

		_device->EndScene();		//End rendering scene
		_device->Present(0, 0, 0, 0);// present backbuffer
	}
}


void Render::Release() {
	if(_device != nullptr)
		_device->Release();
	
	//Release shaders
	if (_vShader != nullptr)
		_vShader->Release();
	if (_pShader != nullptr)
		_pShader->Release();

	//Release camera
	if (_cam != nullptr) {
		delete _cam;
		_cam = nullptr;
	}
}

Render::~Render() {
	Release();

	//Delete shaders 
	delete _vShader;
	delete _pShader;
}

void RenderPush(Sprite* sprite) {
	Render_queue.push(sprite);
}

void BackgroundPush(Background_Sprite* background) {
	Background_queue.push(background);
}