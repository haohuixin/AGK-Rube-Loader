// ========================================================================
// AGK R.U.B.E Loader
// Version 1.0
// 22/01/2014
// Stuart Tresadern
//
// Requires data in the format from the AGK Rube Exporter v1.0
// ------------------------------------------------------------------------


// =============================================================================================================
// Load in the Rube Data File and recreates the physics world in AGK
//
// Use the AGK Exporter.rs script to export the data from R.U.B.E
// Parameters:
//              filename$               string  the filename and path to the rube data.
//              imageStartId            integer value used to start the allocation of id's for images
//              physicsSpriteStartId    integer value used to start the allocation of id's for physics sprites
//              imageSpriteStartId      integer value used to start the allocation of id's for image sprites
// -------------------------------------------------------------------------------------------------------------
Function LoadRubeScene( filename$ ,imageStartId, physicsSpriteStartId, imageSpriteStartId)

     if GetFileExists( filename$ ) = 0
        Message("R.U.B.E Loader" + Chr(13) + Chr(13) + "File not found." + Chr(13) + filename$)
        exitfunction
     endif

    iRubefile = OpenToRead(filename$)

    while FileEOF(iRubefile) = 0

        rubedata$ = ReadLine( iRubefile )

        iTypeId = Val(GetStringToken(rubedata$,"|",1))

        select iTypeId
            case 0:
                CreatePhysicsWorld( rubedata$ )
            endcase
            case 1:
                PreLoadImage( rubedata$ , imageStartId)
            endcase
            case 2:
                CreateBaseSprites( rubedata$ , physicsSpriteStartId, imageStartId , imageSpriteStartId)
            endcase
            case 3:
                CreatePhysicsSprites( rubedata$ , physicsSpriteStartId, imageStartId)
            endcase
            case 4:
                CreatePolygonFixtures( rubedata$ , physicsSpriteStartId )
            endcase
            case 5:
                CreateCircleFixtures( rubedata$ , physicsSpriteStartId)
            endcase
            case 6:
                CreateRevoluteJoints( rubedata$ , physicsSpriteStartId)
            endcase
            case 7:
                CreatePrismaticJoints( rubedata$ , physicsSpriteStartId)
            endcase
            case 9:
                CreateFrictionJoints( rubedata$ , physicsSpriteStartId)
            endcase
            case 10:
                CreateWeldJoints( rubedata$ , physicsSpriteStartId)
            endcase
            case 11:
                CreateDistanceJoints( rubedata$ , physicsSpriteStartId)
            endcase
            case 12:
                CreateRopeJoints( rubedata$ , physicsSpriteStartId)
            endcase
            case 13:
                CreateWheelJoints( rubedata$ , physicsSpriteStartId)
            endcase

        endselect

    endwhile

    CloseFile(iRubefile)

Endfunction

// ========================================================================
// Creates the physics world ( Not Implemented )
// ------------------------------------------------------------------------
Function CreatePhysicsWorld (data$)


Endfunction

// ========================================================================
// Pre Load Images
// parse data and extract imageId and filename
// ------------------------------------------------------------------------
Function PreLoadImage(data$, imageStartId)

        iImageId = Val(GetStringToken(data$,"|",2)) + imageStartId
        sImageFileName$ = GetStringToken(data$,"|",3)
        LoadImage( iImageId, sImageFileName$ )

Endfunction

// ========================================================================
// Creates background sprites and links them to preloaded images
// These are sprites not connected to a physics body.
// ------------------------------------------------------------------------
Function CreateBaseSprites(data$,spriteStartId, imageStartId, imageSpriteStartId)

        iSpriteId = Val(GetStringToken(data$,"|",2)) + spriteStartId + imageSpriteStartId
        iImageId = Val(GetStringToken(data$,"|",2)) + imageStartId
        imageX# = ValFloat(GetStringToken(data$,"|",3))
        imageY# = ValFloat(GetStringToken(data$,"|",4))
        imageAngle# = ValFloat(GetStringToken(data$,"|",5))
        imageScale# = ValFloat(GetStringToken(data$,"|",6))
        imageAspectScale# = ValFloat(GetStringToken(data$,"|",7))
        imageHorizontalFlip = Val(GetStringToken(data$,"|",8))
        imageRenderOrder = Val(GetStringToken(data$,"|",9))
        rgba$ = GetStringToken(data$,"|",10)
        imageTintRed = Val(GetStringToken(rgba$,",",1))
        imageTintGreen = Val(GetStringToken(rgba$,",",2))
        imageTintBlue = Val(GetStringToken(rgba$,",",3))
        imageTintAlpha = Val(GetStringToken(rgba$,",",4))

        CreateSprite(iSpriteId, iImageId)
        SetSpritePositionByOffset(iSpriteId, imageX# * drawScale#, imageY# * -drawScale#)
        imageHeight# = GetImageHeight(iImageId) / drawScale#
        SetSpriteSize(iSpriteId, -1 ,drawScale#)
        SetSpriteScaleByOffset(iSpriteId,imageScale# * imageAspectScale#, imageScale# )
        SetSpriteAngle(iSpriteId, imageAngle# * -1)
        SetSpriteFlip(iSpriteId, imageHorizontalFlip, 0)
        // SetSpriteDepth(iSpriteId, imageRenderOrder ) Order is reversed..... how to fix this !
        SetSpriteColor(iSpriteId,imageTintRed,imageTintGreen,imageTintBlue,imageTintAlpha)

Endfunction

// ========================================================================
// Creates Physics bodies and attch the pre loaded image
// Only One image per body allowed !
// Multiple Fixtures (shapes) are allowed
// ------------------------------------------------------------------------
Function CreatePhysicsSprites( data$ ,spriteStartId, imageStartId)

        iSpriteId = Val(GetStringToken(data$,"|",2)) + spriteStartId
        iImageId = Val(GetStringToken(data$,"|",3))
        spriteAngle# = ValFloat(GetStringToken(data$,"|",7)) * -1

        if iImageId = -1
            iImageId = Val(GetStringToken(data$,"|",3)) + 1
            CreateDummySprite(iSpriteId)
        else
            iImageId = Val(GetStringToken(data$,"|",3)) + imageStartId
            imageX# = ValFloat(GetStringToken(data$,"|",5))
            imageY# = ValFloat(GetStringToken(data$,"|",6))
            imageAngle# = ValFloat(GetStringToken(data$,"|",7))
            imageScale# = ValFloat(GetStringToken(data$,"|",21))
            imageAspectScale# = ValFloat(GetStringToken(data$,"|",22))
            imageHorizontalFlip = Val(GetStringToken(data$,"|",23))
            imageRenderOrder = Val(GetStringToken(data$,"|",24))
            rgba$ = GetStringToken(data$,"|",25)
            imageTintRed = Val(GetStringToken(rgba$,",",1))
            imageTintGreen = Val(GetStringToken(rgba$,",",2))
            imageTintBlue = Val(GetStringToken(rgba$,",",3))
            imageTintAlpha = Val(GetStringToken(rgba$,",",4))

            CreateSprite(iSpriteId, iImageId)
            SetSpritePositionByOffset(iSpriteId, imageX# * drawScale#, imageY# * -drawScale#)
            imageHeight# = GetImageHeight(iImageId) / drawScale#
            SetSpriteSize(iSpriteId, -1 ,drawScale#)
            SetSpriteScaleByOffset(iSpriteId,imageScale# * imageAspectScale#, imageScale# )
            SetSpriteAngle(iSpriteId, imageAngle# * -1)
            SetSpriteFlip(iSpriteId, imageHorizontalFlip, 0)
            // SetSpriteDepth(iSpriteId, imageRenderOrder ) Order is reversed..... how to fix this !
            SetSpriteColor(iSpriteId,imageTintRed,imageTintGreen,imageTintBlue,imageTintAlpha)
        endif

        SetSpritePhysicsOn(iSpriteId, Val(GetStringToken(data$,"|",4)))
        SetSpritePositionByOffset(iSpriteId, ValFloat(GetStringToken(data$,"|",5)) * drawScale#, ValFloat(GetStringToken(data$,"|",6))) * -drawScale#
        SetSpritePhysicsCanRotate(iSpriteId, Val(GetStringToken(data$,"|",9)))
        SetSpritePhysicsIsBullet(iSpriteId, Val(GetStringToken(data$,"|",8)))
        SetSpriteAngle(iSpriteId, spriteAngle# )

        SetSpritePhysicsDamping( iSpriteId, ValFloat(GetStringToken(data$,"|",13)) )
        SetSpritePhysicsAngularDamping( iSpriteId, ValFloat(GetStringToken(data$,"|",14)) )
        SetSpritePhysicsCOM( iSpriteId, ValFloat(GetStringToken(data$,"|",16)) * drawScale#, ValFloat(GetStringToken(data$,"|",17)) * -drawScale# )
        SetSpritePhysicsMass( iSpriteId, ValFloat(GetStringToken(data$,"|",15))) * drawScale#
        SetSpritePhysicsAngularVelocity( iSpriteId, ValFloat(GetStringToken(data$,"|",12)) *-1 )
        SetSpritePhysicsVelocity( iSpriteId,  ValFloat(GetStringToken(data$,"|",10)) * drawScale# ,  ValFloat(GetStringToken(data$,"|",11)) *-drawScale#)

        // Calculated from fictures !
        // Any fixture with isSensor on will set the sensor on in AGK
        // Restitution and Friction are the Average values from all the fictures(shapes) set in R.U.B.E for a body(sprite).
        SetSpritePhysicsIsSensor( iSpriteId, ValFloat(GetStringToken(data$,"|",18)) )
        SetSpritePhysicsFriction( iSpriteId, ValFloat(GetStringToken(data$,"|",19)) )
        SetSpritePhysicsRestitution( iSpriteId, ValFloat(GetStringToken(data$,"|",20)))


Endfunction

// ========================================================================
// Create Polygon Fixtures (Shapes)
// ------------------------------------------------------------------------
Function CreatePolygonFixtures ( data$ ,spriteStartId)

        iSpriteId = Val(GetStringToken(data$,"|",2)) + spriteStartId
        dim verticesX#[Val(GetStringToken(data$,"|",4))]
        dim verticesY#[Val(GetStringToken(data$,"|",4))]

        vcounter = 0
        verts$ = GetStringToken(data$,"|",5)

        vc = 0
        for v = 0 to (Val(GetStringToken(data$,"|",4)) * 2) -1 step 2
            verticesX#[vc] = (ValFloat(GetStringToken(verts$,",",v + 1))* drawScale#)
            verticesY#[vc] = (ValFloat(GetStringToken(verts$,",",v + 2)) * -drawScale#)
            vc = vc + 1
        next v

        counter = 0
        for c = Val(GetStringToken(data$,"|",4)) -1 to 0 step -1
            if Val(GetStringToken(data$,"|",3)) = 1
                SetSpriteShapePolygon(iSpriteId,Val(GetStringToken(data$,"|",4)),counter,verticesX#[c],verticesY#[c])
            else
                AddSpriteShapePolygon(iSpriteId,Val(GetStringToken(data$,"|",4)),counter,verticesX#[c],verticesY#[c])
            endif
            inc counter
        next c

Endfunction

// ========================================================================
// Create Circle Fixtures. (Shapes)
// ------------------------------------------------------------------------
Function CreateCircleFixtures ( data$ , spriteStartId)

    iSpriteId = Val(GetStringToken(data$,"|",2)) + spriteStartId
    radius# = ValFloat(GetStringToken(data$,"|",6)) * drawScale#

    if Val(GetStringToken(data$,"|",3)) = 1
        SetSpriteShapeCircle(iSpriteId, ValFloat(GetStringToken(data$,"|",4)) * drawScale#,ValFloat(GetStringToken(data$,"|",5)) * -drawScale#, radius# )
    else
        AddSpriteShapeCircle(iSpriteId, ValFloat(GetStringToken(data$,"|",4)) * drawScale#,ValFloat(GetStringToken(data$,"|",5)) * -drawScale#, radius# )
    endif

Endfunction

// ========================================================================
// Joint Issues
// Can not set motor speed or torque (no output from rube)
// Can not set joint collide connected ( no output from rube)
// both should be available in the next rube build.
// ------------------------------------------------------------------------


// ========================================================================
// Creates revolute physics joins
// ------------------------------------------------------------------------
Function CreateRevoluteJoints( data$, spriteStartId )

    iJointId = Val(GetStringToken(data$,"|",2))
    iSpriteAid = Val(GetStringToken(data$,"|",3)) + spriteStartId
    iSpriteBid = Val(GetStringToken(data$,"|",4)) + spriteStartId
    AnchorAx# = ValFloat(GetStringToken(data$,"|",5))
    AnchorAy# = ValFloat(GetStringToken(data$,"|",6))
    CreateRevoluteJoint(iJointId,iSpriteAid,iSpriteBid,(AnchorAx# * drawScale#),(AnchorAy# * -drawScale#),0)

     // Motor and Limits
    if  Val(GetStringToken(data$,"|",13)) = 1
        SetJointLimitOn( iJointId, ValFloat(GetStringToken(data$,"|",10)) , ValFloat(GetStringToken(data$,"|",11)))
    endif

   if  Val(GetStringToken(data$,"|",12)) = 1
        // R.U.B.E Does not currently output the Motor speed and torque (as of 25/01/2014)
        SetJointMotorOn( iJointId, .5 / drawscale# , 50 * drawscale# )
    endif

Endfunction

// ========================================================================
// Creates prismatic physics joins
// ------------------------------------------------------------------------
Function CreatePrismaticJoints( data$ , spriteStartId)

    iJointId = Val(GetStringToken(data$,"|",2))
    iSpriteAid = Val(GetStringToken(data$,"|",3)) + spriteStartId
    iSpriteBid = Val(GetStringToken(data$,"|",4)) + spriteStartId
    AnchorAx# = ValFloat(GetStringToken(data$,"|",5)) * drawScale#
    AnchorAy# = ValFloat(GetStringToken(data$,"|",6)) * -drawScale#
    Axisx# = ValFloat(GetStringToken(data$,"|",14))
    Axisy# = ValFloat(GetStringToken(data$,"|",15))  * -1
    CreatePrismaticJoint(iJointId,iSpriteAid,iSpriteBid,AnchorAx#,AnchorAy#, Axisx#, Axisy#, 0)

    // Motor and Limits
    if  Val(GetStringToken(data$,"|",13)) = 1
        SetJointLimitOn( iJointId, ValFloat(GetStringToken(data$,"|",10)) / drawScale#, ValFloat(GetStringToken(data$,"|",11)) / drawScale# )
    endif

   if  Val(GetStringToken(data$,"|",12)) = 1
         // R.U.B.E Does not currently output the Motor speed and torque (as of 25/01/2014)
        SetJointMotorOn( iJointId, .5 / drawscale# , 50 * drawscale#)
    endif

Endfunction

// ========================================================================
// Creates distance physics joins
// ------------------------------------------------------------------------
Function CreateDistanceJoints( data$ ,spriteStartId)

    iJointId = Val(GetStringToken(data$,"|",2))
    iSpriteAid = Val(GetStringToken(data$,"|",3)) + spriteStartId
    iSpriteBid = Val(GetStringToken(data$,"|",4)) + spriteStartId
    AnchorAx# = ValFloat(GetStringToken(data$,"|",5)) * drawScale#
    AnchorAy# = ValFloat(GetStringToken(data$,"|",6)) * -drawScale#
    AnchorBx# = ValFloat(GetStringToken(data$,"|",7)) * drawScale#
    AnchorBy# = ValFloat(GetStringToken(data$,"|",8)) * -drawScale#
    CreateDistanceJoint(iJointId,iSpriteAid,iSpriteBid,AnchorAx#,AnchorAy#, AnchorBx#, AnchorBy#, 0)

Endfunction

// ========================================================================
// Creates Friction joints, if i can work out a way !
// ------------------------------------------------------------------------
Function CreateFrictionJoints( data$, spriteStartId )


Endfunction

// ========================================================================
// Creates Weld joints
// ------------------------------------------------------------------------
Function CreateWeldJoints( data$, spriteStartId)

    iJointId = Val(GetStringToken(data$,"|",2))
    iSpriteAid = Val(GetStringToken(data$,"|",3)) + spriteStartId
    iSpriteBid = Val(GetStringToken(data$,"|",4)) + spriteStartId
    AnchorAx# = ValFloat(GetStringToken(data$,"|",5)) * drawScale#
    AnchorAy# = ValFloat(GetStringToken(data$,"|",6)) * -drawScale#
    CreateWeldJoint(iJointId,iSpriteAid,iSpriteBid,AnchorAx#,AnchorAy#,0)

Endfunction

// ========================================================================
// Create Rope Joints
// rope joints are not supported so we can create a distance joint instead.
// ------------------------------------------------------------------------
Function CreateRopeJoints( data$ ,spriteStartId)

    CreateDistanceJoints( data$ ,spriteStartId)

Endfunction

// ========================================================================
// Create Wheel joints
// ------------------------------------------------------------------------
Function CreateWheelJoints( data$ ,spriteStartId)

    iJointId = Val(GetStringToken(data$,"|",2))
    iSpriteAid = Val(GetStringToken(data$,"|",3)) + spriteStartId
    iSpriteBid = Val(GetStringToken(data$,"|",4)) + spriteStartId
    AnchorAx# = ValFloat(GetStringToken(data$,"|",5)) * drawScale#
    AnchorAy# = ValFloat(GetStringToken(data$,"|",6)) * -drawScale#
    Axisx# = ValFloat(GetStringToken(data$,"|",10))
    Axisy# = ValFloat(GetStringToken(data$,"|",11)) * -1

    CreateDistanceJoints( data$ , spriteStartId)
    iJointId = iJointId + 1000
    CreateLineJoint(iJointId,iSpriteAid,iSpriteBid,AnchorAx#,AnchorAy#, Axisx#, Axisy#, 0)

Endfunction


