
scene1Time = 6 --7
scence2Time = 5 --5
scene3Time = 5   --5
scene4Time = 4.5  --6


function Scene1()

    BeginCommandGroup("CameraInit","Parallel")

        BindGameObject("Falcon")
        MoveWithTime(4,-1,0,0)
        RotateWithTime(0,-80,-90,0)

        WaitForSeconds(0.5)

        BindGameObject("Camera")
        MoveWithTime(0,0,5,0)

        --WaitForSeconds(0.01)

        --FollowObject("Falcon",10).SetSimpleFollow(1).SetMaxSpeed(20).SetFollowAxis(1,0,0)
       

        --FollowCurveWithTime(6).AddPoint(139,2,346, 0,0,-20,  90,0,0)
        --.AddPoint(80,2,346, 0,0,-20 ,-90,0,0)
        --.AddPoint(10,2,346, 0,0,20 ,0,0,0)
        
       
        --.LookAtCurve(1).LookAtOffset(0,-75,-90)
    EndCommandGroup("CameraInit")

       
    BeginCommandGroup("FalconInit", "Serial")

        --FollowCurveWithTime(5).AddPoint(0,0,0  0,1,0,  0,0,0)
        --.AddPoint(2,1,0,  0,0,0, 0,0,0)

        BindGameObject("Falcon")
        FollowCurveWithTime(0.5).AddPoint(4,-1,0, 0,1,0)
        .AddPoint(2.7,0,0, 1,0,0)

        FollowCurveWithTime(0.8).AddPoint(2.7,0,0, 0,0,0 ,0,0,0)
        .AddPoint(0.5,0,3.5, 0,0,0, 0,50,0)
        .LookAtCurve(1).LookAtOffset(-180,-110,90)


        FollowCurveWithTime(1).AddPoint(0.5,0,3.5, 0,0,0, 0,-80,0)
        .AddPoint(-1,0,2, 0,0,0,  0,0,0)
        .LookAtCurve(1).LookAtOffset(-180,-110,90)

        

        --.AddPoint(10,2,346, 0,0,20 ,0,0,0)

    EndCommandGroup("Falcon")

    BeginCommandGroup("FalconFade", "Parallel")

        WaitForSeconds(3)

        MoveWithSpeed(-8,0,2,1)
        RotateWithTime(0,-80,-90,2)

    EndCommandGroup("FalconFade")

    BeginCommandGroup("Asteroid Spawn", "Parallel")

        SpawnGameObject("Asteroid","Asteroid1" , 2);

        WaitForSeconds(0.01)
        BindGameObject("Asteroid1")
        MoveWithTime(0,0,-7,0)
        RotateWithTime(0,90,0,0)
        WaitForSeconds(0.01)
        MoveWithSpeed(10,0,-3,0.1)

        SpawnGameObject("Asteroid","Asteroid2" , 2);
        WaitForSeconds(0.01)
        BindGameObject("Asteroid2")
        MoveWithTime(-8,-1,1,0)
        RotateWithTime(0,-90,0,0)
        MoveWithSpeed(10,1,-4,0.15)

        WaitForSeconds(0.01)
        SpawnGameObject("Asteroid","Asteroid3" , 0);
        BindGameObject("Asteroid3")
        MoveWithTime(-3,0,0,0)
        RotateWithTime(0,90,0,0)
        MoveWithSpeed(10,0,-3,0.1)

        SpawnGameObject("Asteroid","Asteroid4" , 2);
        WaitForSeconds(0.01)
        BindGameObject("Asteroid4")
        MoveWithTime(-15,0,-7,0)
        RotateWithTime(0,90,0,0)
        WaitForSeconds(0.01)
        MoveWithSpeed(10,0,-3,0.1)


    EndCommandGroup("Asteroid Spawn")
end

function Scene2()

    BeginCommandGroup("CameraInit","Parallel")

        WaitForSeconds(scene1Time);
        BindGameObject("Falcon")
        MoveWithTime(4,-1,0,0)
        RotateWithTime(0,-80,-90,0)
        ScaleWithTime(0.002,0.002,0.002,0)

        WaitForSeconds(0.5)

        BindGameObject("Camera")
        MoveWithTime(-20,0,5,0)

    EndCommandGroup("CameraInit")


    BeginCommandGroup("AsteroidSpawn2", "Parallel")

    WaitForSeconds(scene1Time);

        SpawnGameObject("Asteroid","Asteroid01" , 3);
        BindGameObject("Asteroid01")
        MoveWithTime(-20,0,4.6,0)
        RotateWithTime(70,90,0,0)

        WaitForSeconds(0.01)

        RotateWithTime(360,180,0,13)
        MoveWithSpeed(-20,0,-5,0.022)

    EndCommandGroup("AsteroidSpawn2")

    BeginCommandGroup("FalconInit", "Parallel")

    WaitForSeconds(scene1Time);
    
    BindGameObject("Falcon")
    RotateWithTime(90,180,-80,0)
    MoveWithTime(-20,0,3, 0)

    WaitForSeconds(0.1)
    FollowCurveWithTime(5).AddPoint(-20,0,3,  1,0,1)
    .AddPoint(-20,0,4.4,   1,0,-1)
    .AddPoint(-22,0,6,  -3,0,5)

    RotateWithTime(90,180,-90,2)
    WaitForSeconds(1.5)
    RotateWithTime(90,180,-180,1)
    WaitForSeconds(0.9)
    RotateWithTime(90,180,-270,1)

    EndCommandGroup("FalconInit")

    

    BindGameObject("Falcon")
    BeginCommandGroup("Fighter1","Parallel")

        WaitForSeconds(scene1Time);

        SpawnGameObject("Fighter","Fighter1");
        BindGameObject("Fighter1")
        MoveWithTime(-20,0,1, 0)
    
        FollowObject("Falcon", 5).SetFollowDistance(0.2).SetMaxSpeed(10).SetFollowOffset(0.4,0.2,-0.2)
        RotateWithTime(0,-30,0,5)

        SpawnGameObject("Fighter","Fighter2");
        BindGameObject("Fighter2")
        MoveWithTime(-20.2,0,0, 0)
        FollowObject("Falcon", 5).SetFollowDistance(0.8).SetMaxSpeed(10).SetFollowOffset(0.3,0.2,-0.5)
        RotateWithTime(0,-30,0,5)

        SpawnGameObject("Fighter","Fighter3");
        BindGameObject("Fighter3")
        MoveWithTime(-20.8,0,0, 0)
        FollowObject("Falcon", 5).SetFollowDistance(0.8).SetMaxSpeed(10).SetFollowOffset(0.8,0.2,-0.5)
        RotateWithTime(0,-30,0,5)

        SpawnGameObject("Fighter","Fighter4");
        BindGameObject("Fighter4")
        MoveWithTime(-20.8,0,0, 0)
        FollowObject("Falcon", 5).SetFollowDistance(0.8).SetMaxSpeed(10).SetFollowOffset(1.4,-0.2,-1.5)
        RotateWithTime(0,-30,0,5)


    EndCommandGroup("Fighter1")

   



    
end

function Scene3()

    BeginCommandGroup("Init3", "Parallel")

    WaitForSeconds(scene1Time + scence2Time)

    BindGameObject("Falcon")
    MoveWithTime(-40,2,0,0)
    RotateWithTime(0,-80,-90,0)
    ScaleWithTime(0.002,0.002,0.002,0)
    
   

    WaitForSeconds(0.1)

    SpawnGameObject("Fighter","Fighter21");
    BindGameObject("Fighter21")
    MoveWithTime(-41,1,1, 0)
    FollowCurveWithTime(5).AddPoint(-40.5,1,1,  0.5,-1.1,0)
    .AddPoint(-39.67,-0.075,3,   -0.5,0,-1)

    SpawnGameObject("Fighter","Fighter22");
    BindGameObject("Fighter22")
    MoveWithTime(-40.2,1,0, 0)
    FollowObject("Fighter21",6).SetFollowDistance(0.2).SetFollowOffset(0.2,0,0).SetMaxSpeed(20)

    SpawnGameObject("Fighter","Fighter23");
    BindGameObject("Fighter23")
    MoveWithTime(-40.8,1,0, 0)
    FollowObject("Fighter21",6).SetFollowDistance(0.2).SetFollowOffset(-0.2,0,0).SetMaxSpeed(20)

    SpawnGameObject("Fighter","Fighter24");
    BindGameObject("Fighter24")
    MoveWithTime(-40.8,1,-0.3, 0)
    FollowObject("Fighter21",6).SetFollowDistance(0.2).SetFollowOffset(-0.1,0.1,-0.4).SetMaxSpeed(20)

    WaitForSeconds(0.5)
    BindGameObject("Camera")
    MoveWithTime(-40,0,2,0)

    EndCommandGroup("Init3")


    BeginCommandGroup("Collision1","Parallel")

    WaitForSeconds(scene1Time + scence2Time)

    SpawnGameObject("Asteroid","AsteroidCollide",3)
    BindGameObject("AsteroidCollide")

    MoveWithTime(-43.2,0.25,1, 0)


    WaitForSeconds(0.01)
    MoveWithTime(-36.2,0.25,1, 6.5)

    
    EndCommandGroup("Collision1")

    BindGameObject("Fighter24")
    BeginCommandGroup("Explosion","Parallel").SetCollisionCondition("AsteroidCollide")

    ScaleWithTime(0,0,0,0.1)
    SpawnGameObject("Asteroid","ExplodeSphere",4)
    BindGameObject("ExplodeSphere")
    MoveWithTime(-40.2,0.25,1, 0)
    ScaleWithTime(.4,.4,.4,4)

    EndCommandGroup("Collision1")



end

function Scene4()

    BeginCommandGroup("Init4", "Parallel")

    WaitForSeconds(scene1Time + scence2Time + scene3Time)

    BindGameObject("Falcon")
    MoveWithTime(-61.5,1.2,0,0)
    RotateWithTime( 0,0,0,0)
    ScaleWithTime(0.001,0.001,0.001,0)

    WaitForSeconds(0.5)
    
    BindGameObject("Camera")
    MoveWithTime(-60,0,2,0)

    EndCommandGroup("Init4")


    BindGameObject("Falcon")
    BeginCommandGroup("Falcon4", "Parallel")

    WaitForSeconds(scene1Time + scence2Time + scene3Time)

    FollowCurveWithTime(3).AddPoint(-61.5,1.2,0,  0,-1.5,1)
    .AddPoint(-60.1,0,2.5,   1,0,-1, 0,40,-70).LookAtCurve(1).LookAtOffset(90,0,0)


    SpawnGameObject("Asteroid","Asteroid41",0)
    BindGameObject("Asteroid41")
    MoveWithTime(-60,0,0,0)
    RotateWithTime(90,-360,0,10)
    
    SpawnGameObject("Asteroid","Asteroid42",0)
    BindGameObject("Asteroid42")
    MoveWithTime(-64,-1.0,0,0)

    SpawnGameObject("Asteroid","Asteroid43",0)
    BindGameObject("Asteroid43")
    MoveWithTime(-64,-1.0,0,0)
    ScaleWithTime(0.0002,0.0002,0.0002,0)


    WaitForSeconds(0.1)

    BindGameObject("Asteroid43")
    MoveWithTime(-60.9,-0.61,0,2.91)


    BindGameObject("Asteroid42")
    MoveWithTime(-61.7,-0.3,0, 1.7)
    RotateWithTime(90,-360,0,10)


    WaitForSeconds(1.7)

    MoveWithTime(-61.7,1,0, 3)

    WaitForSeconds(1.25)
    BindGameObject("Asteroid43")
    MoveWithTime(-53.9,-0.61,0,5)


    EndCommandGroup("Falcon4")


    BeginCommandGroup("Fighters4", "Parallel")
    WaitForSeconds(scene1Time + scence2Time + scene3Time)

    WaitForSeconds(0.1)
    SpawnGameObject("Fighter","Fighter41");
    BindGameObject("Fighter41")
    MoveWithTime(-61.5,1.2,1,0)

    FollowObject("Falcon",6).SetFollowOffset(0.5,0.5,-0.5).SetFollowDistance(0.5).SetMaxSpeed(20)

    SpawnGameObject("Fighter","Fighter42");
    BindGameObject("Fighter42")
    MoveWithTime(-61,-0.8,0,0)
    FollowObject("Falcon",6).SetFollowOffset(-0.5,-0.5,-0.5).SetFollowDistance(0.5).SetMaxSpeed(20)

    SpawnGameObject("Fighter","Fighter43");
    BindGameObject("Fighter43")
    MoveWithTime(-61,-0.8,-1,0)
    FollowObject("Falcon",5.5).SetFollowOffset(-0.7,-0.6,-1.2).SetFollowDistance(1).SetMaxSpeed(20)

    
    EndCommandGroup("Fighters4")

    BindGameObject("Fighter43")
    BeginCommandGroup("FighterDown", "Parallel").SetCollisionCondition("Asteroid43")
    WaitForSeconds(0.1)
    MoveWithTime(-59.75,0.17,2.5, 2)    
    RotateWithTime(10,10,360, 2)

    EndCommandGroup("FighterDown")
    

end

function Scene5()

    BeginCommandGroup("Init4", "Parallel")

    WaitForSeconds(scene1Time + scence2Time + scene3Time + scene4Time)

    WaitForSeconds(0.5)

    BindGameObject("Camera")
    MoveWithTime(-79.75,0.3,2.2,0)
    RotateWithTime(-12,9,0,0)

    EndCommandGroup("Init4")


    BeginCommandGroup("AsteroidScene5", "Parallel")

    WaitForSeconds(scene1Time + scence2Time + scene3Time + scene4Time)

    SpawnGameObject("Asteroid","Asteroid51",1)
    BindGameObject("Asteroid51")

    MoveWithTime(-80,0,2,0)
    
    EndCommandGroup("AsteroidScene5")



    BeginCommandGroup("FighterScene5", "Parallel")

    WaitForSeconds(scene1Time + scence2Time + scene3Time + scene4Time)

    WaitForSeconds(0.1)
    SpawnGameObject("Fighter","Fighter51");
    BindGameObject("Fighter51")
    MoveWithTime(-79.75,0.3,2.21,0)

    WaitForSeconds(0.1)
    MoveWithTime(-79.6,0.1,1.6,2)
    RotateWithTime(0,0,360,2)

    WaitForSeconds(2)

    ScaleWithTime(0,0,0,0.1)
    SpawnGameObject("Asteroid","ExplodeSphere2",4)
    BindGameObject("ExplodeSphere2")

    MoveWithTime(-79.6,0.1,1.6,0)
    ScaleWithTime(0.25,0.25,0.25,0.7)


    EndCommandGroup("FighterScene5")
    


end

Scene1()
Scene2()
Scene3()
Scene4()
Scene5()
