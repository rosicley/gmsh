// Gmsh - Copyright (C) 1997-2019 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// issues on https://gitlab.onelab.info/gmsh/gmsh/issues.

#ifndef CROSS_FIELDS_H
#define CROSS_FIELDS_H

#include <string>
class GModel;

int computeCrossField       (GModel *, std::vector<int> &tags);
int computeQuadDecomposition(GModel *, std::vector<int> &tags);

#endif
