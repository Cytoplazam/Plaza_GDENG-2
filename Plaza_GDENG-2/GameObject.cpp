#include "GameObject.h"

GameObject::GameObject(string name, PrimitiveType type)
{
	this->name = name;
	this->type = type;
	this->rot = Vector3D::zeros();
	this->pos = Vector3D::zeros();
	this->scale = Vector3D::ones();
}

GameObject::~GameObject()
{
	this->vs->release();
	this->ps->release();
}

void GameObject::setPos(float x, float y, float z)
{
	this->pos = Vector3D(x, y, z);
}

void GameObject::setPos(Vector3D pos)
{
	this->pos = pos;
}

Vector3D GameObject::getLocalPosition()
{
	return this->pos;
}

void GameObject::setScale(float x, float y, float z)
{
	this->scale = Vector3D(x, y, z);
}

void GameObject::setScale(Vector3D scale)
{
	this->scale = scale;
}

Vector3D GameObject::getLocalScale()
{
	return this->scale;
}

void GameObject::setRot(float x, float y, float z)
{
	this->rot = Vector3D(x, y, z);
}

void GameObject::setRot(Vector3D rot)
{
	this->rot = rot;
}

Vector3D GameObject::getLocalRotation()
{
	return this->rot;
}

GameObject::PrimitiveType GameObject::getType()
{
	return this->type;
}

void GameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

//AComponent* GameObject::findComponentByType(AComponent::ComponentType type, String name)
//{
//	for (int i = 0; i < this->componentList.size(); i++)
//	{
//		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type)
//		{
//			return this->componentList[i];
//		}
//	}
//}

AComponent* GameObject::findComponentByName(String name)
{
	for (int i = 0; i < this->componentList.size(); i++)
	{
		if (this->componentList[i]->getName() == name)
		{
			return this->componentList[i];
		}
	}
}

void GameObject::ComputeLocalMatrix()
{
	this->Summation.setIdentity();
	this->translate.setIdentity();
	this->ScaleMatrix.setIdentity();

	translate.setTranslation(this->getLocalPosition());
	ScaleMatrix.setScale(this->getLocalScale());
	rot = Vector3D(this->getLocalRotation());

	this->RotationZ.setIdentity();
	this->RotationZ.setRotationZ(rot.m_z);

	this->RotationF.setIdentity();
	this->RotationF.setRotationX(rot.m_x);

	this->RotationGl.setIdentity();
	this->RotationGl.setRotationY(rot.m_y);

	this->RotationTotal.setIdentity();
	this->RotationTotal = this->RotationTotal.multiplyMatrix(RotationF.multiplyMatrix(RotationGl.multiplyMatrix(RotationZ)));
	this->Summation = this->Summation.multiplyMatrix(ScaleMatrix.multiplyMatrix(this->RotationTotal));
	this->Summation = this->Summation.multiplyMatrix(this->translate);
	this->localMatrix = this->Summation;
}

Matrix4x4 GameObject::getLocalMatrix()
{
	return this->localMatrix;
}

void GameObject::setLocalMatrix(float matrix[16])
{
	float Matrix[4][4];

	Matrix[0][0] = matrix[0];
	Matrix[0][1] = matrix[1];
	Matrix[0][2] = matrix[2];
	Matrix[0][3] = matrix[3];

	Matrix[1][0] = matrix[4];
	Matrix[1][1] = matrix[5];
	Matrix[1][2] = matrix[6];
	Matrix[1][3] = matrix[7];

	Matrix[2][0] = matrix[8];
	Matrix[2][1] = matrix[9];
	Matrix[2][2] = matrix[10];
	Matrix[2][3] = matrix[11];

	Matrix[3][0] = matrix[12];
	Matrix[3][1] = matrix[13];
	Matrix[3][2] = matrix[14];
	Matrix[3][3] = matrix[15];

	Matrix4x4 coordinate;
	coordinate.setIdentity();
	coordinate.setMatrix(Matrix);

	Matrix4x4 scale;
	scale.setIdentity();
	scale.setScale(this->scale);

	Matrix4x4 translate;
	translate.setIdentity();
	translate.setTranslation(this->pos);

	this->localMatrix = scale.multiplyMatrix(translate.multiplyMatrix(coordinate));
	this->overrideMatrix = true;
}

float* GameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 MatrixAll;
	MatrixAll.setIdentity();

	Matrix4x4 translationMatrix;
	translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->pos);

	Matrix4x4 scaleMatrix;
	scaleMatrix.setIdentity();
	scaleMatrix.setScale(Vector3D::ones());

	Vector3D rotation = this->getLocalRotation();

	Matrix4x4 xMatrix;
	xMatrix.setIdentity();
	xMatrix.setRotationX(rotation.m_x);

	Matrix4x4 yMatrix;
	yMatrix.setIdentity();
	yMatrix.setRotationY(rotation.m_y);

	Matrix4x4 zMatrix;
	zMatrix.setIdentity();
	zMatrix.setRotationY(rotation.m_z);

	Matrix4x4 rotationMatrix;
	rotationMatrix.setIdentity();
	rotationMatrix.multiplyMatrix(xMatrix.multiplyMatrix(yMatrix.multiplyMatrix(zMatrix)));

	MatrixAll = MatrixAll.multiplyMatrix(scaleMatrix.multiplyMatrix(rotationMatrix));
	MatrixAll = MatrixAll.multiplyMatrix(translationMatrix);

	return *MatrixAll.m_mat;
}

string GameObject::getName()
{
	return this->name;
}
