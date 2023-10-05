#pragma once

#ifndef CAPPPARCIAL1_H
#define CAPPPARCIAL1_H

#include "Globals.h"
#include "CApp.h"

#include "../Include/Parcial-1.h"

// --------------------------------------------------------------------------------------------------------------------------------------
// Class that inherits from Base class CApp
// Base class CApp has members for: CGameWindow, CGameMenu, and COpenGLRenderer, which we can access through the public/protected methods
// --------------------------------------------------------------------------------------------------------------------------------------
class CAppParcial1 : public CApp
{
private:

	// ---------------------------------------------------
	// Private member variables specific to CAppParcial1 only
	// ---------------------------------------------------
	//
	// ---------------------------------------------------

protected:

	// Method to initialize the menu 
	// (not needed in CAppParcial1, so return false)
	bool initializeMenu() { return false; }

public:
	// Constructors and destructor
	CAppParcial1();
	CAppParcial1(int window_width, int window_height);
	~CAppParcial1();

	// --------------------------------------------------------------------------------------------------------------------------
	// Inherited methods from CApp
	// Initialize(), update(), run(), and render() are PURE VIRTUAL methods, so they need to be implemented in this DERIVED class
	// --------------------------------------------------------------------------------------------------------------------------

	// Method to initialize any objects for this class
	void initialize();

	// Method to update any objecs based on time elapsed since last frame
	void update(double deltaTime);

	// Method to run the app
	void run();

	// Method to render the app
	void render();

	// ------------------------------------------------------------------------------------------------------------------------
	// Other inherited methods from CApp. These are optional to override.
	// Only provide an implementation in this DERIVED class if you need them to do something different than the base class CApp
	// -----------------------------------------------------------------------------------------------------------------------

	// Executes the action corresponding to the selected menu item
	void executeMenuAction();

	// Called when mouse moves within the window
	void onMouseMove(float deltaX, float deltaY);

	// -----------------------------------------
	// Public methods specific to CAppEmpty only
	// -----------------------------------------
	//
	// -----------------------------------------
	void onF2(int mods) override;                       // F2

private:

	// ------------------------------------------
	// Private methods specific to CAppEmpty only
	// ------------------------------------------
	//
	// ------------------------------------------
	obj3D objeto3D;
	vector<unsigned int> textureID;
	unsigned int currentShaderID;
	unsigned int geometryID;
};

#endif // !CAPPEMPTY_H