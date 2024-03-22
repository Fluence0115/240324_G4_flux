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
#include "G4Material.hh"
#include "G4Element.hh"
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
    auto matWater = nist->FindOrBuildMaterial("G4_WATER");
     
    // Solid : 지오메트리 모양, 크기
    // Logical : 지오메트리의 매질 등 질적인 특성에 대한 정보
    // Physical : 지오메트리의 위치, 회전, 소속 등 배치에 대한 정보 담당

    // World
    auto worldSize = 3. * m;
    auto worldSol = new G4Box("World", .5 * worldSize, .5 * worldSize, .5 * worldSize); 
    auto worldLog = new G4LogicalVolume(worldSol, matAir, "World");                     
    auto worldPhy = new G4PVPlacement(nullptr, G4ThreeVector(), worldLog, "World", nullptr, false, 0); 
    
    // Water Phantom
    auto phantomPos = G4ThreeVector(0., 0., 100. *cm);

    auto phantomDiameter = 1 * cm;
    auto phantomHeight = 1 * cm;    
    auto phantomSol = new G4Tubs("phantom", 0, .5 * phantomDiameter, .5 * phantomHeight, 0., 360. * deg);     
    auto phantomLog = new G4LogicalVolume(phantomSol, matWater, "phantom");     
    new G4PVPlacement(nullptr, phantomPos, phantomLog, "phantom", worldLog, false, 0);     
 
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

    // Logical Volume에 SD setting
    SetSensitiveDetector("phantom", mfd);

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

    
    
   }
