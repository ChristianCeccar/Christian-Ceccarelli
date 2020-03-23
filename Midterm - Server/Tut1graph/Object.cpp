#include "Object.h"


Object::Object()
{
	scale = 1.0f;
}

//Deconstructs object by unloading mesh
Object::~Object()
{
	unload();
}

void Object::update(float dt) {
	if (rotXZ == false)
	{
		glm::mat4 rx = glm::rotate(glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 ry = glm::rotate(glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rz = glm::rotate(glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));


		// Note: pay attention to rotation order, ZYX is not the same as XYZ
		//apparently zxy is better?
		localRotation = rz * rx * ry;
	}
	else
	{
		glm::mat4 rxz = glm::rotate(glm::radians(rotX), glm::vec3(XHelp, 0.0f, ZHelp));
		glm::mat4 ry = glm::rotate(glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));

		localRotation = rxz * ry;
	}
	// Create translation matrix
	glm::mat4 tran = glm::translate(localPosition);

	// Create scale matrix
	glm::mat4 scal = glm::scale(glm::vec3(scale, scale, scale));

	// Combine all above transforms into a single matrix
	// This is the local transformation matrix, ie. where is this game object relative to it's parent
	// If a game object has no parent (it is a root node) then its local transform is also it's global transform
	// If a game object has a parent, then we must apply the parent's transform
	localTransformMatrix = tran * (localRotation * scal);

	if (m_pParent)
		localToWorldMatrix = m_pParent->getLocalToWorldMatrix() * localTransformMatrix;
	else
		localToWorldMatrix = localTransformMatrix;

	Position = tran * glm::vec4(localPosition.x, localPosition.y, localPosition.z, 1);

	// Update children
	for (int i = 0; i < children.size(); i++)
		children[i]->update(dt);
}

//Creates a object with a filepath to the mesh, and a name (make the name the same as the instance name)
void Object::construct(std::string n, std::string file)
{
	name = n;
	filePath = file;
	load();
}

void Object::addChild(Object* newChild) {
	if (newChild)
	{
		children.push_back(newChild);
		newChild->m_pParent = this; // tell new child that this game object is its parent
	}
}

void Object::removeChild(Object* rip) {
	for (int i = 0; i < children.size(); ++i)
	{
		if (children[i] == rip) // compare memory locations (pointers)
		{
			std::cout << "Removing child: " + rip->name << " from object: " << this->name;
			children.erase(children.begin() + i);
		}
	}
}
void Object::setLocalPosition(glm::vec3 newPosition) {
	localPosition = newPosition;

}

void Object::setLocalRotationAngleX(float newAngle) {
	rotX = newAngle;
}

void Object::setLocalRotationAngleY(float newAngle) {
	rotY = newAngle;
}

void Object::setLocalRotationAngleZ(float newAngle) {
	rotZ = newAngle;
}

void Object::setLocalScale(float newScale) {
	scale = newScale;
	mesh.width *= newScale;
	mesh.depth *= newScale;
}

void Object::setLocalScaleX(float newScale)
{
	mesh.width *= newScale;
}

void Object::setLocalScaleY(float newScale)
{
	mesh.height *= newScale;
}

void Object::setLocalScaleZ(float newScale)
{
	mesh.depth *= newScale;
}

glm::vec3 Object::getLocalPosition() {
	return localPosition;
}

glm::mat4 Object::getLocalToWorldMatrix() {
	return localToWorldMatrix;
}

glm::vec3 Object::getWorldPosition() {
	if (m_pParent)
		return m_pParent->getLocalToWorldMatrix() * glm::vec4(localPosition, 1.0f);
	else
		return localPosition;
}

glm::mat4 Object::getWorldRotation() {
	if (m_pParent)
		return m_pParent->getWorldRotation() * localRotation;
	else
		return localRotation;
}

std::vector<Object*> Object::getChildren() {
	return children;

}

Object* Object::getParent() {
	return m_pParent;

}

float Object::getLocalScale()
{
	return scale;
}

float Object::getLocalRotationAngleX()
{
	return rotX;
}

float Object::getLocalRotationAngleY()
{
	return rotY;
}

float Object::getLocalRotationAngleZ()
{
	return rotZ;
}

//loads mesh on object
void Object::load()
{
	if (!mesh.loadFromFile(filePath)) {
		std::cout << "Mesh " << name << " failed to load." << std::endl;
		system("pause");
		exit(0);
	}
}


Mesh Object::getMesh()
{
	return mesh;
}

//unloads mesh
void Object::unload()
{
	mesh.unload();
}

//gets the name of the object
std::string Object::getName()
{
	return name;
}


bool Object::collision(Object &col) {
	bool isXcolliding = abs(Position.x - col.Position.x) < mesh.width / 2.f + col.mesh.width / 2.f;

	bool isZcolliding = abs(Position.z - col.Position.z) < mesh.depth / 2.f + col.mesh.depth / 2.f;

	bool isYcolliding = abs((Position.y + mesh.height / 2.f) - (col.Position.y + col.mesh.height / 2.f)) < mesh.height / 2.f + col.mesh.height / 2.f;

	//std::cout << isXcolliding << isYcolliding << isZcolliding << std::endl;


	return isXcolliding && isYcolliding && isZcolliding;



}

bool Object::Roofcollision(Object &col) {
	bool isXcolliding = abs(Position.x - col.Position.x) < mesh.width / 2.f + col.mesh.width / 2.f;

	bool isZcolliding = abs(Position.z - col.Position.z) < mesh.depth / 2.f + col.mesh.depth / 2.f;

	bool isYcolliding = abs((Position.y + mesh.height / 2) < (col.Position.y));

	//std::cout << isXcolliding << isYcolliding << isZcolliding << std::endl;


	return isXcolliding && isYcolliding && isZcolliding;



}
void Object::setShader(Shader &s, glm::mat4 cameraProjection, glm::mat4 cameraTransform, std::vector<Light>pointLights, Light directionalLight) {
	glm::mat4 temp = this->getLocalToWorldMatrix();
	s.bind();
	s.sendUniformMat4("uModel", glm::value_ptr(temp), false);
	s.sendUniformMat4("uView", glm::value_ptr(cameraTransform), false);
	s.sendUniformMat4("uProj", glm::value_ptr(cameraProjection), false);

	s.sendUniform("material.diffuse", 0);
	s.sendUniform("material.specular", 1);
	s.sendUniform("material.normal", 2);
	s.sendUniform("material.hue", mat.hue);
	s.sendUniform("material.SpecularExponent", mat.specularExponent);

	for (int i = 0; i < pointLights.size(); i++)
	{
		std::string prefix = "pointLights[" + std::to_string(i) + "].";
		s.sendUniform(prefix + "position", cameraTransform * pointLights[i].PositionorDirection);

		s.sendUniform(prefix + "Ambient", pointLights[i].Ambient);
		s.sendUniform(prefix + "Diffuse", pointLights[i].Diffuse);
		s.sendUniform(prefix + "Specular", pointLights[i].Specular);

		s.sendUniform(prefix + "SpecularExponent", pointLights[i].SpecularExponent);

		s.sendUniform(prefix + "constantAttenuation", pointLights[i].constantAttenuation);
		s.sendUniform(prefix + "linearAttenuation", pointLights[i].linearAttenuation);
		s.sendUniform(prefix + "quadraticAttenuation", pointLights[i].quadraticAttenuation);
	}

	s.sendUniform("directionalLight.direction", cameraTransform * directionalLight.PositionorDirection);
	s.sendUniform("directionalLight.Ambient", directionalLight.Ambient);
	s.sendUniform("directionalLight.Diffuse", directionalLight.Diffuse);
	s.sendUniform("directionalLight.Specular", directionalLight.Specular);
	s.sendUniform("directionalLight.SpecularExponent", directionalLight.SpecularExponent);


	glActiveTexture(GL_TEXTURE0);
	mat.Diffuse.bind();

	glActiveTexture(GL_TEXTURE1);

	mat.Specular.bind();

	glActiveTexture(GL_TEXTURE2);
	mat.Normal.bind();
	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.getNumVertices());
	glBindVertexArray(GL_NONE);

	mat.Normal.unbind();
	glActiveTexture(GL_TEXTURE1);

	mat.Specular.unbind();
	glActiveTexture(GL_TEXTURE0);
	mat.Diffuse.unbind();
	s.unbind();

}