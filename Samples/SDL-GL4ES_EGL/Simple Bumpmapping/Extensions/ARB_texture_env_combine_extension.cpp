//
//	ARB_texture_env_combine_extension.cpp
//	ARB_texture_env_combine extension setup
//	Downloaded from: www.paulsprojects.net
//	Created:	15th November 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//
//#include <windows.h>
#include <stdio.h>
#include <EGLSDL/SDL.h>
#include <EGL/gl.h>
#include <EGL/glext.h>
//#include <EGL/wglext.h>
#include "ARB_texture_env_combine_extension.h"

bool ARB_texture_env_combine_supported=false;

bool SetUpARB_texture_env_combine()
{
	//Check for support
	char * extensionString=(char *)glGetString(GL_EXTENSIONS);
	char * extensionName="GL_ARB_texture_env_combine";

	char * endOfString;									//store pointer to end of string
	unsigned int distanceToSpace;						//distance to next space

	endOfString=extensionString+strlen(extensionString);

	//loop through string
	while(extensionString<endOfString)
	{
		//find distance to next space
		distanceToSpace=strcspn(extensionString, " ");

		//see if we have found extensionName
		if((strlen(extensionName)==distanceToSpace) &&
			(strncmp(extensionName, extensionString, distanceToSpace)==0))
		{
			ARB_texture_env_combine_supported=true;
		}

		//if not, move on
		extensionString+=distanceToSpace+1;
	}

	if(!ARB_texture_env_combine_supported)
	{
		printf("ARB_texture_env_combine unsupported!\n");
		return false;
	}

	printf("ARB_texture_env_combine supported!\n");

	//get function pointers
	//None specified

	return true;
}