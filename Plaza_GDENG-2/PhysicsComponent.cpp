#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(String name, GameObject* owner) : AComponent(name, ComponentType::Physics, owner)
{
    BaseComponentSystem::get()->getPhysicsSystem()->registerComponent(this);
    PhysicsCommon* physicsCommon = BaseComponentSystem::get()->getPhysicsSystem()->getPhysicsCommon();
    PhysicsWorld* physicsWorld = BaseComponentSystem::get()->getPhysicsSystem()->getPhysicsWorld();

    Vector3D scale = this->getOwner()->getLocalScale();
    Transform transform;
    transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
    BoxShape* boxshape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));
    this->rigidbody = physicsWorld->createRigidBody(transform);
    this->rigidbody->addCollider(boxshape, transform);
    this->rigidbody->updateMassPropertiesFromColliders();
    this->rigidbody->setMass(this->mass);
    this->rigidbody->setType(BodyType::DYNAMIC);

    transform = this->rigidbody->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);

    this->getOwner()->setLocalMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::perform(float deltaTime)
{
    const Transform transform = this->rigidbody->getTransform();
    float Matrix[16];

    transform.getOpenGLMatrix(Matrix);

    this->getOwner()->setLocalMatrix(Matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
    return this->rigidbody;
}
