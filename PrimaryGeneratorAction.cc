#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomTools.hh"
#include "G4Gamma.hh"
#include "G4Neutron.hh"

#include "PrimaryGeneratorAction.hh"

// 생성자
PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction()
{
    fPrimary = new G4ParticleGun();
}

// 소멸자
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fPrimary;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
    fPrimary->SetParticleDefinition(G4Neutron::Definition());
    fPrimary->SetParticleEnergy(0.1*MeV);
    fPrimary->SetParticlePosition(G4ThreeVector(0., 0., 7.* cm));
    fPrimary->SetParticleMomentumDirection(G4RandomDirection());
    
    fPrimary->GeneratePrimaryVertex(anEvent);
}
