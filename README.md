AGK-Rube-Loader
===============

AGK (App Game Kit) R.U.B.E Editor Exporter and Loader

AGK http://www.appgamekit.com/

R.U.B.E Editor https://www.iforce2d.net/rube/


Exporter script for Rube

Load the script into the rube script editor
Edit the defaultExportPath and defualtFileName (AGK media folder recommended)

run the script to generate the data file for AGK.


AGK RubeLoader.

Add the RubeLoader.agc to your project.

example main.agc to import and run the physics scene.


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
