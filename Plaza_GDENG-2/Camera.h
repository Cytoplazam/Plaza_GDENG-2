#pragma once
#include "GameObject.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "Matrix4x4.h"
#include "EngineTime.h"

class Camera: public GameObject, public InputListener
{
public:
	Camera(string name);
	~Camera();

	void draw(int w, int h, VertexShader* vs, PixelShader* ps, float forward, float right) override;
	void update(float deltaTime) override;
	void updateViewMatrix();
	Matrix4x4 getViewMatrix();

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;

	virtual void onMouseMove(const Point& mousePos) override;

	virtual void onLMD(const Point& mousePos) override;
	virtual void onLMU(const Point& mousePos) override;

	virtual void onRMD(const Point& mousePos) override;
	virtual void onRMU(const Point& mousePos) override;
private:
	Matrix4x4 localMatrix;
	bool rmd = false;
};

