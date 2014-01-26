// ========================================================================
// Name: AGK Rube Exporter v1.03
// Tags: AGKExporter
//
// Version: 1.03
// Created: 22/01/2014
// By: Stuart Tresadern
//
// RUBE Editor Version: 1.5.4
// AGK Version: 108 & current Alpha 2
// ----------------------------------------------------------------------------------------------------------------------------------


// ========================================================================
// Globals
// ----------------------------------------------------------------------------------------------------------------------------------
	
string seperator = "|";
string newline = "\n";
string defaultExportPath = "C:\\Development\\TrezSoft\\AGK\\RubeLoader\\media\\";
string defaultFileName = "myrubescene.txt"; 
string pathSepartor = "/";
string exportText;

// ========================================================================
// main
// ----------------------------------------------------------------------------------------------------------------------------------
void main() 
{
	array<int> imageOrder(getAllImages().length);

	print("AGK Exporter Started");
	print("       Getting Images for AGK image loader.");

	imageOrder = GetAllImageFiles();

	print("       " + imageOrder.length + " images processed");
	print("       Getting Image sprites for AGK");
	print("       " + GetAllImageSprites(imageOrder) + " image sprites processed");
	print("       Getting Physics sprites for AGK");
	print("       " + GetAllPhysicsSprites(imageOrder) + " physics sprites processed");
	print("       Getting Joints for AGK");
	print("       " +  GetAllPhysicsJoints() + " joints processed");
	print("       Saving Export File : " + defaultExportPath + defaultFileName);
	print("AGK Export complete : " + SaveExportFile());
}

// ========================================================================
// Save the AGK Export File
// ----------------------------------------------------------------------------------------------------------------------------------

bool SaveExportFile()
{
	bool exportfile = writeFile(defaultExportPath + defaultFileName , exportText);
	return exportfile;
}

// ========================================================================
// Gets all the image files so that they can be pre loaded in AGK
// ----------------------------------------------------------------------------------------------------------------------------------

int[] GetAllImageFiles()
{
	image[] bimage = getAllImages();
	array<int> imageOrder(bimage.length);

	for (uint i = 0; i < bimage.length(); i++)
	{		
		if(bimage[i].valid)
		{
			int id = bimage[i].id;		
			exportText += "1" + seperator + id + seperator + GetFileNameFromPath(bimage[i].getFile()) + newline;			
			imageOrder[i] = bimage[i].getRenderOrder();
		}		
	}
	
	imageOrder.reverse();

	return imageOrder;
}

// ========================================================================
// Gets all the image sprites for AGK (Images that are not attached to a physics body
// ----------------------------------------------------------------------------------------------------------------------------------

int  GetAllImageSprites(int[] imageOrder) 
{
	image[] bimages = getAllImages();

	for (uint i = 0; i < bimages.length(); i++)
	{
		if(!bimages[i].getBody().valid)
		{
			int id = bimages[i].id;	
			float positionX =  bimages[i].center.x ;
			float positionY =  bimages[i].center.y ;
			float angle = rd(bimages[i].getAngle());	
			float scale = bimages[i].getScale();
			float aspect = bimages[i].getAspectScale();
			int flipped = BoolToInt(bimages[i].getFlip());
			int renderOrder =  imageOrder[i];
			string colorTint = bimages[i].getColorTint().getStr255();
			
			exportText += "2" + seperator + id + seperator + positionX + seperator + positionY + seperator + angle + seperator + scale + seperator + aspect + seperator + flipped + seperator + renderOrder + seperator + colorTint + newline;	
		}

	}

	return 0;
}

// ========================================================================
// Gets all physics bodies
// 		Bodies without images have an image id of -1 to allow for dummy sprite creation in AGK
// 		Bodies will only include the first assigned image, AGK only supports one image per body.
// 		If any fixture has isSensor set to true the body will be set as a sensor in AGK
// 		Friction & Restitution will be returned from the average of all fixtures on the body.
// 		Filter category, Mask Bits and group index will be taken from the first returned fixture
// 		Vertices limit in AGK are between 2 - 12 the results window will show warnings for shapes that exceed this range.
// ----------------------------------------------------------------------------------------------------------------------------------

int GetAllPhysicsSprites(int[] imageOrder)
{
	body[] worldbodies = getAllBodies();

	for ( uint i = 0; i < worldbodies .length() ; i++)
	{
		int imageId = GetBodyImageId( worldbodies[i]);
		int spriteId = worldbodies[i].id;
		int type = BodyTypeConvert(worldbodies[i].getType());
		int bullet = BoolToInt(worldbodies[i].isBullet());
		int fixedrotation = BoolToInt(!worldbodies[i].isFixedRotation());
		float positionX = 0.0;
		float positionY = 0.0;
		float angle = 0.0;
		float scale = 0.0;
		float aspect = 0.0;
		int flipped = 0;
		int renderOrder =0;
		string colorTint ="";
 
		if ( imageId != -1)
		{
			image[] bimages =  worldbodies[i].getImages();
			positionX =  worldbodies[i].pos.x + (bimages[0].center.x );
			positionY =  worldbodies[i].pos.y + (bimages[0].center.y );
			angle = rd(worldbodies[i].angle);
			scale = bimages[0].getScale();
			aspect = bimages[0].getAspectScale();
			flipped = BoolToInt(bimages[0].getFlip());
			renderOrder = imageOrder[i];
			colorTint = bimages[0].getColorTint().getStr255();
		}
		else
		{
			positionX = worldbodies[i].pos.x ;
			positionY = worldbodies[i].pos.y ;
			angle = rd(worldbodies[i].angle);
		}

		fixture[] bfixtures = worldbodies[i].getFixtures();

		float friction = GetAverageFriction(bfixtures);
		float restitution = GetAverageRestitution(bfixtures);
		int sensor = CheckFixturesForSensor(bfixtures);
	
		int categorybits = 1;
		int maskbits = 65535;
		int filtergroup = 0;

		if(bfixtures[0].valid)
		{
			categorybits = bfixtures[0].getFilterCategoryBits();
			maskbits = bfixtures[0].getFilterMaskBits();
			filtergroup = bfixtures[0].getFilterGroupIndex();			
		}

		exportText += "3" + seperator + spriteId + seperator + imageId + seperator +  type + seperator + positionX + seperator + positionY + seperator + angle + seperator + bullet + seperator + fixedrotation + seperator + worldbodies[i].getLinearVelocity().x + seperator + worldbodies[i].getLinearVelocity().y + seperator + worldbodies[i].getAngularVelocity() + seperator + worldbodies[i].getLinearDamping() + seperator + worldbodies[i].getAngularDamping() + seperator + worldbodies[i].getMass() + seperator + worldbodies[i].getLocalCenter().x + seperator + worldbodies[i].getLocalCenter().y + seperator + sensor + seperator + friction + seperator + restitution + seperator + scale + seperator + aspect + seperator + flipped + seperator + renderOrder + seperator + colorTint + seperator + filtergroup + seperator + categorybits + seperator + maskbits + newline;

		for (uint f = 0; f < bfixtures.length(); f++)
		{		
			int fixtureType = bfixtures[f].getShape(0).type;
			
			int firstFixture = 0;
			if ( f == 0)
			{
				firstFixture = 1;
			}

			if (fixtureType == 0 ) // circle
			{
				exportText += "5" + seperator + spriteId + seperator  + firstFixture +  seperator  + bfixtures[f].getVertex(0).x + seperator + bfixtures[f].getVertex(0).y + seperator +  bfixtures[f].getShape(0).getRadius() + newline;
			}
			else if (fixtureType == 1 || fixtureType == 2)
			{
 	     		vertex[] fvertices = bfixtures[f].getVertices();
				string vertstring  = "";

				for (int v = 0; v < bfixtures[f].getNumVertices(); v++)
				{
					string sep = ",";
					if (v == bfixtures[f].getNumVertices() -1)
					{
						sep =""; 
					}
					vertstring += fvertices[v].x +","+ fvertices[v].y + sep;
				}

				if ( bfixtures[f].getNumVertices() > 12 )
				{
					print("       ** WARNING ** Body " +  worldbodies[i].id + ":" + worldbodies[i].getName() + " - fixture  has " + bfixtures[f].getNumVertices() + "vetices." );
 					print("                                AGK Supports a maximum of 12 vertices, please reduce the vertex count." );
					print("                                TIP: Consider using Action->Fixture->Split Fixture to create multiple polygons." );
				}
		
				exportText += "4" + seperator + spriteId + seperator + firstFixture + seperator + bfixtures[f].getNumVertices() + seperator + vertstring + newline;
			}
		}
	}

	return worldbodies .length();
}

// ========================================================================
// Gets All Physics Joints
// AGK does not support friction and motor joints
// ISSUE: Cannot access MotorSpeed and MotorTorque in script.
// ----------------------------------------------------------------------------------------------------------------------------------
int GetAllPhysicsJoints()
{
	joint[] bjoints = getAllJoints();

	for (uint i = 0; i < bjoints.length() ; i++)
	{		
		int spriteAid = bjoints[i].getBodyA().id;
		int spriteBid = bjoints[i].getBodyB().id;
		float anchorAx = bjoints[i].getWorldAnchorA().x;
		float anchorAy = bjoints[i].getWorldAnchorA().y;
		float anchorBx =bjoints[i].getWorldAnchorB().x;
		float anchorBy =  bjoints[i].getWorldAnchorB().y;


		if (  bjoints[i].getType() == 1 ) // Revolute Joint
		{
			exportText += "6" + seperator +  bjoints[i].id + seperator + spriteAid + seperator +spriteBid + seperator + anchorAx + seperator + anchorAy + seperator + anchorBx + seperator + anchorBy + seperator + bjoints[i].getReferenceAngle() + seperator + rd(bjoints[i].getLowerLimit()) + seperator + rd(bjoints[i].getUpperLimit()) + seperator + BoolToInt(bjoints[i].getEnableMotor()) + seperator + BoolToInt(bjoints[i].getEnableLimit()) + seperator + bjoints[i].getMotorSpeed() + seperator + bjoints[i].getMaxMotorTorque() + seperator + bjoints[i].getLocalAxis().x + seperator + bjoints[i].getLocalAxis().y + seperator + bjoints[i].getCollideConnected() + newline;
		}	

		if (  bjoints[i].getType() == 2 ) // Prismatic Joint
		{
			exportText += "7" + seperator +  bjoints[i].id + seperator + spriteAid + seperator +spriteBid + seperator + anchorAx + seperator + anchorAy + seperator + anchorBx + seperator + anchorBy + seperator + bjoints[i].getReferenceAngle() + seperator + bjoints[i].getLowerLimit() + seperator + bjoints[i].getUpperLimit() + seperator + BoolToInt(bjoints[i].getEnableMotor()) + seperator + BoolToInt(bjoints[i].getEnableLimit()) + seperator + bjoints[i].getMotorSpeed() + seperator + bjoints[i].getMaxMotorForce() + seperator + bjoints[i].getLocalAxis().x + seperator + bjoints[i].getLocalAxis().y + seperator + bjoints[i].getCollideConnected() + newline;
		}

		if (  bjoints[i].getType() == 8 ) // Weld Joint
		{
			exportText += "10" + seperator +  bjoints[i].id + seperator + spriteAid + seperator +spriteBid + seperator + anchorAx + seperator + anchorAy + seperator + anchorBx + seperator + anchorBy + seperator + bjoints[i].getReferenceAngle() + seperator + bjoints[i].getLocalAxis().x + seperator + bjoints[i].getLocalAxis().y + seperator + bjoints[i].getCollideConnected() + newline;
		}

		if (  bjoints[i].getType() == 3  ) // Distance Joint
		{
			exportText += "11" + seperator +  bjoints[i].id + seperator + spriteAid + seperator +spriteBid + seperator + anchorAx + seperator + anchorAy + seperator + anchorBx + seperator + anchorBy + seperator + bjoints[i].getLocalAxis().x + seperator + bjoints[i].getLocalAxis().y + seperator + bjoints[i].getCollideConnected() + newline;
		}

		if (  bjoints[i].getType() == 10  ) // Rope Joint
		{
			exportText += "12" + seperator +  bjoints[i].id + seperator + spriteAid + seperator +spriteBid + seperator + anchorAx + seperator + anchorAy + seperator + anchorBx + seperator + anchorBy + seperator + bjoints[i].getLocalAxis().x + seperator + bjoints[i].getLocalAxis().y + seperator + bjoints[i].getCollideConnected() + newline;
		}

		if (  bjoints[i].getType() == 7 ) // Wheel Joint
		{
			exportText += "13" + seperator +  bjoints[i].id + seperator + spriteAid + seperator +spriteBid + seperator + anchorAx + seperator + anchorAy + seperator + anchorBx + seperator + anchorBy + seperator + bjoints[i].getEnableMotor() + seperator + bjoints[i].getLocalAxis().x + seperator + bjoints[i].getLocalAxis().y + seperator + bjoints[i].getCollideConnected() + newline;
		}
	}

	return bjoints.length();
}

// ========================================================================
// Gets the body image id
// ----------------------------------------------------------------------------------------------------------------------------------
int GetBodyImageId(body currentbody)
{
	image[] wbImages = currentbody.getImages();
	int imageId = -1;

	if ( wbImages.length() >= 1 )
	{
		imageId = wbImages[0].id;

		if ( wbImages.length() > 1 )
		{
			print("       ** WARNING ** Body " +  currentbody.id + ":" + currentbody.getName() + " has " + wbImages.length() + " images assigned.");
 			print("                                only the first image will be exported. AGK only supports one image per body." );
			print("                                TIP: Consider creating a composite image and creating fixtures as required." );
		}			
	}

	return imageId;
}

// ========================================================================
// Converts a bool to integer
// ----------------------------------------------------------------------------------------------------------------------------------
int BoolToInt(bool testValue)
{
	if(testValue)
	{
		return 1;
	}
	return 0;
}

// ========================================================================
// Coverts RUBE body type to AGK body type
// ----------------------------------------------------------------------------------------------------------------------------------

int BodyTypeConvert(int currentType)
{
	if( currentType == 0)
	{
		return  1;
	}
	else if (currentType == 1)
	{
		return 3;
	}
	else
	{
		return  2;
	}
}

// ========================================================================
// Checks an array of fixtures and returns 1 (true) if any of the
// fixtures has isSensor set to true. 
// ----------------------------------------------------------------------------------------------------------------------------------

int CheckFixturesForSensor(fixture[] checkFixtures)
{
	int result = 0;

	for(uint i = 0; i < checkFixtures.length; i++)
	{
		if(checkFixtures[i].isSensor() == true)
		{
			return 1;
		}
	}

	return result;
}

// ========================================================================
// Returns the average friction for the supplied array of fixtures.
// AGK only allows the friction to be set on the physics body.
// ----------------------------------------------------------------------------------------------------------------------------------

float GetAverageFriction(fixture[] checkFixtures)
{
	if ( checkFixtures.length == 0 )
	{		
		return 0.0;
	}
	float result = 0.0;
	for(uint i = 0; i < checkFixtures.length; i++)
	{
		result += checkFixtures[i].getFriction();
	}
	
	if ( result == 0.0)
	{
		return 0.0;
	}
	result = result / checkFixtures.length;
	return result;
}

// ========================================================================
// Returns the average friction for the supplied array of fixtures
// AGK only allows the friction to be set on the physics body.
// ----------------------------------------------------------------------------------------------------------------------------------

float GetAverageRestitution(fixture[] checkFixtures)
{
	if ( checkFixtures.length == 0 )
	{		
		return 0.0;
	}

	float result = 0.0;
	for(uint i = 0; i < checkFixtures.length; i++)
	{
		result += checkFixtures[i].getRestitution();
	}

	if ( result == 0.0)
	{
		return 0.0;
	}
	result = result / checkFixtures.length;
	return result;
}

// ========================================================================
// Gets the Filename from the path
// ----------------------------------------------------------------------------------------------------------------------------------

string GetFileNameFromPath(string fullFileName)
{
	int fileNameStartPosition = 0;
	fileNameStartPosition = fullFileName.findLast(pathSepartor) + 1;
			
	if ( fileNameStartPosition == -1)
	{
		fileNameStartPosition = 0;
	}
	string fileName = fullFileName.substr(fileNameStartPosition);

	return fileName;
}

