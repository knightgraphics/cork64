// +-------------------------------------------------------------------------
// | cork.h
// | 
// | Author: Gilbert Bernstein
// +-------------------------------------------------------------------------
// | COPYRIGHT:
// |    Copyright Gilbert Bernstein 2013
// |    See the included COPYRIGHT file for further details.
// |    
// |    This file is part of the Cork library.
// |
// |    Cork is free software: you can redistribute it and/or modify
// |    it under the terms of the GNU Lesser General Public License as
// |    published by the Free Software Foundation, either version 3 of
// |    the License, or (at your option) any later version.
// |
// |    Cork is distributed in the hope that it will be useful,
// |    but WITHOUT ANY WARRANTY; without even the implied warranty of
// |    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// |    GNU Lesser General Public License for more details.
// |
// |    You should have received a copy 
// |    of the GNU Lesser General Public License
// |    along with Cork.  If not, see <http://www.gnu.org/licenses/>.
// +-------------------------------------------------------------------------
#pragma once

#if 0 //def WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#ifndef uint
typedef unsigned int uint;
#endif

// if a mesh is taken as input, the client must manage the memory
// if a mesh is given as output, please use the provided
// function to free the allocated memory.
DLLEXPORT struct CorkTriMesh
{
    uint    n_triangles;
    uint    n_vertices;
    uint    *triangles;

    // Originally this was float, but we use double
    double   *vertices;
};

DLLEXPORT void freeCorkTriMesh(CorkTriMesh *mesh);

// the inputs to Boolean operations must be "solid":
//  -   closed (aka. watertight; see comment at bottom)
//  -   non-self-intersecting
// additionally, inputs should use a counter-clockwise convention
// for triangle facing.  If the triangles are presented in clockwise
// orientation, the object is interpreted as its unbounded complement

// This function will test whether or not a mesh is solid
DLLEXPORT bool isSolid(CorkTriMesh mesh);

// Boolean operations follow
// result = A U B
DLLEXPORT void computeUnion(CorkTriMesh in0, CorkTriMesh in1, CorkTriMesh *out);

// result = A - B
DLLEXPORT void computeDifference(CorkTriMesh in0, CorkTriMesh in1, CorkTriMesh *out);

// result = A ^ B
DLLEXPORT void computeIntersection(CorkTriMesh in0, CorkTriMesh in1, CorkTriMesh *out);

// result = A XOR B
DLLEXPORT void computeSymmetricDifference(
                        CorkTriMesh in0, CorkTriMesh in1, CorkTriMesh *out);

// Not a Boolean operation, but related:
//  No portion of either surface is deleted.  However, the
//  curve of intersection between the two surfaces is made explicit,
//  such that the two surfaces are now connected.
DLLEXPORT void resolveIntersections(CorkTriMesh in0, CorkTriMesh in1, CorkTriMesh *out);

