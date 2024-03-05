#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4VisAttributes.hh"

#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    // materials
    auto nist = G4NistManager::Instance();
    auto matAir = nist->FindOrBuildMaterial("G4_AIR");
    auto matAluminum = nist->FindOrBuildMaterial("G4_Al");
    auto matHPGe = nist->FindOrBuildMaterial("G4_Ge");
    auto matLithium = nist->FindOrBuildMaterial("G4_Li");

    // Solid : 지오메트리 모양, 크기
    // Logical : 지오메트리의 매질 등 질적인 특성에 대한 정보
    // Physical : 지오메트리의 위치, 회전, 소속 등 배치에 대한 정보 담당

    // World
    auto worldSize = 1. * m;
    auto worldSol = new G4Box("World", .5 * worldSize, .5 * worldSize, .5 * worldSize); 
    auto worldLog = new G4LogicalVolume(worldSol, matAir, "World");                     
    auto worldPhy = new G4PVPlacement(nullptr, G4ThreeVector(), worldLog, "World", nullptr, false, 0); 
    
    // Aluminum1
    auto Aluminum1Pos = G4ThreeVector(0., 0., 0.);

    auto Aluminum1Diameter = 7.8 * cm;
    auto Aluminum1Height = 12.44 * cm;    
    auto Aluminum1Sol = new G4Tubs("Aluminum1", 3.6 *cm, .5 * Aluminum1Diameter, .5 * Aluminum1Height, 0., 360. * deg);     
    auto Aluminum1Log = new G4LogicalVolume(Aluminum1Sol, matAluminum, "Aluminum1");     
    new G4PVPlacement(nullptr, Aluminum1Pos, Aluminum1Log, "Aluminum1", worldLog, false, 0);     

    G4VisAttributes* va_Aluminum1 = 
    new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.3));
    va_Aluminum1->SetForceSolid(true);
    va_Aluminum1->SetVisAttributes(va_Aluminum1);
    
    // Aluminum2_celling
    auto Aluminum2Pos = G4ThreeVector(0., 0., 6.27 * cm);

    auto Aluminum2Diameter = 7.8 * cm;
    auto Aluminum2Height   = 0.4 * cm;    
    auto Aluminum2Sol = new G4Tubs("Aluminum2", 0 *cm, .5 * Aluminum2Diameter, .5 * Aluminum2Height, 0., 360. * deg);     
    auto Aluminum2Log = new G4LogicalVolume(Aluminum2Sol, matAluminum, "Aluminum2");     
    new G4PVPlacement(nullptr, Aluminum2Pos, Aluminum2Log, "Aluminum2", worldLog, false, 0);     

    // Aluminum3_Floor
    auto Aluminum3Pos = G4ThreeVector(0., 0., -6.27 * cm);

    auto Aluminum3Diameter = 7.8 * cm;
    auto Aluminum3Height   = 0.4 * cm;    
    auto Aluminum3Sol = new G4Tubs("Aluminum3", 0 *cm, .5 * Aluminum2Diameter, .5 * Aluminum2Height, 0., 360. * deg);     
    auto Aluminum3Log = new G4LogicalVolume(Aluminum3Sol, matAluminum, "Aluminum3");     
    new G4PVPlacement(nullptr, Aluminum3Pos, Aluminum3Log, "Aluminum3", worldLog, false, 0);     

    // Lithium1
    auto Lithium1Pos = G4ThreeVector(0., 0., 4.8 * cm);

    auto Lithium1Diameter = 5.09 * cm;
    auto Lithium1Height =   2.00 * cm;
    auto Lithium1Sol = new G4Tubs("Lithium1", 2.525 * cm, .5 * Lithium1Diameter, .5 * Lithium1Height, 0., 360. * deg);  
    auto Lithium1Log = new G4LogicalVolume(Lithium1Sol, matLithium, "Lithium1");
    new G4PVPlacement(nullptr, Lithium1Pos, Lithium1Log, "Lithium1", worldLog, false, 0);

    // Lithium2_celling
    auto Lithium2Pos = G4ThreeVector(0., 0., 5.82 * cm);

    auto Lithium2Diameter = 5.09 * cm;
    auto Lithium2Height =   0.04 * cm;
    auto Lithium2Sol = new G4Tubs("Lithium2", 0* cm, .5 * Lithium2Diameter, .5 * Lithium2Height, 0., 360. * deg);  
    auto Lithium2Log = new G4LogicalVolume(Lithium2Sol, matLithium, "Lithium2");
    new G4PVPlacement(nullptr, Lithium2Pos, Lithium2Log, "Lithium2", worldLog, false, 0);
    
    // Lithium3_Floor
    auto Lithium3Pos = G4ThreeVector(0., 0., 3.78 * cm);

    auto Lithium3Diameter = 5.09 * cm;
    auto Lithium3Height =   0.04 * cm;
    auto Lithium3Sol = new G4Tubs("Lithium3", 0 * cm, .5 * Lithium3Diameter, .5 * Lithium3Height, 0., 360. * deg);  
    auto Lithium3Log = new G4LogicalVolume(Lithium3Sol, matLithium, "Lithium3");
    new G4PVPlacement(nullptr, Lithium3Pos, Lithium3Log, "Lithium3", worldLog, false, 0);
    
    // HPGe
    auto HPGePos = G4ThreeVector(0., 0., 4.8 * cm);

    auto HPGeDiameter = 5.05 * cm;
    auto HPGeHeight =   2 * cm;
    auto HPGeSol = new G4Tubs("HPGe", 0, .5 * HPGeDiameter, .5 * HPGeHeight, 0., 360. * deg);  
    auto HPGeLog = new G4LogicalVolume(HPGeSol, matHPGe, "HPGe");
    new G4PVPlacement(nullptr, HPGePos, HPGeLog, "HPGe", worldLog, false, 0);

    return worldPhy;
}

void DetectorConstruction::ConstructSDandField()
{
    // MFD 등록
    auto mfd = new G4MultiFunctionalDetector("Detector");
    G4SDManager::GetSDMpointer()->AddNewDetector(mfd);

    // PS 1 등록 -> 여러개의 PS를 등록할 때도 마찬가지로 사용하면 된다.
    auto psEDep = new G4PSEnergyDeposit("EDep"); 
    mfd->RegisterPrimitive(psEDep);
    
    /* 
    PS 2 등록 예시

    auto psDoseDep = new G4PSDoseDeposit("DoseDep"); 
    mfd->RegisterPrimitive(psDoseDep);
    */

    /*     
    Filter 세팅하기 : Filter는 PS의 추가옵션같은 기능 

    1) 원하는 PS 클래스의 객체를 만든다.
    2) 해당 Filter 객체를 PS에 세팅 
    3) 해당 PS 객체를 MFD에 등록    
    */ 

    // Logical Volume에 SD setting
    /*
    SetSensitiveDetector("Polyethylene1", mfd);
    SetSensitiveDetector("Lithium", mfd);

    
    SetSensitiveDetector("shielding1", mfd);
    SetSensitiveDetector("shielding2", mfd);
    */
   }
