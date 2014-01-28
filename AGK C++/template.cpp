
#include "template.h"
#include "RubeLoader.h"

///=================================================================================================
// namespace: AGK
//
// summary:	.
///-------------------------------------------------------------------------------------------------

using namespace AGK;

/// <summary>	The application. </summary>
app App;

///=================================================================================================
/// <summary>	Begins this object. </summary>
///
/// <remarks>	Stuartt, 28/01/2014. </remarks>
///-------------------------------------------------------------------------------------------------

void app::Begin(void)
{
	agk::SetVirtualResolution (100, 100);
	agk::SetSyncRate(60,0);
	agk::SetScissor(0,0,0,0);
	agk::SetViewOffset(-50,-50);
	agk::SetPhysicsScale(0.2f);
	agk::SetPhysicsGravity(0,50);
	agk::SetPhysicsDebugOn();

	RubeLoader rb = RubeLoader();
	rb.LoadRubeScene("media/myrubescene.txt",1000,1000,1000,5);
}

///=================================================================================================
/// <summary>	Loops this object. </summary>
///
/// <remarks>	Stuartt, 28/01/2014. </remarks>
///-------------------------------------------------------------------------------------------------

void app::Loop (void)
{
	agk::Sync();
}

///=================================================================================================
/// <summary>	Ends this object. </summary>
///
/// <remarks>	Stuartt, 28/01/2014. </remarks>
///-------------------------------------------------------------------------------------------------

void app::End (void)
{

}

