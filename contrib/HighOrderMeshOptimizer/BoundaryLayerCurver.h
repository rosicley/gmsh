// Copyright (C) 2017 ULg-UCL
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, and/or sell copies of the
// Software, and to permit persons to whom the Software is furnished
// to do so, provided that the above copyright notice(s) and this
// permission notice appear in all copies of the Software and that
// both the above copyright notice(s) and this permission notice
// appear in supporting documentation.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR
// ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY
// DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
// WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
// ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
//
// Please report all bugs and problems to the public mailing list
// <gmsh@onelab.info>.
//
// Contributors: Amaury Johnen

#ifndef _BOUNDARYLAYERCURVER_H_
#define _BOUNDARYLAYERCURVER_H_

//#include <map>
#include <list>

#include "Medge.h"
#include "MFace.h"
#include "fullMatrix.h"

class MElement;
class GEntity;
class MVertex;

typedef std::vector<std::pair<MElement*, std::vector<MElement*>>> VecPairMElemVecMElem;

void curve2DBoundaryLayer(VecPairMElemVecMElem &bndEl2column, SVector3 normal);
//void curve2DColumn(MElement *bottomEdge, std::vector<MElement*> &column);

void curve3DBoundaryLayer(VecPairMElemVecMElem &bndEl2column);

#endif
