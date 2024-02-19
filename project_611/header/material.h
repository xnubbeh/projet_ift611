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
		Constructeur de la classe � partir du nom du mat�riau
		@param name : nom du mat�riau
	*/
	Material(std::string name = "");

	/**
		Destructeur de la classe
	*/
	~Material() = default;

	//M�thodes

	/**
		M�thode virtuelle qui est appel�e pour faire le rendu d'un objet en utilisant ce mat�riau
		@param o : Node/Objet pour lequel on veut effectuer le rendu
	*/
	virtual void render(GameObject* o);

	/**
		M�thode virtuelle qui est appel�e pour modifier une valeur d'un param�tre n�cessaire pour le rendu
		@param o : Node/Objet concern� par le rendu
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
