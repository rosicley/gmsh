// Gmsh - Copyright (C) 1997-2021 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// issues on https://gitlab.onelab.info/gmsh/gmsh/issues.

#include <string.h>
#include <stdlib.h>
#include "gmsh.h"

extern "C" {
  #include "gmshc.h"
}

GMSH_API void *gmshMalloc(size_t n)
{
  return malloc(n);
}

GMSH_API void gmshFree(void *p)
{
  if(p) free(p);
}

template<typename t>
void vector2ptr(const std::vector<t> &v, t **p, size_t *size)
{
  *p = (t*)gmshMalloc(sizeof(t) * v.size());
  for(size_t i = 0; i < v.size(); ++i){
    (*p)[i] = v[i];
  }
  *size = v.size();
}

void vectorpair2intptr(const gmsh::vectorpair &v, int **p, size_t *size)
{
  *p = (int*)gmshMalloc(sizeof(int) * v.size() * 2);
  for(size_t i = 0; i < v.size(); ++i){
    (*p)[i * 2 + 0] = v[i].first;
    (*p)[i * 2 + 1] = v[i].second;
  }
  *size = v.size() * 2;
}

void vectorstring2charptrptr(const std::vector<std::string> &v, char ***p, size_t *size)
{
  *p = (char**)gmshMalloc(sizeof(char*) * v.size());
  for(size_t i = 0; i < v.size(); ++i){
    (*p)[i] = (char*)gmshMalloc(sizeof(char) * (v[i].size() + 1));
    for(size_t j = 0; j < v[i].size(); j++) (*p)[i][j] = v[i][j];
    (*p)[i][v[i].size()] = '\0';
  }
  *size = v.size();
}

template<typename t>
void vectorvector2ptrptr(const std::vector<std::vector<t> > &v, t ***p, size_t **size, size_t *sizeSize)
{
  *p = (t**)gmshMalloc(sizeof(t*) * v.size());
  *size = (size_t*)gmshMalloc(sizeof(size_t) * v.size());
  for(size_t i = 0; i < v.size(); ++i)
    vector2ptr(v[i], &((*p)[i]), &((*size)[i]));
  *sizeSize = v.size();
}

void vectorvectorpair2intptrptr(const std::vector<gmsh::vectorpair > &v, int ***p, size_t **size, size_t *sizeSize)
{
  *p = (int**)gmshMalloc(sizeof(int*) * v.size());
  *size = (size_t*)gmshMalloc(sizeof(size_t) * v.size());
  for(size_t i = 0; i < v.size(); ++i)
    vectorpair2intptr(v[i], &(*p)[i], &((*size)[i]));
  *sizeSize = v.size();
}

GMSH_API void gmshInitialize(int argc, char ** argv, const int readConfigFiles, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::initialize(argc, argv, readConfigFiles);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFinalize(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::finalize();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOpen(const char * fileName, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::open(fileName);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshMerge(const char * fileName, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::merge(fileName);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshWrite(const char * fileName, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::write(fileName);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshClear(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::clear();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOptionSetNumber(const char * name, const double value, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::option::setNumber(name, value);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOptionGetNumber(const char * name, double * value, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::option::getNumber(name, *value);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOptionSetString(const char * name, const char * value, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::option::setString(name, value);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOptionGetString(const char * name, char ** value, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::string api_value_;
    gmsh::option::getString(name, api_value_);
    *value = strdup(api_value_.c_str());
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOptionSetColor(const char * name, const int r, const int g, const int b, const int a, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::option::setColor(name, r, g, b, a);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOptionGetColor(const char * name, int * r, int * g, int * b, int * a, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::option::getColor(name, *r, *g, *b, *a);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelAdd(const char * name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::add(name);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelRemove(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::remove();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelList(char *** names, size_t * names_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::string> api_names_;
    gmsh::model::list(api_names_);
    vectorstring2charptrptr(api_names_, names, names_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetCurrent(char ** name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::string api_name_;
    gmsh::model::getCurrent(api_name_);
    *name = strdup(api_name_.c_str());
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelSetCurrent(const char * name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::setCurrent(name);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetFileName(char ** fileName, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::string api_fileName_;
    gmsh::model::getFileName(api_fileName_);
    *fileName = strdup(api_fileName_.c_str());
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelSetFileName(const char * fileName, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::setFileName(fileName);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetEntities(int ** dimTags, size_t * dimTags_n, const int dim, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_;
    gmsh::model::getEntities(api_dimTags_, dim);
    vectorpair2intptr(api_dimTags_, dimTags, dimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelSetEntityName(const int dim, const int tag, const char * name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::setEntityName(dim, tag, name);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetEntityName(const int dim, const int tag, char ** name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::string api_name_;
    gmsh::model::getEntityName(dim, tag, api_name_);
    *name = strdup(api_name_.c_str());
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetPhysicalGroups(int ** dimTags, size_t * dimTags_n, const int dim, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_;
    gmsh::model::getPhysicalGroups(api_dimTags_, dim);
    vectorpair2intptr(api_dimTags_, dimTags, dimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetEntitiesForPhysicalGroup(const int dim, const int tag, int ** tags, size_t * tags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_tags_;
    gmsh::model::getEntitiesForPhysicalGroup(dim, tag, api_tags_);
    vector2ptr(api_tags_, tags, tags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetPhysicalGroupsForEntity(const int dim, const int tag, int ** physicalTags, size_t * physicalTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_physicalTags_;
    gmsh::model::getPhysicalGroupsForEntity(dim, tag, api_physicalTags_);
    vector2ptr(api_physicalTags_, physicalTags, physicalTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelAddPhysicalGroup(const int dim, int * tags, size_t tags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_tags_(tags, tags + tags_n);
    result_api_ = gmsh::model::addPhysicalGroup(dim, api_tags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelRemovePhysicalGroups(int * dimTags, size_t dimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::removePhysicalGroups(api_dimTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelSetPhysicalName(const int dim, const int tag, const char * name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::setPhysicalName(dim, tag, name);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelRemovePhysicalName(const char * name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::removePhysicalName(name);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetPhysicalName(const int dim, const int tag, char ** name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::string api_name_;
    gmsh::model::getPhysicalName(dim, tag, api_name_);
    *name = strdup(api_name_.c_str());
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetBoundary(int * dimTags, size_t dimTags_n, int ** outDimTags, size_t * outDimTags_n, const int combined, const int oriented, const int recursive, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    gmsh::model::getBoundary(api_dimTags_, api_outDimTags_, combined, oriented, recursive);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetAdjacencies(const int dim, const int tag, int ** upward, size_t * upward_n, int ** downward, size_t * downward_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_upward_;
    std::vector<int> api_downward_;
    gmsh::model::getAdjacencies(dim, tag, api_upward_, api_downward_);
    vector2ptr(api_upward_, upward, upward_n);
    vector2ptr(api_downward_, downward, downward_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetEntitiesInBoundingBox(const double xmin, const double ymin, const double zmin, const double xmax, const double ymax, const double zmax, int ** tags, size_t * tags_n, const int dim, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_tags_;
    gmsh::model::getEntitiesInBoundingBox(xmin, ymin, zmin, xmax, ymax, zmax, api_tags_, dim);
    vectorpair2intptr(api_tags_, tags, tags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetBoundingBox(const int dim, const int tag, double * xmin, double * ymin, double * zmin, double * xmax, double * ymax, double * zmax, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::getBoundingBox(dim, tag, *xmin, *ymin, *zmin, *xmax, *ymax, *zmax);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelGetDimension(int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::getDimension();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelAddDiscreteEntity(const int dim, const int tag, int * boundary, size_t boundary_n, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_boundary_(boundary, boundary + boundary_n);
    result_api_ = gmsh::model::addDiscreteEntity(dim, tag, api_boundary_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelRemoveEntities(int * dimTags, size_t dimTags_n, const int recursive, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::removeEntities(api_dimTags_, recursive);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelRemoveEntityName(const char * name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::removeEntityName(name);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetType(const int dim, const int tag, char ** entityType, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::string api_entityType_;
    gmsh::model::getType(dim, tag, api_entityType_);
    *entityType = strdup(api_entityType_.c_str());
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetParent(const int dim, const int tag, int * parentDim, int * parentTag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::getParent(dim, tag, *parentDim, *parentTag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetPartitions(const int dim, const int tag, int ** partitions, size_t * partitions_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_partitions_;
    gmsh::model::getPartitions(dim, tag, api_partitions_);
    vector2ptr(api_partitions_, partitions, partitions_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetValue(const int dim, const int tag, double * parametricCoord, size_t parametricCoord_n, double ** coord, size_t * coord_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_parametricCoord_(parametricCoord, parametricCoord + parametricCoord_n);
    std::vector<double> api_coord_;
    gmsh::model::getValue(dim, tag, api_parametricCoord_, api_coord_);
    vector2ptr(api_coord_, coord, coord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetDerivative(const int dim, const int tag, double * parametricCoord, size_t parametricCoord_n, double ** derivatives, size_t * derivatives_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_parametricCoord_(parametricCoord, parametricCoord + parametricCoord_n);
    std::vector<double> api_derivatives_;
    gmsh::model::getDerivative(dim, tag, api_parametricCoord_, api_derivatives_);
    vector2ptr(api_derivatives_, derivatives, derivatives_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetSecondDerivative(const int dim, const int tag, double * parametricCoord, size_t parametricCoord_n, double ** derivatives, size_t * derivatives_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_parametricCoord_(parametricCoord, parametricCoord + parametricCoord_n);
    std::vector<double> api_derivatives_;
    gmsh::model::getSecondDerivative(dim, tag, api_parametricCoord_, api_derivatives_);
    vector2ptr(api_derivatives_, derivatives, derivatives_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetCurvature(const int dim, const int tag, double * parametricCoord, size_t parametricCoord_n, double ** curvatures, size_t * curvatures_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_parametricCoord_(parametricCoord, parametricCoord + parametricCoord_n);
    std::vector<double> api_curvatures_;
    gmsh::model::getCurvature(dim, tag, api_parametricCoord_, api_curvatures_);
    vector2ptr(api_curvatures_, curvatures, curvatures_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetPrincipalCurvatures(const int tag, double * parametricCoord, size_t parametricCoord_n, double ** curvatureMax, size_t * curvatureMax_n, double ** curvatureMin, size_t * curvatureMin_n, double ** directionMax, size_t * directionMax_n, double ** directionMin, size_t * directionMin_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_parametricCoord_(parametricCoord, parametricCoord + parametricCoord_n);
    std::vector<double> api_curvatureMax_;
    std::vector<double> api_curvatureMin_;
    std::vector<double> api_directionMax_;
    std::vector<double> api_directionMin_;
    gmsh::model::getPrincipalCurvatures(tag, api_parametricCoord_, api_curvatureMax_, api_curvatureMin_, api_directionMax_, api_directionMin_);
    vector2ptr(api_curvatureMax_, curvatureMax, curvatureMax_n);
    vector2ptr(api_curvatureMin_, curvatureMin, curvatureMin_n);
    vector2ptr(api_directionMax_, directionMax, directionMax_n);
    vector2ptr(api_directionMin_, directionMin, directionMin_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetNormal(const int tag, double * parametricCoord, size_t parametricCoord_n, double ** normals, size_t * normals_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_parametricCoord_(parametricCoord, parametricCoord + parametricCoord_n);
    std::vector<double> api_normals_;
    gmsh::model::getNormal(tag, api_parametricCoord_, api_normals_);
    vector2ptr(api_normals_, normals, normals_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetParametrization(const int dim, const int tag, double * coord, size_t coord_n, double ** parametricCoord, size_t * parametricCoord_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_coord_(coord, coord + coord_n);
    std::vector<double> api_parametricCoord_;
    gmsh::model::getParametrization(dim, tag, api_coord_, api_parametricCoord_);
    vector2ptr(api_parametricCoord_, parametricCoord, parametricCoord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetParametrizationBounds(const int dim, const int tag, double ** min, size_t * min_n, double ** max, size_t * max_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_min_;
    std::vector<double> api_max_;
    gmsh::model::getParametrizationBounds(dim, tag, api_min_, api_max_);
    vector2ptr(api_min_, min, min_n);
    vector2ptr(api_max_, max, max_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelIsInside(const int dim, const int tag, double * parametricCoord, size_t parametricCoord_n, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_parametricCoord_(parametricCoord, parametricCoord + parametricCoord_n);
    result_api_ = gmsh::model::isInside(dim, tag, api_parametricCoord_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelGetClosestPoint(const int dim, const int tag, double * coord, size_t coord_n, double ** closestCoord, size_t * closestCoord_n, double ** parametricCoord, size_t * parametricCoord_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_coord_(coord, coord + coord_n);
    std::vector<double> api_closestCoord_;
    std::vector<double> api_parametricCoord_;
    gmsh::model::getClosestPoint(dim, tag, api_coord_, api_closestCoord_, api_parametricCoord_);
    vector2ptr(api_closestCoord_, closestCoord, closestCoord_n);
    vector2ptr(api_parametricCoord_, parametricCoord, parametricCoord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelReparametrizeOnSurface(const int dim, const int tag, double * parametricCoord, size_t parametricCoord_n, const int surfaceTag, double ** surfaceParametricCoord, size_t * surfaceParametricCoord_n, const int which, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_parametricCoord_(parametricCoord, parametricCoord + parametricCoord_n);
    std::vector<double> api_surfaceParametricCoord_;
    gmsh::model::reparametrizeOnSurface(dim, tag, api_parametricCoord_, surfaceTag, api_surfaceParametricCoord_, which);
    vector2ptr(api_surfaceParametricCoord_, surfaceParametricCoord, surfaceParametricCoord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelSetVisibility(int * dimTags, size_t dimTags_n, const int value, const int recursive, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::setVisibility(api_dimTags_, value, recursive);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetVisibility(const int dim, const int tag, int * value, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::getVisibility(dim, tag, *value);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelSetVisibilityPerWindow(const int value, const int windowIndex, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::setVisibilityPerWindow(value, windowIndex);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelSetColor(int * dimTags, size_t dimTags_n, const int r, const int g, const int b, const int a, const int recursive, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::setColor(api_dimTags_, r, g, b, a, recursive);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGetColor(const int dim, const int tag, int * r, int * g, int * b, int * a, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::getColor(dim, tag, *r, *g, *b, *a);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelSetCoordinates(const int tag, const double x, const double y, const double z, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::setCoordinates(tag, x, y, z);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGenerate(const int dim, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::generate(dim);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshPartition(const int numPart, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::partition(numPart);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshUnpartition(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::unpartition();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshOptimize(const char * method, const int force, const int niter, int * dimTags, size_t dimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::mesh::optimize(method, force, niter, api_dimTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshRecombine(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::recombine();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshRefine(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::refine();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetOrder(const int order, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::setOrder(order);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetLastEntityError(int ** dimTags, size_t * dimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_;
    gmsh::model::mesh::getLastEntityError(api_dimTags_);
    vectorpair2intptr(api_dimTags_, dimTags, dimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetLastNodeError(size_t ** nodeTags, size_t * nodeTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_;
    gmsh::model::mesh::getLastNodeError(api_nodeTags_);
    vector2ptr(api_nodeTags_, nodeTags, nodeTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshClear(int * dimTags, size_t dimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::mesh::clear(api_dimTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshReverse(int * dimTags, size_t dimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::mesh::reverse(api_dimTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetNodes(size_t ** nodeTags, size_t * nodeTags_n, double ** coord, size_t * coord_n, double ** parametricCoord, size_t * parametricCoord_n, const int dim, const int tag, const int includeBoundary, const int returnParametricCoord, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_;
    std::vector<double> api_coord_;
    std::vector<double> api_parametricCoord_;
    gmsh::model::mesh::getNodes(api_nodeTags_, api_coord_, api_parametricCoord_, dim, tag, includeBoundary, returnParametricCoord);
    vector2ptr(api_nodeTags_, nodeTags, nodeTags_n);
    vector2ptr(api_coord_, coord, coord_n);
    vector2ptr(api_parametricCoord_, parametricCoord, parametricCoord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetNodesByElementType(const int elementType, size_t ** nodeTags, size_t * nodeTags_n, double ** coord, size_t * coord_n, double ** parametricCoord, size_t * parametricCoord_n, const int tag, const int returnParametricCoord, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_;
    std::vector<double> api_coord_;
    std::vector<double> api_parametricCoord_;
    gmsh::model::mesh::getNodesByElementType(elementType, api_nodeTags_, api_coord_, api_parametricCoord_, tag, returnParametricCoord);
    vector2ptr(api_nodeTags_, nodeTags, nodeTags_n);
    vector2ptr(api_coord_, coord, coord_n);
    vector2ptr(api_parametricCoord_, parametricCoord, parametricCoord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetNode(const size_t nodeTag, double ** coord, size_t * coord_n, double ** parametricCoord, size_t * parametricCoord_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_coord_;
    std::vector<double> api_parametricCoord_;
    gmsh::model::mesh::getNode(nodeTag, api_coord_, api_parametricCoord_);
    vector2ptr(api_coord_, coord, coord_n);
    vector2ptr(api_parametricCoord_, parametricCoord, parametricCoord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetNode(const size_t nodeTag, double * coord, size_t coord_n, double * parametricCoord, size_t parametricCoord_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_coord_(coord, coord + coord_n);
    std::vector<double> api_parametricCoord_(parametricCoord, parametricCoord + parametricCoord_n);
    gmsh::model::mesh::setNode(nodeTag, api_coord_, api_parametricCoord_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshRebuildNodeCache(const int onlyIfNecessary, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::rebuildNodeCache(onlyIfNecessary);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshRebuildElementCache(const int onlyIfNecessary, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::rebuildElementCache(onlyIfNecessary);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetNodesForPhysicalGroup(const int dim, const int tag, size_t ** nodeTags, size_t * nodeTags_n, double ** coord, size_t * coord_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_;
    std::vector<double> api_coord_;
    gmsh::model::mesh::getNodesForPhysicalGroup(dim, tag, api_nodeTags_, api_coord_);
    vector2ptr(api_nodeTags_, nodeTags, nodeTags_n);
    vector2ptr(api_coord_, coord, coord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshAddNodes(const int dim, const int tag, size_t * nodeTags, size_t nodeTags_n, double * coord, size_t coord_n, double * parametricCoord, size_t parametricCoord_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_(nodeTags, nodeTags + nodeTags_n);
    std::vector<double> api_coord_(coord, coord + coord_n);
    std::vector<double> api_parametricCoord_(parametricCoord, parametricCoord + parametricCoord_n);
    gmsh::model::mesh::addNodes(dim, tag, api_nodeTags_, api_coord_, api_parametricCoord_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshReclassifyNodes(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::reclassifyNodes();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshRelocateNodes(const int dim, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::relocateNodes(dim, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetElements(int ** elementTypes, size_t * elementTypes_n, size_t *** elementTags, size_t ** elementTags_n, size_t *elementTags_nn, size_t *** nodeTags, size_t ** nodeTags_n, size_t *nodeTags_nn, const int dim, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_elementTypes_;
    std::vector<std::vector<std::size_t> > api_elementTags_;
    std::vector<std::vector<std::size_t> > api_nodeTags_;
    gmsh::model::mesh::getElements(api_elementTypes_, api_elementTags_, api_nodeTags_, dim, tag);
    vector2ptr(api_elementTypes_, elementTypes, elementTypes_n);
    vectorvector2ptrptr(api_elementTags_, elementTags, elementTags_n, elementTags_nn);
    vectorvector2ptrptr(api_nodeTags_, nodeTags, nodeTags_n, nodeTags_nn);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetElement(const size_t elementTag, int * elementType, size_t ** nodeTags, size_t * nodeTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_;
    gmsh::model::mesh::getElement(elementTag, *elementType, api_nodeTags_);
    vector2ptr(api_nodeTags_, nodeTags, nodeTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetElementByCoordinates(const double x, const double y, const double z, size_t * elementTag, int * elementType, size_t ** nodeTags, size_t * nodeTags_n, double * u, double * v, double * w, const int dim, const int strict, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_;
    gmsh::model::mesh::getElementByCoordinates(x, y, z, *elementTag, *elementType, api_nodeTags_, *u, *v, *w, dim, strict);
    vector2ptr(api_nodeTags_, nodeTags, nodeTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetElementsByCoordinates(const double x, const double y, const double z, size_t ** elementTags, size_t * elementTags_n, const int dim, const int strict, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_elementTags_;
    gmsh::model::mesh::getElementsByCoordinates(x, y, z, api_elementTags_, dim, strict);
    vector2ptr(api_elementTags_, elementTags, elementTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetLocalCoordinatesInElement(const size_t elementTag, const double x, const double y, const double z, double * u, double * v, double * w, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::getLocalCoordinatesInElement(elementTag, x, y, z, *u, *v, *w);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetElementTypes(int ** elementTypes, size_t * elementTypes_n, const int dim, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_elementTypes_;
    gmsh::model::mesh::getElementTypes(api_elementTypes_, dim, tag);
    vector2ptr(api_elementTypes_, elementTypes, elementTypes_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelMeshGetElementType(const char * familyName, const int order, const int serendip, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::mesh::getElementType(familyName, order, serendip);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelMeshGetElementProperties(const int elementType, char ** elementName, int * dim, int * order, int * numNodes, double ** localNodeCoord, size_t * localNodeCoord_n, int * numPrimaryNodes, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::string api_elementName_;
    std::vector<double> api_localNodeCoord_;
    gmsh::model::mesh::getElementProperties(elementType, api_elementName_, *dim, *order, *numNodes, api_localNodeCoord_, *numPrimaryNodes);
    *elementName = strdup(api_elementName_.c_str());
    vector2ptr(api_localNodeCoord_, localNodeCoord, localNodeCoord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetElementsByType(const int elementType, size_t ** elementTags, size_t * elementTags_n, size_t ** nodeTags, size_t * nodeTags_n, const int tag, const size_t task, const size_t numTasks, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_elementTags_;
    std::vector<std::size_t> api_nodeTags_;
    gmsh::model::mesh::getElementsByType(elementType, api_elementTags_, api_nodeTags_, tag, task, numTasks);
    vector2ptr(api_elementTags_, elementTags, elementTags_n);
    vector2ptr(api_nodeTags_, nodeTags, nodeTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshPreallocateElementsByType(const int elementType, const int elementTag, const int nodeTag, size_t ** elementTags, size_t * elementTags_n, size_t ** nodeTags, size_t * nodeTags_n, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_elementTags_;
    std::vector<std::size_t> api_nodeTags_;
    gmsh::model::mesh::preallocateElementsByType(elementType, elementTag, nodeTag, api_elementTags_, api_nodeTags_, tag);
    vector2ptr(api_elementTags_, elementTags, elementTags_n);
    vector2ptr(api_nodeTags_, nodeTags, nodeTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshAddElements(const int dim, const int tag, int * elementTypes, size_t elementTypes_n, const size_t ** elementTags, const size_t * elementTags_n, size_t elementTags_nn, const size_t ** nodeTags, const size_t * nodeTags_n, size_t nodeTags_nn, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_elementTypes_(elementTypes, elementTypes + elementTypes_n);
    std::vector<std::vector<std::size_t> > api_elementTags_(elementTags_nn);
    for(size_t i = 0; i < elementTags_nn; ++i)
      api_elementTags_[i] = std::vector<std::size_t>(elementTags[i], elementTags[i] + elementTags_n[i]);
    std::vector<std::vector<std::size_t> > api_nodeTags_(nodeTags_nn);
    for(size_t i = 0; i < nodeTags_nn; ++i)
      api_nodeTags_[i] = std::vector<std::size_t>(nodeTags[i], nodeTags[i] + nodeTags_n[i]);
    gmsh::model::mesh::addElements(dim, tag, api_elementTypes_, api_elementTags_, api_nodeTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshAddElementsByType(const int tag, const int elementType, size_t * elementTags, size_t elementTags_n, size_t * nodeTags, size_t nodeTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_elementTags_(elementTags, elementTags + elementTags_n);
    std::vector<std::size_t> api_nodeTags_(nodeTags, nodeTags + nodeTags_n);
    gmsh::model::mesh::addElementsByType(tag, elementType, api_elementTags_, api_nodeTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetIntegrationPoints(const int elementType, const char * integrationType, double ** localCoord, size_t * localCoord_n, double ** weights, size_t * weights_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_localCoord_;
    std::vector<double> api_weights_;
    gmsh::model::mesh::getIntegrationPoints(elementType, integrationType, api_localCoord_, api_weights_);
    vector2ptr(api_localCoord_, localCoord, localCoord_n);
    vector2ptr(api_weights_, weights, weights_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetJacobians(const int elementType, double * localCoord, size_t localCoord_n, double ** jacobians, size_t * jacobians_n, double ** determinants, size_t * determinants_n, double ** coord, size_t * coord_n, const int tag, const size_t task, const size_t numTasks, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_localCoord_(localCoord, localCoord + localCoord_n);
    std::vector<double> api_jacobians_;
    std::vector<double> api_determinants_;
    std::vector<double> api_coord_;
    gmsh::model::mesh::getJacobians(elementType, api_localCoord_, api_jacobians_, api_determinants_, api_coord_, tag, task, numTasks);
    vector2ptr(api_jacobians_, jacobians, jacobians_n);
    vector2ptr(api_determinants_, determinants, determinants_n);
    vector2ptr(api_coord_, coord, coord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshPreallocateJacobians(const int elementType, const int numEvaluationPoints, const int allocateJacobians, const int allocateDeterminants, const int allocateCoord, double ** jacobians, size_t * jacobians_n, double ** determinants, size_t * determinants_n, double ** coord, size_t * coord_n, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_jacobians_;
    std::vector<double> api_determinants_;
    std::vector<double> api_coord_;
    gmsh::model::mesh::preallocateJacobians(elementType, numEvaluationPoints, allocateJacobians, allocateDeterminants, allocateCoord, api_jacobians_, api_determinants_, api_coord_, tag);
    vector2ptr(api_jacobians_, jacobians, jacobians_n);
    vector2ptr(api_determinants_, determinants, determinants_n);
    vector2ptr(api_coord_, coord, coord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetJacobian(const size_t elementTag, double * localCoord, size_t localCoord_n, double ** jacobians, size_t * jacobians_n, double ** determinants, size_t * determinants_n, double ** coord, size_t * coord_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_localCoord_(localCoord, localCoord + localCoord_n);
    std::vector<double> api_jacobians_;
    std::vector<double> api_determinants_;
    std::vector<double> api_coord_;
    gmsh::model::mesh::getJacobian(elementTag, api_localCoord_, api_jacobians_, api_determinants_, api_coord_);
    vector2ptr(api_jacobians_, jacobians, jacobians_n);
    vector2ptr(api_determinants_, determinants, determinants_n);
    vector2ptr(api_coord_, coord, coord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetBasisFunctions(const int elementType, double * localCoord, size_t localCoord_n, const char * functionSpaceType, int * numComponents, double ** basisFunctions, size_t * basisFunctions_n, int * numOrientations, int * wantedOrientations, size_t wantedOrientations_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_localCoord_(localCoord, localCoord + localCoord_n);
    std::vector<double> api_basisFunctions_;
    std::vector<int> api_wantedOrientations_(wantedOrientations, wantedOrientations + wantedOrientations_n);
    gmsh::model::mesh::getBasisFunctions(elementType, api_localCoord_, functionSpaceType, *numComponents, api_basisFunctions_, *numOrientations, api_wantedOrientations_);
    vector2ptr(api_basisFunctions_, basisFunctions, basisFunctions_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetBasisFunctionsOrientationForElements(const int elementType, const char * functionSpaceType, int ** basisFunctionsOrientation, size_t * basisFunctionsOrientation_n, const int tag, const size_t task, const size_t numTasks, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_basisFunctionsOrientation_;
    gmsh::model::mesh::getBasisFunctionsOrientationForElements(elementType, functionSpaceType, api_basisFunctionsOrientation_, tag, task, numTasks);
    vector2ptr(api_basisFunctionsOrientation_, basisFunctionsOrientation, basisFunctionsOrientation_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetBasisFunctionsOrientationForElement(const size_t elementTag, const char * functionSpaceType, int * basisFunctionsOrientation, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::getBasisFunctionsOrientationForElement(elementTag, functionSpaceType, *basisFunctionsOrientation);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelMeshGetNumberOfOrientations(const int elementType, const char * functionSpaceType, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::mesh::getNumberOfOrientations(elementType, functionSpaceType);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelMeshPreallocateBasisFunctionsOrientationForElements(const int elementType, int ** basisFunctionsOrientation, size_t * basisFunctionsOrientation_n, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_basisFunctionsOrientation_;
    gmsh::model::mesh::preallocateBasisFunctionsOrientationForElements(elementType, api_basisFunctionsOrientation_, tag);
    vector2ptr(api_basisFunctionsOrientation_, basisFunctionsOrientation, basisFunctionsOrientation_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetEdges(size_t * nodeTags, size_t nodeTags_n, size_t ** edgeTags, size_t * edgeTags_n, int ** edgeOrientations, size_t * edgeOrientations_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_(nodeTags, nodeTags + nodeTags_n);
    std::vector<std::size_t> api_edgeTags_;
    std::vector<int> api_edgeOrientations_;
    gmsh::model::mesh::getEdges(api_nodeTags_, api_edgeTags_, api_edgeOrientations_);
    vector2ptr(api_edgeTags_, edgeTags, edgeTags_n);
    vector2ptr(api_edgeOrientations_, edgeOrientations, edgeOrientations_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetFaces(const int faceType, size_t * nodeTags, size_t nodeTags_n, size_t ** faceTags, size_t * faceTags_n, int ** faceOrientations, size_t * faceOrientations_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_(nodeTags, nodeTags + nodeTags_n);
    std::vector<std::size_t> api_faceTags_;
    std::vector<int> api_faceOrientations_;
    gmsh::model::mesh::getFaces(faceType, api_nodeTags_, api_faceTags_, api_faceOrientations_);
    vector2ptr(api_faceTags_, faceTags, faceTags_n);
    vector2ptr(api_faceOrientations_, faceOrientations, faceOrientations_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshCreateEdges(int * dimTags, size_t dimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::mesh::createEdges(api_dimTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshCreateFaces(int * dimTags, size_t dimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::mesh::createFaces(api_dimTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetLocalMultipliersForHcurl0(const int elementType, int ** localMultipliers, size_t * localMultipliers_n, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_localMultipliers_;
    gmsh::model::mesh::getLocalMultipliersForHcurl0(elementType, api_localMultipliers_, tag);
    vector2ptr(api_localMultipliers_, localMultipliers, localMultipliers_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetKeysForElements(const int elementType, const char * functionSpaceType, int ** keys, size_t * keys_n, double ** coord, size_t * coord_n, const int tag, const int returnCoord, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_keys_;
    std::vector<double> api_coord_;
    gmsh::model::mesh::getKeysForElements(elementType, functionSpaceType, api_keys_, api_coord_, tag, returnCoord);
    vectorpair2intptr(api_keys_, keys, keys_n);
    vector2ptr(api_coord_, coord, coord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetKeysForElement(const size_t elementTag, const char * functionSpaceType, int ** keys, size_t * keys_n, double ** coord, size_t * coord_n, const int returnCoord, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_keys_;
    std::vector<double> api_coord_;
    gmsh::model::mesh::getKeysForElement(elementTag, functionSpaceType, api_keys_, api_coord_, returnCoord);
    vectorpair2intptr(api_keys_, keys, keys_n);
    vector2ptr(api_coord_, coord, coord_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelMeshGetNumberOfKeysForElements(const int elementType, const char * functionSpaceType, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::mesh::getNumberOfKeysForElements(elementType, functionSpaceType);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelMeshGetInformationForElements(int * keys, size_t keys_n, const int elementType, const char * functionSpaceType, int ** infoKeys, size_t * infoKeys_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_keys_(keys_n/2);
    for(size_t i = 0; i < keys_n/2; ++i){
      api_keys_[i].first = keys[i * 2 + 0];
      api_keys_[i].second = keys[i * 2 + 1];
    }
    gmsh::vectorpair api_infoKeys_;
    gmsh::model::mesh::getInformationForElements(api_keys_, elementType, functionSpaceType, api_infoKeys_);
    vectorpair2intptr(api_infoKeys_, infoKeys, infoKeys_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetBarycenters(const int elementType, const int tag, const int fast, const int primary, double ** barycenters, size_t * barycenters_n, const size_t task, const size_t numTasks, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_barycenters_;
    gmsh::model::mesh::getBarycenters(elementType, tag, fast, primary, api_barycenters_, task, numTasks);
    vector2ptr(api_barycenters_, barycenters, barycenters_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshPreallocateBarycenters(const int elementType, double ** barycenters, size_t * barycenters_n, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_barycenters_;
    gmsh::model::mesh::preallocateBarycenters(elementType, api_barycenters_, tag);
    vector2ptr(api_barycenters_, barycenters, barycenters_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetElementEdgeNodes(const int elementType, size_t ** nodeTags, size_t * nodeTags_n, const int tag, const int primary, const size_t task, const size_t numTasks, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_;
    gmsh::model::mesh::getElementEdgeNodes(elementType, api_nodeTags_, tag, primary, task, numTasks);
    vector2ptr(api_nodeTags_, nodeTags, nodeTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetElementFaceNodes(const int elementType, const int faceType, size_t ** nodeTags, size_t * nodeTags_n, const int tag, const int primary, const size_t task, const size_t numTasks, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_;
    gmsh::model::mesh::getElementFaceNodes(elementType, faceType, api_nodeTags_, tag, primary, task, numTasks);
    vector2ptr(api_nodeTags_, nodeTags, nodeTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetGhostElements(const int dim, const int tag, size_t ** elementTags, size_t * elementTags_n, int ** partitions, size_t * partitions_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_elementTags_;
    std::vector<int> api_partitions_;
    gmsh::model::mesh::getGhostElements(dim, tag, api_elementTags_, api_partitions_);
    vector2ptr(api_elementTags_, elementTags, elementTags_n);
    vector2ptr(api_partitions_, partitions, partitions_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetSize(int * dimTags, size_t dimTags_n, const double size, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::mesh::setSize(api_dimTags_, size);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetSizes(int * dimTags, size_t dimTags_n, double ** sizes, size_t * sizes_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    std::vector<double> api_sizes_;
    gmsh::model::mesh::getSizes(api_dimTags_, api_sizes_);
    vector2ptr(api_sizes_, sizes, sizes_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetSizeAtParametricPoints(const int dim, const int tag, double * parametricCoord, size_t parametricCoord_n, double * sizes, size_t sizes_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_parametricCoord_(parametricCoord, parametricCoord + parametricCoord_n);
    std::vector<double> api_sizes_(sizes, sizes + sizes_n);
    gmsh::model::mesh::setSizeAtParametricPoints(dim, tag, api_parametricCoord_, api_sizes_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetSizeCallback(double (*callback)(int dim, int tag, double x, double y, double z, void * data), void * callback_data, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::setSizeCallback(std::bind(callback, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, callback_data));
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshRemoveSizeCallback(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::removeSizeCallback();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetTransfiniteCurve(const int tag, const int numNodes, const char * meshType, const double coef, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::setTransfiniteCurve(tag, numNodes, meshType, coef);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetTransfiniteSurface(const int tag, const char * arrangement, int * cornerTags, size_t cornerTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_cornerTags_(cornerTags, cornerTags + cornerTags_n);
    gmsh::model::mesh::setTransfiniteSurface(tag, arrangement, api_cornerTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetTransfiniteVolume(const int tag, int * cornerTags, size_t cornerTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_cornerTags_(cornerTags, cornerTags + cornerTags_n);
    gmsh::model::mesh::setTransfiniteVolume(tag, api_cornerTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetTransfiniteAutomatic(int * dimTags, size_t dimTags_n, const double cornerAngle, const int recombine, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::mesh::setTransfiniteAutomatic(api_dimTags_, cornerAngle, recombine);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetRecombine(const int dim, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::setRecombine(dim, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetSmoothing(const int dim, const int tag, const int val, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::setSmoothing(dim, tag, val);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetReverse(const int dim, const int tag, const int val, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::setReverse(dim, tag, val);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetAlgorithm(const int dim, const int tag, const int val, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::setAlgorithm(dim, tag, val);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetSizeFromBoundary(const int dim, const int tag, const int val, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::setSizeFromBoundary(dim, tag, val);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetCompound(const int dim, int * tags, size_t tags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_tags_(tags, tags + tags_n);
    gmsh::model::mesh::setCompound(dim, api_tags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetOutwardOrientation(const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::setOutwardOrientation(tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshRemoveConstraints(int * dimTags, size_t dimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::mesh::removeConstraints(api_dimTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshEmbed(const int dim, int * tags, size_t tags_n, const int inDim, const int inTag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_tags_(tags, tags + tags_n);
    gmsh::model::mesh::embed(dim, api_tags_, inDim, inTag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshRemoveEmbedded(int * dimTags, size_t dimTags_n, const int dim, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::mesh::removeEmbedded(api_dimTags_, dim);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetEmbedded(const int dim, const int tag, int ** dimTags, size_t * dimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_;
    gmsh::model::mesh::getEmbedded(dim, tag, api_dimTags_);
    vectorpair2intptr(api_dimTags_, dimTags, dimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshReorderElements(const int elementType, const int tag, size_t * ordering, size_t ordering_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_ordering_(ordering, ordering + ordering_n);
    gmsh::model::mesh::reorderElements(elementType, tag, api_ordering_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshRenumberNodes(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::renumberNodes();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshRenumberElements(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::renumberElements();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSetPeriodic(const int dim, int * tags, size_t tags_n, int * tagsMaster, size_t tagsMaster_n, double * affineTransform, size_t affineTransform_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_tags_(tags, tags + tags_n);
    std::vector<int> api_tagsMaster_(tagsMaster, tagsMaster + tagsMaster_n);
    std::vector<double> api_affineTransform_(affineTransform, affineTransform + affineTransform_n);
    gmsh::model::mesh::setPeriodic(dim, api_tags_, api_tagsMaster_, api_affineTransform_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshGetPeriodicNodes(const int dim, const int tag, int * tagMaster, size_t ** nodeTags, size_t * nodeTags_n, size_t ** nodeTagsMaster, size_t * nodeTagsMaster_n, double ** affineTransform, size_t * affineTransform_n, const int includeHighOrderNodes, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_nodeTags_;
    std::vector<std::size_t> api_nodeTagsMaster_;
    std::vector<double> api_affineTransform_;
    gmsh::model::mesh::getPeriodicNodes(dim, tag, *tagMaster, api_nodeTags_, api_nodeTagsMaster_, api_affineTransform_, includeHighOrderNodes);
    vector2ptr(api_nodeTags_, nodeTags, nodeTags_n);
    vector2ptr(api_nodeTagsMaster_, nodeTagsMaster, nodeTagsMaster_n);
    vector2ptr(api_affineTransform_, affineTransform, affineTransform_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshRemoveDuplicateNodes(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::removeDuplicateNodes();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshSplitQuadrangles(const double quality, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::splitQuadrangles(quality, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshClassifySurfaces(const double angle, const int boundary, const int forReparametrization, const double curveAngle, const int exportDiscrete, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::classifySurfaces(angle, boundary, forReparametrization, curveAngle, exportDiscrete);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshCreateGeometry(int * dimTags, size_t dimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::mesh::createGeometry(api_dimTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshCreateTopology(const int makeSimplyConnected, const int exportDiscrete, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::createTopology(makeSimplyConnected, exportDiscrete);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshComputeHomology(int * domainTags, size_t domainTags_n, int * subdomainTags, size_t subdomainTags_n, int * dims, size_t dims_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_domainTags_(domainTags, domainTags + domainTags_n);
    std::vector<int> api_subdomainTags_(subdomainTags, subdomainTags + subdomainTags_n);
    std::vector<int> api_dims_(dims, dims + dims_n);
    gmsh::model::mesh::computeHomology(api_domainTags_, api_subdomainTags_, api_dims_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshComputeCohomology(int * domainTags, size_t domainTags_n, int * subdomainTags, size_t subdomainTags_n, int * dims, size_t dims_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_domainTags_(domainTags, domainTags + domainTags_n);
    std::vector<int> api_subdomainTags_(subdomainTags, subdomainTags + subdomainTags_n);
    std::vector<int> api_dims_(dims, dims + dims_n);
    gmsh::model::mesh::computeCohomology(api_domainTags_, api_subdomainTags_, api_dims_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshComputeCrossField(int ** viewTags, size_t * viewTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_viewTags_;
    gmsh::model::mesh::computeCrossField(api_viewTags_);
    vector2ptr(api_viewTags_, viewTags, viewTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshTriangulate(double * coord, size_t coord_n, size_t ** tri, size_t * tri_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_coord_(coord, coord + coord_n);
    std::vector<std::size_t> api_tri_;
    gmsh::model::mesh::triangulate(api_coord_, api_tri_);
    vector2ptr(api_tri_, tri, tri_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshTetrahedralize(double * coord, size_t coord_n, size_t ** tetra, size_t * tetra_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_coord_(coord, coord + coord_n);
    std::vector<std::size_t> api_tetra_;
    gmsh::model::mesh::tetrahedralize(api_coord_, api_tetra_);
    vector2ptr(api_tetra_, tetra, tetra_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelMeshFieldAdd(const char * fieldType, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::mesh::field::add(fieldType, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelMeshFieldRemove(const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::field::remove(tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshFieldSetNumber(const int tag, const char * option, const double value, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::field::setNumber(tag, option, value);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshFieldSetString(const int tag, const char * option, const char * value, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::field::setString(tag, option, value);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshFieldSetNumbers(const int tag, const char * option, double * value, size_t value_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_value_(value, value + value_n);
    gmsh::model::mesh::field::setNumbers(tag, option, api_value_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshFieldSetAsBackgroundMesh(const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::field::setAsBackgroundMesh(tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelMeshFieldSetAsBoundaryLayer(const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::mesh::field::setAsBoundaryLayer(tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelGeoAddPoint(const double x, const double y, const double z, const double meshSize, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::geo::addPoint(x, y, z, meshSize, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddLine(const int startTag, const int endTag, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::geo::addLine(startTag, endTag, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddCircleArc(const int startTag, const int centerTag, const int endTag, const int tag, const double nx, const double ny, const double nz, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::geo::addCircleArc(startTag, centerTag, endTag, tag, nx, ny, nz);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddEllipseArc(const int startTag, const int centerTag, const int majorTag, const int endTag, const int tag, const double nx, const double ny, const double nz, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::geo::addEllipseArc(startTag, centerTag, majorTag, endTag, tag, nx, ny, nz);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddSpline(int * pointTags, size_t pointTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_pointTags_(pointTags, pointTags + pointTags_n);
    result_api_ = gmsh::model::geo::addSpline(api_pointTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddBSpline(int * pointTags, size_t pointTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_pointTags_(pointTags, pointTags + pointTags_n);
    result_api_ = gmsh::model::geo::addBSpline(api_pointTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddBezier(int * pointTags, size_t pointTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_pointTags_(pointTags, pointTags + pointTags_n);
    result_api_ = gmsh::model::geo::addBezier(api_pointTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddPolyline(int * pointTags, size_t pointTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_pointTags_(pointTags, pointTags + pointTags_n);
    result_api_ = gmsh::model::geo::addPolyline(api_pointTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddCompoundSpline(int * curveTags, size_t curveTags_n, const int numIntervals, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_curveTags_(curveTags, curveTags + curveTags_n);
    result_api_ = gmsh::model::geo::addCompoundSpline(api_curveTags_, numIntervals, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddCompoundBSpline(int * curveTags, size_t curveTags_n, const int numIntervals, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_curveTags_(curveTags, curveTags + curveTags_n);
    result_api_ = gmsh::model::geo::addCompoundBSpline(api_curveTags_, numIntervals, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddCurveLoop(int * curveTags, size_t curveTags_n, const int tag, const int reorient, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_curveTags_(curveTags, curveTags + curveTags_n);
    result_api_ = gmsh::model::geo::addCurveLoop(api_curveTags_, tag, reorient);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelGeoAddCurveLoops(int * curveTags, size_t curveTags_n, int ** tags, size_t * tags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_curveTags_(curveTags, curveTags + curveTags_n);
    std::vector<int> api_tags_;
    gmsh::model::geo::addCurveLoops(api_curveTags_, api_tags_);
    vector2ptr(api_tags_, tags, tags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelGeoAddPlaneSurface(int * wireTags, size_t wireTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_wireTags_(wireTags, wireTags + wireTags_n);
    result_api_ = gmsh::model::geo::addPlaneSurface(api_wireTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddSurfaceFilling(int * wireTags, size_t wireTags_n, const int tag, const int sphereCenterTag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_wireTags_(wireTags, wireTags + wireTags_n);
    result_api_ = gmsh::model::geo::addSurfaceFilling(api_wireTags_, tag, sphereCenterTag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddSurfaceLoop(int * surfaceTags, size_t surfaceTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_surfaceTags_(surfaceTags, surfaceTags + surfaceTags_n);
    result_api_ = gmsh::model::geo::addSurfaceLoop(api_surfaceTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelGeoAddVolume(int * shellTags, size_t shellTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_shellTags_(shellTags, shellTags + shellTags_n);
    result_api_ = gmsh::model::geo::addVolume(api_shellTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelGeoExtrude(int * dimTags, size_t dimTags_n, const double dx, const double dy, const double dz, int ** outDimTags, size_t * outDimTags_n, int * numElements, size_t numElements_n, double * heights, size_t heights_n, const int recombine, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    std::vector<int> api_numElements_(numElements, numElements + numElements_n);
    std::vector<double> api_heights_(heights, heights + heights_n);
    gmsh::model::geo::extrude(api_dimTags_, dx, dy, dz, api_outDimTags_, api_numElements_, api_heights_, recombine);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoRevolve(int * dimTags, size_t dimTags_n, const double x, const double y, const double z, const double ax, const double ay, const double az, const double angle, int ** outDimTags, size_t * outDimTags_n, int * numElements, size_t numElements_n, double * heights, size_t heights_n, const int recombine, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    std::vector<int> api_numElements_(numElements, numElements + numElements_n);
    std::vector<double> api_heights_(heights, heights + heights_n);
    gmsh::model::geo::revolve(api_dimTags_, x, y, z, ax, ay, az, angle, api_outDimTags_, api_numElements_, api_heights_, recombine);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoTwist(int * dimTags, size_t dimTags_n, const double x, const double y, const double z, const double dx, const double dy, const double dz, const double ax, const double ay, const double az, const double angle, int ** outDimTags, size_t * outDimTags_n, int * numElements, size_t numElements_n, double * heights, size_t heights_n, const int recombine, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    std::vector<int> api_numElements_(numElements, numElements + numElements_n);
    std::vector<double> api_heights_(heights, heights + heights_n);
    gmsh::model::geo::twist(api_dimTags_, x, y, z, dx, dy, dz, ax, ay, az, angle, api_outDimTags_, api_numElements_, api_heights_, recombine);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoExtrudeBoundaryLayer(int * dimTags, size_t dimTags_n, int ** outDimTags, size_t * outDimTags_n, int * numElements, size_t numElements_n, double * heights, size_t heights_n, const int recombine, const int second, const int viewIndex, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    std::vector<int> api_numElements_(numElements, numElements + numElements_n);
    std::vector<double> api_heights_(heights, heights + heights_n);
    gmsh::model::geo::extrudeBoundaryLayer(api_dimTags_, api_outDimTags_, api_numElements_, api_heights_, recombine, second, viewIndex);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoTranslate(int * dimTags, size_t dimTags_n, const double dx, const double dy, const double dz, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::geo::translate(api_dimTags_, dx, dy, dz);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoRotate(int * dimTags, size_t dimTags_n, const double x, const double y, const double z, const double ax, const double ay, const double az, const double angle, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::geo::rotate(api_dimTags_, x, y, z, ax, ay, az, angle);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoDilate(int * dimTags, size_t dimTags_n, const double x, const double y, const double z, const double a, const double b, const double c, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::geo::dilate(api_dimTags_, x, y, z, a, b, c);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoMirror(int * dimTags, size_t dimTags_n, const double a, const double b, const double c, const double d, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::geo::mirror(api_dimTags_, a, b, c, d);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoSymmetrize(int * dimTags, size_t dimTags_n, const double a, const double b, const double c, const double d, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::geo::symmetrize(api_dimTags_, a, b, c, d);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoCopy(int * dimTags, size_t dimTags_n, int ** outDimTags, size_t * outDimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    gmsh::model::geo::copy(api_dimTags_, api_outDimTags_);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoRemove(int * dimTags, size_t dimTags_n, const int recursive, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::geo::remove(api_dimTags_, recursive);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoRemoveAllDuplicates(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::geo::removeAllDuplicates();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoSplitCurve(const int tag, int * pointTags, size_t pointTags_n, int ** curveTags, size_t * curveTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_pointTags_(pointTags, pointTags + pointTags_n);
    std::vector<int> api_curveTags_;
    gmsh::model::geo::splitCurve(tag, api_pointTags_, api_curveTags_);
    vector2ptr(api_curveTags_, curveTags, curveTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelGeoGetMaxTag(const int dim, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::geo::getMaxTag(dim);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelGeoSetMaxTag(const int dim, const int maxTag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::geo::setMaxTag(dim, maxTag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelGeoAddPhysicalGroup(const int dim, int * tags, size_t tags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_tags_(tags, tags + tags_n);
    result_api_ = gmsh::model::geo::addPhysicalGroup(dim, api_tags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelGeoRemovePhysicalGroups(int * dimTags, size_t dimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::geo::removePhysicalGroups(api_dimTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoSynchronize(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::geo::synchronize();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoMeshSetSize(int * dimTags, size_t dimTags_n, const double size, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::geo::mesh::setSize(api_dimTags_, size);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoMeshSetTransfiniteCurve(const int tag, const int nPoints, const char * meshType, const double coef, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::geo::mesh::setTransfiniteCurve(tag, nPoints, meshType, coef);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoMeshSetTransfiniteSurface(const int tag, const char * arrangement, int * cornerTags, size_t cornerTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_cornerTags_(cornerTags, cornerTags + cornerTags_n);
    gmsh::model::geo::mesh::setTransfiniteSurface(tag, arrangement, api_cornerTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoMeshSetTransfiniteVolume(const int tag, int * cornerTags, size_t cornerTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_cornerTags_(cornerTags, cornerTags + cornerTags_n);
    gmsh::model::geo::mesh::setTransfiniteVolume(tag, api_cornerTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoMeshSetRecombine(const int dim, const int tag, const double angle, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::geo::mesh::setRecombine(dim, tag, angle);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoMeshSetSmoothing(const int dim, const int tag, const int val, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::geo::mesh::setSmoothing(dim, tag, val);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoMeshSetReverse(const int dim, const int tag, const int val, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::geo::mesh::setReverse(dim, tag, val);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoMeshSetAlgorithm(const int dim, const int tag, const int val, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::geo::mesh::setAlgorithm(dim, tag, val);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelGeoMeshSetSizeFromBoundary(const int dim, const int tag, const int val, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::geo::mesh::setSizeFromBoundary(dim, tag, val);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelOccAddPoint(const double x, const double y, const double z, const double meshSize, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addPoint(x, y, z, meshSize, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddLine(const int startTag, const int endTag, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addLine(startTag, endTag, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddCircleArc(const int startTag, const int centerTag, const int endTag, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addCircleArc(startTag, centerTag, endTag, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddCircle(const double x, const double y, const double z, const double r, const int tag, const double angle1, const double angle2, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addCircle(x, y, z, r, tag, angle1, angle2);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddEllipseArc(const int startTag, const int centerTag, const int majorTag, const int endTag, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addEllipseArc(startTag, centerTag, majorTag, endTag, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddEllipse(const double x, const double y, const double z, const double r1, const double r2, const int tag, const double angle1, const double angle2, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addEllipse(x, y, z, r1, r2, tag, angle1, angle2);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddSpline(int * pointTags, size_t pointTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_pointTags_(pointTags, pointTags + pointTags_n);
    result_api_ = gmsh::model::occ::addSpline(api_pointTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddBSpline(int * pointTags, size_t pointTags_n, const int tag, const int degree, double * weights, size_t weights_n, double * knots, size_t knots_n, int * multiplicities, size_t multiplicities_n, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_pointTags_(pointTags, pointTags + pointTags_n);
    std::vector<double> api_weights_(weights, weights + weights_n);
    std::vector<double> api_knots_(knots, knots + knots_n);
    std::vector<int> api_multiplicities_(multiplicities, multiplicities + multiplicities_n);
    result_api_ = gmsh::model::occ::addBSpline(api_pointTags_, tag, degree, api_weights_, api_knots_, api_multiplicities_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddBezier(int * pointTags, size_t pointTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_pointTags_(pointTags, pointTags + pointTags_n);
    result_api_ = gmsh::model::occ::addBezier(api_pointTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddWire(int * curveTags, size_t curveTags_n, const int tag, const int checkClosed, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_curveTags_(curveTags, curveTags + curveTags_n);
    result_api_ = gmsh::model::occ::addWire(api_curveTags_, tag, checkClosed);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddCurveLoop(int * curveTags, size_t curveTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_curveTags_(curveTags, curveTags + curveTags_n);
    result_api_ = gmsh::model::occ::addCurveLoop(api_curveTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddRectangle(const double x, const double y, const double z, const double dx, const double dy, const int tag, const double roundedRadius, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addRectangle(x, y, z, dx, dy, tag, roundedRadius);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddDisk(const double xc, const double yc, const double zc, const double rx, const double ry, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addDisk(xc, yc, zc, rx, ry, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddPlaneSurface(int * wireTags, size_t wireTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_wireTags_(wireTags, wireTags + wireTags_n);
    result_api_ = gmsh::model::occ::addPlaneSurface(api_wireTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddSurfaceFilling(const int wireTag, const int tag, int * pointTags, size_t pointTags_n, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_pointTags_(pointTags, pointTags + pointTags_n);
    result_api_ = gmsh::model::occ::addSurfaceFilling(wireTag, tag, api_pointTags_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddBSplineFilling(const int wireTag, const int tag, const char * type, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addBSplineFilling(wireTag, tag, type);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddBezierFilling(const int wireTag, const int tag, const char * type, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addBezierFilling(wireTag, tag, type);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddBSplineSurface(int * pointTags, size_t pointTags_n, const int numPointsU, const int tag, const int degreeU, const int degreeV, double * weights, size_t weights_n, double * knotsU, size_t knotsU_n, double * knotsV, size_t knotsV_n, int * multiplicitiesU, size_t multiplicitiesU_n, int * multiplicitiesV, size_t multiplicitiesV_n, int * wireTags, size_t wireTags_n, const int wire3D, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_pointTags_(pointTags, pointTags + pointTags_n);
    std::vector<double> api_weights_(weights, weights + weights_n);
    std::vector<double> api_knotsU_(knotsU, knotsU + knotsU_n);
    std::vector<double> api_knotsV_(knotsV, knotsV + knotsV_n);
    std::vector<int> api_multiplicitiesU_(multiplicitiesU, multiplicitiesU + multiplicitiesU_n);
    std::vector<int> api_multiplicitiesV_(multiplicitiesV, multiplicitiesV + multiplicitiesV_n);
    std::vector<int> api_wireTags_(wireTags, wireTags + wireTags_n);
    result_api_ = gmsh::model::occ::addBSplineSurface(api_pointTags_, numPointsU, tag, degreeU, degreeV, api_weights_, api_knotsU_, api_knotsV_, api_multiplicitiesU_, api_multiplicitiesV_, api_wireTags_, wire3D);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddBezierSurface(int * pointTags, size_t pointTags_n, const int numPointsU, const int tag, int * wireTags, size_t wireTags_n, const int wire3D, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_pointTags_(pointTags, pointTags + pointTags_n);
    std::vector<int> api_wireTags_(wireTags, wireTags + wireTags_n);
    result_api_ = gmsh::model::occ::addBezierSurface(api_pointTags_, numPointsU, tag, api_wireTags_, wire3D);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddTrimmedSurface(const int surfaceTag, int * wireTags, size_t wireTags_n, const int wire3D, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_wireTags_(wireTags, wireTags + wireTags_n);
    result_api_ = gmsh::model::occ::addTrimmedSurface(surfaceTag, api_wireTags_, wire3D, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddSurfaceLoop(int * surfaceTags, size_t surfaceTags_n, const int tag, const int sewing, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_surfaceTags_(surfaceTags, surfaceTags + surfaceTags_n);
    result_api_ = gmsh::model::occ::addSurfaceLoop(api_surfaceTags_, tag, sewing);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddVolume(int * shellTags, size_t shellTags_n, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_shellTags_(shellTags, shellTags + shellTags_n);
    result_api_ = gmsh::model::occ::addVolume(api_shellTags_, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddSphere(const double xc, const double yc, const double zc, const double radius, const int tag, const double angle1, const double angle2, const double angle3, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addSphere(xc, yc, zc, radius, tag, angle1, angle2, angle3);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddBox(const double x, const double y, const double z, const double dx, const double dy, const double dz, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addBox(x, y, z, dx, dy, dz, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddCylinder(const double x, const double y, const double z, const double dx, const double dy, const double dz, const double r, const int tag, const double angle, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addCylinder(x, y, z, dx, dy, dz, r, tag, angle);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddCone(const double x, const double y, const double z, const double dx, const double dy, const double dz, const double r1, const double r2, const int tag, const double angle, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addCone(x, y, z, dx, dy, dz, r1, r2, tag, angle);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddWedge(const double x, const double y, const double z, const double dx, const double dy, const double dz, const int tag, const double ltx, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addWedge(x, y, z, dx, dy, dz, tag, ltx);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshModelOccAddTorus(const double x, const double y, const double z, const double r1, const double r2, const int tag, const double angle, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::addTorus(x, y, z, r1, r2, tag, angle);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelOccAddThruSections(int * wireTags, size_t wireTags_n, int ** outDimTags, size_t * outDimTags_n, const int tag, const int makeSolid, const int makeRuled, const int maxDegree, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_wireTags_(wireTags, wireTags + wireTags_n);
    gmsh::vectorpair api_outDimTags_;
    gmsh::model::occ::addThruSections(api_wireTags_, api_outDimTags_, tag, makeSolid, makeRuled, maxDegree);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccAddThickSolid(const int volumeTag, int * excludeSurfaceTags, size_t excludeSurfaceTags_n, const double offset, int ** outDimTags, size_t * outDimTags_n, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_excludeSurfaceTags_(excludeSurfaceTags, excludeSurfaceTags + excludeSurfaceTags_n);
    gmsh::vectorpair api_outDimTags_;
    gmsh::model::occ::addThickSolid(volumeTag, api_excludeSurfaceTags_, offset, api_outDimTags_, tag);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccExtrude(int * dimTags, size_t dimTags_n, const double dx, const double dy, const double dz, int ** outDimTags, size_t * outDimTags_n, int * numElements, size_t numElements_n, double * heights, size_t heights_n, const int recombine, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    std::vector<int> api_numElements_(numElements, numElements + numElements_n);
    std::vector<double> api_heights_(heights, heights + heights_n);
    gmsh::model::occ::extrude(api_dimTags_, dx, dy, dz, api_outDimTags_, api_numElements_, api_heights_, recombine);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccRevolve(int * dimTags, size_t dimTags_n, const double x, const double y, const double z, const double ax, const double ay, const double az, const double angle, int ** outDimTags, size_t * outDimTags_n, int * numElements, size_t numElements_n, double * heights, size_t heights_n, const int recombine, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    std::vector<int> api_numElements_(numElements, numElements + numElements_n);
    std::vector<double> api_heights_(heights, heights + heights_n);
    gmsh::model::occ::revolve(api_dimTags_, x, y, z, ax, ay, az, angle, api_outDimTags_, api_numElements_, api_heights_, recombine);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccAddPipe(int * dimTags, size_t dimTags_n, const int wireTag, int ** outDimTags, size_t * outDimTags_n, const char * trihedron, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    gmsh::model::occ::addPipe(api_dimTags_, wireTag, api_outDimTags_, trihedron);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccFillet(int * volumeTags, size_t volumeTags_n, int * curveTags, size_t curveTags_n, double * radii, size_t radii_n, int ** outDimTags, size_t * outDimTags_n, const int removeVolume, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_volumeTags_(volumeTags, volumeTags + volumeTags_n);
    std::vector<int> api_curveTags_(curveTags, curveTags + curveTags_n);
    std::vector<double> api_radii_(radii, radii + radii_n);
    gmsh::vectorpair api_outDimTags_;
    gmsh::model::occ::fillet(api_volumeTags_, api_curveTags_, api_radii_, api_outDimTags_, removeVolume);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccChamfer(int * volumeTags, size_t volumeTags_n, int * curveTags, size_t curveTags_n, int * surfaceTags, size_t surfaceTags_n, double * distances, size_t distances_n, int ** outDimTags, size_t * outDimTags_n, const int removeVolume, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_volumeTags_(volumeTags, volumeTags + volumeTags_n);
    std::vector<int> api_curveTags_(curveTags, curveTags + curveTags_n);
    std::vector<int> api_surfaceTags_(surfaceTags, surfaceTags + surfaceTags_n);
    std::vector<double> api_distances_(distances, distances + distances_n);
    gmsh::vectorpair api_outDimTags_;
    gmsh::model::occ::chamfer(api_volumeTags_, api_curveTags_, api_surfaceTags_, api_distances_, api_outDimTags_, removeVolume);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccFuse(int * objectDimTags, size_t objectDimTags_n, int * toolDimTags, size_t toolDimTags_n, int ** outDimTags, size_t * outDimTags_n, int *** outDimTagsMap, size_t ** outDimTagsMap_n, size_t *outDimTagsMap_nn, const int tag, const int removeObject, const int removeTool, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_objectDimTags_(objectDimTags_n/2);
    for(size_t i = 0; i < objectDimTags_n/2; ++i){
      api_objectDimTags_[i].first = objectDimTags[i * 2 + 0];
      api_objectDimTags_[i].second = objectDimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_toolDimTags_(toolDimTags_n/2);
    for(size_t i = 0; i < toolDimTags_n/2; ++i){
      api_toolDimTags_[i].first = toolDimTags[i * 2 + 0];
      api_toolDimTags_[i].second = toolDimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    std::vector<gmsh::vectorpair >api_outDimTagsMap_;
    gmsh::model::occ::fuse(api_objectDimTags_, api_toolDimTags_, api_outDimTags_, api_outDimTagsMap_, tag, removeObject, removeTool);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
    vectorvectorpair2intptrptr(api_outDimTagsMap_, outDimTagsMap, outDimTagsMap_n, outDimTagsMap_nn);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccIntersect(int * objectDimTags, size_t objectDimTags_n, int * toolDimTags, size_t toolDimTags_n, int ** outDimTags, size_t * outDimTags_n, int *** outDimTagsMap, size_t ** outDimTagsMap_n, size_t *outDimTagsMap_nn, const int tag, const int removeObject, const int removeTool, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_objectDimTags_(objectDimTags_n/2);
    for(size_t i = 0; i < objectDimTags_n/2; ++i){
      api_objectDimTags_[i].first = objectDimTags[i * 2 + 0];
      api_objectDimTags_[i].second = objectDimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_toolDimTags_(toolDimTags_n/2);
    for(size_t i = 0; i < toolDimTags_n/2; ++i){
      api_toolDimTags_[i].first = toolDimTags[i * 2 + 0];
      api_toolDimTags_[i].second = toolDimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    std::vector<gmsh::vectorpair >api_outDimTagsMap_;
    gmsh::model::occ::intersect(api_objectDimTags_, api_toolDimTags_, api_outDimTags_, api_outDimTagsMap_, tag, removeObject, removeTool);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
    vectorvectorpair2intptrptr(api_outDimTagsMap_, outDimTagsMap, outDimTagsMap_n, outDimTagsMap_nn);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccCut(int * objectDimTags, size_t objectDimTags_n, int * toolDimTags, size_t toolDimTags_n, int ** outDimTags, size_t * outDimTags_n, int *** outDimTagsMap, size_t ** outDimTagsMap_n, size_t *outDimTagsMap_nn, const int tag, const int removeObject, const int removeTool, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_objectDimTags_(objectDimTags_n/2);
    for(size_t i = 0; i < objectDimTags_n/2; ++i){
      api_objectDimTags_[i].first = objectDimTags[i * 2 + 0];
      api_objectDimTags_[i].second = objectDimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_toolDimTags_(toolDimTags_n/2);
    for(size_t i = 0; i < toolDimTags_n/2; ++i){
      api_toolDimTags_[i].first = toolDimTags[i * 2 + 0];
      api_toolDimTags_[i].second = toolDimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    std::vector<gmsh::vectorpair >api_outDimTagsMap_;
    gmsh::model::occ::cut(api_objectDimTags_, api_toolDimTags_, api_outDimTags_, api_outDimTagsMap_, tag, removeObject, removeTool);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
    vectorvectorpair2intptrptr(api_outDimTagsMap_, outDimTagsMap, outDimTagsMap_n, outDimTagsMap_nn);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccFragment(int * objectDimTags, size_t objectDimTags_n, int * toolDimTags, size_t toolDimTags_n, int ** outDimTags, size_t * outDimTags_n, int *** outDimTagsMap, size_t ** outDimTagsMap_n, size_t *outDimTagsMap_nn, const int tag, const int removeObject, const int removeTool, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_objectDimTags_(objectDimTags_n/2);
    for(size_t i = 0; i < objectDimTags_n/2; ++i){
      api_objectDimTags_[i].first = objectDimTags[i * 2 + 0];
      api_objectDimTags_[i].second = objectDimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_toolDimTags_(toolDimTags_n/2);
    for(size_t i = 0; i < toolDimTags_n/2; ++i){
      api_toolDimTags_[i].first = toolDimTags[i * 2 + 0];
      api_toolDimTags_[i].second = toolDimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    std::vector<gmsh::vectorpair >api_outDimTagsMap_;
    gmsh::model::occ::fragment(api_objectDimTags_, api_toolDimTags_, api_outDimTags_, api_outDimTagsMap_, tag, removeObject, removeTool);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
    vectorvectorpair2intptrptr(api_outDimTagsMap_, outDimTagsMap, outDimTagsMap_n, outDimTagsMap_nn);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccTranslate(int * dimTags, size_t dimTags_n, const double dx, const double dy, const double dz, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::occ::translate(api_dimTags_, dx, dy, dz);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccRotate(int * dimTags, size_t dimTags_n, const double x, const double y, const double z, const double ax, const double ay, const double az, const double angle, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::occ::rotate(api_dimTags_, x, y, z, ax, ay, az, angle);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccDilate(int * dimTags, size_t dimTags_n, const double x, const double y, const double z, const double a, const double b, const double c, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::occ::dilate(api_dimTags_, x, y, z, a, b, c);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccMirror(int * dimTags, size_t dimTags_n, const double a, const double b, const double c, const double d, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::occ::mirror(api_dimTags_, a, b, c, d);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccSymmetrize(int * dimTags, size_t dimTags_n, const double a, const double b, const double c, const double d, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::occ::symmetrize(api_dimTags_, a, b, c, d);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccAffineTransform(int * dimTags, size_t dimTags_n, double * a, size_t a_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    std::vector<double> api_a_(a, a + a_n);
    gmsh::model::occ::affineTransform(api_dimTags_, api_a_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccCopy(int * dimTags, size_t dimTags_n, int ** outDimTags, size_t * outDimTags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::vectorpair api_outDimTags_;
    gmsh::model::occ::copy(api_dimTags_, api_outDimTags_);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccRemove(int * dimTags, size_t dimTags_n, const int recursive, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::occ::remove(api_dimTags_, recursive);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccRemoveAllDuplicates(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::occ::removeAllDuplicates();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccHealShapes(int ** outDimTags, size_t * outDimTags_n, int * dimTags, size_t dimTags_n, const double tolerance, const int fixDegenerated, const int fixSmallEdges, const int fixSmallFaces, const int sewFaces, const int makeSolids, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_outDimTags_;
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::occ::healShapes(api_outDimTags_, api_dimTags_, tolerance, fixDegenerated, fixSmallEdges, fixSmallFaces, sewFaces, makeSolids);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccImportShapes(const char * fileName, int ** outDimTags, size_t * outDimTags_n, const int highestDimOnly, const char * format, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_outDimTags_;
    gmsh::model::occ::importShapes(fileName, api_outDimTags_, highestDimOnly, format);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccImportShapesNativePointer(const void * shape, int ** outDimTags, size_t * outDimTags_n, const int highestDimOnly, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_outDimTags_;
    gmsh::model::occ::importShapesNativePointer(shape, api_outDimTags_, highestDimOnly);
    vectorpair2intptr(api_outDimTags_, outDimTags, outDimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccGetEntities(int ** dimTags, size_t * dimTags_n, const int dim, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_;
    gmsh::model::occ::getEntities(api_dimTags_, dim);
    vectorpair2intptr(api_dimTags_, dimTags, dimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccGetEntitiesInBoundingBox(const double xmin, const double ymin, const double zmin, const double xmax, const double ymax, const double zmax, int ** tags, size_t * tags_n, const int dim, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_tags_;
    gmsh::model::occ::getEntitiesInBoundingBox(xmin, ymin, zmin, xmax, ymax, zmax, api_tags_, dim);
    vectorpair2intptr(api_tags_, tags, tags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccGetBoundingBox(const int dim, const int tag, double * xmin, double * ymin, double * zmin, double * xmax, double * ymax, double * zmax, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::occ::getBoundingBox(dim, tag, *xmin, *ymin, *zmin, *xmax, *ymax, *zmax);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccGetMass(const int dim, const int tag, double * mass, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::occ::getMass(dim, tag, *mass);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccGetCenterOfMass(const int dim, const int tag, double * x, double * y, double * z, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::occ::getCenterOfMass(dim, tag, *x, *y, *z);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccGetMatrixOfInertia(const int dim, const int tag, double ** mat, size_t * mat_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_mat_;
    gmsh::model::occ::getMatrixOfInertia(dim, tag, api_mat_);
    vector2ptr(api_mat_, mat, mat_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshModelOccGetMaxTag(const int dim, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::model::occ::getMaxTag(dim);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshModelOccSetMaxTag(const int dim, const int maxTag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::occ::setMaxTag(dim, maxTag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccSynchronize(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::model::occ::synchronize();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshModelOccMeshSetSize(int * dimTags, size_t dimTags_n, const double size, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_(dimTags_n/2);
    for(size_t i = 0; i < dimTags_n/2; ++i){
      api_dimTags_[i].first = dimTags[i * 2 + 0];
      api_dimTags_[i].second = dimTags[i * 2 + 1];
    }
    gmsh::model::occ::mesh::setSize(api_dimTags_, size);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshViewAdd(const char * name, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::view::add(name, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshViewRemove(const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::view::remove(tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshViewGetIndex(const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::view::getIndex(tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshViewGetTags(int ** tags, size_t * tags_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_tags_;
    gmsh::view::getTags(api_tags_);
    vector2ptr(api_tags_, tags, tags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewAddModelData(const int tag, const int step, const char * modelName, const char * dataType, size_t * tags, size_t tags_n, const double ** data, const size_t * data_n, size_t data_nn, const double time, const int numComponents, const int partition, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_tags_(tags, tags + tags_n);
    std::vector<std::vector<double> > api_data_(data_nn);
    for(size_t i = 0; i < data_nn; ++i)
      api_data_[i] = std::vector<double>(data[i], data[i] + data_n[i]);
    gmsh::view::addModelData(tag, step, modelName, dataType, api_tags_, api_data_, time, numComponents, partition);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewAddHomogeneousModelData(const int tag, const int step, const char * modelName, const char * dataType, size_t * tags, size_t tags_n, double * data, size_t data_n, const double time, const int numComponents, const int partition, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_tags_(tags, tags + tags_n);
    std::vector<double> api_data_(data, data + data_n);
    gmsh::view::addHomogeneousModelData(tag, step, modelName, dataType, api_tags_, api_data_, time, numComponents, partition);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewGetHomogeneousModelData(const int tag, const int step, char ** dataType, size_t ** tags, size_t * tags_n, double ** data, size_t * data_n, double * time, int * numComponents, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::string api_dataType_;
    std::vector<std::size_t> api_tags_;
    std::vector<double> api_data_;
    gmsh::view::getHomogeneousModelData(tag, step, api_dataType_, api_tags_, api_data_, *time, *numComponents);
    *dataType = strdup(api_dataType_.c_str());
    vector2ptr(api_tags_, tags, tags_n);
    vector2ptr(api_data_, data, data_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewAddListData(const int tag, const char * dataType, const int numEle, double * data, size_t data_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_data_(data, data + data_n);
    gmsh::view::addListData(tag, dataType, numEle, api_data_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewGetListData(const int tag, char *** dataType, size_t * dataType_n, int ** numElements, size_t * numElements_n, double *** data, size_t ** data_n, size_t *data_nn, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::string> api_dataType_;
    std::vector<int> api_numElements_;
    std::vector<std::vector<double> > api_data_;
    gmsh::view::getListData(tag, api_dataType_, api_numElements_, api_data_);
    vectorstring2charptrptr(api_dataType_, dataType, dataType_n);
    vector2ptr(api_numElements_, numElements, numElements_n);
    vectorvector2ptrptr(api_data_, data, data_n, data_nn);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewAddListDataString(const int tag, double * coord, size_t coord_n, char ** data, size_t data_n, char ** style, size_t style_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_coord_(coord, coord + coord_n);
    std::vector<std::string> api_data_(data, data + data_n);
    std::vector<std::string> api_style_(style, style + style_n);
    gmsh::view::addListDataString(tag, api_coord_, api_data_, api_style_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewGetListDataStrings(const int tag, const int dim, double ** coord, size_t * coord_n, char *** data, size_t * data_n, char *** style, size_t * style_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_coord_;
    std::vector<std::string> api_data_;
    std::vector<std::string> api_style_;
    gmsh::view::getListDataStrings(tag, dim, api_coord_, api_data_, api_style_);
    vector2ptr(api_coord_, coord, coord_n);
    vectorstring2charptrptr(api_data_, data, data_n);
    vectorstring2charptrptr(api_style_, style, style_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewSetInterpolationMatrices(const int tag, const char * type, const int d, double * coef, size_t coef_n, double * exp, size_t exp_n, const int dGeo, double * coefGeo, size_t coefGeo_n, double * expGeo, size_t expGeo_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_coef_(coef, coef + coef_n);
    std::vector<double> api_exp_(exp, exp + exp_n);
    std::vector<double> api_coefGeo_(coefGeo, coefGeo + coefGeo_n);
    std::vector<double> api_expGeo_(expGeo, expGeo + expGeo_n);
    gmsh::view::setInterpolationMatrices(tag, type, d, api_coef_, api_exp_, dGeo, api_coefGeo_, api_expGeo_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshViewAddAlias(const int refTag, const int copyOptions, const int tag, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::view::addAlias(refTag, copyOptions, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshViewCopyOptions(const int refTag, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::view::copyOptions(refTag, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewCombine(const char * what, const char * how, const int remove, const int copyOptions, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::view::combine(what, how, remove, copyOptions);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewProbe(const int tag, const double x, const double y, const double z, double ** value, size_t * value_n, const int step, const int numComp, const int gradient, const double tolerance, double * xElemCoord, size_t xElemCoord_n, double * yElemCoord, size_t yElemCoord_n, double * zElemCoord, size_t zElemCoord_n, const int dim, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_value_;
    std::vector<double> api_xElemCoord_(xElemCoord, xElemCoord + xElemCoord_n);
    std::vector<double> api_yElemCoord_(yElemCoord, yElemCoord + yElemCoord_n);
    std::vector<double> api_zElemCoord_(zElemCoord, zElemCoord + zElemCoord_n);
    gmsh::view::probe(tag, x, y, z, api_value_, step, numComp, gradient, tolerance, api_xElemCoord_, api_yElemCoord_, api_zElemCoord_, dim);
    vector2ptr(api_value_, value, value_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewWrite(const int tag, const char * fileName, const int append, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::view::write(tag, fileName, append);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshViewSetVisibilityPerWindow(const int tag, const int value, const int windowIndex, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::view::setVisibilityPerWindow(tag, value, windowIndex);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshPluginSetNumber(const char * name, const char * option, const double value, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::plugin::setNumber(name, option, value);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshPluginSetString(const char * name, const char * option, const char * value, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::plugin::setString(name, option, value);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshPluginRun(const char * name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::plugin::run(name);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshGraphicsDraw(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::graphics::draw();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkInitialize(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::initialize();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkWait(const double time, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::wait(time);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkUpdate(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::update();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkAwake(const char * action, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::awake(action);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkLock(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::lock();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkUnlock(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::unlock();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkRun(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::run();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API int gmshFltkIsAvailable(int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::fltk::isAvailable();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshFltkSelectEntities(int ** dimTags, size_t * dimTags_n, const int dim, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    gmsh::vectorpair api_dimTags_;
    result_api_ = gmsh::fltk::selectEntities(api_dimTags_, dim);
    vectorpair2intptr(api_dimTags_, dimTags, dimTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshFltkSelectElements(size_t ** elementTags, size_t * elementTags_n, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<std::size_t> api_elementTags_;
    result_api_ = gmsh::fltk::selectElements(api_elementTags_);
    vector2ptr(api_elementTags_, elementTags, elementTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API int gmshFltkSelectViews(int ** viewTags, size_t * viewTags_n, int * ierr)
{
  int result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    std::vector<int> api_viewTags_;
    result_api_ = gmsh::fltk::selectViews(api_viewTags_);
    vector2ptr(api_viewTags_, viewTags, viewTags_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshFltkSplitCurrentWindow(const char * how, const double ratio, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::splitCurrentWindow(how, ratio);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkSetCurrentWindow(const int windowIndex, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::setCurrentWindow(windowIndex);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkSetStatusMessage(const char * message, const int graphics, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::setStatusMessage(message, graphics);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkShowContextWindow(const int dim, const int tag, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::showContextWindow(dim, tag);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkOpenTreeItem(const char * name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::openTreeItem(name);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshFltkCloseTreeItem(const char * name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::fltk::closeTreeItem(name);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOnelabSet(const char * data, const char * format, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::onelab::set(data, format);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOnelabGet(char ** data, const char * name, const char * format, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::string api_data_;
    gmsh::onelab::get(api_data_, name, format);
    *data = strdup(api_data_.c_str());
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOnelabGetNames(char *** names, size_t * names_n, const char * search, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::string> api_names_;
    gmsh::onelab::getNames(api_names_, search);
    vectorstring2charptrptr(api_names_, names, names_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOnelabSetNumber(const char * name, double * value, size_t value_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_value_(value, value + value_n);
    gmsh::onelab::setNumber(name, api_value_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOnelabSetString(const char * name, char ** value, size_t value_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::string> api_value_(value, value + value_n);
    gmsh::onelab::setString(name, api_value_);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOnelabGetNumber(const char * name, double ** value, size_t * value_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<double> api_value_;
    gmsh::onelab::getNumber(name, api_value_);
    vector2ptr(api_value_, value, value_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOnelabGetString(const char * name, char *** value, size_t * value_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::string> api_value_;
    gmsh::onelab::getString(name, api_value_);
    vectorstring2charptrptr(api_value_, value, value_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOnelabClear(const char * name, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::onelab::clear(name);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshOnelabRun(const char * name, const char * command, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::onelab::run(name, command);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshLoggerWrite(const char * message, const char * level, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::logger::write(message, level);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshLoggerStart(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::logger::start();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshLoggerGet(char *** log, size_t * log_n, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::vector<std::string> api_log_;
    gmsh::logger::get(api_log_);
    vectorstring2charptrptr(api_log_, log, log_n);
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API void gmshLoggerStop(int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    gmsh::logger::stop();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

GMSH_API double gmshLoggerGetWallTime(int * ierr)
{
  double result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::logger::getWallTime();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API double gmshLoggerGetCpuTime(int * ierr)
{
  double result_api_ = 0;
  if(ierr) *ierr = 0;
  try {
    result_api_ = gmsh::logger::getCpuTime();
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
  return result_api_;
}

GMSH_API void gmshLoggerGetLastError(char ** error, int * ierr)
{
  if(ierr) *ierr = 0;
  try {
    std::string api_error_;
    gmsh::logger::getLastError(api_error_);
    *error = strdup(api_error_.c_str());
  }
  catch(...){
    if(ierr) *ierr = 1;
  }
}

