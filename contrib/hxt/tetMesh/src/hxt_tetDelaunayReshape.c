#include "hxt_tetDelaunayReshape.h"
#include "hxt_tetFlag.h"
#include "predicates.h"
#include <stdint.h>

/* check if the cavity is star shaped
   This isn't usefull for pure Delaunay but when we constrain cavity with color,
   it is usefull */
static HXTStatus isStarShaped(TetLocal* local, HXTMesh* mesh, const uint32_t vta, uint64_t* blindFaceIndex)
{
  HXTVertex* vertices = (HXTVertex*) mesh->vertices.coord;
  double *vtaCoord = vertices[vta].coord;

  for (uint64_t i=0; i<local->ball.num; i++) {
    if(local->ball.array[i].node[2]!=HXT_GHOST_VERTEX){
      double* b = vertices[local->ball.array[i].node[0]].coord;
      double* c = vertices[local->ball.array[i].node[1]].coord;
      double* d = vertices[local->ball.array[i].node[2]].coord;
      if(orient3d(vtaCoord, b, c, d)>=0.0){
        *blindFaceIndex = i;
        return HXT_STATUS_INTERNAL;
      }
    }
  }
  return HXT_STATUS_OK;
}


static HXTStatus undeleteTetrahedron(TetLocal* local, HXTMesh* mesh, uint64_t tetToUndelete) {
  // the tetrahedra should not be deleted anymore
  for (uint64_t i=local->deleted.num; ; i--) {
    if(local->deleted.array[i-1]==tetToUndelete) {
      local->deleted.num--;
      local->deleted.array[i-1] = local->deleted.array[local->deleted.num];
      break;
    }
#ifdef DEBUG
    if(i==1)
      return HXT_ERROR_MSG(HXT_STATUS_ERROR, "could not find the tetrahedra in the deleted array");
#endif
  }
  unsetDeletedFlag(mesh, tetToUndelete);

  uint64_t bndFaces[4] = {HXT_NO_ADJACENT, HXT_NO_ADJACENT, HXT_NO_ADJACENT, HXT_NO_ADJACENT};
  int nbndFace = 0;

  // we should update the boundary (that's the difficult part...)
  // first remove all the boundary faces that come from the tetrahedron we just removed from the cavity
  for (uint64_t i=local->ball.num; nbndFace<4 && i>0; i--) {
    if(mesh->tetrahedra.neigh[local->ball.array[i-1].neigh]/4==tetToUndelete) {
      bndFaces[nbndFace++] = local->ball.array[i-1].neigh;
      local->ball.num--;
      local->ball.array[i-1] = local->ball.array[local->ball.num];
    }
  }

  // we must replace them by all the other faces of the tetrahedron we just removed
  const uint64_t* __restrict__ curNeigh = mesh->tetrahedra.neigh + tetToUndelete*4;
  const uint32_t* __restrict__ curNode = mesh->tetrahedra.node + tetToUndelete*4;

#ifdef DEBUG
  int nbndFace2 = (getDeletedFlag(mesh, curNeigh[0]/4)==0 || getFacetConstraint(mesh, tetToUndelete, 0)) +
                  (getDeletedFlag(mesh, curNeigh[1]/4)==0 || getFacetConstraint(mesh, tetToUndelete, 1)) +
                  (getDeletedFlag(mesh, curNeigh[2]/4)==0 || getFacetConstraint(mesh, tetToUndelete, 2)) +
                  (getDeletedFlag(mesh, curNeigh[3]/4)==0 || getFacetConstraint(mesh, tetToUndelete, 3));
  if(nbndFace!=nbndFace2)
    return HXT_ERROR_MSG(HXT_STATUS_ERROR, "found %d non-deleted tet adjacent to the tet we unremove but there should be %d %lu %lu %lu %lu", nbndFace, nbndFace2, bndFaces[0], bndFaces[1], bndFaces[2], bndFaces[3]);
#endif

  HXT_CHECK( askForBall(local, 3) );

  if(curNeigh[0]!=bndFaces[0] && curNeigh[0]!=bndFaces[1] && curNeigh[0]!=bndFaces[2] && curNeigh[0]!=bndFaces[3])
    bndPush(local, (getFacetConstraint(mesh, tetToUndelete, 0)   ) |
                   (getEdgeConstraint(mesh, tetToUndelete, 1)>>1) | // constraint on edge 1 (facet 0 2) goes on edge 0
                   (getEdgeConstraint(mesh, tetToUndelete, 0)<<1) | // constraint on edge 0 (facet 0 1) goes on edge 1
                   (getEdgeConstraint(mesh, tetToUndelete, 2)   ),  // constraint on edge 2 (facet 0 3) goes on edge 2
                   curNode[2], curNode[1], curNode[3], 4*tetToUndelete+0);

  if(curNeigh[1]!=bndFaces[0] && curNeigh[1]!=bndFaces[1] && curNeigh[1]!=bndFaces[2] && curNeigh[1]!=bndFaces[3])
    bndPush(local,  (getFacetConstraint(mesh, tetToUndelete, 1)>>1) |// constraint on facet 1 goes on facet 0
                    (getEdgeConstraint(mesh, tetToUndelete, 0)   ) | // constraint on edge 0 (facet 1 0) goes on edge 0
                    (getEdgeConstraint(mesh, tetToUndelete, 3)>>2) | // constraint on edge 3 (facet 1 2) goes on edge 1
                    (getEdgeConstraint(mesh, tetToUndelete, 4)>>2),  // constraint on edge 4 (facet 1 3) goes on edge 2
                    curNode[0], curNode[2], curNode[3], 4*tetToUndelete+1);

  if(curNeigh[2]!=bndFaces[0] && curNeigh[2]!=bndFaces[1] && curNeigh[2]!=bndFaces[2] && curNeigh[2]!=bndFaces[3])
    bndPush(local,  (getFacetConstraint(mesh, tetToUndelete, 2)>>2) |// constraint on facet 2 goes on facet 0
                    (getEdgeConstraint(mesh, tetToUndelete, 3)>>3) | // constraint on edge 3 (facet 2 1) goes on edge 0
                    (getEdgeConstraint(mesh, tetToUndelete, 1)   ) | // constraint on edge 1 (facet 2 0) goes on edge 1
                    (getEdgeConstraint(mesh, tetToUndelete, 5)>>3),  // constraint on edge 5 (facet 2 3) goes on edge 2
                     curNode[1], curNode[0], curNode[3], 4*tetToUndelete+2);

  if(curNeigh[3]!=bndFaces[0] && curNeigh[3]!=bndFaces[1] && curNeigh[3]!=bndFaces[2] && curNeigh[3]!=bndFaces[3])
    bndPush(local, (getFacetConstraint(mesh, tetToUndelete, 3)>>3) |// constraint on facet 3 goes on facet 0
                   (getEdgeConstraint(mesh, tetToUndelete, 2)>>2) | // constraint on edge 2 (facet 3 0) goes on edge 0
                   (getEdgeConstraint(mesh, tetToUndelete, 4)>>3) | // constraint on edge 4 (facet 3 1) goes on edge 1
                   (getEdgeConstraint(mesh, tetToUndelete, 5)>>3),  // constraint on edge 5 (facet 3 2) goes on edge 2
                   curNode[0], curNode[1], curNode[2], 4*tetToUndelete+3);

  return HXT_STATUS_OK;
}



HXTStatus respectEdgeConstraint(TetLocal* local, HXTMesh* mesh, const uint32_t vta, const uint32_t color, const uint64_t prevDeleted)
{
  // HXT_WARNING("a constrained edge was inside the cavity, recovering it");

  // all the tetrahedron have the same color 'color', we will use that color to flag them
  for (uint64_t i=prevDeleted; i<local->deleted.num; i++) {
    uint64_t delTet = local->deleted.array[i];
    mesh->tetrahedra.color[delTet] = 0;
  }

  for (uint64_t i=prevDeleted; i<local->deleted.num; i++) {
    uint64_t delTet = local->deleted.array[i];
    int exist = 1;
    for (int edge=0; exist && edge<6; edge++) {
      if(getEdgeConstraint(mesh, delTet, edge) && (mesh->tetrahedra.color[delTet] & (1U<<edge))==0) {
        unsigned in_facet;
        unsigned out_facet;

        getFacetsFromEdge(edge, &in_facet, &out_facet);

        int edgeIsSafe = 0;
        uint64_t curTet = delTet;

        // first turn
        do
        {
          uint32_t newV = mesh->tetrahedra.node[4*curTet + in_facet];

          // go into the neighbor through out_facet
          uint64_t neigh = mesh->tetrahedra.neigh[4*curTet + out_facet];
          curTet = neigh/4;
          in_facet = neigh%4;

          uint32_t* nodes = mesh->tetrahedra.node + 4*curTet;
          for (out_facet=0; out_facet<3; out_facet++)
            if(nodes[out_facet]==newV)
              break;

          if(getDeletedFlag(mesh, curTet)!=0) {
            // mark that the edge as been treate
            #ifdef DEBUG
              if((mesh->tetrahedra.color[curTet] & (1U<<getEdgeFromFacets(in_facet, out_facet)))!=0)
                return HXT_ERROR_MSG(HXT_STATUS_ERROR, "the flag says that the tet has already been processed for this edge...");
            #endif
            mesh->tetrahedra.color[curTet] |= (1U<<getEdgeFromFacets(in_facet, out_facet));
          }
          else {
            edgeIsSafe=1;
          }

        } while (curTet!=delTet);

        if(!edgeIsSafe) { // we must find a tetrahedron on the opposite side of vta and delete it.
          getFacetsFromEdge(edge, &in_facet, &out_facet);
          curTet = delTet;

          uint64_t tetContainingVta = local->deleted.array[prevDeleted];
          uint64_t tetToUndelete = HXT_NO_ADJACENT;
          double distMax = 0.0;
          double* vtaCoord = mesh->vertices.coord + 4*vta;

        #ifdef DEBUG
          double* a = mesh->vertices.coord + 4*mesh->tetrahedra.node[4*tetContainingVta];
          double* b = mesh->vertices.coord + 4*mesh->tetrahedra.node[4*tetContainingVta+1];
          double* c = mesh->vertices.coord + 4*mesh->tetrahedra.node[4*tetContainingVta+2];
          double* d = mesh->vertices.coord + 4*mesh->tetrahedra.node[4*tetContainingVta+3];

          if(orient3d(vtaCoord,b,c,d)>0.0 || orient3d(a,vtaCoord,c,d)>0.0 || orient3d(a,b,vtaCoord,d)>0.0 || orient3d(a,b,c,vtaCoord)>0.0) {
            return HXT_ERROR_MSG(HXT_STATUS_ERROR, "an edge part of a ghost tetrahedron is constrained");
          }
        #endif

          // second turn
          do
          {
            uint32_t newV = mesh->tetrahedra.node[4*curTet + in_facet];

            // go into the neighbor through out_facet
            uint64_t neigh = mesh->tetrahedra.neigh[4*curTet + out_facet];
            curTet = neigh/4;
            in_facet = neigh%4;

            uint32_t* nodes = mesh->tetrahedra.node + 4*curTet;
            for (out_facet=0; out_facet<3; out_facet++)
              if(nodes[out_facet]==newV)
                break;

            double* coord1 = mesh->vertices.coord + newV;
            double* coord2 = mesh->vertices.coord + nodes[in_facet];

            if(curTet!=tetContainingVta) {
              double dist = 0.0;
              for (int l=0; l<3; l++) {
                double meanCoord = (coord1[l]+coord2[l])*0.5;
                double diff = meanCoord-vtaCoord[l];
                dist += diff*diff;
              }

              if(dist>distMax) {
                dist = distMax;
                tetToUndelete = curTet;
              }
            }
          } while (curTet!=delTet);

          if(tetToUndelete==delTet)
            exist = 0;

          // printf("undeleting tetrahedron %lu\n", tetToUndelete);
          mesh->tetrahedra.color[tetToUndelete] = color;
          HXT_CHECK( undeleteTetrahedron(local, mesh, tetToUndelete) );
        }
      }
    }
  }

  for (uint64_t i=prevDeleted; i<local->deleted.num; i++) {
    uint64_t delTet = local->deleted.array[i];
    mesh->tetrahedra.color[delTet] = color;
  }

  return HXT_STATUS_OK;
}


// functions above should be replaced













#define BND_FACE_FLAG (UINT64_C(1)<<63)

// remove the tetrahedra adjacent to the face that does not see the point, progressively, until the cavity is star shaped...
HXTStatus reshapeCavityIfNeeded(TetLocal* local, HXTMesh* mesh, const uint32_t vta, uint64_t prevNumDeleted)
{
  uint64_t count = 0;

  // STEP 1: for each ball faces, we need the index of the tet in the deleted array, instead of the index of the tet in the mesh
  // for each deleted tet, we need the index of the 4 faces in the ball, or the index of the neighbor in the deleted array
  // if the facet is not a facet of the cavity. To differentiate both, BND_FACE_FLAG is set for indices of the ball.
  uint64_t numTet = local->deleted.num - prevNumDeleted;
  uint64_t* tets = &local->deleted.array[prevNumDeleted];
  uint64_t* faces;
  HXT_CHECK( hxtMalloc(&faces, sizeof(uint64_t) * 4 * numTet) );

  for(uint64_t i=0; i<4*numTet; i++) {
    faces[i] = 0;
  }

  // A priori, the order in which the delete tet appear and the order in which the faces appear should match (see @diggingACavity)
  uint64_t tetToFind = mesh->tetrahedra.neigh[local->ball.array[0].neigh];
  uint64_t curFace = 0;
  uint64_t curTet = 0;
  while(curTet<numTet) {
    if(tets[curTet] == tetToFind / 4) {
      uint64_t index = 4 * curTet + tetToFind % 4;
      local->ball.array[curFace].neigh = index;
      faces[index] = curFace;
      curFace++;

      if(curFace >= local->ball.num)
        break;

      tetToFind = mesh->tetrahedra.neigh[local->ball.array[curFace].neigh];
    }
    else {
      curTet++;
    }
  }

  if(curFace < local->ball.num) {
    return HXT_ERROR_MSG(HXT_STATUS_ERROR, "DEBUG: Faces did not appear in the same order as deleted tet");
  }

  // double *vtaCoord = &mesh->vertices.coord[4 * vta];

  // // STEP 2: for each face that does not see vta, delete the associated tet, and update the boundary of the cavity
  // for (uint64_t curFace=0; curFace<local->ball.num; curFace++) {
  //   if(local->ball.array[curFace].node[2]==HXT_GHOST_VERTEX){
  //     continue;
  //   }

  //   double* b = &mesh->vertices.coord[4 * local->ball.array[curFace].node[0]];
  //   double* c = &mesh->vertices.coord[4 * local->ball.array[curFace].node[1]];
  //   double* d = &mesh->vertices.coord[4 * local->ball.array[curFace].node[2]];
  //   if(orient3d(vtaCoord, b, c, d)<0.0){
  //     continue;
  //   }

  //   // 2.1 update the facets so that no facet points to the current tet... does not work with our structure. SHITTT !!
  //   // => we are forced to use an O(n^2) algo if we do not want to use a super large table

  //   // 2.2: undelete the tetrahedron
  //   uint64_t index = local->ball.array[curFace].neigh;
  //   uint64_t tetToUndelete = local->deleted.array[index / 4];
  //   unsigned facet = index % 4;
  //   unsetDeletedFlag(mesh, tetToUndelete);



  //   // second part: remove the faces of the tet that were on the boundary
  //   // do not forget to update curFace to point just before the next face to process
  //   uint64_t bndFaces[4] = {HXT_NO_ADJACENT, HXT_NO_ADJACENT, HXT_NO_ADJACENT, HXT_NO_ADJACENT};
  //   int nbndFace = 0;

  //   // the way that the boundary faces are contructed,
  //   // TODO: use a bidirectional structure to be able to find the faces of deleted tet.

  //   // face to delete: curface

  //   for (uint64_t i=local->ball.num; nbndFace<4 && i>0; i--) {
  //     if(mesh->tetrahedra.neigh[local->ball.array[i-1].neigh]/4==tetToUndelete) {
  //       bndFaces[nbndFace++] = local->ball.array[i-1].neigh;
  //       local->ball.num--;
  //       local->ball.array[i-1] = local->ball.array[local->ball.num];
  //     }
  //   }


  //   // third part: add new facets to the boundary

  //   count++;
  // }

  // if(count)
  //   printf("nbr of tet to undelete = %lu, nbr of deleted tet = %lu\n", count, local->deleted.num);

  // // STEP 3: compute all the flags at once ! ??


  // STEP 4: put back the right neighbor value inside the ball struct
  for(uint64_t i=0; i<local->ball.num; i++) {
    uint64_t index = local->ball.array[i].neigh;
    uint64_t interiorTet = tets[index / 4];
    unsigned facet = index % 4;
    local->ball.array[i].neigh = mesh->tetrahedra.neigh[4 * interiorTet + facet];
  }


  HXT_CHECK( hxtFree(&faces) );


  uint64_t blindFace = 0;

  // TODO: optimize this part of the algorithm.
  // 1: only the faces that were not yet tested for star-shapedness need to be tested
  // 2: only mark the tet as not deleted, and push it on a stack.
  //  => finding the tet. in local->deleted.array should be done with an optimized algo
  // 3: the face and flags should not be pushed directly if it is going to be removed... recursive strategy ??
  // 4 ??: maybe use the SPR in some cases
  while(isStarShaped(local, mesh, vta, &blindFace)==HXT_STATUS_INTERNAL)
  {
    HXT_CHECK( undeleteTetrahedron(local, mesh, mesh->tetrahedra.neigh[local->ball.array[blindFace].neigh]/4) );
  }

  return HXT_STATUS_OK;
}
