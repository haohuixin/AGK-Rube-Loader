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

see example main.agc to import and run the physics scene.

function LoadRubeScene takes 4 parameters

LoadRubeScene( filename$ ,imageStartId, physicsSpriteStartId, imageSpriteStartId)

Parameters:
//              filename$               string  the filename and path to the rube data.
//              imageStartId            integer value used to start the allocation of id's for images
//              physicsSpriteStartId    integer value used to start the allocation of id's for physics sprites
//              imageSpriteStartId      integer value used to start the allocation of id's for image sprites

