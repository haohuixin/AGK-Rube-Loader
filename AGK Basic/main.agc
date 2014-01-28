rem
rem AGK Application
rem

// Includes
#include "RubeLoader.agc"

SetVirtualResolution ( 100, 100 )

SetViewOffset( -50, -50 )
Global drawScale#
drawScale# = 5
SetPhysicsScale(0.2)

LoadRubeScene("myrubescene.txt", 1000, 1000, 1000)
SetPhysicsGravity(0,50)
SetPhysicsDebugOn()

do
 Sync()
loop
