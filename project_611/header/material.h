#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include "shader_pipeline.h"
#include "game_object.h"
#include "scene.h"
#include "sprite_sheet.h"

class Material {
public:

	//Attributs

	ShaderPipeline* shaderPipeline;

	//Constructeur-Destructeur

	/**
		Constructeur de la classe à partir du nom du matériau
		@param name : nom du matériau
	*/
	Material(std::string name = "");

	/**
		Destructeur de la classe
	*/
	~Material() = default;

	//Méthodes

	/**
		Méthode virtuelle qui est appelée pour faire le rendu d'un objet en utilisant ce matériau
		@param o : Node/Objet pour lequel on veut effectuer le rendu
	*/
	virtual void render(GameObject* o);

	/**
		Méthode virtuelle qui est appelée pour modifier une valeur d'un paramètre nécessaire pour le rendu
		@param o : Node/Objet concerné par le rendu
		@param elapsedTime : temps
	*/
	virtual void animate(GameObject* o, const float elapsedTime);


	std::string getName() { return name; };

	virtual void displayInterface() {};


protected:
	std::string name;

	Scene* scene;

	// TODO
	//CECI NE DEVRAIT PAS ETERE ICI, CETTE CLASSE DEVRAIT ETRE UNE INTERFACE
	SpriteSheet* texture;

private:

};

#endif // MATERIAL_H
