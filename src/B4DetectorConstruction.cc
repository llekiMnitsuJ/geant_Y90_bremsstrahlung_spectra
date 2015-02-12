//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id$
// 
/// \file B4DetectorConstruction.cc
/// \brief Implementation of the B4DetectorConstruction class

#include "B4DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4GenericMessenger.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include <stdio.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::B4DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fMessenger(0),
   fSpherePV(0),
   fCheckOverlaps(true)
{
  // Define /B4/det commands using generic messenger class
  //this does nothing
  fMessenger 
    = new G4GenericMessenger(this, "/B4/det/", "Detector construction control");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4DetectorConstruction::~B4DetectorConstruction()
{
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::Construct()
{
  // Define materials 
  DefineMaterials();
  
  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4DetectorConstruction::DefineMaterials()
{ 
  
  G4NistManager* nistManager = G4NistManager::Instance();

  // Add TISSUECRISTY to NIST Manager
  G4double density = 1.04*g/cm3;
  G4Material* myMat = nistManager->BuildMaterialWithNewDensity(
		  "TISSUECRISTY", "G4_TISSUE_SOFT_ICRP", density);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B4DetectorConstruction::DefineVolumes()
{
  // Geometry parameters
  G4double sphereRadius = 15.*mm;
  G4double world_xyz = 1.2*sphereRadius;
  
  G4NistManager* nist = G4NistManager::Instance();
  this->fCheckOverlaps = true;
  G4Material* world_mat = nist->FindOrBuildMaterial("TISSUECRISTY");
  G4Material* sphere_mat = nist->FindOrBuildMaterial("TISSUECRISTY");
   
  //     
  // World
  //
  G4VSolid* worldS 
    = new G4Box("World",           // its name
                 world_xyz/2., world_xyz/2., world_xyz/2.); // its size
                         
  G4LogicalVolume* worldLV
    = new G4LogicalVolume(
                 worldS,           // its solid
                 world_mat,  // its material
                 "World");         // its name
                                   
  G4VPhysicalVolume* worldPV
    = new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 worldLV,          // its logical volume                         
                 "World",          // its name
                 0,                // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 this->fCheckOverlaps);  // checking overlaps

                         
  G4VSolid* sphereS = new G4Orb("sphere", sphereRadius);
  G4LogicalVolume* sphereLV
    = new G4LogicalVolume(
                 sphereS,     // its solid
                 sphere_mat,  // its material
                 "sphere");   // its name
                                   
  G4VPhysicalVolume* spherePV =
		  new G4PVPlacement(
                 0,                // no rotation
                 G4ThreeVector(),  // at (0,0,0)
                 sphereLV,          // its logical volume
                 "sphere",    // its name
                 worldLV,          // its mother  volume
                 false,            // no boolean operation
                 0,                // copy number
                 this->fCheckOverlaps);  // checking overlaps
  this->fSpherePV = spherePV;
  
  //
  // print parameters
  //
  G4cout << "\n------------------------------------------------------------"
         << "\n---> The sphere has radius: " << sphereRadius/mm << "mm"
         << "\n------------------------------------------------------------\n";
  
  //                                        
  // Visualization attributes
  //
  worldLV->SetVisAttributes (G4VisAttributes::Invisible);

  G4VisAttributes* sphereVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  sphereVisAtt->SetVisibility(true);
  sphereLV->SetVisAttributes(sphereVisAtt);

  //
  // Always return the physical World
  //
  return worldPV;
}

