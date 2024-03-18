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
    auto matAluminum = nist->FindOrBuildMaterial("G4_Al");
    auto matHPGe = nist->FindOrBuildMaterial("G4_Ge");
    auto matLithium = nist->FindOrBuildMaterial("G4_Li");
    auto matZirlo = nist->FindOrBuildMaterial("G4_Zr");
    auto matelu = nist->FindOrBuildMaterial("Enriched Uranium")
    // auto matelU = nist->FindOrBuildMaterial("G4_U");

    /* Uranium
    G4Isotope* U235 = new G4Isotope("U235", 92, 235, 235.01 * g/mole);
    G4Isotope* U238 = new G4Isotope("U238", 92, 238, 238.03 * g/mole);
    G4Element* enrichedU = new G4Element("enrichedU", 2);
    enrichedU->AddIsotope(U235, 1.71*perCent);
    enrichedU->AddIsotope(U238, 98.29*perCent);
    */

    auto G4Material* enrichedU = new G4Material("Uranium", 19.050* g/cm3, 1)
    
    // Solid : 지오메트리 모양, 크기
    // Logical : 지오메트리의 매질 등 질적인 특성에 대한 정보
    // Physical : 지오메트리의 위치, 회전, 소속 등 배치에 대한 정보 담당

    // World
    auto worldSize = 10. * m;
    auto worldSol = new G4Box("World", .5 * worldSize, .5 * worldSize, .5 * worldSize); 
    auto worldLog = new G4LogicalVolume(worldSol, matAir, "World");                     
    auto worldPhy = new G4PVPlacement(nullptr, G4ThreeVector(), worldLog, "World", nullptr, false, 0); 
    
    // Zirlo1
    auto Zirlo1Pos = G4ThreeVector(0., 0., 0.);

    auto Zirlo1Diameter = 9.5 * mm;
    auto Zirlo1Height = 409.7 * cm;    
    auto Zirlo1Sol = new G4Tubs("Zirlo1", 4.25 * mm, .5 * Zirlo1Diameter, .5 * Zirlo1Height, 0., 360. * deg);     
    auto Zirlo1Log = new G4LogicalVolume(Zirlo1Sol, matZirlo, "Zirlo1");     
    new G4PVPlacement(nullptr, Zirlo1Pos, Zirlo1Log, "Zirlo1", worldLog, false, 0);     

    // enrichedU1
    auto enrichedU1Pos = G4ThreeVector(0., 0., 0.);

    auto enrichedU1Diameter = 8.19 * mm;
    auto enrichedU1Height = 9.8 * mm;
    auto enrichedU1Sol = new G4Tubs("enrichedU1", 0, .5 * enrichedU1Diameter, .5 * enrichedU1Height, 0., 360. * deg);     
    auto enrichedU1Log = new G4LogicalVolume(enrichedU1Sol, enrichedU, "enrichedU1");
    new G4PVPlacement(nullptr, enrichedU1Pos, enrichedU1Log, "enrichedU1", worldLog, false, 0);

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
