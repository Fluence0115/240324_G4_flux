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
    // auto matelU = nist->FindOrBuildMaterial("G4_U");
    
    G4Isotope* U235 = new G4Isotope("U235", 92, 235, 235.01 * g/mole);
    G4Isotope* U238 = new G4Isotope("U238", 92, 238, 238.03 * g/mole);
    
    //Uranium1
    G4Element* elU1 = new G4Element("Uranium1", "U1", 2);
    elU1->AddIsotope(U238, 98.29*perCent);
    elU1->AddIsotope(U235, 1.71*perCent);
    G4double density = 0.;
    G4Material*matU1 = new G4Material("U1", density, 1);
    matU1->AddElement(elU1, 1);

    //Uranium2
    G4Element* elU2 = new G4Element("Uranium2", "U2", 2);
    elU2->AddIsotope(U238, 97.8*perCent);
    elU2->AddIsotope(U235, 2.2*perCent);
    G4Material*matU2 = new G4Material("U2", density, 1);
    matU2->AddElement(elU2, 1);

    //Uranium3
    G4Element* elU3 = new G4Element("Uranium3", "U3", 2);
    elU3->AddIsotope(U238, 97.36*perCent);
    elU3->AddIsotope(U235, 2.64*perCent);
    G4Material*matU3 = new G4Material("U3", density, 1);
    matU3->AddElement(elU3, 1);

    //Uranium4
    G4Element* elU4 = new G4Element("Uranium4", "U4", 2);
    elU4->AddIsotope(U238, 96.36*perCent);
    elU4->AddIsotope(U235, 3.64*perCent);
    G4Material*matU4 = new G4Material("U4", density, 1);
    matU4->AddElement(elU4, 1);

    //Uranium5
    G4Element* elU5 = new G4Element("Uranium5", "U5", 2);
    elU5->AddIsotope(U238, 96.0*perCent);
    elU5->AddIsotope(U235, 4.0*perCent);
    G4Material*matU5 = new G4Material("U5", density, 1);
    matU5->AddElement(elU5, 1);

    //Uranium6
    G4Element* elU6 = new G4Element("Uranium6", "U6", 2);
    elU6->AddIsotope(U238, 95.5*perCent);
    elU6->AddIsotope(U235, 4.5*perCent);
    G4Material*matU6 = new G4Material("U6", density, 1);
    matU6->AddElement(elU6, 1);

    //Uranium7
    G4Element* elU7 = new G4Element("Uranium7", "U7", 2);
    elU7->AddIsotope(U238, 95.5*perCent);
    elU7->AddIsotope(U235, 4.5*perCent);
    G4Material*matU7 = new G4Material("U7", density, 1);
    matU7->AddElement(elU7, 1);
            
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

    auto Zirlo1Diameter = 0.95 * cm;
    auto Zirlo1Height = 409.7 * cm;    
    auto Zirlo1Sol = new G4Tubs("Zirlo1", 0.425 * cm, .5 * Zirlo1Diameter, .5 * Zirlo1Height, 0., 360. * deg);     
    auto Zirlo1Log = new G4LogicalVolume(Zirlo1Sol, matZirlo, "Zirlo1");     
    new G4PVPlacement(nullptr, Zirlo1Pos, Zirlo1Log, "Zirlo1", worldLog, false, 0);     

    G4VisAttributes* va_Zirlo1 =
    new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.3));
    va_Zirlo1->SetForceSolid(true);
    // va_Zirlo1->SetVisAttributes(va_Zirlo1);

    // Uranium1
    auto Uranium1Pos = G4ThreeVector(0., 0., -92.94 * cm);

    auto Uranium1Diameter = 0.819 * cm;
    auto Uranium1Height = 0.98 * cm;
    auto Uranium1Sol = new G4Tubs("Uranium1", 0, .5 * Uranium1Diameter, .5 * Uranium1Height, 0., 360. * deg);     
    auto Uranium1Log = new G4LogicalVolume(Uranium1Sol, matU1, "Uranium1");
    new G4PVPlacement(nullptr, Uranium1Pos, Uranium1Log, "Uranium1", worldLog, false, 0);

    // Uranium2
    auto Uranium2Pos = G4ThreeVector(0., 0., -62.94 * cm);

    auto Uranium2Diameter = 0.819 * cm;
    auto Uranium2Height = 0.98 * cm;
    auto Uranium2Sol = new G4Tubs("Uranium2", 0, .5 * Uranium2Diameter, .5 * Uranium2Height, 0., 360. * deg);     
    auto Uranium2Log = new G4LogicalVolume(Uranium2Sol, matU2, "Uranium2");
    new G4PVPlacement(nullptr, Uranium2Pos, Uranium2Log, "Uranium2", worldLog, false, 0);

     // Uranium3
    auto Uranium3Pos = G4ThreeVector(0., 0., -32.94 * cm);

    auto Uranium3Diameter = 0.819 * cm;
    auto Uranium3Height = 0.98 * cm;
    auto Uranium3Sol = new G4Tubs("Uranium3", 0, .5 * Uranium3Diameter, .5 * Uranium3Height, 0., 360. * deg);     
    auto Uranium3Log = new G4LogicalVolume(Uranium3Sol, matU3, "Uranium3");
    new G4PVPlacement(nullptr, Uranium3Pos, Uranium3Log, "Uranium3", worldLog, false, 0);

    // Uranium4
    auto Uranium4Pos = G4ThreeVector(0., 0., -2.94 * cm);

    auto Uranium4Diameter = 0.819 * cm;
    auto Uranium4Height = 0.98 * cm;
    auto Uranium4Sol = new G4Tubs("Uranium4", 0, .5 * Uranium4Diameter, .5 * Uranium4Height, 0., 360. * deg);     
    auto Uranium4Log = new G4LogicalVolume(Uranium4Sol, matU4, "Uranium4");
    new G4PVPlacement(nullptr, Uranium4Pos, Uranium4Log, "Uranium4", worldLog, false, 0);

    // Uranium5
    auto Uranium5Pos = G4ThreeVector(0., 0., 28.94 * cm);

    auto Uranium5Diameter = 0.819 * cm;
    auto Uranium5Height = 0.98 * cm;
    auto Uranium5Sol = new G4Tubs("Uranium5", 0, .5 * Uranium5Diameter, .5 * Uranium5Height, 0., 360. * deg);     
    auto Uranium5Log = new G4LogicalVolume(Uranium5Sol, matU5, "Uranium5");
    new G4PVPlacement(nullptr, Uranium5Pos, Uranium5Log, "Uranium5", worldLog, false, 0);

    // Uranium6
    auto Uranium6Pos = G4ThreeVector(0., 0., 58.94 * cm);

    auto Uranium6Diameter = 0.819 * cm;
    auto Uranium6Height = 0.98 * cm;
    auto Uranium6Sol = new G4Tubs("Uranium6", 0, .5 * Uranium6Diameter, .5 * Uranium6Height, 0., 360. * deg);     
    auto Uranium6Log = new G4LogicalVolume(Uranium6Sol, matU6, "Uranium6");
    new G4PVPlacement(nullptr, Uranium6Pos, Uranium6Log, "Uranium6", worldLog, false, 0);

    // Uranium7
    auto Uranium7Pos = G4ThreeVector(0., 0., 88.94 * cm);

    auto Uranium7Diameter = 0.819 * cm;
    auto Uranium7Height = 0.98 * cm;
    auto Uranium7Sol = new G4Tubs("Uranium7", 0, .5 * Uranium7Diameter, .5 * Uranium7Height, 0., 360. * deg);     
    auto Uranium7Log = new G4LogicalVolume(Uranium7Sol, matU7, "Uranium7");
    new G4PVPlacement(nullptr, Uranium7Pos, Uranium7Log, "Uranium7", worldLog, false, 0);

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
