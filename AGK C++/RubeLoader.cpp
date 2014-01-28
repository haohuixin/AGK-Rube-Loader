///-------------------------------------------------------------------------------------------------
// file:	RubeLoader.cpp
//
// summary:	Implements the rube loader class
///-------------------------------------------------------------------------------------------------

#include "RubeLoader.h"
#include <string>
#include <iostream>

using namespace AGK;

///-------------------------------------------------------------------------------------------------
/// <summary>	Default constructor. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///-------------------------------------------------------------------------------------------------

RubeLoader::RubeLoader(void)
{
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Destructor. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///-------------------------------------------------------------------------------------------------

RubeLoader::~RubeLoader(void)
{
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Loads rube scene. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="fileName">			 	Filename of the file. </param>
/// <param name="imageStartId">		 	Identifier for the image start. </param>
/// <param name="physicsStartId">	 	Identifier for the physics start. </param>
/// <param name="imageSpriteStartId">	Identifier for the image sprite start. </param>
/// <param name="drawScale">		 	The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::LoadRubeScene(const char *fileName, int imageStartId, int physicsStartId,int imageSpriteStartId, float drawScale) 
{		
	if (agk::GetFileExists( fileName ) != 1 )
	{
		agk::Message("R.U.B.E Loader File not Found.");
		return;
	}

	int iRubeFile = agk::OpenToRead(fileName);

	agk::SetPhysicsMaxPolygonPoints(12);

	while( agk::FileEOF(iRubeFile) == 0)
	{
		const char* rubeData = agk::ReadLine( iRubeFile );

		int iTypeId = agk::Val(agk::GetStringToken(rubeData,"|",1));

		switch( iTypeId )
		{
			case 1:
				PreLoadImages(rubeData, imageStartId);
				break;
			case 2:
				CreateBaseSprites(rubeData, physicsStartId,imageStartId,imageSpriteStartId, drawScale);
				break;
			case 3:
				CreatePhysicsSprites(rubeData,physicsStartId,imageStartId, drawScale);
				break;
			case 4:
				CreatePolygonFixtures(rubeData, physicsStartId, drawScale);
				break;
			case 5:
				CreateCircleFixtures(rubeData, physicsStartId, drawScale);
				break;
			case 6:
				 CreateRevoluteJoints(rubeData, physicsStartId, drawScale);
				break;
			case 7:
				CreatePrismaticJoints(rubeData, physicsStartId, drawScale);
				break;
			case 9:
				CreateFrictionJoints(rubeData, physicsStartId, drawScale);
				break;
			case 10:
				CreateWeldJoints(rubeData, physicsStartId, drawScale);
				break;
			case 11:
				CreateDistanceJoints(rubeData, physicsStartId, drawScale);
				break;
			case 12:
				CreateRopeJoints(rubeData, physicsStartId, drawScale);
				break;
			case 13:
				CreateWheelJoints(rubeData, physicsStartId, drawScale);
				break;
		}
	}

	agk::CloseFile(iRubeFile);
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Pre load images. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">		   	The data. </param>
/// <param name="imageStartId">	Identifier for the image start. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::PreLoadImages (const char* data, int imageStartId)
{
	int iImageId = agk::Val(agk::GetStringToken(data,"|",2)) + imageStartId;
	std::string fileName = agk::GetStringToken(data,"|",3);
	std::string imageFileName = "media/" + fileName;	
	agk::LoadImage(iImageId, imageFileName.c_str() );
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Creates base sprites. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">				 	The data. </param>
/// <param name="spriteStartId">	 	Identifier for the sprite start. </param>
/// <param name="imageStartId">		 	Identifier for the image start. </param>
/// <param name="imageSpriteStartId">	Identifier for the image sprite start. </param>
/// <param name="drawScale">		 	The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::CreateBaseSprites(const char* data, int spriteStartId, int imageStartId, int imageSpriteStartId, float drawScale)
{
	int iSpriteId = agk::Val(agk::GetStringToken(data,"|",2)) + spriteStartId + imageSpriteStartId;
    int iImageId = agk::Val(agk::GetStringToken(data,"|",2)) + imageStartId;
    float imageX = agk::ValFloat(agk::GetStringToken(data,"|",3));
    float imageY = agk::ValFloat(agk::GetStringToken(data,"|",4));
    float imageAngle = agk::ValFloat(agk::GetStringToken(data,"|",5));
    float imageScale = agk::ValFloat(agk::GetStringToken(data,"|",6));
    float imageAspectScale = agk::ValFloat(agk::GetStringToken(data,"|",7));
    int imageHorizontalFlip = agk::Val(agk::GetStringToken(data,"|",8));
    int imageRenderOrder = agk::Val(agk::GetStringToken(data,"|",9));
    char* rgba = agk::GetStringToken(data,"|",10);
    int imageTintRed = agk::Val(agk::GetStringToken(rgba,",",1));
    int imageTintGreen = agk::Val(agk::GetStringToken(rgba,",",2));
    int imageTintBlue = agk::Val(agk::GetStringToken(rgba,",",3));
    int imageTintAlpha = agk::Val(agk::GetStringToken(rgba,",",4));

    agk::CreateSprite(iSpriteId, iImageId);
    agk::SetSpritePositionByOffset(iSpriteId, imageX * drawScale, imageY * -drawScale);
    float imageHeight = agk::GetImageHeight(iImageId) / drawScale;
    agk::SetSpriteSize(iSpriteId, -1 ,drawScale);
    agk::SetSpriteScaleByOffset(iSpriteId,imageScale * imageAspectScale, imageScale );
    agk::SetSpriteAngle(iSpriteId, imageAngle * -1);
    agk::SetSpriteFlip(iSpriteId, imageHorizontalFlip, 0);
    agk::SetSpriteDepth(iSpriteId, imageRenderOrder );
    agk::SetSpriteColor(iSpriteId,imageTintRed,imageTintGreen,imageTintBlue,imageTintAlpha);
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Creates physics sprites. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">				The data. </param>
/// <param name="spriteStartId">	Identifier for the sprite start. </param>
/// <param name="imageStartId"> 	Identifier for the image start. </param>
/// <param name="drawScale">		The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::CreatePhysicsSprites(const char* data, int spriteStartId, int imageStartId, float drawScale)
{
	int iSpriteId = agk::Val(agk::GetStringToken(data,"|",2)) + spriteStartId;
    int iImageId = agk::Val(agk::GetStringToken(data,"|",3));
    float spriteAngle = agk::ValFloat(agk::GetStringToken(data,"|",7)) * -1;

    if (iImageId == -1)
	{
        iImageId = agk::Val(agk::GetStringToken(data,"|",3)) + 1;
        agk::CreateDummySprite(iSpriteId);
	}
	else
	{
        int iImageId = agk::Val(agk::GetStringToken(data,"|",3)) + imageStartId;
        float imageX = agk::ValFloat(agk::GetStringToken(data,"|",5));
        float imageY = agk::ValFloat(agk::GetStringToken(data,"|",6));
        float imageAngle = agk::ValFloat(agk::GetStringToken(data,"|",7));
        float imageScale = agk::ValFloat(agk::GetStringToken(data,"|",21));
        float imageAspectScale = agk::ValFloat(agk::GetStringToken(data,"|",22));
        int imageHorizontalFlip = agk::Val(agk::GetStringToken(data,"|",23));
        int imageRenderOrder = agk::Val(agk::GetStringToken(data,"|",24));
        char* rgba = agk::GetStringToken(data,"|",25);
        int imageTintRed = agk::Val(agk::GetStringToken(rgba,",",1));
        int imageTintGreen = agk::Val(agk::GetStringToken(rgba,",",2));
        int imageTintBlue = agk::Val(agk::GetStringToken(rgba,",",3));
        int imageTintAlpha = agk::Val(agk::GetStringToken(rgba,",",4));

        agk::CreateSprite(iSpriteId, iImageId);
        agk::SetSpritePositionByOffset(iSpriteId, imageX * drawScale, imageY * -drawScale);
        float imageHeight = agk::GetImageHeight(iImageId) / drawScale;
        agk::SetSpriteSize(iSpriteId, -1 ,drawScale);
        agk::SetSpriteScaleByOffset(iSpriteId,imageScale * imageAspectScale, imageScale );
        agk::SetSpriteAngle(iSpriteId, imageAngle );
        agk::SetSpriteFlip(iSpriteId, imageHorizontalFlip, 0);
        agk::SetSpriteColor(iSpriteId,imageTintRed,imageTintGreen,imageTintBlue,imageTintAlpha);
        agk::SetSpriteDepth(iSpriteId, imageRenderOrder );
	}

    agk::SetSpritePhysicsOn(iSpriteId, agk::Val(agk::GetStringToken(data,"|",4)));
    agk::SetSpritePositionByOffset(iSpriteId, agk::ValFloat(agk::GetStringToken(data,"|",5)) * drawScale, agk::ValFloat(agk::GetStringToken(data,"|",6)) * -drawScale);
    agk::SetSpritePhysicsCanRotate(iSpriteId, agk::Val(agk::GetStringToken(data,"|",9)));
    agk::SetSpritePhysicsIsBullet(iSpriteId, agk::Val(agk::GetStringToken(data,"|",8)));
    agk::SetSpriteAngle(iSpriteId, spriteAngle );

    agk::SetSpritePhysicsDamping( iSpriteId, agk::ValFloat(agk::GetStringToken(data,"|",13)) );
    agk::SetSpritePhysicsAngularDamping( iSpriteId, agk::ValFloat(agk::GetStringToken(data,"|",14)) );
	// Exception when seting COM : from box2d : m_l > 0.0f !!!!
    //agk::SetSpritePhysicsCOM( iSpriteId, agk::ValFloat(agk::GetStringToken(data,"|",16)) * drawScale, agk::ValFloat(agk::GetStringToken(data,"|",17)) * -drawScale );
    agk::SetSpritePhysicsMass( iSpriteId, agk::ValFloat(agk::GetStringToken(data,"|",15)) * drawScale);
    agk::SetSpritePhysicsAngularVelocity( iSpriteId, agk::ValFloat(agk::GetStringToken(data,"|",12)) *-1 );
    agk::SetSpritePhysicsVelocity( iSpriteId,  agk::ValFloat(agk::GetStringToken(data,"|",10)) * drawScale ,  agk::ValFloat(agk::GetStringToken(data,"|",11)) *-drawScale);

    // Calculated from fictures !
    // Any fixture with isSensor on will set the sensor on in AGK
    // Restitution and Friction are the Average values from all the fictures(shapes) set in R.U.B.E for a body(sprite).
    agk::SetSpritePhysicsIsSensor( iSpriteId, agk::Val(agk::GetStringToken(data,"|",18)) );
    agk::SetSpritePhysicsFriction( iSpriteId, agk::ValFloat(agk::GetStringToken(data,"|",19)) );
    agk::SetSpritePhysicsRestitution( iSpriteId, agk::ValFloat(agk::GetStringToken(data,"|",20)));

    agk::SetSpriteGroup(iSpriteId, agk::Val(agk::GetStringToken(data,"|",26)));
    agk::SetSpriteCollideBits(iSpriteId, agk::Val(agk::GetStringToken(data,"|",28)));
    agk::SetSpriteCategoryBits(iSpriteId, agk::Val(agk::GetStringToken(data,"|",27)));
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Creates polygon fixtures. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">				The data. </param>
/// <param name="spriteStartId">	Identifier for the sprite start. </param>
/// <param name="drawScale">		The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::CreatePolygonFixtures(const char* data, int spriteStartId, float drawScale)
{
	int iSpriteId = agk::Val(agk::GetStringToken(data,"|",2)) + spriteStartId;
	const int vertCount = agk::Val(agk::GetStringToken(data,"|",4));
    float* verticesX = new float[vertCount];
    float* verticesY = new float[vertCount];
	PointsArr vertices = new Point[vertCount];

    int vcounter = 0;
    const char* verts = agk::GetStringToken(data,"|",5);

    int vc = 0;
    for (int v = 0; v < vertCount * 2 ; v=v+2)
	{       
		vertices[vc].x = (agk::ValFloat(agk::GetStringToken(verts,",",v + 1)) * drawScale);
		vertices[vc].y = (agk::ValFloat(agk::GetStringToken(verts,",",v + 2)) * -drawScale);
		vc++;
	}

    int counter = 0;
	for(int c = 0; c < vertCount ; c++)
	{
		if (agk::Val(agk::GetStringToken(data,"|",3)) == 1)
		{
            agk::SetSpriteShapePolygon(iSpriteId,vertCount,counter,vertices[c].x,vertices[c].y);
		}
		else
		{
            agk::AddSpriteShapePolygon(iSpriteId,vertCount,counter,vertices[c].x,vertices[c].y);
		}
        
		counter++;
	}
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Creates circle fixtures. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">				The data. </param>
/// <param name="spriteStartId">	Identifier for the sprite start. </param>
/// <param name="drawScale">		The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::CreateCircleFixtures (const char* data , int spriteStartId, float drawScale)
{
    int iSpriteId = agk::Val(agk::GetStringToken(data,"|",2)) + spriteStartId;
    float radius = agk::ValFloat(agk::GetStringToken(data,"|",6)) * drawScale;

    if (agk::Val(agk::GetStringToken(data,"|",3)) == 1)
	{
        agk::SetSpriteShapeCircle(iSpriteId, agk::ValFloat(agk::GetStringToken(data,"|",4)) * drawScale,agk::ValFloat(agk::GetStringToken(data,"|",5)) * -drawScale, radius );
	}
	else
	{
        agk::AddSpriteShapeCircle(iSpriteId, agk::ValFloat(agk::GetStringToken(data,"|",4)) * drawScale,agk::ValFloat(agk::GetStringToken(data,"|",5)) * -drawScale, radius );
	}

}

///-------------------------------------------------------------------------------------------------
/// <summary>	Creates revolute joints. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">				The data. </param>
/// <param name="spriteStartId">	Identifier for the sprite start. </param>
/// <param name="drawScale">		The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::CreateRevoluteJoints(const char* data, int spriteStartId, float drawScale)
{
	int iJointId = agk::Val(agk::GetStringToken(data,"|",2));
	int iSpriteAid = agk::Val(agk::GetStringToken(data,"|",3)) + spriteStartId;
	int iSpriteBid = agk::Val(agk::GetStringToken(data,"|",4)) + spriteStartId;
	float AnchorAx = agk::ValFloat(agk::GetStringToken(data,"|",5));
	float AnchorAy = agk::ValFloat(agk::GetStringToken(data,"|",6));
	int collide = agk::Val(agk::GetStringToken(data,"|",18));

	agk::CreateRevoluteJoint(iJointId,iSpriteAid,iSpriteBid,(AnchorAx * drawScale),(AnchorAy * -drawScale),collide);

	if(agk::Val(agk::GetStringToken(data,"|",13)) == 1)
	{
		agk::SetJointLimitOn( iJointId, agk::ValFloat(agk::GetStringToken(data,"|",10)) , agk::ValFloat(agk::GetStringToken(data,"|",11)) );
	}

	if(agk::Val(agk::GetStringToken(data,"|",12)) == 1)
	{
		agk::SetJointMotorOn( iJointId, agk::ValFloat(agk::GetStringToken(data,"|",14)) * -1 , agk::ValFloat(agk::GetStringToken(data,"|",15)) * drawScale );
	}
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Creates prismatic joints. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">				The data. </param>
/// <param name="spriteStartId">	Identifier for the sprite start. </param>
/// <param name="drawScale">		The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::CreatePrismaticJoints(const char* data, int spriteStartId, float drawScale)
{
    int iJointId = agk::Val(agk::GetStringToken(data,"|",2));
    int iSpriteAid = agk::Val(agk::GetStringToken(data,"|",3)) + spriteStartId;
    int iSpriteBid = agk::Val(agk::GetStringToken(data,"|",4)) + spriteStartId;
    float AnchorAx = agk::ValFloat(agk::GetStringToken(data,"|",5)) * drawScale;
    float AnchorAy = agk::ValFloat(agk::GetStringToken(data,"|",6)) * -drawScale;
    float Axisx = agk::ValFloat(agk::GetStringToken(data,"|",16));
    float Axisy = agk::ValFloat(agk::GetStringToken(data,"|",17))  * -1;
    int collide = agk::Val(agk::GetStringToken(data,"|",18));

    agk::CreatePrismaticJoint(iJointId,iSpriteAid,iSpriteBid,AnchorAx,AnchorAy, Axisx, Axisy, collide);

    if(agk::Val(agk::GetStringToken(data,"|",13)) == 1)
	{
        agk::SetJointLimitOn( iJointId, agk::ValFloat(agk::GetStringToken(data,"|",10)) / drawScale, agk::ValFloat(agk::GetStringToken(data,"|",11)) / drawScale );
	}

	if(agk::Val(agk::GetStringToken(data,"|",12)) == 1)
	{
		agk::SetJointMotorOn( iJointId, agk::ValFloat(agk::GetStringToken(data,"|",14)) , agk::ValFloat(agk::GetStringToken(data,"|",15)) * drawScale );
	}
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Creates distance joints. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">				The data. </param>
/// <param name="spriteStartId">	Identifier for the sprite start. </param>
/// <param name="drawScale">		The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::CreateDistanceJoints(const char* data, int spriteStartId, float drawScale)
{
    int iJointId = agk::Val(agk::GetStringToken(data,"|",2));
    int iSpriteAid = agk::Val(agk::GetStringToken(data,"|",3)) + spriteStartId;
    int iSpriteBid = agk::Val(agk::GetStringToken(data,"|",4)) + spriteStartId;
    float AnchorAx = agk::ValFloat(agk::GetStringToken(data,"|",5)) * drawScale;
    float AnchorAy = agk::ValFloat(agk::GetStringToken(data,"|",6)) * -drawScale;
    float AnchorBx = agk::ValFloat(agk::GetStringToken(data,"|",7)) * drawScale;
    float AnchorBy = agk::ValFloat(agk::GetStringToken(data,"|",8)) * -drawScale;
    int collide = agk::Val(agk::GetStringToken(data,"|",11));

    agk::CreateDistanceJoint(iJointId,iSpriteAid,iSpriteBid,AnchorAx,AnchorAy, AnchorBx, AnchorBy, collide);
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Creates friction joints. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">				The data. </param>
/// <param name="spriteStartId">	Identifier for the sprite start. </param>
/// <param name="drawScale">		The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::CreateFrictionJoints(const char* data, int spriteStartId, float drawScale)
{
	// Not Implemented ( AGK Does not currently support friction joints )
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Creates weld joints. </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">				The data. </param>
/// <param name="spriteStartId">	Identifier for the sprite start. </param>
/// <param name="drawScale">		The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::CreateWeldJoints(const char* data, int spriteStartId, float drawScale)
{
    int iJointId = agk::Val(agk::GetStringToken(data,"|",2));
    int iSpriteAid = agk::Val(agk::GetStringToken(data,"|",3)) + spriteStartId;
    int iSpriteBid = agk::Val(agk::GetStringToken(data,"|",4)) + spriteStartId;
    float AnchorAx = agk::ValFloat(agk::GetStringToken(data,"|",5)) * drawScale;
    float AnchorAy = agk::ValFloat(agk::GetStringToken(data,"|",6)) * -drawScale;
    int collide = agk::Val(agk::GetStringToken(data,"|",12));

    agk::CreateWeldJoint(iJointId,iSpriteAid,iSpriteBid,AnchorAx,AnchorAy,collide);
}

///-------------------------------------------------------------------------------------------------
/// <summary>
/// 	Creates rope joints. (Creates a distance joint, AGK does not support rope joints)
/// </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">				The data. </param>
/// <param name="spriteStartId">	Identifier for the sprite start. </param>
/// <param name="drawScale">		The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::CreateRopeJoints(const char* data, int spriteStartId, float drawScale)
{
    CreateDistanceJoints( data ,spriteStartId,drawScale);
}

///-------------------------------------------------------------------------------------------------
/// <summary>	Creates wheel joints. (Creates a Line joint and distance joint cobination) </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///
/// <param name="data">				The data. </param>
/// <param name="spriteStartId">	Identifier for the sprite start. </param>
/// <param name="drawScale">		The draw scale. </param>
///-------------------------------------------------------------------------------------------------

void RubeLoader::CreateWheelJoints(const char* data, int spriteStartId, float drawScale)
{
    int iJointId = agk::Val(agk::GetStringToken(data,"|",2));
    int iSpriteAid = agk::Val(agk::GetStringToken(data,"|",3)) + spriteStartId;
    int iSpriteBid = agk::Val(agk::GetStringToken(data,"|",4)) + spriteStartId;
    float AnchorAx = agk::ValFloat(agk::GetStringToken(data,"|",5)) * drawScale;
    float AnchorAy = agk::ValFloat(agk::GetStringToken(data,"|",6)) * -drawScale;
    float Axisx = agk::ValFloat(agk::GetStringToken(data,"|",10));
    float Axisy = agk::ValFloat(agk::GetStringToken(data,"|",11)) * -1;
    int collide = agk::Val(agk::GetStringToken(data,"|",12));

    CreateDistanceJoints( data , spriteStartId, drawScale);
    iJointId = iJointId + 1000;
    agk::CreateLineJoint(iJointId,iSpriteAid,iSpriteBid,AnchorAx,AnchorAy, Axisx, Axisy, collide);
}
