#ifndef RubeLoader_H
#define RubeLoader_H

#include "AGK.h"

///-------------------------------------------------------------------------------------------------
/// <summary>	Rube Editor Scene loader. 
///				Version 1.04			
/// 			Requires data in the format from the AGK Rube Exporter v1.04
/// </summary>
///
/// <remarks>	Stuartt, 27/01/2014. </remarks>
///-------------------------------------------------------------------------------------------------

class RubeLoader
{

	///=================================================================================================
	/// <summary>	A point. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///-------------------------------------------------------------------------------------------------

	struct Point             
	{   
		/// <summary>	The x coordinate. </summary>
		float x;
		/// <summary>	The y coordinate. </summary>
		float y;
	} ;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Defines an alias representing array of points. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///-------------------------------------------------------------------------------------------------

	typedef  Point* PointsArr;

	///=================================================================================================
	/// <summary>	Pre load images. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///
	/// <param name="data">		   	The data. </param>
	/// <param name="imageStartId">	Identifier for the image start. </param>
	///-------------------------------------------------------------------------------------------------

	void RubeLoader::PreLoadImages (const char* data, int imageStartId);

	///=================================================================================================
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

	void RubeLoader::CreateBaseSprites(const char* data, int spriteStartId, int imageStartId, int imageSpriteStartId, float drawScale);

	///=================================================================================================
	/// <summary>	Creates physics sprites. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///
	/// <param name="data">				The data. </param>
	/// <param name="spriteStartId">	Identifier for the sprite start. </param>
	/// <param name="imageStartId"> 	Identifier for the image start. </param>
	/// <param name="drawScale">		The draw scale. </param>
	///-------------------------------------------------------------------------------------------------

	void RubeLoader::CreatePhysicsSprites(const char* data, int spriteStartId, int imageStartId, float drawScale);

	///=================================================================================================
	/// <summary>	Creates polygon fixtures. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///
	/// <param name="data">				The data. </param>
	/// <param name="spriteStartId">	Identifier for the sprite start. </param>
	/// <param name="drawScale">		The draw scale. </param>
	///-------------------------------------------------------------------------------------------------

	void RubeLoader::CreatePolygonFixtures(const char* data, int spriteStartId, float drawScale);

	///=================================================================================================
	/// <summary>	Creates circle fixtures. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///
	/// <param name="data">				The data. </param>
	/// <param name="spriteStartId">	Identifier for the sprite start. </param>
	/// <param name="drawScale">		The draw scale. </param>
	///-------------------------------------------------------------------------------------------------

	void RubeLoader::CreateCircleFixtures (const char* data , int spriteStartId, float drawScale);

	///=================================================================================================
	/// <summary>	Creates revolute joints. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///
	/// <param name="data">				The data. </param>
	/// <param name="spriteStartId">	Identifier for the sprite start. </param>
	/// <param name="drawScale">		The draw scale. </param>
	///-------------------------------------------------------------------------------------------------

	void RubeLoader::CreateRevoluteJoints(const char* data, int spriteStartId, float drawScale);

	///=================================================================================================
	/// <summary>	Creates prismatic joints. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///
	/// <param name="data">				The data. </param>
	/// <param name="spriteStartId">	Identifier for the sprite start. </param>
	/// <param name="drawScale">		The draw scale. </param>
	///-------------------------------------------------------------------------------------------------

	void RubeLoader::CreatePrismaticJoints(const char* data, int spriteStartId, float drawScale);

	///=================================================================================================
	/// <summary>	Creates distance joints. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///
	/// <param name="data">				The data. </param>
	/// <param name="spriteStartId">	Identifier for the sprite start. </param>
	/// <param name="drawScale">		The draw scale. </param>
	///-------------------------------------------------------------------------------------------------

	void RubeLoader::CreateDistanceJoints(const char* data, int spriteStartId, float drawScale);

	///=================================================================================================
	/// <summary>	Creates friction joints. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///
	/// <param name="data">				The data. </param>
	/// <param name="spriteStartId">	Identifier for the sprite start. </param>
	/// <param name="drawScale">		The draw scale. </param>
	///-------------------------------------------------------------------------------------------------

	void RubeLoader::CreateFrictionJoints(const char* data, int spriteStartId, float drawScale);

	///=================================================================================================
	/// <summary>	Creates weld joints. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///
	/// <param name="data">				The data. </param>
	/// <param name="spriteStartId">	Identifier for the sprite start. </param>
	/// <param name="drawScale">		The draw scale. </param>
	///-------------------------------------------------------------------------------------------------

	void RubeLoader::CreateWeldJoints(const char* data, int spriteStartId, float drawScale);

	///=================================================================================================
	/// <summary>	Creates rope joints. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///
	/// <param name="data">				The data. </param>
	/// <param name="spriteStartId">	Identifier for the sprite start. </param>
	/// <param name="drawScale">		The draw scale. </param>
	///-------------------------------------------------------------------------------------------------

	void RubeLoader::CreateRopeJoints(const char* data, int spriteStartId, float drawScale);

	///=================================================================================================
	/// <summary>	Creates wheel joints. </summary>
	///
	/// <remarks>	Stuartt, 27/01/2014. </remarks>
	///
	/// <param name="data">				The data. </param>
	/// <param name="spriteStartId">	Identifier for the sprite start. </param>
	/// <param name="drawScale">		The draw scale. </param>
	///-------------------------------------------------------------------------------------------------

	void RubeLoader::CreateWheelJoints(const char* data, int spriteStartId, float drawScale);

	public:

		///=================================================================================================
		/// <summary>	Default constructor. </summary>
		///
		/// <remarks>	Stuartt, 27/01/2014. </remarks>
		///-------------------------------------------------------------------------------------------------

		RubeLoader(void);

		///=================================================================================================
		/// <summary>	Destructor. </summary>
		///
		/// <remarks>	Stuartt, 27/01/2014. </remarks>
		///-------------------------------------------------------------------------------------------------

		~RubeLoader(void);

		///=================================================================================================
		/// <summary>	Loads rube scene. </summary>
		///
		/// <remarks>	Stuartt, 27/01/2014. </remarks>
		///
		/// <param name="fileName">			   	Filename of the file. </param>
		/// <param name="imageStartId">		   	Identifier for the image start. </param>
		/// <param name="physicsSpriteStartId">	Identifier for the physics sprite start. </param>
		/// <param name="imageSpriteStartId">  	Identifier for the image sprite start. </param>
		/// <param name="drawScale">		   	The draw scale. </param>
		///-------------------------------------------------------------------------------------------------

		void RubeLoader::LoadRubeScene(const char *fileName, int imageStartId, int physicsSpriteStartId, int imageSpriteStartId, float drawScale);
};
#endif

